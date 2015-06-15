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

#include "isomorph_panel.h"
#include "dsp_gen_panel.h"
#include "dsp_multi_panel.h"
#include "fpga_panel.h"
#include "no_panel.h"

#include "States/ipc_states.h"
#include "Functional/SFBS/Channels/Observer/event_bridge.h"
#include "Functional/SFBS/Channels/Observer/thread_bridge_rx.h"

#include <sfb_stream/libsfbs.h>

#include <QTimer>
#include <QLayout>

IsomorphPanel::IsomorphPanel(QWidget *parent)
    :QFrame(parent)
    ,panel(0)
    ,is_work(false)
    ,local_task_id(0)
    ,local_channel_id(0)
    ,remote_task_id(0)
    ,remote_channel_id(0)
{
    // Initialize state machine for this panel
    sfbs_get_info = state_t(new sfbsGetInfo(this));
    sfbs_hello = state_t(new sfbsHello(this));
    sfbs_user = state_t(new sfbsUser(this));
    sfbs_no_state = state_t(new sfbsNoState(this));
    state = sfbs_hello;

    // Initialization of frame
    setLayout(new QVBoxLayout(this));
    setFrameStyle(QFrame::Panel | QFrame::Raised);

    changeHighlayerPanel(sfbs_cmd_reply_info_msg_data_t());

    // Create connect
    connect(&EventBridge::getInstance(), SIGNAL(emitEventData(libsfbs_event_data_t)), SLOT(handleEventData(libsfbs_event_data_t)), Qt::QueuedConnection);
}

void IsomorphPanel::initIPC(quint32 ltid, quint32 rtid)
{
    local_task_id = ltid;
    remote_task_id = rtid;

    // Request a free channel id.
    if((local_channel_id = libsfbs_ch_request_id()) == SFBS_FALSE)
        throw std::runtime_error(toConstChar("Can not get ID of channel."));

    // Try create channel.
    QString ch_name = QString("fft_ipc_%1").arg(local_channel_id);
    if(libsfbs_ch_create(local_channel_id, local_task_id, SFBS_CH_TYPE_BUFFER, SFBS_CH_OPT_DEFAULT, toConstChar(ch_name)) != SFBS_SUCCESS)
        throw std::runtime_error(toConstChar("Can not create channel" + ch_name));

    // Try attach to channel.
    if(libsfbs_ch_attach(local_channel_id, remote_task_id) != SFBS_SUCCESS)
        throw std::runtime_error("Can not attach to channel");

    name = QString("IPC %1").arg(remote_task_id);
    state->sendMessage();
}

void IsomorphPanel::doUserIPC()
{
    if(is_work)
    {
        libsfbs_status_t status = SFBS_SUCCESS;
        void *ipc_msg = 0;
        quint32 size = 0;

        status = libsfbs_ch_buffer_receive(remote_channel_id, &ipc_msg, &size, SFBS_NO_WAIT);

        if(status == SFBS_SUCCESS)
        {
            state->messageReceive(ipc_msg);
            state->sendMessage();
        }
        else if(status == SFBS_NO_CHANNEL)
        {
            remote_channel_id = 0;
            is_work = false;
        }

        QTimer::singleShot(100, this, SLOT(doUserIPC()));
    }
}

