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

#include "interpolation_linear.h"

void InterpolationLinear::prepare(IppiSize src, Ipp32s src_stp,
                                  IppiSize dst, Ipp32s dst_stp)
{
    if(!check_settings(src, src_stp))
        throw std::invalid_argument("Size of source image must be positive.");

    src_size = src;
    src_step = src_stp;

    if(!check_settings(dst, dst_stp))
        throw std::invalid_argument("Size of destination image must be positive.");

    dst_size = dst;
    dst_step = dst_stp;

    IppStatus message = ippiResizeGetSize_64f(src_size, dst_size, ippLinear, 0, &spec_size, &init_size);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    spec.reset((IppiResizeSpec_64f*)ippsMalloc_64f(spec_size));

    message = ippiResizeLinearInit_64f(src_size, dst_size, spec.get());
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    message = ippiResizeGetBufferSize_64f(spec.get(), dst_size, num_channels, &buff_size);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    buffer.reset(ippsMalloc_8u(buff_size));
}

void InterpolationLinear::interpolate(Ipp64f *_src, Ipp64f *_dst)
{
    if(!_src || !_dst)
        throw std::invalid_argument("Null pointer not contain data.");

    IppStatus message = ippiResizeLinear_64f_C1R(_src, src_step, _dst, dst_step, dst_offset, dst_size, ippBorderRepl, 0, spec.get(), buffer.get());
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));
}
