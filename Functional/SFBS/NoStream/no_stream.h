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

#ifndef NOSTREAM_H
#define NOSTREAM_H

#include "empty_panel.h"
#include "Functional/SFBS/stream_device.h"

class NoStream : public StreamDevice
{
    Q_OBJECT

public:
    explicit NoStream(QObject *parent = 0);

    // Read functions:
    QStringList getDeviceList() const;
    QString getDeviceType() const;

signals:
    // Notifications:
    void statusChanged(bool flag);
    void statusMessage(const QString &msg);
    void widgetChanged(QWidget *, const QString&);

    // Modificators:
    void setDeviceName(const QString &name);

};

#endif // NOSTREAM_H
