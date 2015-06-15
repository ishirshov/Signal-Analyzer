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

#include "simple_kalman_filter.h"

SimpleKalmanFilter::SimpleKalmanFilter(MathModule *module)
    :MathDecorators(module)
    ,_K_stab(c_Kalman_gain)
{
}

ipp_vector<Ipp32f>* SimpleKalmanFilter::signal_data()
{
    // Get signal data
    QScopedPointer<ipp_vector<Ipp32f> > signal(_module->signal_data());

    if(signal && !signal->empty())
    {
        Ipp32f *data = signal->data();
        Ipp32s sz = signal->size() - 1;

        // Kalman algorithm
        for(qint32 i = 0; i < sz; ++i)
            data[i + 1] =  data[i] * (1 - _K_stab) + _K_stab * data[i + 1];
    }

    return signal.take();
}

void SimpleKalmanFilter::setKalmanGain(Ipp32f val)
{
    _K_stab = val;
}
