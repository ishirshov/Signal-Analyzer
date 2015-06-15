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

#ifndef LEVELS_TO_VLTS_H
#define LEVELS_TO_VLTS_H

#include <QObject>
#include "math_decorators.h"

class LevelToVlts : public QObject, public MathDecorators
{
    Q_OBJECT

public:
    explicit LevelToVlts(MathModule *module)
        :MathDecorators(module)
        ,_Vlts(c_V_DSP_12bit)
    {}

    ipp_vector<Ipp32f>* signal_data()
    {
        QScopedPointer<ipp_vector<Ipp32f> > signal(_module->signal_data());

        if(signal && !signal->empty()) {
            Ipp32f *signal_data = signal->data();
            ipp_div_c(signal_data, _Vlts,
                      signal_data, signal->size());
        }

        return signal.take();
    }

public slots:
    void setVolts(Ipp32f val)
    {
        if(val == c_V_DSP_12bit) _Vlts = val;
        if(val == c_V_FPGA_12bit) _Vlts = val;
        if(val == c_V_FPGA_16bit) _Vlts = val;
        if(val == c_V_FPGA_32bit) _Vlts = val;
        if(val == c_V_GPP_12bit) _Vlts = val;
    }

private:
    Ipp32f _Vlts;

};

#endif // LEVELS_TO_VLTS_H
