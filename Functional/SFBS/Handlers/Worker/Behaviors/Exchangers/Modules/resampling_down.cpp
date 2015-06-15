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

#include "resampling_down.h"

ResamplingDown::ResamplingDown(int target_frequency,
                               int factor)
    :_current_frequency(0)
    ,_target_frequency(target_frequency)
    ,_factor(factor)
    ,_phase(0)
{
    if(_target_frequency <= _current_frequency)
        throw std::runtime_error("Sampling frequency of output signal must be greather than input signal.");
    if(_factor < 1)
        throw std::runtime_error("Downsampling factor must be 0 < phase < factor.");
}

void ResamplingDown::operate(const ipp_vector<Ipp16s> &signal)
{
    if(signal.empty()) return;

    if(_current_frequency < _target_frequency)
    {
        const Ipp16s *data = signal.data();
        qint32 size = signal.size();

        if(size != _buffer_data.size())
            _buffer_data.resize(size);

        Ipp32f *data_32f = _buffer_data.data();
        ipp_convert(data, data_32f, size);

        ulong decimate_size = _target_frequency - _current_frequency;
        if(decimate_size > size) decimate_size = size;

        qint32 accum_sz = 0;

        ipp_sample_down(data_32f, decimate_size, data_32f, &accum_sz, _factor, &_phase);

        _signal_data.push_back(data_32f, accum_sz);
        _current_frequency += decimate_size;
    }
}

void ResamplingDown::clear()
{
    _signal_data.clear();
    _current_frequency = 0;
}
