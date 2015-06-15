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

#ifndef IPP_WAVELET_INIT_FWD_H
#define IPP_WAVELET_INIT_FWD_H

#include "../ipp_ptr.h"

inline void ipp_wavelet_init_fwd(ipp_ptr<IppsWTFwdState_32f> &state,
                                 const Ipp32f* taps_low, int len_low, int offset_low,
                                 const Ipp32f* taps_high, int len_high, int offset_high)
{
    IppsWTFwdState_32f *p_state = 0;

    IppStatus status = ippsWTFwdInitAlloc_32f(&p_state, taps_low, len_low, offset_low, taps_high, len_high, offset_high);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

    state.reset(p_state);
}

inline void ipp_wavelet_init_fwd(ipp_ptr<IppsWTFwdState_8u32f> &state,
                                 const Ipp32f* taps_low, int len_low, int offset_low,
                                 const Ipp32f* taps_high, int len_high, int offset_high)
{
    IppsWTFwdState_8u32f *p_state = 0;

    IppStatus status = ippsWTFwdInitAlloc_8u32f(&p_state, taps_low, len_low, offset_low, taps_high, len_high, offset_high);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

    state.reset(p_state);
}

inline void ipp_wavelet_init_fwd(ipp_ptr<IppsWTFwdState_16s32f> &state,
                                 const Ipp32f* taps_low, int len_low, int offset_low,
                                 const Ipp32f* taps_high, int len_high, int offset_high)
{
    IppsWTFwdState_16s32f *p_state = 0;

    IppStatus status = ippsWTFwdInitAlloc_16s32f(&p_state, taps_low, len_low, offset_low, taps_high, len_high, offset_high);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

    state.reset(p_state);
}

inline void ipp_wavelet_init_fwd(ipp_ptr<IppsWTFwdState_16u32f> &state,
                                 const Ipp32f* taps_low, int len_low, int offset_low,
                                 const Ipp32f* taps_high, int len_high, int offset_high)
{
    IppsWTFwdState_16u32f *p_state = 0;

    IppStatus status = ippsWTFwdInitAlloc_16u32f(&p_state, taps_low, len_low, offset_low, taps_high, len_high, offset_high);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

    state.reset(p_state);
}

#endif // IPP_WAVELET_INIT_FWD_H
