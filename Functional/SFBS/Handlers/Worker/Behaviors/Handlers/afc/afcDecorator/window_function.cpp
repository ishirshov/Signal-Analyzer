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

#include "window_function.h"
#include <mkl_vml.h>

WindowFunction::WindowFunction()
    :function(None)
    ,alpha(0.16f)
    ,win_data(initWindowFunction(c_Default_Buffer_sz))
    ,win_length(c_Default_Buffer_sz)
{
    initHashTable();
}

void WindowFunction::handleData(ipp_vector<Ipp32f> &signal)
{
    if(signal.empty() || (function == None)) return;

    Ipp32f *data = signal.data();
    Ipp32s size = signal.size();

    if(size != win_length) {
        win_data.reset(initWindowFunction(size));
        win_length = size;
    }

    vsMul(size, win_data.get(), data, data);
}

void WindowFunction::setWindowAlpha(double _alpha)
{
    switch (function)
    {
    case Blackman:
    {
        if((_alpha >= 0 && _alpha <= 1.0))
            alpha = _alpha;

        win_data.reset(initWindowFunction(win_length));
        break;
    }
    case Kaiser:
    {
        if((_alpha >= 0 && _alpha <= 2.0))
            alpha = _alpha;

        win_data.reset(initWindowFunction(win_length));
        break;
    }
    default:
        break;
    }
}

void WindowFunction::setWindowType(int _type)
{
    if(func_table.contains(_type)) {
        function = func_table.value(_type);
        alpha = (function == Blackman)?(0.16f):((function == Kaiser)?(1.0):(0.0));
    }

    win_data.reset(initWindowFunction(win_length));
}

Ipp32f* WindowFunction::initWindowFunction(const int length)
{
    ipp_ptr<Ipp32f> window(ippsMalloc_32f(length));

    IppStatus status = ippStsNoErr;
    Ipp32f *_window_ptr = window.get();

    if(function != None)
        ipp_set(1.0f, _window_ptr, length);

    switch(function)
    {
    case Bartlett:
        status = ippsWinBartlett_32f(_window_ptr, _window_ptr, length);
        break;
    case Blackman:
        status = ippsWinBlackman_32f(_window_ptr, _window_ptr, length, alpha);
        break;
    case BlackmanStd:
        status = ippsWinBlackmanStd_32f(_window_ptr, _window_ptr, length);
        break;
    case BlackmanOpt:
        status = ippsWinBlackmanOpt_32f(_window_ptr, _window_ptr, length);
        break;
    case Hamming:
        status = ippsWinHamming_32f(_window_ptr, _window_ptr, length);
        break;
    case Hann:
        status = ippsWinHann_32f(_window_ptr, _window_ptr, length);
        break;
    case Kaiser:
        status = ippsWinKaiser_32f(_window_ptr, _window_ptr, length, alpha);
        break;
    default:
        break;
    };

    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

    return window.release();
}

void WindowFunction::initHashTable()
{
    func_table.insert(0, None);
    func_table.insert(1, Bartlett);
    func_table.insert(2, Blackman);
    func_table.insert(3, BlackmanStd);
    func_table.insert(4, BlackmanOpt);
    func_table.insert(5, Hamming);
    func_table.insert(6, Hann);
    func_table.insert(7, Kaiser);
}
