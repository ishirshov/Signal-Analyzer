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

#ifndef SHORT_RANGE_AFC_H
#define SHORT_RANGE_AFC_H

#include "afcDecorator/compute_module.h"
#include "Functional/SFBS/Handlers/Worker/Behaviors/Handlers/handler_behavior.h"

class ShortRangeAfc : public HandlerBehavior
{
    Q_OBJECT

public:
    explicit ShortRangeAfc(ComputeModule *mod, QObject *parent = 0);

    Weight behaviorWeight() const;

    ~ShortRangeAfc();

public slots:
    void setSamplingFrequency(ulong);
    void setAcceptToStore(bool);

    void receiveData(const ipp_vector<Ipp16s>&);

private slots:
    void makeWork();

signals:
    void dataProcessed(ipp_vector<Ipp16s>);
    void dataProcessed(ipp_vector<Ipp32f>);

    void valueChanged(int);

private:
    bool is_accpt_stor;                    // Condition var.
    quint32 buff_sz;                       // Length condition.
    ipp_vector<Ipp32f> sig_data;           // Signal, AFC and Peaks data.

    QScopedPointer<ComputeModule> module;  // Behavior modules.

};

#endif // SHORT_RANGE_AFC_H
