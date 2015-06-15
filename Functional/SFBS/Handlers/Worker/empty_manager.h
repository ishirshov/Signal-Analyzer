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

#ifndef EMPTY_MANAGER_H
#define EMPTY_MANAGER_H

#include "worker_manager.h"

class EmptyManager : public WorkerManager
{
    Q_OBJECT

public:
    explicit EmptyManager(QObject *parent = 0) { setParent(parent); }

    void addWorker(WorkerBehavior *worker) { workers.append(worker); }
    void removeWorker(WorkerBehavior *worker) { workers.removeAll(worker); }

signals:
    void receiveData(const ipp_vector<Ipp16s> &);

public slots:
    void setRejectData(bool) { }

private slots:
    void workerDestroyed(QObject *) { }
    void threadDestroyed(QObject *) { }

private:
    QList<WorkerBehavior*> workers;

};

#endif // EMPTY_MANAGER_H
