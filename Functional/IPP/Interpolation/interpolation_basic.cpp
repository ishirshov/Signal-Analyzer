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

#include "interpolation_basic.h"

InterpolationBasic::InterpolationBasic()
    :num_channels(1)
    ,buff_size(0)
    ,spec_size(0)
    ,init_size(0)
{
    dst_offset.x = 0;
    dst_offset.y = 0;
}

bool InterpolationBasic::check_settings(IppiSize size, Ipp32s step)
{
    if(size.width <= 0) return false;
    if(size.height <= 0) return false;
    if(step <= 0) return false;

    return true;
}

InterpolationBasic::~InterpolationBasic()
{
}
