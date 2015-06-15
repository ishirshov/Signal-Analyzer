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

#ifndef WORKER_DECORATOR_H
#define WORKER_DECORATOR_H

#include "Functional/SFBS/Handlers/Worker/Behaviors/worker_behavior.h"

class WorkerDecorator : public WorkerBehavior
{
    Q_OBJECT

protected:
    WorkerBehavior *worker;

public:
    explicit WorkerDecorator(WorkerBehavior *_behavior);

    Weight behaviorWeight() const;

    virtual ~WorkerDecorator();

signals:
    void dataProcessed(ipp_vector<Ipp16s>);
    void dataProcessed(ipp_vector<Ipp32f>);
    void transmitData(ipp_vector<Ipp16s>);

public slots:
    void setAcceptToStore(bool flag);

private slots:
    void workerDestroyed();

};

#endif // WORKER_DECORATOR_H
