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

#include "autocorr_norm.h"

AutoCorrNorm::AutoCorrNorm(MathModule *module)
    :MathDecorators(module)
    ,_last_len(c_Default_Buffer_sz)
{
    _buffer.reset(ipp_autocorr_norm_get_buff(_last_len, _last_len, ipp32f));
}

ipp_vector<Ipp32f>* AutoCorrNorm::signal_data()
{
    QScopedPointer<ipp_vector<Ipp32f> > signal(_module->signal_data());

    if(signal && !signal->empty()) {
        Ipp32f *signal_data = signal->data();
        int len = signal->size();

        if(len != _last_len)
        {
            _buffer.reset(ipp_autocorr_norm_get_buff(len, len, ipp32f));
            _last_len = len;
        }

        Ipp32f mean = 1024;
        ipp_autocorr_norm(signal_data, len, signal_data, len, _buffer.get());
        ipp_div_c(signal_data, mean, signal_data, len);
    }

    return signal.take();
}
