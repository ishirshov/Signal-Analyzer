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

#ifndef USER_GEN_H
#define USER_GEN_H

#include <QObject>

class UserGenerator : public QObject
{
    Q_OBJECT

public:
    virtual quint32 getBufferSize() const = 0;
    virtual ulong getSamplingFrequency() const = 0;
    virtual qreal getSignalFrequency() const = 0;
    virtual qreal getSignalAmplitude() const = 0;
    virtual qreal getNoiseAmplitude() const = 0;
    virtual qreal getVoltsLevel() const = 0;
    virtual const QString& getName() const = 0;
    virtual const QString& getType() const = 0;

    virtual void started() = 0;
    virtual void finished() = 0;

    virtual void workerStatusChanged(bool) = 0;
    virtual void workerStatusMessage(const QString&) = 0;
    virtual void samplingFrequencyChanged(ulong) = 0;

    virtual ~UserGenerator() {}

public slots:
    virtual void start() = 0;
    virtual void stop() = 0;

};

#endif // USER_GEN_H
