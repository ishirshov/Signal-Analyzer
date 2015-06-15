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

#include "param_extract.h"

#include <mkl_cblas.h>

paramExtract::paramExtract(ComputeModule *_module)
    :ComputeDecorator(_module)
    ,sampl_freq(c_Default_Fs)
{
}

void paramExtract::setSamplingFrequency(ulong freq)
{
    if(freq > 1) sampl_freq = freq;
}

void paramExtract::handleData(ipp_vector<Ipp32f> &afc)
{
    if(afc.empty()) return;

    // Extract only peaks and his parameters.
    module->handleData(afc);

    // Parameter search in range [0:(N/2)] for even
    // and [0:(N-1)/2] for odd N.
    const Ipp32f *data = afc.data();
    Ipp32s size = afc.size();
    Ipp32s length = size + 2;
    length = (!(length%2))?(length/2):((length-1)/2);

    const Ipp32fc *_pfft = (Ipp32fc*)data;

    // Find maximum peak in FFT bin.
    CBLAS_INDEX indx = cblas_icamax(length, _pfft, 1);

    param[1] = std::sqrt((_pfft[indx].re * _pfft[indx].re) + (_pfft[indx].im * _pfft[indx].im));

    // Get amplitude in levels.
    param[1] = param[1] * (2.0/Ipp32f(length));

    // Convert levels to amplitude.
    param[2] = c_B * log10(param[1]);
    std::modf(param[2], &param[2]);

    // Compute frequency (index * samplingFrequency / N).
    param[0] = indx * (sampl_freq/(size));

    emit updateFrequencyLCD(param[0]);
    emit updateAmplitudeLCD(param[2]);
}
