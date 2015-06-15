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

#include "curveprivatedata.h"

CurvePrivateData::CurvePrivateData()
    :divider(1.0)
    ,frequency(1.0)
    ,array_size(c_Default_Buffer_sz)
    ,window_with(250)
    ,offset(0)
    ,sampling_freq(c_Default_Fs)
    ,bounding_rect(0.0, 0.0, -1.0, -1.0)
    ,title_time(QObject::tr("s"))
    ,is_enable_phase_detect(false)
    ,is_enable_sig_transform(false)
    ,is_enable_decimate_sig(false)
    ,current_filter_type(DenoisedGroupBox::None)
{
    initTimeVector();
    initAmplitudeMap();

    changeWidth(window_with);
}

void CurvePrivateData::initTimeVector()
{    
    time.push_back(Second(1,QObject::tr("second"),QObject::tr("s")));
    time.push_back(Second(0.001,QObject::tr("millisecond"),QObject::tr("ms")));
    time.push_back(Second(0.000001,QObject::tr("microsecond"), QString::fromUtf8("\u00b5") + QObject::tr("s")));
    time.push_back(Second(0.000000001,QObject::tr("nanosecond"),QObject::tr("ns")));
    time.push_back(Second(0.000000000001,QObject::tr("picosecond"),QObject::tr("ps")));
}

void CurvePrivateData::initAmplitudeMap()
{
    amplitude.insert(0.0005, QString::fromUtf8("\u00b5") + QObject::tr("V"));
    amplitude.insert(0.001, QObject::tr("mV"));
    amplitude.insert(0.002, QObject::tr("mV"));
    amplitude.insert(0.005, QObject::tr("mV"));
    amplitude.insert(0.01, QObject::tr("mV"));
    amplitude.insert(0.02, QObject::tr("mV"));
    amplitude.insert(0.05, QObject::tr("mV"));
    amplitude.insert(0.1, QObject::tr("V"));
    amplitude.insert(0.2, QObject::tr("V"));
    amplitude.insert(0.5, QObject::tr("V"));
    amplitude.insert(1, QObject::tr("V"));
}

void CurvePrivateData::updateTimeVector()
{
    quint32 indx = 0, size = time.size();

    // Find last index before translate.
    for(quint32 i = 0; i < size; ++i)
        if(time[i].symbol() == title_time)
            indx = i;

    time[0].name(QObject::tr("second"));
    time[0].symbol(QObject::tr("s"));
    time[1].name(QObject::tr("millisecond"));
    time[1].symbol(QObject::tr("ms"));
    time[2].name(QObject::tr("microsecond"));
    time[2].symbol(QString::fromUtf8("\u00b5") + QObject::tr("s"));
    time[3].name(QObject::tr("nanosecond"));
    time[3].symbol(QObject::tr("ns"));
    time[4].name(QObject::tr("picosecond"));
    time[4].symbol(QObject::tr("ps"));

    // Update title time.
    title_time = time[indx].symbol();
}

void CurvePrivateData::updateAmplitudeMap()
{
    amplitude.clear();
    initAmplitudeMap();
}

void CurvePrivateData::changeWidth(int width)
{    
    // Remember width.
    window_with = width;

    // Algorithm conditions.
    width = topwr_of_2(width);

    if((width > 0) && (width != values.size()))
        values.resize(width);
}

void CurvePrivateData::changeTimeAxis()
{
    // Prepare data:
    quint32 time_size = time.size();
    Second *time_data = time.data();

    quint32 val_size = values.size();
    QPointF *val_data = values.data();

    qreal time_range = 1/(frequency/divider);
    quint32 i = 0;

    // Determine new title for time axis.
    for(; i < time_size; ++i)
    {
        qreal value = time_data[i].value();

        if(time_range >= value)
        {
            time_range /= value;
            title_time = time_data[i].symbol();
            break;
        }
    }

    // Create new timeline for time axis.
    qreal scale_step = time_range/qreal(val_size);
    qreal x = 0.0;

    for(i = 0; i < val_size; ++i)
    {
        val_data[i].setX(x);   
        x += scale_step;
    }
}

void CurvePrivateData::clearData()
{
    QPointF *data = values.data();
    quint32 size = values.size();

    for(quint32 i = 0; i < size; ++i)
        data[i].setY(0.0);
}
