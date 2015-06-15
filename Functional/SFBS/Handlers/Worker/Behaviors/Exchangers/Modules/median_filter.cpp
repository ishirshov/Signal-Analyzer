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

#include "median_filter.h"

MedianFilter::MedianFilter(MathModule *module)
    :MathDecorators(module)
    ,_kernel(c_Median_K)
{    
}

ipp_vector<Ipp32f>* MedianFilter::signal_data()
{
    QScopedPointer<ipp_vector<Ipp32f> > signal(_module->signal_data());

    if(signal && !signal->empty())
    {        
        Ipp32f *signal_data = signal->data();
        quint32 len = signal->size();

        ipp_median(signal_data, signal_data, len, _kernel);
    }

    return signal.take();
}

void MedianFilter::setMedianK(Ipp32s val)
{
    if(val%2 == 0) return;

    _kernel = val;
}
