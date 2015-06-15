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

#include "worker_pipeline.h"
#include "Behaviors/decorators.h"
#include "Behaviors/Handlers/empty_handler.h"

WorkerPipeline::WorkerPipeline(QObject *parent)
    :tail(new purgingDecorator(new EmptyHandler))
    ,head(tail.data())
    ,transmit_is_permit(true)
{
    setParent(parent);
}

void WorkerPipeline::addWorker(WorkerBehavior *worker)
{
    if(!worker || (worker && workers.contains(worker))) return;

    transmit_is_permit = false;
    QThread *_thread = 0;

    switch(worker->behaviorWeight())
    {
    case WorkerBehavior::Heavy:
    {
        _thread = createThread();
        connect(worker, SIGNAL(destroyed()), _thread, SLOT(quit()));

        break;
    }
    case WorkerBehavior::Light:
    {
        thread_map::ConstIterator p = threads.begin();
        thread_map::ConstIterator end = threads.end();
        qint32 num_workers = 0;

        for(; p != end; ++p)
        {
            num_workers = p.value();
            if(num_workers < 2)
            {
                _thread = p.key();
                break;
            }
        }

        if(!_thread) {
            _thread = createThread();
            num_workers = 0;
        }

        threads[_thread] = num_workers + 1;
        break;
    }
    default:
        if(worker->behaviorWeight())
            printException("Empty behavior not permit in this manager.");
        else
            printException("Unknown behavior weight.");
        transmit_is_permit = true;
        return;
    };

    // Move worker to worker decorator
    worker = new forwadingDecorator(worker);
    worker->moveToThread(_thread);

    // Create SLOT/SIGNAL channel
    // and insert current worker to head
    // of pipeline
    disconnect(this, SIGNAL(receiveData(ipp_vector<Ipp16s>)), 0, 0);
    connect(worker, SIGNAL(transmitData(ipp_vector<Ipp16s>)), head, SLOT(receiveData(ipp_vector<Ipp16s>)), Qt::QueuedConnection);
    connect(worker, SIGNAL(destroyed(QObject*)), SLOT(workerDestroyed(QObject*)), Qt::DirectConnection);
    connect(_thread, SIGNAL(finished()), worker, SLOT(deleteLater()), Qt::QueuedConnection);

    // Append previous head to line
    workers_line.prepend(head);
    head = worker;
    connect(this, SIGNAL(receiveData(ipp_vector<Ipp16s>)), head, SLOT(receiveData(ipp_vector<Ipp16s>)), Qt::QueuedConnection);

    // Register decorator and his thread
    workers[worker] = _thread;
    transmit_is_permit = true;
}

void WorkerPipeline::removeWorker(WorkerBehavior *worker)
{
    if(!worker || (worker && !workers.contains(worker))) return;

    transmit_is_permit = false;

    // Send destroy signal to worker in other thread
    QMetaObject::invokeMethod(worker, "deleteLater", Qt::QueuedConnection);

    transmit_is_permit = true;
}

WorkerPipeline::~WorkerPipeline()
{
    transmit_is_permit = false;

    while(!threads.empty())
    {
        QThread *_thread = threads.constBegin().key();

        // Tell to thread abort all operations
        _thread->quit();

        if(!_thread->wait(500))
        {
            // May be thread in deadlock
            _thread->terminate();
            _thread->wait();
        }

        threads.remove(_thread);
    }

    while(!workers.empty())
        delete workers.constBegin().key();
}

void WorkerPipeline::workerDestroyed(QObject *o)
{
    if(!o) return;    

    transmit_is_permit = false;
    WorkerBehavior *worker = static_cast<WorkerBehavior*>(o);

    if(!workers_line.empty())
    {
        if(worker == head) {
            head = workers_line.front();
            workers_line.pop_front();
        }
        else {
            const int i = workers_line.indexOf(worker);

            WorkerBehavior *prev_worker = (i == 0) ? (head) : (workers_line.at(i - 1));
            WorkerBehavior *next_worker = workers_line.at(i + 1);
            workers_line.removeOne(worker);

            connect(prev_worker, SIGNAL(transmitData(ipp_vector<Ipp16s>)), next_worker, SLOT(receiveData(ipp_vector<Ipp16s>)), Qt::QueuedConnection);
        }

        disconnect(this, SIGNAL(receiveData(ipp_vector<Ipp16s>)), 0, 0);
        connect(this, SIGNAL(receiveData(ipp_vector<Ipp16s>)), head, SLOT(receiveData(ipp_vector<Ipp16s>)), Qt::QueuedConnection);
    }

    QThread* _thread = workers[worker];
    workers.remove(worker);

    // If thread is empty
    if(threads.contains(_thread)) {
        if((--threads[_thread]) == 0) {
            _thread->quit();
            threads.remove(_thread);
        }
    }

    transmit_is_permit = true;

    printDebug(QString("Worker 0x%1 was destroyed!").arg((quintptr)worker, QT_POINTER_SIZE, 16, QChar('0')));
}

void WorkerPipeline::threadDestroyed(QObject *o)
{
    if(!o) return;

    transmit_is_permit = false;

    QThread *_thread = static_cast<QThread*>(o);
    threads.remove(_thread);

    transmit_is_permit = true;

    printDebug(QString("Thread 0x%1 was destroyed!").arg((quintptr)_thread, QT_POINTER_SIZE, 16, QChar('0')));
}

QThread* WorkerPipeline::createThread()
{
    QScopedPointer<QThread> new_thread(new QThread(this));
    new_thread->start();

    // Destroy rule for threads
    connect(new_thread.data(), SIGNAL(finished()), new_thread.data(), SLOT(deleteLater()), Qt::UniqueConnection);
    connect(new_thread.data(), SIGNAL(destroyed(QObject*)), SLOT(threadDestroyed(QObject*)), Qt::DirectConnection);

    return new_thread.take();
}
