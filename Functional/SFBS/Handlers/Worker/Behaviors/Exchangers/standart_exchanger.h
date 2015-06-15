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

#ifndef STANDART_EXCHANGER_H
#define STANDART_EXCHANGER_H

#include "exchanger_behavior.h"
#include <QAtomicPointer>
#include <QAtomicInt>

class StandartExchanger : public ExchangerBehavior
{
    Q_OBJECT

public:
    explicit StandartExchanger(QObject *parent = 0);

    Weight behaviorWeight() const;

public slots:
    void setMathModule(MathModule*);
    void setAcceptToStore(bool);

    void receiveData(const ipp_vector<Ipp16s>&);

signals:
    void dataProcessed(ipp_vector<Ipp16s>);
    void dataProcessed(ipp_vector<Ipp32f>);

private:
    QScopedPointer<MathModule> _module;
    bool _current_flag;

};

#endif // STANDART_EXCHANGER_H
