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

#ifndef IPP_FFT_FWD_H
#define IPP_FFT_FWD_H

#include "compute_decorator.h"

class ippFFTFWD : public ComputeDecorator
{
    Q_OBJECT

public:
    explicit ippFFTFWD(ComputeModule *_module);

public slots:
    void handleData(ipp_vector<Ipp32f>&);

signals:
    // Unused signal
    void dataProcessed(const ipp_vector<Ipp32f>&);

private:
    ipp_ptr<IppsFFTSpec_R_32f> spec;
    ipp_ptr<Ipp8u> buffer;

    qint32 fft_size;

};

#endif // IPP_FFT_FWD_H
