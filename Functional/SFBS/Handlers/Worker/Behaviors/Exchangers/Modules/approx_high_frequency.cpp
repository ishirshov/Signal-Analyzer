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

#include "approx_high_frequency.h"

ApproxHighFrequency::ApproxHighFrequency(int size_points, int delta_t)
    :_size_points(size_points)
    ,_delta_t(delta_t)
    ,_skip_samples(0)
{
    if(_size_points < 1)
        throw std::runtime_error("Size of points must be positive.");
    if(_delta_t < 0)
        throw std::runtime_error("Delta T must be positive value.");
}

void ApproxHighFrequency::operate(const ipp_vector<Ipp16s> &signal)
{
    if(signal.empty()) return;

    if(_signal_data.size() < _size_points)
    {
        Ipp32s avg = 0;
        Ipp32s num_sz = _delta_t;
        IppStatus status = ippStsNoErr;

        const Ipp16s *data = signal.data();
        qint32 size = signal.size();

        Ipp16s const *_p = data;
        Ipp16s const *_end = data + size;

        if(_skip_samples > 0)
        {
            status = ippsSum_16s32s_Sfs(_p, _skip_samples, &avg, 0);
            if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

            if(_signal_data.size())
            {
                Ipp32f &last_avg = _signal_data.back();
                last_avg = (last_avg + avg)/num_sz;
            }
            else _signal_data.push_back(avg/_skip_samples);

            _p += _skip_samples + 1;
            _skip_samples = 0;
        }

        while((_p < _end) && (_signal_data.size() < _size_points))
        {
            Ipp32s avail_samples = _end - _p;

            if(avail_samples < num_sz)
            {
                _skip_samples = num_sz - avail_samples;
                num_sz = avail_samples;
            }

            avg = 0;
            status = ippsSum_16s32s_Sfs(_p, num_sz, &avg, 0);
            if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

            _p += num_sz + 1;
            _signal_data.push_back((_skip_samples > 0) ? (avg) : (avg/num_sz));
        }
    }
}

void ApproxHighFrequency::clear()
{
    _signal_data.clear();
    _skip_samples = 0;
}
