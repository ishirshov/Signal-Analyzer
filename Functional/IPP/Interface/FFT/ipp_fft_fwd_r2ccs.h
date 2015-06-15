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

#ifndef IPP_FFT_FWD_R2CCS_H
#define IPP_FFT_FWD_R2CCS_H

#include <ipps.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>

/// \brief ipp_fft_fwd_r2ccs    Provides a specialize interface for
///                             working with the forward FFT function.
///
/// \param pSrc                 Inputs signal in real format.
/// \param pDst                 Destination pointer for spectrum in CCS format.
/// \param pSpec                Special structure for FFT function.
/// \param pBuffer              External buffer.
///
inline void ipp_fft_fwd_r2ccs(const Ipp64f *pSrc, Ipp64f *pDst,
                              const IppsFFTSpec_R_64f *pSpec, Ipp8u *pBuffer)
{
    IppStatus message = ippsFFTFwd_RToCCS_64f(pSrc, pDst, pSpec, pBuffer);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));
}

inline void ipp_fft_fwd_r2ccs(const Ipp32f *pSrc, Ipp32f *pDst,
                              const IppsFFTSpec_R_32f *pSpec, Ipp8u *pBuffer)
{
    IppStatus message = ippsFFTFwd_RToCCS_32f(pSrc, pDst, pSpec, pBuffer);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));
}

#endif // IPP_FFT_FWD_R2CCS_H
