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

#ifndef ISOMORPH_PANEL_H
#define ISOMORPH_PANEL_H

#include "Functional/SFBS/Channels/Interfaces/ipc_panel.h"
#include "Functional/SFBS/Channels/Interfaces/ipc_state.h"
#include <QFrame>

class IsomorphPanel : public QFrame
{
    Q_OBJECT

public:
    typedef QSharedPointer<IPCState> state_t;

    explicit IsomorphPanel(QWidget *parent = 0);

    QString getPanelName() const { return name; }
    QString getDeviceType() const { return (panel) ? (panel->getPanelType()) : (QString()); }
    qint32 getRemoteTaskID() const { return remote_task_id; }
    qint32 getRemoteChannelID() const { return remote_channel_id; }

    void initIPC(quint32 ltid, quint32 rtid);

    ~IsomorphPanel();

signals:
    void ipcDataReceive(void *);

private slots:
    void doUserIPC();
    void handleEventData(libsfbs_event_data_t event);

private:
    void changeHighlayerPanel(sfbs_cmd_reply_info_msg_data_t info);

    // Highlayer panel
    IPCPanel *panel;

    // Flag of work
    QString name;
    bool is_work;

    // ID's of this program
    quint32 local_task_id;
    quint32 local_channel_id;

    // Remote ID's of devices
    quint32 remote_task_id;
    quint32 remote_channel_id;

    // Will be friends
    friend class sfbsGetInfo;
    friend class sfbsHello;
    friend class sfbsNoState;
    friend class sfbsUser;

    state_t state;
    // Local state for SFBS IPC
    state_t sfbs_hello;
    state_t sfbs_get_info;
    state_t sfbs_user;
    state_t sfbs_no_state;

};

#endif // ISOMORPH_PANEL_H
