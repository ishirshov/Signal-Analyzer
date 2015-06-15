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

#include "resampling_up.h"

ResamplingUp::ResamplingUp(int src_frequency, int dst_frequency)
    :_src_frequency(src_frequency)
    ,_dst_frequency(dst_frequency)
{
    if(_src_frequency < 1)
        throw std::runtime_error("Sampling frequency of input signal must be positive.");
    if(_dst_frequency <= _src_frequency)
        throw std::runtime_error("Sampling frequency of output signal must be greather than input signal.");
}

void ResamplingUp::operate(const ipp_vector<Ipp16s> &signal)
{
    if(signal.empty()) return;

    if(_signal_data.size() < _dst_frequency)
    {
        const Ipp16s *data = signal.data();
        qint32 size = signal.size();

        if(size != _buffer_data.size())
            _buffer_data.resize(size);

        Ipp32f *data_32f = _buffer_data.data();
        ipp_convert(data, data_32f, size);

        ipp_dft_resampl_stat(data_32f, _src_frequency,
                             data_32f, _dst_frequency);

        _signal_data.push_back(data_32f, _dst_frequency);
    }
}
