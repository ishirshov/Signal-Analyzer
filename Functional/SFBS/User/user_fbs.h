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

#ifndef USER_FBS_H
#define USER_FBS_H

#include "Interface/user_gen.h"
#include "Interface/user_ipc_panel.h"
#include "Functional/SFBS/stream_device.h"

class UserStream : public StreamDevice
{
    Q_OBJECT

public:
    explicit UserStream(QObject *parent = 0);

    // Read functions:
    QStringList getDeviceList() const;
    QString getDeviceType() const;

    ~UserStream();

signals:
    // Manipulations:
    void startStream();
    void stopStream();

    // Notifications:
    void statusChanged(bool);
    void statusMessage(const QString&);
    void widgetChanged(QWidget*, const QString&);

public slots:
    void setDeviceName(const QString&);

private slots:
    void deleteLastPanel();

private:
    UserStream(const UserStream&);
    UserStream& operator=(const UserStream&);

    UserGenerator *_userGenerator;
    QThread *_genThread;
    bool _ipcpanel_created;

};

#endif // USER_FBS_H
