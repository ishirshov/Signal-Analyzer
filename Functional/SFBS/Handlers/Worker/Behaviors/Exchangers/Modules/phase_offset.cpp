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

#include "phase_offset.h"

PhaseOffset::PhaseOffset(MathModule *module)
    :MathDecorators(module)
{
}

ipp_vector<Ipp32f> *PhaseOffset::signal_data()
{
    QScopedPointer<ipp_vector<Ipp32f> > signal(_module->signal_data());

    if(signal && !signal->empty())
    {
        Ipp32f *src_signal = signal->data();
        Ipp32s src_size = signal->size();

        Ipp32f *orig_signal = _original_signal.data();
        Ipp32s orig_size = _original_signal.size();

        if(!_original_signal.empty())
        {
            Ipp32f offset = 0.0;
            offset = ipp_phase_offset(orig_signal, orig_size,
                                      src_signal, src_size,
                                      ipp_phase_offset_stat);

            if((offset >= 0) && (offset < orig_size))
                src_signal += quint32(round(offset));
            else if((offset >= orig_size) && (offset < src_size))
                src_signal += quint32((round(offset) - orig_size));
            else
                ipp_copy(src_signal, orig_signal, orig_size);

            _buffer.clear();
            _buffer.push_back(src_signal, orig_size);

            signal->swap(_buffer);
        }

        if(_original_signal.empty())
        {
            _original_signal = *signal;
            _original_signal.resize(src_size/2);
        }
    }

    return signal.take();
}
