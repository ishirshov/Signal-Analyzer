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

#include "playback_exchanger.h"

#include <QStringList>
#include <QProcess>

PlaybackExchanger::PlaybackExchanger(QObject *parent)
    :is_accpt_stor(false)
    ,is_end_mem(false)
    ,current_record(0)
    ,avail_mem(2048)
    ,used_mem(0.0)
{
    // Init main settings
    setParent(parent);
    long free_mem = memFree();

    if(free_mem == 0)
        is_end_mem = true;
    if(free_mem < avail_mem)
        avail_mem = free_mem;
}

PlaybackExchanger::Weight PlaybackExchanger::behaviorWeight() const
{
    return WorkerBehavior::Heavy;
}

long PlaybackExchanger::availableMemory() const
{
    return avail_mem;
}

PlaybackExchanger::~PlaybackExchanger()
{
    is_accpt_stor = false;

    emit blockSamplingFrequency(false);
    emit recordsListChanged(QStringList());

    record_iter pos = records.begin();
    record_iter end = records.end();

    for(; pos != end; ++pos)
        delete *pos;
}

void PlaybackExchanger::setMathModule(MathModule *_p)
{
    if(_p) delete _p;
}

void PlaybackExchanger::setAcceptToStore(bool /*flag*/)
{
}

void PlaybackExchanger::setAcceptToStore(bool flag, ulong samplingf)
{
    if(is_end_mem) return;

    is_accpt_stor = flag;

    if(flag)
    {
        records.append(new PlaybackRecord(samplingf));
        current_record = records.back();

        connect(current_record, SIGNAL(maximumValueChanged(int)), this, SIGNAL(maxWorkValueChanged(int)));
        connect(current_record, SIGNAL(minimumValueChanged(int)), this, SIGNAL(minWorkValueChanged(int)));
        connect(current_record, SIGNAL(progressValueChanged(int)), this, SIGNAL(workValueChanged(int)));

        emit blockSamplingFrequency(true);
    }
    else {
        current_record = 0;
        createRecordList();

        emit blockSamplingFrequency(false);
    }
}

void PlaybackExchanger::receiveData(const ipp_vector<Ipp16s> &data)
{
    if(!is_accpt_stor || is_end_mem) return;

    if(current_record)
    {
        current_record->appendData(data);
        used_mem += (data.size() * sizeof(Ipp16s))/1024.0/1024.0;

        checkUsedMemory();
    }
}

void PlaybackExchanger::requestData(const QString &name, PlaybackSettings *_p)
{
    QScopedPointer<PlaybackSettings> clean_up(_p);

    if(name.isEmpty()) return;

    record_iter pos = records.begin();
    record_iter end = records.end();

    for(; pos != end; ++pos) {
        PlaybackRecord *record = *pos;

        if(record->name() == name) {
            emit dataProcessed(record->prepareVector(clean_up.take()));
            break;
        }
    }
}

void PlaybackExchanger::removeData(const QString &name)
{
    if(name.isEmpty()) return;

    record_iter pos = records.begin();
    record_iter end = records.end();

    for(; pos != end; ++pos) {
        PlaybackRecord *record = *pos;

        if(record->name() == name) {
            used_mem -= record->sizeMb();
            records.removeOne(record);
            delete record;

            checkUsedMemory();
            createRecordList();
            break;
        }
    }
}

void PlaybackExchanger::dumpData(const QString &name)
{
    if(name.isEmpty()) return;

    record_iter pos = records.begin();
    record_iter end = records.end();

    for(; pos != end; ++pos) {
        PlaybackRecord *record = *pos;

        if(record->name() == name) {
            record->dumpToFile();
            break;
        }
    }
}

void PlaybackExchanger::createRecordList()
{
    QStringList names;

    record_iter pos = records.begin();
    record_iter end = records.end();

    for(; pos != end; ++pos) {
        PlaybackRecord *record = *pos;

        if(record->size() > 0 && record != current_record)
            names.push_back(record->name());
    }

    emit recordsListChanged(names);
}

void PlaybackExchanger::checkUsedMemory()
{
    emit spaceValueChanged(std::ceil(used_mem));

    if(used_mem >= avail_mem) {
        is_end_mem = true;
        is_accpt_stor = false;

        current_record = 0;
        createRecordList();

        emit blockSamplingFrequency(false);
    }
    else {
        is_end_mem = false;
    }
}
