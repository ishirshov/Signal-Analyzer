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

#ifndef PURGING_H
#define PURGING_H

#include "Functional/SFBS/Handlers/Worker/Behaviors/worker_decorator.h"

class purgingDecorator : public WorkerDecorator
{
    Q_OBJECT

public:
    explicit purgingDecorator(WorkerBehavior *worker)
        :WorkerDecorator(worker) { }

    void receiveData(const ipp_vector<Ipp16s> &_data)
    {
        QMetaObject::invokeMethod(worker, "receiveData",
                                          Qt::DirectConnection,
                                          Q_ARG(ipp_vector<Ipp16s>, _data));
    }

};

#endif // PURGING_H
