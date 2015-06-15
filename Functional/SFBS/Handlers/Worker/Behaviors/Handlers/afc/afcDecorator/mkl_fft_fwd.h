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

#ifndef MKL_FFT_FWD
#define MKL_FFT_FWD

#include "compute_decorator.h"

#include <mkl_dfti.h>

//-------------------------------------- Declare getSpectrum class ------------------------------//

class mklFFTFWD : public ComputeDecorator
{
    Q_OBJECT

public:
    explicit mklFFTFWD(ComputeModule *_module);

    ~mklFFTFWD();

public slots:
    void handleData(ipp_vector<Ipp32f> &);

signals:
    // Unused signal
    void dataProcessed(const ipp_vector<Ipp32f>&);

private:
    void initDescriptor();

    DFTI_DESCRIPTOR_HANDLE fft_handle;
    quint32 fft_size;

};

#endif // MKL_FFT_FWD
