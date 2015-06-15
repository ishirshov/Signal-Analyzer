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

#ifndef IPP_WAVELET_FWD_H
#define IPP_WAVELET_FWD_H

#include <ipps.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>

inline void ipp_wavelet_fwd(const Ipp32f *src, Ipp32f *dst_low, Ipp32f *dst_high, int dst_len, IppsWTFwdState_32f *state)
{
    IppStatus status = ippsWTFwd_32f(src, dst_low, dst_high, dst_len, state);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

inline void ipp_wavelet_fwd(const Ipp8u *src, Ipp32f *dst_low, Ipp32f *dst_high, int dst_len, IppsWTFwdState_8u32f *state)
{
    IppStatus status = ippsWTFwd_8u32f(src, dst_low, dst_high, dst_len, state);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

inline void ipp_wavelet_fwd(const Ipp16s *src, Ipp32f *dst_low, Ipp32f *dst_high, int dst_len, IppsWTFwdState_16s32f *state)
{
    IppStatus status = ippsWTFwd_16s32f(src, dst_low, dst_high, dst_len, state);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

inline void ipp_wavelet_fwd(const Ipp16u *src, Ipp32f *dst_low, Ipp32f *dst_high, int dst_len, IppsWTFwdState_16u32f *state)
{
    IppStatus status = ippsWTFwd_16u32f(src, dst_low, dst_high, dst_len, state);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_WAVELET_FWD_H
