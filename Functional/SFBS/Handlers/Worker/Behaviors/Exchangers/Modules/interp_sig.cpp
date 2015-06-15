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

#include "interp_sig.h"
#include "Functional/IPP/general_functions.h"

InterpSig::InterpSig(MathModule *module, int signal_size)
    :MathDecorators(module)
    ,_signal_size(signal_size)
{
    if(signal_size < 1)
        throw std::runtime_error("Signal size cannot be negative.");

    _buffer.resize(_signal_size);
}

ipp_vector<Ipp32f>* InterpSig::signal_data()
{
    QScopedPointer<ipp_vector<Ipp32f> > signal(_module->signal_data());

    if(signal && (signal->size() < _signal_size))
    {
        ipp_vector<Ipp64f> tmp = *signal;
        interpolate_64f(tmp.data(), tmp.size(), _buffer.data(), _buffer.size());

        *signal = _buffer;
    }

    return signal.take();
}
