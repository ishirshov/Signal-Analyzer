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

#ifndef PLAYBACK_EXCHANGER_H
#define PLAYBACK_EXCHANGER_H

#include "exchanger_behavior.h"
#include "playback_record.h"

class PlaybackExchanger : public ExchangerBehavior
{
    Q_OBJECT

public:    
    typedef QList<PlaybackRecord*>::Iterator record_iter;

    explicit PlaybackExchanger(QObject *parent = 0);

    Weight behaviorWeight() const;
    long availableMemory() const;

    ~PlaybackExchanger();

public slots:
    void setMathModule(MathModule *);  // unused slot
    void setAcceptToStore(bool);       // unused slot
    void setAcceptToStore(bool, ulong);

    void receiveData(const ipp_vector<Ipp16s>&);
    void requestData(const QString& record, PlaybackSettings*);
    void removeData(const QString& record);
    void dumpData(const QString& record);

signals:
    void spaceValueChanged(int);
    void workValueChanged(int);
    void maxWorkValueChanged(int);
    void minWorkValueChanged(int);

    void recordsListChanged(const QStringList&);
    void blockSamplingFrequency(bool);

    void dataProcessed(QVector<QPointF>*);
    // unused signals
    void dataProcessed(ipp_vector<Ipp16s>);
    void dataProcessed(ipp_vector<Ipp32f>);

private:    
    void createRecordList();
    void checkUsedMemory();

    // All records in linked-list
    QList<PlaybackRecord*> records;
    PlaybackRecord *current_record;

    bool is_accpt_stor;
    bool is_end_mem;
    long avail_mem;
    qreal used_mem;

};

#endif // PLAYBACK_EXCHANGER_H
