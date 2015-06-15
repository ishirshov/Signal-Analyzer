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

#ifndef APPROX_LOW_FREQUENCY_H
#define APPROX_LOW_FREQUENCY_H

#include "math_module.h"

///
/// \brief The ApproximateLDT class
///        implements a function
///        approximation for low frequency
///        range (from 1Hz to 100Hz).
///
class ApproxLowFrequency : public MathModule
{
    Ipp32s _size_points;
    Ipp32s _delta_t;
    Ipp32s _last_size;
    Ipp32s _loop_cond;

    ipp_vector<Ipp16s> _avg_sum;
    ipp_vector<Ipp32f> _signal_data;

    void determine_optimal_sz(const qint32 size);

public:
    ApproxLowFrequency(int size_points, float delta_t);

    void operate(const ipp_vector<Ipp16s> &);
    void clear()  { _signal_data.clear(); }

    ipp_vector<Ipp32f>* signal_data() { return new ipp_vector<Ipp32f>(_signal_data); }
    bool is_compelete() const { return (_size_points <= _signal_data.size()); }

};

#endif // APPROX_LOW_FREQUENCY_H
