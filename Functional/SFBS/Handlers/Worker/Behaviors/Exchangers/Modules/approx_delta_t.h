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

#ifndef APPROX_DELTA_T_H
#define APPROX_DELTA_T_H

#include "math_module.h"

///
/// \brief The ApproxDeltaT class
///        implements the algorithm
///        samples points from the
///        stream by a variable Delta T.
///
class ApproxDeltaT : public MathModule
{
    Ipp32s _size_points;
    Ipp32s _array_counter;
    Ipp32f _point_index;
    Ipp32f _array_index;
    Ipp32f _delta_t;
    Ipp32f _payload_array;

    ipp_vector<Ipp32f> _signal_data;

public:
    ApproxDeltaT(int size_points, double delta_t, double payload_array);

    void operate(const ipp_vector<Ipp16s> &);
    void clear();

    ipp_vector<Ipp32f>* signal_data() { return new ipp_vector<Ipp32f>(_signal_data); }
    bool is_compelete() const { return (_signal_data.size() == _size_points); }

};

#endif // APPROX_DELTA_T_H
