/*
* Please visit https://bitbucket.org/ishirshov/signal-analyzer for more information.
*
* Copyright (c) 2015 Scan Engineering Telecom, CJSC.
* Written by Ildar Shirshov <ildar-shirshov@ya.ru>
*
* This file is part of Signal Analyzer.
*
* Signal Analyzer is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Signal Analyzer is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with Signal Analyzer.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ipp_phase_offset.h"
#include "FFT/ipp_fft_fwd_r2ccs.h"
#include "ipp_norm_biased.h"
#include "ipp_phase_angle.h"
#include "FFT/ipp_fft_init.h"

Ipp64f ipp_phase_offset_rellc(const Ipp64f *_orig, Ipp32s orig_len, const Ipp64f *_src, Ipp32s src_len)
{
    if(!_orig || !_src) throw std::runtime_error("Pointers cannot be null.");
    if(orig_len < 1) throw std::runtime_error("The lengths must be positive.");
    if(orig_len > src_len) throw std::runtime_error("Length of source signal must be greater than original.");

    int orig_ccs_len = (orig_len % 2 == 0) ? (orig_len + 2) : (orig_len + 1);

    ipp_ptr<Ipp64f> orig_ccs(ipp_malloc<Ipp64f>(orig_ccs_len)); // Need to CCS format data.
    ipp_ptr<Ipp64f> src_ccs(ipp_malloc<Ipp64f>(orig_ccs_len));
    Ipp64f *_ccs_orig = orig_ccs.get(), *_ccs_src = src_ccs.get();

    ipp_norm_biased(_orig, _ccs_orig, orig_len);
    ipp_norm_biased(_src, _ccs_src, orig_len);

    ipp_ptr<IppsFFTSpec_R_64f> fft_spec;
    ipp_ptr<Ipp8u> buffer;

    ipp_fft_init(fft_spec, buffer, orig_len);

    IppsFFTSpec_R_64f *_spec = fft_spec.get();
    Ipp8u *_buffer = buffer.get();

    ipp_fft_fwd_r2ccs(_ccs_orig, _ccs_orig, _spec, _buffer);
    ipp_fft_fwd_r2ccs(_ccs_src, _ccs_src, _spec, _buffer);

    // Determine the phase difference at
    // the maximum point.
    Ipp64f phs_ccs_orig = ipp_phase_angle((Ipp64fc*)_ccs_orig, orig_ccs_len/2);
    Ipp64f phs_ccs_src = ipp_phase_angle((Ipp64fc*)_ccs_src, orig_ccs_len/2);
    Ipp64f t_estimate1 = phs_ccs_src - phs_ccs_orig;

    if(t_estimate1 == 0) return t_estimate1;

    ipp_norm_biased(_src + 1, _ccs_src, orig_len);
    ipp_fft_fwd_r2ccs(_ccs_src, _ccs_src, _spec, _buffer);

    // Again determine the phase difference.
    phs_ccs_src = ipp_phase_angle((Ipp64fc*)_ccs_src, orig_ccs_len/2);
    Ipp64f t_estimate2 = phs_ccs_src - phs_ccs_orig;

    return lag_detect(t_estimate1, t_estimate2);
}

Ipp64f ipp_phase_offset_stat(const Ipp64f *_orig, Ipp32s orig_len, const Ipp64f *_src, Ipp32s src_len)
{
    if(!_orig || !_src) throw std::runtime_error("Pointers cannot be null.");
    if(orig_len < 1) throw std::runtime_error("The lengths must be positive.");
    if(orig_len > src_len) throw std::runtime_error("Length of source signal must be greater than original.");

    static int last_orig_len = 0;
    static int orig_ccs_len = 0;

    static ipp_ptr<IppsFFTSpec_R_64f> fft_spec;
    static ipp_ptr<Ipp8u> buffer;
    static ipp_ptr<Ipp64f> orig_ccs, src_ccs;

    if(last_orig_len != orig_len) {
        orig_ccs_len = (orig_len % 2 == 0) ? (orig_len + 2) : (orig_len + 1);
        orig_ccs.reset(ipp_malloc<Ipp64f>(orig_ccs_len));
        src_ccs.reset(ipp_malloc<Ipp64f>(orig_ccs_len));

        ipp_fft_init(fft_spec, buffer, orig_len);
        last_orig_len = orig_len;
    }

    Ipp64f *_ccs_orig = orig_ccs.get();
    Ipp64f *_ccs_src = src_ccs.get();

    ipp_norm_biased(_orig, _ccs_orig, orig_len);
    ipp_norm_biased(_src, _ccs_src, orig_len);

    IppsFFTSpec_R_64f *_spec = fft_spec.get();
    Ipp8u *_buffer = buffer.get();

    ipp_fft_fwd_r2ccs(_ccs_orig, _ccs_orig, _spec, _buffer);
    ipp_fft_fwd_r2ccs(_ccs_src, _ccs_src, _spec, _buffer);

    // Determine the phase difference at
    // the maximum point.
    Ipp64f phs_ccs_orig = ipp_phase_angle((Ipp64fc*)_ccs_orig, orig_ccs_len/2);
    Ipp64f phs_ccs_src = ipp_phase_angle((Ipp64fc*)_ccs_src, orig_ccs_len/2);
    Ipp64f t_estimate1 = phs_ccs_src - phs_ccs_orig;

    if(t_estimate1 == 0) return t_estimate1;

    ipp_norm_biased(_src + 1, _ccs_src, orig_len);
    ipp_fft_fwd_r2ccs(_ccs_src, _ccs_src, _spec, _buffer);

    // Again determine the phase difference.
    phs_ccs_src = ipp_phase_angle((Ipp64fc*)_ccs_src, orig_ccs_len/2);
    Ipp64f t_estimate2 = phs_ccs_src - phs_ccs_orig;

    return lag_detect(t_estimate1, t_estimate2);
}
