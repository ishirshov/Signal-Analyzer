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

#include "ipp_fft_init.h"
#include <cmath>
#include <stdexcept>

void ipp_fft_init(ipp_ptr<IppsFFTSpec_R_64f> &spec, ipp_ptr<Ipp8u> &buff, const Ipp32s length)
{
    Ipp32s order = Ipp32s(log2(Ipp64f(length)));
    Ipp32s specinit_sz = 0, specbuff_sz = 0, buff_sz = 0;

    IppStatus message = ippsFFTGetSize_R_64f(order, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, &specinit_sz, &specbuff_sz, &buff_sz);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    buff.reset(ippsMalloc_8u(buff_sz));

    ipp_ptr<Ipp8u> specInit(ippsMalloc_8u(specinit_sz));
    ipp_ptr<Ipp8u> specBuff(ippsMalloc_8u(specbuff_sz));

    IppsFFTSpec_R_64f *_spec = 0;

    message = ippsFFTInit_R_64f(&_spec, order, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, specInit.release(), specBuff.get());
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    spec.reset(_spec);
}

void ipp_fft_init(ipp_ptr<IppsFFTSpec_R_32f> &spec, ipp_ptr<Ipp8u> &buff, const Ipp32s length)
{
    Ipp32s order = Ipp32s(log2(Ipp64f(length)));
    Ipp32s specinit_sz = 0, specbuff_sz = 0, buff_sz = 0;

    IppStatus message = ippsFFTGetSize_R_32f(order, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, &specinit_sz, &specbuff_sz, &buff_sz);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    buff.reset(ippsMalloc_8u(buff_sz));

    ipp_ptr<Ipp8u> specInit(ippsMalloc_8u(specinit_sz));
    ipp_ptr<Ipp8u> specBuff(ippsMalloc_8u(specbuff_sz));

    IppsFFTSpec_R_32f *_spec = 0;

    message = ippsFFTInit_R_32f(&_spec, order, IPP_FFT_NODIV_BY_ANY, ippAlgHintFast, specInit.release(), specBuff.get());
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    spec.reset(_spec);
}
