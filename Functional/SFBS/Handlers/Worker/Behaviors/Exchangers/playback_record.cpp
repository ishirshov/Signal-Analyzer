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

#include "playback_record.h"
#include <QApplication>

PlaybackRecord::PlaybackRecord(ulong sampling_frequency)
    :sampling_freq(sampling_frequency)
    ,_size(0)
{    
    if(!c_Fs_range.contains(sampling_frequency))
        throw std::runtime_error("Wrong sampling frequency.");

    time_stamp = QTime::currentTime();  // Create time stamp
}

void PlaybackRecord::dumpToFile()
{
    QString file_txt = QApplication::applicationDirPath() + "/dumps/";
    file_txt = file_txt + fileName() + ".txt";

    QFile file(file_txt);

    if(!file.open(QIODevice::WriteOnly)) return;

    QTextStream stream(&file);

    sigVector::ConstIterator p = signal.begin();
    sigVector::ConstIterator end = signal.end();

    emit maximumValueChanged(_size);

    quint32 i_size = 0;
    for(; p != end; ++p)
    {
        Ipp16s *data = p->first;
        quint32 size = p->second;

        for(quint32 i = 0; i < size; ++i)
            stream << data[i] << '\n';

        i_size += size;
        emit progressValueChanged(i_size);
    }
}

QVector<QPointF>* PlaybackRecord::prepareVector(PlaybackSettings *_p)
{
    QScopedPointer<PlaybackSettings> settings(_p);
    QScopedPointer<QVector<QPointF> > vector(new QVector<QPointF>);

    qreal delta_t = settings->get_delta_t();
    qreal time_dt = settings->get_time_dt();
    qreal pnt_indx = 0.0;
    qreal time_indx = 0.0;

    sigVector::ConstIterator p = signal.begin();
    sigVector::ConstIterator end = signal.end();

    emit maximumValueChanged(std::ceil(_size/delta_t));

    for(; p != end; ++p)
    {
        Ipp16s *data = p->first;
        quint32 size = p->second;

        while(pnt_indx >= 0)
            pnt_indx -= size;
        pnt_indx += size;

        while(pnt_indx < size)
        {
            qreal y = data[int(pnt_indx)]/GlobalVariables::getInstance().getVoltsLevel();

            vector->push_back(QPointF(time_indx, y));
            pnt_indx += delta_t;
            time_indx += time_dt;
        }

        emit progressValueChanged(vector->size());
    }

    return vector.take();
}

bool PlaybackRecord::operator ==(const PlaybackRecord& b)
{
    return (sampling_freq == b.sampling_freq) &&
            (time_stamp == b.time_stamp) &&
            (_size == b._size);
}

bool PlaybackRecord::operator !=(const PlaybackRecord& b)
{
    return !(*this == b);
}

bool PlaybackRecord::operator <(const PlaybackRecord& b)
{
    return (time_stamp < b.time_stamp);
}

bool PlaybackRecord::operator >(const PlaybackRecord& b)
{
    return (time_stamp > b.time_stamp);
}

bool PlaybackRecord::operator <=(const PlaybackRecord& b)
{
    return (*this < b) || (*this == b);
}

bool PlaybackRecord::operator >=(const PlaybackRecord& b)
{
    return (*this > b) || (*this == b);
}

PlaybackRecord::~PlaybackRecord()
{
    // Delete all arrays
    sigVector::Iterator p = signal.begin();
    sigVector::Iterator end = signal.end();

    for(; p != end; ++p)
        ipp_free(p->first);
}
