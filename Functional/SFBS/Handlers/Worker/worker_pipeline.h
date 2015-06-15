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

#ifndef WORKER_PIPELINE_H
#define WORKER_PIPELINE_H

#include <QThread>
#include "worker_manager.h"

class WorkerPipeline : public WorkerManager
{
    Q_OBJECT

public:
    explicit WorkerPipeline(QObject *parent = 0);

    void addWorker(WorkerBehavior*);
    void removeWorker(WorkerBehavior*);

    ~WorkerPipeline();

signals:
    void receiveData(const ipp_vector<Ipp16s>&);

private slots:
    void workerDestroyed(QObject*);
    void threadDestroyed(QObject*);

private:
    typedef QList<QThread*> thread_lst;
    typedef QList<WorkerBehavior*> worker_lst;
    typedef QMap<QThread*, quint32> thread_map;
    typedef QMap<WorkerBehavior*, QThread*> worker_map;

    WorkerPipeline(const WorkerPipeline&);
    WorkerPipeline& operator=(const WorkerPipeline&);

    QThread* createThread();

    QScopedPointer<WorkerBehavior> tail;
    WorkerBehavior *head;

    thread_map threads;
    worker_map workers;
    worker_lst workers_line;

    bool transmit_is_permit;

};

#endif // WORKER_PIPELINE_H
