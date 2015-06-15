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

#include "afcprivatedata.h"

AFCPrivateData::AFCPrivateData()
    :signalFreq(c_Default_Fs/2)
    ,userPeaks(0)
    ,titleAxisY(QObject::tr("dB"))
    ,boundingRect(0.0, 0.0, -1.0, -1.0)
    ,isData(false)
{
    changeWidth(250, QPointF(0.0, -95.0));
    changeAxisX();
    changeTitles();
}

void AFCPrivateData::changeWidth(int width, QPointF def_value)
{
    if((width > 0) && (width != values.size()))
    {
        QVector<QPointF> new_vals(width, def_value);

        QPointF *newData = new_vals.data();
        QPointF *valData = values.data();
        qint32 val_size = values.size();

        qint32 n = 0, i = 0;

        if(width < val_size)
            i = val_size - width;
        else if(width > val_size)
            n = width - val_size;

        for(; i < val_size; ++i, ++n)
            newData[n].setY(valData[i].y());

        values = new_vals;
    }
}

void AFCPrivateData::changeAxisX()
{
    quint32 size = values.size();
    quint32 div = 1;

    if(signalFreq <= 999999)
        div = 1000;
    else if(signalFreq <= 999999999)
        div = 1000000;
    else
        div = 1000000000;

    values[0].setX(0);
    for(quint32 i = 1; i < size; ++i) {
        qreal x = signalFreq / size;
        x = x * i;
        x = x / div;

        values[i].setX(x);
    }
}

void AFCPrivateData::changeTitles()
{
    if(signalFreq <= 999)
        titleAxisX = QObject::tr("Hz");
    else if(signalFreq <= 999999)
        titleAxisX = QObject::tr("KHz");
    else if(signalFreq <= 999999999)
        titleAxisX = QObject::tr("MHz");
    else
        titleAxisX = QObject::tr("GHz");

    titleAxisY = QObject::tr("dB");
}
