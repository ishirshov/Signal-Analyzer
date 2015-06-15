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

#ifndef INTERPOLATION_BASIC_H
#define INTERPOLATION_BASIC_H

#include "interpolation_interface.h"
#include "../additional.h"

class InterpolationBasic : public InterpolationInterface
{
    InterpolationBasic(const InterpolationBasic&);
    InterpolationBasic& operator=(const InterpolationBasic&);

protected:
    // Internal class types:
    typedef ipp_ptr<Ipp8u> buffer_guard;
    typedef ipp_ptr<IppiResizeSpec_64f> spec_guard;

    //// Interpolate method data:
    // Work sizes:
    Ipp32s buff_size;
    Ipp32s spec_size;
    Ipp32s init_size;

    // Spec data and buffer:
    buffer_guard buffer;
    spec_guard spec;

    // Settings:
    IppiPoint dst_offset;
    Ipp32u num_channels;

    //// Input data:
    // Image sizes:
    IppiSize src_size;
    IppiSize dst_size;

    // Image step:
    Ipp32s src_step;
    Ipp32s dst_step;

    bool check_settings(IppiSize sz, Ipp32s step);

public:
    InterpolationBasic();

    virtual void prepare(IppiSize src, Ipp32s src_stp,
                         IppiSize dst, Ipp32s dst_stp) = 0;

    virtual void interpolate(Ipp64f *_src, Ipp64f *_dst) = 0;

    virtual ~InterpolationBasic();

};

#endif // INTERPOLATION_BASIC_H
