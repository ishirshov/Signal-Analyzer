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

#include "short_range_afc.h"

ShortRangeAfc::ShortRangeAfc(ComputeModule *_mod, QObject *parent)
    :is_accpt_stor(true)
    ,buff_sz(131072)
    ,module(_mod)
{
    if(!_mod)
        throw std::runtime_error("Can't initialize compute module.");

    connect(_mod, SIGNAL(dataProcessed(ipp_vector<Ipp32f>)), SIGNAL(dataProcessed(ipp_vector<Ipp32f>)), Qt::QueuedConnection);

    // When object are replace to different thread he cannot have parent.
    setParent(parent);
}

ShortRangeAfc::Weight ShortRangeAfc::behaviorWeight() const
{
    return Light;
}

ShortRangeAfc::~ShortRangeAfc()
{
    is_accpt_stor = false;
}

void ShortRangeAfc::setSamplingFrequency(ulong /*val*/)
{
}

void ShortRangeAfc::setAcceptToStore(bool val)
{
    is_accpt_stor = val;
}

void ShortRangeAfc::receiveData(const ipp_vector<Ipp16s> &segment)
{
    if(segment.empty() || !is_accpt_stor) return;

    qint32 size = segment.size();
    qint32 lastPosition = sig_data.size();

    if(lastPosition < buff_sz)
    {
        if((lastPosition + size) > buff_sz)
            size = buff_sz - lastPosition;

        sig_data.push_back(segment, size);
    }

    if((sig_data.size() == buff_sz) && is_accpt_stor) {
        is_accpt_stor = false;
        QMetaObject::invokeMethod(this, "makeWork", Qt::QueuedConnection);
    }
}

void ShortRangeAfc::makeWork()
{
    // The compute module will emit the
    // signal of the end of processing.
    module->handleData(sig_data);
    sig_data.clear();
}
