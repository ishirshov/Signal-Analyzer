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

#include "ipp_signal_parameters.h"
#include "FFT/ipp_fft_fwd_r2ccs.h"
#include "FFT/ipp_fft_init.h"
#include "ipp_convert.h"
#include "ipp_ptr.h"
#include "../Additionals/vars.h"
#include <cmath>

Ipp64f* ipp_find_parameters(const Ipp64fc *pSrc, const Ipp32s length, const Ipp32s samplFreq)
{
    if(!pSrc) throw std::invalid_argument("Null pointer are not allowed.");
    if(!length) throw std::invalid_argument("Length must be a positive.");

    // Parameter search in range [0:(N/2)] for even
    // and [0:(N-1)/2] for odd N.
    Ipp64f max_value = 0;
    Ipp32s max_index = 0;
    Ipp32s size = (!(length%2))?(length/2):((length+1)/2);

    ipp_ptr<Ipp64f> param(ippsMalloc_64f(3));
    ipp_ptr<Ipp64f> magnitude(ippsMalloc_64f(size));
    Ipp64f *pMag = magnitude.get();

    // Find peak of each FFT bin.
    IppStatus message = ippsMagnitude_64fc(pSrc, pMag, size);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    message = ippsMaxIndx_64f(pMag, size, &max_value, &max_index);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    // Get amplitude in levels.
    param[1] = max_value * (2.0/Ipp64f(size));

    // Convert levels to amplitude.
    param[2] = c_B * log10(param[1]);
    std::modf(param[2], &param[2]);

    // Compute frequency (index * samplingFrequency / N).
    param[0] = (max_index * (samplFreq/(length)));

    return param.release();
}

Ipp64f* ipp_real_to_ccs(const Ipp16s *pSrc, const Ipp32s length, const Ipp32s samplFreq)
{
    const int ccs_length = (length % 2 == 0) ? (length + 2) : (length + 1);

    ipp_ptr<Ipp64f> Dst(ippsMalloc_64f(ccs_length));
    Ipp64f* pDst = Dst.get();
    ipp_convert(pSrc, pDst, length);

    ipp_ptr<IppsFFTSpec_R_64f> pFFTSpec;
    ipp_ptr<Ipp8u> pBuffer;

    ipp_fft_init(pFFTSpec, pBuffer, length);
    ipp_fft_fwd_r2ccs(pDst, pDst, pFFTSpec.get(), pBuffer.get());

    return ipp_find_parameters((Ipp64fc*)pDst, ccs_length/2, samplFreq);
}

Ipp64f* ipp_real_to_ccs(const Ipp64f *pSrc, const Ipp32s length, const Ipp32s samplFreq)
{
    const int ccs_length = (length % 2 == 0) ? (length + 2) : (length + 1);

    ipp_ptr<Ipp64f> Dst(ippsMalloc_64f(ccs_length));
    Ipp64f* pDst = Dst.get();

    ipp_ptr<IppsFFTSpec_R_64f> pFFTSpec;
    ipp_ptr<Ipp8u> pBuffer;

    ipp_fft_init(pFFTSpec, pBuffer, length);
    ipp_fft_fwd_r2ccs(pDst, pDst, pFFTSpec.get(), pBuffer.get());

    return ipp_find_parameters((Ipp64fc*)pDst, ccs_length/2, samplFreq);
}
