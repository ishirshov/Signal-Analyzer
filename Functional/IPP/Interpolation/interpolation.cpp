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

#include "interpolation.h"

bool Interpolation::check_size(IppiSize size, Ipp32s step)
{
    if(size.width <= 0) return false;
    if(size.height <= 0) return false;
    if(step <= 0) return false;

    return true;
}

void Interpolation::prepare(Type type, IppiSize src, Ipp32s src_step, IppiSize dest, Ipp32s dst_step)
{
    reset(); // If new data then reset old.

    switch (type) {
    case Nearest:
    {
        break;
    }
    case Linear:
    {
        interpolation.reset(new InterpolationLinear);
        interpolation->prepare(src, src_step, dest, dst_step);
        break;
    }
    default:
        throw std::invalid_argument("Don't know this interpolation method.");
        break;
    }
}

void Interpolation::interpolate(Ipp64f *source, Ipp64f *dest)
{
    if(interpolation)
        interpolation->interpolate(source, dest);
}

void Interpolation::reset()
{
    if(interpolation)
        interpolation.reset();
}
