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

#include "sfbs_channels.h"

#include "IPCPanels/isomorph_panel.h"
#include "Observer/event_bridge.h"
#include "Observer/thread_bridge_rx.h"

#include <QTimer>
#include <QRegExp>

SFBSChannels::SFBSChannels(QObject *parent)
    :local_task_id(0)
{
    // Setup parent for this object
    setParent(parent);

    QString message;
    QTextStream stream(&message);

    // Initialize stream library.
    if(libsfbs_init(SFBS_INIT_DEFAULT, SFBS_DEFAULT_CONFIG) != SFBS_SUCCESS)
    {
        stream << tr("Can not initialize library.");
        throw std::runtime_error(toConstChar(message));
    }

    // Request a free task id.
    if((local_task_id = libsfbs_task_request_id()) == SFBS_FALSE)
    {
        stream << tr("Can not get ID of task.");
        throw std::runtime_error(toConstChar(message));
    }

    // Try create task.
    if(libsfbs_task_create(local_task_id, SFBS_TASK_TYPE_USER, SFBS_TASK_OPT_RTPR, 0) != SFBS_SUCCESS)
    {
        stream << tr("Can not create task with ID ") << local_task_id << '.';
        throw std::runtime_error(toConstChar(message));
    }

    // Get list of tasks.
    libsfbs_task_info_t *tasks_list = 0;
    quint32 list_size = 0;

    if(libsfbs_task_get_list(&tasks_list, &list_size) != SFBS_SUCCESS)
    {
        stream << tr("Can not get tasks list.");
        throw std::runtime_error(toConstChar(message));
    }

    for(int i = 0; i < list_size; ++i)
        if(tasks_list[i].type == SFBS_TASK_TYPE_MASTER)
            task_list[QString("%1 (%2)").arg(tasks_list[i].id).arg(tasks_list[i].name)] = tasks_list[i];

    libsfbs_task_free_list(tasks_list);

    // Register RX callback function.
    if(libsfbs_task_set_rx_callback(local_task_id, threadRxCallback) != SFBS_SUCCESS)
    {
        stream << tr("Can not register RX callback function.");
        throw std::runtime_error(toConstChar(message));
    }

    // Register event handler.
    libsfbs_set_event_callback(eventCallback);

    // Set buffer size for stream.
    GlobalVariables::getInstance().setBufferSize(libsfbs_get_queue_buffer_size()/sizeof(Ipp16s));
}

QStringList SFBSChannels::getDeviceList() const
{
    QStringList devices(task_list.keys());

    if(!devices.size())
        devices.push_back(QObject::tr("No device"));

    return devices;
}

QString SFBSChannels::getDeviceType() const
{
    // FIXME: Hardcode
    return "FPGA";
}

void SFBSChannels::setDeviceName(const QString &dev)
{
    if(task_list.contains(dev))
    {
        QRegExp rx("(\\d+).");
        int pos = rx.indexIn(dev);

        if(pos > -1)
        {
            IsomorphPanel *panel = new IsomorphPanel;
            panel->initIPC(local_task_id, rx.cap(1).toInt());

            emit widgetChanged(panel, panel->getPanelName());
        }
    }
}

SFBSChannels::~SFBSChannels()
{
    if(local_task_id)
        libsfbs_task_destroy(local_task_id);

    libsfbs_cleanup();
}
