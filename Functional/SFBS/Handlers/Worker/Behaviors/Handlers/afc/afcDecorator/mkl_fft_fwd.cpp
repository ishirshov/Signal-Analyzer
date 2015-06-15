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

#include "mkl_fft_fwd.h"

//-------------------------------------- Define getSpectrum class ------------------------------//

mklFFTFWD::mklFFTFWD(ComputeModule *_module)
    :ComputeDecorator(_module)
    ,fft_size(c_Default_Fs/2)
{
    initDescriptor();
}

void mklFFTFWD::handleData(ipp_vector<Ipp32f> &signal)
{
    if(signal.empty()) return;

    module->handleData(signal);

    Ipp32f *data = signal.data();
    Ipp32s size = signal.size();

    if(size != fft_size)
    {
        fft_size = size;

        DftiFreeDescriptor(&fft_handle);
        initDescriptor();
    }

     // Get spectrum.
    DftiComputeForward(fft_handle, data);
}

void mklFFTFWD::initDescriptor()
{
    DftiCreateDescriptor(&fft_handle, DFTI_SINGLE, DFTI_REAL, 1, fft_size);
    DftiCommitDescriptor(fft_handle);
}

mklFFTFWD::~mklFFTFWD()
{
    DftiFreeDescriptor(&fft_handle);
}
