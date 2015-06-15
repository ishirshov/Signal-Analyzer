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

#include "worker_decorator.h"

WorkerDecorator::WorkerDecorator(WorkerBehavior *_worker)
    :worker(_worker)
{
    if(!worker)
        throw std::runtime_error("Can't initialize worker.");
    if(worker == this)
        throw std::runtime_error("Decorator cannot pointed to self-to-self.");

    connect(worker, SIGNAL(dataProcessed(ipp_vector<Ipp16s>)), SIGNAL(dataProcessed(ipp_vector<Ipp16s>)), Qt::DirectConnection);
    connect(worker, SIGNAL(dataProcessed(ipp_vector<Ipp32f>)), SIGNAL(dataProcessed(ipp_vector<Ipp32f>)), Qt::DirectConnection);
    connect(worker, SIGNAL(destroyed()), SLOT(workerDestroyed()), Qt::DirectConnection);
}

WorkerBehavior::Weight WorkerDecorator::behaviorWeight() const
{
    return (worker) ? (worker->behaviorWeight()) : (WorkerBehavior::Empty);
}

WorkerDecorator::~WorkerDecorator()
{
    delete worker;
}

void WorkerDecorator::setAcceptToStore(bool flag)
{
    if(worker)
        worker->setAcceptToStore(flag);
}

void WorkerDecorator::workerDestroyed()
{
    worker = 0;

    QMetaObject::invokeMethod(this, "deleteLater", Qt::QueuedConnection);
}
