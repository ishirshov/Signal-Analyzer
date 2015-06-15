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

#ifndef WORKER_MANAGER_H
#define WORKER_MANAGER_H

#include "Behaviors/worker_behavior.h"

class WorkerManager : public QObject
{
    Q_OBJECT

public:
    enum Type
    {
        Pipeline,
        Multiplier,
        Empty
    };

    virtual void addWorker(WorkerBehavior *) = 0;
    virtual void removeWorker(WorkerBehavior *) = 0;
    virtual void receiveData(const ipp_vector<Ipp16s>&) = 0;

    virtual ~WorkerManager() { }

protected slots:
    virtual void workerDestroyed(QObject *) = 0;
    virtual void threadDestroyed(QObject *) = 0;

};

#endif // WORKER_MANAGER_H
