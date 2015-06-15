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

#include "approx_delta_t.h"

ApproxDeltaT::ApproxDeltaT(int size_points, double delta_t, double payload_array)
    :_size_points(size_points)
    ,_array_counter(0)
    ,_point_index(0.f)
    ,_array_index(0.f)
    ,_delta_t(delta_t)
    ,_payload_array(payload_array)
{
    if(_size_points < 1)
        throw std::runtime_error("Size of points must be positive.");
    if(_delta_t < 0)
        throw std::runtime_error("Delta T must be positive value.");
    if(_payload_array < 0)
        throw std::runtime_error("Index of payload array must be positive number of equal zero.");
}

void ApproxDeltaT::operate(const ipp_vector<Ipp16s> &signal)
{
    if(signal.empty()) return;

    if(_signal_data.size() < _size_points)
    {
        if(_payload_array >= 1.0)
        {
            if(std::ceil(_array_index) == _array_counter)
            {
                _array_index += _payload_array;
                ++_array_counter;
            }
            else
            {
                ++_array_counter;
                return;
            }
        }

        qint32 size = signal.size();

        while(_point_index >= 0)
            _point_index -= size;
        _point_index += size;

        for(; (_point_index < size) && (_signal_data.size() < _size_points); _point_index += _delta_t)
            _signal_data.push_back(signal[int(_point_index)]);
    }
}

void ApproxDeltaT::clear()
{
    _signal_data.clear();
    _array_counter = _array_index = 0;
}
