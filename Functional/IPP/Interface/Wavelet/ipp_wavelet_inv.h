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

#ifndef IPP_WAVELET_INV_H
#define IPP_WAVELET_INV_H

#include <ipps.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>

inline void ipp_wavelet_inv(const Ipp32f *src_low, const Ipp32f *src_high, int src_len, Ipp32f *dst, IppsWTInvState_32f *state)
{
    IppStatus status = ippsWTInv_32f(src_low, src_high, src_len, dst, state);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

inline void ipp_wavelet_inv(const Ipp32f *src_low, const Ipp32f *src_high, int src_len, Ipp8u *dst, IppsWTInvState_32f8u *state)
{
    IppStatus status = ippsWTInv_32f8u(src_low, src_high, src_len, dst, state);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

inline void ipp_wavelet_inv(const Ipp32f *src_low, const Ipp32f *src_high, int src_len, Ipp16s *dst, IppsWTInvState_32f16s *state)
{
    IppStatus status = ippsWTInv_32f16s(src_low, src_high, src_len, dst, state);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

inline void ipp_wavelet_inv(const Ipp32f *src_low, const Ipp32f *src_high, int src_len, Ipp16u *dst, IppsWTInvState_32f16u *state)
{
    IppStatus status = ippsWTInv_32f16u(src_low, src_high, src_len, dst, state);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_WAVELET_INV_H
