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

#include "playbackcurvedata.h"

PlaybackCurveData::PlaybackCurveData()
    :bndngRct(0.0, 0.0, -1.0, -1.0)
    ,values(new QVector<QPointF>)
{
}

void PlaybackCurveData::appendData(QVector<QPointF> *samples)
{
    if(!samples) return;

    // Delete old values.
    values.reset(samples);
}

void PlaybackCurveData::clearData()
{
    QPointF *v_data = values->data();
    quint32 size = values->size();

    for(quint32 i = 0; i < size; ++i)
        v_data[i].setY(0.0);
}

QwtInterval PlaybackCurveData::min_maxX() const
{
    qreal min_x = (values->size())?(values->at(0).x()):(0);
    qreal max_x = (values->size())?(values->at(values->size()-1).x()):(1);

    return QwtInterval(min_x, max_x);
}

QwtInterval PlaybackCurveData::min_maxY() const
{
    qreal min_y = -1.0;
    qreal max_y = 1.0;

    QPointF *v_data = values->data();
    quint32 size = values->size();

    for(quint32 i = 0; i < size; ++i)
    {
        qreal curr_y = v_data[i].y();

        if(curr_y < min_y) min_y = curr_y;
        if(curr_y > max_y) max_y = curr_y;
    }

    return QwtInterval(min_y, max_y);
}

bool PlaybackCurveData::readyToUpdate() const
{
    return bool(values->size());
}
