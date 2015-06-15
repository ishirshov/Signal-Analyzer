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

#ifndef IPP_WAVELET_INV_HAAR_H
#define IPP_WAVELET_INV_HAAR_H

#include <ipps.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>

inline void ipp_wavelet_inv_haar(const Ipp16s *src_low, const Ipp16s *src_high, Ipp16s *dst, int len)
{
    IppStatus status = ippsWTHaarInv_16s(src_low, src_high, dst, len);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

inline void ipp_wavelet_inv_haar(const Ipp32f *src_low, const Ipp32f *src_high, Ipp32f *dst, int len)
{
    IppStatus status = ippsWTHaarInv_32f(src_low, src_high, dst, len);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

inline void ipp_wavelet_inv_haar(const Ipp64f *src_low, const Ipp64f *src_high, Ipp64f *dst, int len)
{
    IppStatus status = ippsWTHaarInv_64f(src_low, src_high, dst, len);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_WAVELET_INV_HAAR_H
