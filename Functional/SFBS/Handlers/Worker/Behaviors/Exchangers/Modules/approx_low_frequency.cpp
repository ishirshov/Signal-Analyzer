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

#include "approx_low_frequency.h"

ApproxLowFrequency::ApproxLowFrequency(int size_points, float delta_t)
    :_size_points(size_points)
    ,_delta_t(std::ceil(delta_t))
    ,_last_size(c_Default_Buffer_sz)
    ,_loop_cond(0)
{
    if(_size_points < 1)
        throw std::runtime_error("Size of points must be positive.");
    if(_delta_t < 1)
        throw std::runtime_error("Size of space in buffer must be positive.");

    determine_optimal_sz(_last_size);
}

void ApproxLowFrequency::operate(const ipp_vector<Ipp16s> &signal)
{
    if(signal.empty()) return;

    if(_signal_data.size() < _size_points)
    {
        qint32 sig_size = signal.size();

        if(_last_size != sig_size) {
            determine_optimal_sz(sig_size);
            _last_size = sig_size;
        }

        qint32 space = _avg_sum.available_space();
        if(space) _avg_sum.push_back(signal, sig_size);

        if(!_avg_sum.available_space())
        {
            Ipp16s *data = _avg_sum.data();

            for(qint32 i = 0; i < _loop_cond; ++i)
            {
                Ipp32s avg = 0;

                ipp_sum(data, _delta_t, avg);

                _signal_data.push_back(avg / _delta_t);
                data += _delta_t;
            }

            _avg_sum.clear();
        }
    }
}

void ApproxLowFrequency::determine_optimal_sz(const qint32 size)
{
    /* Determine optimal size of accum vector */
    qint32 opt_sz = size;
    qreal diff = opt_sz / qreal(_delta_t);
    qint32 opt_loop = std::floor(diff);
    diff = diff - opt_loop;

    /* Acceptable threshold difference */
    while(diff > 0.1)
    {
        opt_sz += size;
        diff = opt_sz / qreal(_delta_t);
        opt_loop = std::floor(diff);
        diff = diff - opt_loop;

        printInfo(QString("Current size: %1.").arg(opt_sz));
    }

    _loop_cond = opt_loop;
    _avg_sum.resize(opt_sz);
    _avg_sum.clear();
}
