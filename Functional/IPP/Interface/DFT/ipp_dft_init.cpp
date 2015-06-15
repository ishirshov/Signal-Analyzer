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

#include "ipp_dft_init.h"
#include <ippcore.h>
#include <stdexcept>

void ipp_dft_init(ipp_ptr<IppsDFTSpec_R_64f> &spec, ipp_ptr<Ipp8u> &buff, const Ipp32s length)
{
    IppsDFTSpec_R_64f *_spec = 0;

    IppStatus message = ippsDFTInitAlloc_R_64f(&_spec, length, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    spec.reset(_spec);
    Ipp32s buff_sz = 0;

    message = ippsDFTGetBufSize_R_64f(_spec, &buff_sz);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    buff.reset(ippsMalloc_8u(buff_sz));
}

void ipp_dft_init(ipp_ptr<IppsDFTSpec_R_32f> &spec, ipp_ptr<Ipp8u> &buff, const Ipp32s length)
{
    IppsDFTSpec_R_32f *_spec = 0;

    IppStatus message = ippsDFTInitAlloc_R_32f(&_spec, length, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    spec.reset(_spec);
    Ipp32s buff_sz = 0;

    message = ippsDFTGetBufSize_R_32f(_spec, &buff_sz);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    buff.reset(ippsMalloc_8u(buff_sz));
}