void IsomorphPanel::handleEventData(libsfbs_event_data_t event)
{
    libsfbs_ch_info_t ch_info;
    libsfbs_status_t status = libsfbs_ch_get_info(event.channel_id, &ch_info);

    if(status == SFBS_SUCCESS)
    {
        switch (event.event_id)
        {
        case SFBS_EVT_CH_ATTACHED:
        {
            if(ch_info.type == SFBS_CH_TYPE_BUFFER)
            {
                if((event.task_id == local_task_id) & (ch_info.owner_task_id == remote_task_id))
                {
                    remote_channel_id = event.channel_id;
                    is_work = true;

                    QMetaObject::invokeMethod(this, "doUserIPC", Qt::QueuedConnection);

                    printDebug(QString("BUFFER: ") + eventEnumToString(event.event_id, event.task_id, event.channel_id));
                }
            }
            else if(ch_info.type == SFBS_CH_TYPE_STREAM)
            {
                if((event.task_id == local_task_id) & (ch_info.owner_task_id == remote_task_id))
                {
                    // FIXME: ThreadRxBridge::getInstance().setRemoteChannelID(event.channel_id);

                    printDebug(QString("STREAM: ") + eventEnumToString(event.event_id, event.task_id, event.channel_id));
                }
            }
            break;
        }
        case SFBS_EVT_CH_DETACHED:
        {
            if(ch_info.type == SFBS_CH_TYPE_BUFFER)
            {
                if((event.task_id == remote_task_id) & (event.channel_id == local_channel_id))
                {
                    remote_task_id = remote_channel_id = 0;
                    state = sfbs_hello;
                    is_work = false;

                    changeHighlayerPanel(sfbs_cmd_reply_info_msg_data_t());

                    printDebug(QString("BUFFER: ") + eventEnumToString(event.event_id, event.task_id, event.channel_id));
                }
            }
            else if(ch_info.type == SFBS_CH_TYPE_STREAM)
            {
                if(event.task_id == local_task_id)
                {
                    // FIXME: ThreadRxBridge::getInstance().setRemoteChannelID(0);

                    printDebug(QString("STREAM: ") + eventEnumToString(event.event_id, event.task_id, event.channel_id));
                }
            }
            break;
        }
        default:
            printException(eventEnumToString(event.event_id, event.task_id, event.channel_id));
            break;
        };
    }
    else printDebug(QString("Command 'libsfbs_ch_get_type()' executed with status: %1").arg(status));
}

void IsomorphPanel::changeHighlayerPanel(sfbs_cmd_reply_info_msg_data_t info)
{
    // Disables all activities
    if(panel) panel->setEnabled(is_work);

    // Detach old panel from panel
    QLayout *layout = this->layout();
    if(panel) layout->removeWidget(panel);

    // Destroy and create empty panel (stub)
    delete panel;

    // Fabric method
    switch(info.dev_type)
    {
    case DEV_TYPE_DSP:
        if(info.service_type == SERVICE_TYPE_SG)
            panel = new DSPGenPanel(this);
        else
            panel = new DSPMultiPanel(this);
        break;
    case DEV_TYPE_FPGA:
        panel = new FPGAPanel(this);
        connect((FPGAPanel*)panel, SIGNAL(rampStreamTypeDetect(bool)), &GlobalVariables::getInstance(), SIGNAL(rampSignalStyleDetected(bool)));
        break;
    default:
        panel = new NoPanel(this);
        break;
    };

    connect(panel, SIGNAL(voltsLevelChanged(float)), &GlobalVariables::getInstance(), SLOT(setVoltsLevel(float)));
    connect(panel, SIGNAL(samplingFrequencyChanged(ulong)), &GlobalVariables::getInstance(), SLOT(setSamplingFrequency(ulong)));
    connect(&GlobalVariables::getInstance(), SIGNAL(blockSamplingFrequencyChanged(bool)), panel, SLOT(blockSamplingFrequency(bool)));
    connect(this, SIGNAL(ipcDataReceive(void*)), panel, SLOT(ipcDataHandle(void*)));

    panel->ipcInit(local_channel_id, local_task_id, remote_channel_id, remote_task_id);
    layout->addWidget(panel);
}

IsomorphPanel::~IsomorphPanel()
{
    is_work = false;

    if(remote_task_id && local_channel_id)
    {
        if(libsfbs_ch_detach(local_channel_id, remote_task_id) != SFBS_SUCCESS)
            printDebug("Can't detach from channel");
        remote_task_id = 0;
    }

    if(local_channel_id)
    {
        if(libsfbs_ch_destroy(local_channel_id) != SFBS_SUCCESS)
            printDebug("Can't destroy channel");
        local_channel_id = 0;
    }
}
