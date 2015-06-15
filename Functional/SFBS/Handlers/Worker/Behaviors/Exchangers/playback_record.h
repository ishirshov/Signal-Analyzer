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

#ifndef PLAYBACK_RECORD_H
#define PLAYBACK_RECORD_H

#include "settings.h"
#include "Functional/IPP/additional.h"

class PlaybackRecord : public QObject
{
    Q_OBJECT

public:
    typedef QPair<Ipp16s*, quint32> sigArray;
    typedef QVector<sigArray> sigVector;

    explicit PlaybackRecord(ulong sampling_frequency);

    void appendData(const ipp_vector<Ipp16s>&);
    void dumpToFile();

    QVector<QPointF> *prepareVector(PlaybackSettings*);
    QString fileName() const { return time_stamp.toString("HH_mm_ss"); }
    qreal duration() const { return qreal(_size)/qreal(sampling_freq); }
    ulong size() const { return _size; }
    qreal sizeMb() const { return (_size * sizeof(Ipp16s))/1024.0/1024.0; }
    QString name() const { return time_stamp.toString("HH:mm:ss"); }

    bool operator==(const PlaybackRecord &b);
    bool operator!=(const PlaybackRecord &b);
    bool operator<(const PlaybackRecord &b);
    bool operator>(const PlaybackRecord &b);
    bool operator<=(const PlaybackRecord &b);
    bool operator>=(const PlaybackRecord &b);

    ~PlaybackRecord();

signals:
    void progressValueChanged(int);
    void minimumValueChanged(int);
    void maximumValueChanged(int);

private:
    // Scale settings for prepare vector
    ulong sampling_freq;
    ulong _size;

    // Main graphic data (multidim)
    sigVector signal;

    // Time info
    QTime time_stamp;

};

inline void PlaybackRecord::appendData(const ipp_vector<Ipp16s> &_data)
{
    quint32 size = signal.size();

    signal.push_back(sigArray(_data.to_pointer(), size));
    _size += size;
}

#endif // PLAYBACK_RECORD_H
