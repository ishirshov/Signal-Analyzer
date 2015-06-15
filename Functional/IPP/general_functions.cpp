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

#include "general_functions.h"
#include "Interpolation/interpolation.h"

//---------------------------------- Sequential functions --------------------------------//

void interpolate_64f(const Ipp64f *pSrc, Ipp32s srcLen, Ipp64f *pDst, Ipp32s dstLen)
{
    if(!pSrc || !pDst)
        throw std::invalid_argument("Null pointer are not allowed.");
    if(srcLen <= 0 || dstLen <= 0)
        throw std::invalid_argument("Image length must be positive.");
    if(dstLen < (srcLen*2))
        throw std::invalid_argument("Destination length must greater then source length.");

    ipp_ptr<Ipp64f> src(ippsMalloc_64f(srcLen*2));
    ipp_ptr<Ipp64f> dst(ippsMalloc_64f(dstLen*2));

    IppiSize src_sz = { srcLen, 2 }, dst_sz = { dstLen, 2 };
    Ipp32s src_step = srcLen*sizeof(Ipp64f);
    Ipp32s dst_step = dstLen*sizeof(Ipp64f);
    Ipp64f *src_ptr = src.get(), *dst_ptr = dst.get();

    IppStatus message = ippsZero_64f(src_ptr, srcLen);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    message = ippsCopy_64f(pSrc, src_ptr+srcLen, srcLen);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    message = ippsZero_64f(dst_ptr, dstLen*2);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    // Check duplicate points.
    Ipp64f chk_number = src_ptr[srcLen];
    Ipp32u i = srcLen+1;

    for(Ipp32u end = srcLen*2; i < end; ++i) {
        if(chk_number == src_ptr[i]) {
            src_ptr[i] += 0.00001;
        }
        chk_number = src_ptr[i];
    }

    // First interpolation with invalid borders.
    Interpolation interpolation;
    interpolation.prepare(Interpolation::Linear, src_sz, src_step, dst_sz, dst_step);
    interpolation.interpolate(src_ptr, dst_ptr);

    // Find duplicate borders.
    Ipp32u dup_cntr = 0, begin_cntr = 0;

    // Loop initialize.
    i = dstLen;
    chk_number = dst_ptr[i];

    // In left side.
    for(Ipp32u end = dstLen*2; ; ++i) {
        if((i >= end) || (chk_number != dst_ptr[i])) {
            begin_cntr = --dup_cntr;
            break;
        }
        if(chk_number == dst_ptr[i]) ++dup_cntr;
    }

    // In rigth side.
    for(i = (dstLen*2)-1, chk_number = dst_ptr[i]; ; --i) {
        if((i < dstLen) || (chk_number != dst_ptr[i])) {
            --dup_cntr;
            break;
        }
        if(chk_number == dst_ptr[i]) ++dup_cntr;
    }

    // Update signal parameters.
    srcLen = dstLen-dup_cntr;
    src_sz.width = srcLen;
    src_step = srcLen*sizeof(Ipp64f);
    src.reset(ippsMalloc_64f(srcLen*2));
    src_ptr = src.get();

    // First copy X data.
    dst_ptr += begin_cntr;

    message = ippsCopy_64f(dst_ptr, src_ptr, srcLen);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    // Then copy Y data.
    dst_ptr += dstLen;
    src_ptr += srcLen;

    message = ippsCopy_64f(dst_ptr, src_ptr, srcLen);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    // Reset previous addresses.
    dst_ptr = dst.get();
    src_ptr = src.get();

    // Interpolate new source image with valid borders.
    interpolation.prepare(Interpolation::Linear, src_sz, src_step, dst_sz, dst_step);
    interpolation.interpolate(src_ptr, dst_ptr);

    // Then copy path of signal data to destination image.
    message = ippsCopy_64f(dst_ptr+dstLen, pDst, dstLen);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));
}
