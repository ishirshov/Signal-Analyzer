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

#include "ipp_fft_fwd.h"

ippFFTFWD::ippFFTFWD(ComputeModule *_module)
    :ComputeDecorator(_module)
    ,fft_size((c_Default_Fs/2))
{
    ipp_fft_init(spec, buffer, fft_size);
}

void ippFFTFWD::handleData(ipp_vector<Ipp32f> &signal)
{
    if(signal.empty()) return;

    module->handleData(signal);

    Ipp32f *data = signal.data();
    Ipp32s size = signal.size();

    if(size != fft_size)
    {
        fft_size = size;
        ipp_fft_init(spec, buffer, fft_size);
    }

    ipp_fft_fwd_r2ccs(data, data, spec.get(), buffer.get());
}
