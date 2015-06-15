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

#ifndef RESAMPLING_DOWN_H
#define RESAMPLING_DOWN_H

#include "math_module.h"

///
/// \brief The ResamplingDown class
///        implements algorithm thinning
///        signal flow, which allows to
///        lower the sampling rate of the signal.
///
class ResamplingDown : public MathModule
{
    ipp_vector<Ipp32f> _buffer_data;
    ipp_vector<Ipp32f> _signal_data;

    Ipp32s _current_frequency;
    Ipp32s _target_frequency;
    Ipp32s _factor;
    Ipp32s _phase;

public:
    ResamplingDown(int target_frequency, int factor);

    void operate(const ipp_vector<Ipp16s>&);
    void clear();

    ipp_vector<Ipp32f>* signal_data() { return new ipp_vector<Ipp32f>(_signal_data); }
    bool is_compelete() const { return (_current_frequency >= _target_frequency);  }

};

#endif // RESAMPLING_DOWN_H
