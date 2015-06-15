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

#ifndef IPP_RESAMPL_H
#define IPP_RESAMPL_H

#include "../ipp_ptr.h"
#include "../ipp_convert.h"

///
/// \brief ispwr_of_2   Checks the number X to the power of two.
/// \param x            Checked values.
/// \return             True if X is power of two or false othrewise.
///
inline bool ispwr_of_2(unsigned long x)
{
    return ((x != 0) && ((x & (x-1)) == 0));
}

///
/// \brief ipp_fft_resampl_rellc    Resampling function based on Fast
///                                 Fourier Transform algorithm.
///                                 (Not optimized function).
///
/// \param pSrc                     Pointer of input signal data in real format.
/// \param srcLen                   Sampling frequency of input signal.
/// \param pDst                     Pointer of output signal data int real format.
/// \param dstLen                   Sampling frequency of output signal.
///
void ipp_fft_resampl_rellc(const Ipp64f *pSrc, Ipp32s srcLen, Ipp64f *pDst, Ipp32s dstLen);

inline void ipp_fft_resampl_rellc(const Ipp32f *pSrc, int srcLen, Ipp32f *pDst, int dstLen)
{
    if(!pSrc || !pDst) throw std::runtime_error("Pointers cannot be null.");
    if(srcLen < 1 || dstLen < 1) throw std::runtime_error("The lengths must be positive.");

    ipp_ptr<Ipp64f> tmp_src(ipp_malloc<Ipp64f>(srcLen));
    ipp_ptr<Ipp64f> tmp_dst(ipp_malloc<Ipp64f>(dstLen));

    Ipp64f *_src_64f = tmp_src.get();
    Ipp64f *_dst_64f = tmp_dst.get();

    ipp_convert(pSrc, _src_64f, srcLen);
    ipp_fft_resampl_rellc(_src_64f, srcLen, _dst_64f, dstLen);
    ipp_convert(_dst_64f, pDst, dstLen);
}

///
/// \brief ipp_fft_resampl_stat     Reimplementation basic resampling function
///                                 based on Fast Fourier Transform algorithm.
///                                 (All internal variables are static and changed
///                                 when srcLen or dstLen will be changed).
///
/// \param pSrc                     Pointer of input signal data in real format.
/// \param srcLen                   Sampling frequency of input signal.
/// \param pDst                     Pointer of output signal data int real format.
/// \param dstLen                   Sampling frequency of output signal.
///
void ipp_fft_resampl_stat(const Ipp64f *pSrc, int srcLen, Ipp64f *pDst, int dstLen);

inline void ipp_fft_resampl_stat(const Ipp32f *pSrc, int srcLen, Ipp32f *pDst, int dstLen)
{
    if(!pSrc || !pDst) throw std::runtime_error("Pointers cannot be null.");
    if(srcLen < 1 || dstLen < 1) throw std::runtime_error("The lengths must be positive.");

    ipp_ptr<Ipp64f> tmp_src(ipp_malloc<Ipp64f>(srcLen));
    ipp_ptr<Ipp64f> tmp_dst(ipp_malloc<Ipp64f>(dstLen));

    Ipp64f *_src_64f = tmp_src.get();
    Ipp64f *_dst_64f = tmp_dst.get();

    ipp_convert(pSrc, _src_64f, srcLen);
    ipp_fft_resampl_stat(_src_64f, srcLen, _dst_64f, dstLen);
    ipp_convert(_dst_64f, pDst, dstLen);
}

#endif // IPP_RESAMPL_H
