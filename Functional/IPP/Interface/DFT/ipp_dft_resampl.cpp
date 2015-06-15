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

#include "ipp_dft_resampl.h"
#include "ipp_dft_fwd_r2css.h"
#include "ipp_dft_inv_ccs2r.h"
#include "ipp_dft_init.h"
#include "../ipp_div_c.h"
#include "../ipp_copy.h"

void ipp_dft_resampl_rellc(const Ipp64f *_src, Ipp32s src_len, Ipp64f *_dst, Ipp32s dst_len)
{
    if(!_src || !_dst) throw std::runtime_error("Pointers cannot be null.");
    if(src_len < 1 || dst_len < 1) throw std::runtime_error("The lengths must be positive.");

    // CCS with odd length have N + 1 elements and N + 2 if even
    const int src_ccs_len = (src_len % 2 == 0) ? (src_len + 2) : (src_len + 1);
    const int dst_ccs_len = (dst_len % 2 == 0) ? (dst_len + 2) : (dst_len + 1);

    // Create arrays for input and output CCS data
    ipp_ptr<Ipp64f> input_ccs(ippsMalloc_64f(src_ccs_len));
    ipp_ptr<Ipp64f> output_ccs(ippsMalloc_64f(dst_ccs_len));
    Ipp64f *_ccs_in = input_ccs.get();
    Ipp64f *_ccs_out = output_ccs.get();

    // Zero-padding operation
    ipp_zero(_ccs_in, src_ccs_len);
    ipp_zero(_ccs_out, dst_ccs_len);

    ipp_ptr<IppsDFTSpec_R_64f> spec;
    ipp_ptr<Ipp8u> buffer;

    // Initialization DFT special structure for FWD
    ipp_dft_init(spec, buffer, src_len);

    ipp_dft_fwd_r2ccs(_src, _ccs_in, spec.get(), buffer.get());
    ipp_copy(_ccs_in, _ccs_out, src_ccs_len);

    // Initialization DFT special structure for INV
    ipp_dft_init(spec, buffer, dst_len);

    // Transform resampling signal from CCS to Real
    ipp_dft_inv_ccs2r(_ccs_out, _dst, spec.get(), buffer.get());
    ipp_div_c(_dst, Ipp64f(src_len), _dst, dst_len);
}

void ipp_dft_resampl_stat(const Ipp64f *_src, int src_len, Ipp64f *_dst, int dst_len)
{
    if(!_src || !_dst) throw std::runtime_error("Pointers cannot be null.");
    if(src_len < 1 || dst_len < 1) throw std::runtime_error("The lengths must be positive.");

    static int last_src_len = 0, last_dst_len = 0;
    static int src_ccs_len = 0, dst_ccs_len = 0;

    static ipp_ptr<IppsDFTSpec_R_64f> src_spec, dst_spec;
    static ipp_ptr<Ipp8u> src_buffer, dst_buffer;
    static ipp_ptr<Ipp64f> src_ccs, dst_ccs;

    if(last_src_len != src_len) {
        src_ccs_len = (src_len % 2 == 0) ? (src_len + 2) : (src_len + 1);
        src_ccs.reset(ipp_malloc<Ipp64f>(src_ccs_len));

        ipp_dft_init(src_spec, src_buffer, src_len);
        last_src_len = src_len;
    }
    if(last_dst_len != dst_len) {
        dst_ccs_len = (dst_len % 2 == 0) ? (dst_len + 2) : (dst_len + 1);
        dst_ccs.reset(ipp_malloc<Ipp64f>(dst_ccs_len));

        ipp_dft_init(dst_spec, dst_buffer, dst_len);
        last_dst_len = dst_len;
    }

    Ipp64f *_ccs_in = src_ccs.get();
    Ipp64f *_ccs_out = dst_ccs.get();

    ipp_zero(_ccs_in, src_ccs_len);
    ipp_zero(_ccs_out, dst_ccs_len);

    ipp_dft_fwd_r2ccs(_src, _ccs_in, src_spec.get(), src_buffer.get());
    ipp_copy(_ccs_in, _ccs_out, src_ccs_len);

    ipp_dft_inv_ccs2r(_ccs_out, _dst, dst_spec.get(), dst_buffer.get());
    ipp_div_c(_dst, Ipp64f(src_len), _dst, dst_len);
}
