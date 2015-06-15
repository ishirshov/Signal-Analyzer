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

#ifndef WINDOW_FUNCTION_H
#define WINDOW_FUNCTION_H

#include "compute_module.h"

class WindowFunction : public ComputeModule
{
    Q_OBJECT

public:
    enum Type {
        None,
        Bartlett,
        Blackman,
        BlackmanStd,
        BlackmanOpt,
        Hamming,
        Hann,
        Kaiser
    };

    WindowFunction();

public slots:
    void handleData(ipp_vector<Ipp32f>&);

    void setWindowAlpha(double);
    void setWindowType(int);

signals:
    // Unused signal
    void dataProcessed(const ipp_vector<Ipp32f>&);

private:
    Ipp32f* initWindowFunction(const int length);
    void initHashTable();

    Type function;
    QMultiHash<quint32, Type> func_table;

    Ipp32f alpha;
    ipp_ptr<Ipp32f> win_data;
    quint32 win_length;

};

#endif // WINDOW_FUNCTION_H
