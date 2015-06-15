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

#ifndef WORKER_BEHAVIOR_H
#define WORKER_BEHAVIOR_H

#include <QObject>
#include "Functional/IPP/additional.h"

class WorkerBehavior : public QObject
{
    Q_OBJECT

public:
    enum Weight
    {
        Heavy,      // Need separate thread for calculate this task
        Light,      // Сan work with the rest of behaviors in one thread
        Empty       // If behavior not consist calculate task
    };

    // Is the prototype for the signal function.
    virtual void dataProcessed(ipp_vector<Ipp16s>) = 0;
    virtual void dataProcessed(ipp_vector<Ipp32f>) = 0;

    virtual Weight behaviorWeight() const = 0;

    virtual ~WorkerBehavior() { }

public slots:
    virtual void setAcceptToStore(bool) = 0;

    virtual void receiveData(const ipp_vector<Ipp16s>&) = 0;

};

#endif // WORKER_BEHAVIOR_H
