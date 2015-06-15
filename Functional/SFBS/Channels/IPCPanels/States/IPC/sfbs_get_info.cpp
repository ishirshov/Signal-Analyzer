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

#include "sfbs_get_info.h"

#include "Functional/SFBS/Channels/IPCPanels/isomorph_panel.h"


#include <stdexcept>

sfbsGetInfo::sfbsGetInfo(IsomorphPanel *panel)
    :_panel(panel)
    ,_is_exec(false)
{
    if(!_panel)
        throw std::runtime_error("Can't initialized state.");
}

void sfbsGetInfo::sendMessage()
{
    if(!_is_exec) {
        ipc_sfbs_send_msg(_panel->local_channel_id, IPC_CMD_SFBS_GET_INFO, 0, 0);
        _is_exec = true;
    }
}

void sfbsGetInfo::messageReceive(void *msg)
{
    if(!msg) return;

    sfbs_cmd_ipc_msg_t *ipc_msg = 0;
    ipc_msg = reinterpret_cast<sfbs_cmd_ipc_msg_t*>(msg);

    if(!ipc_msg->data_size) {
        printDebug("Data size of reply message is equal to zero");
        return;
    }

    switch(ipc_msg->cmd) {
    case IPC_CMD_SFBS_REPLY:
    {
        sfbs_cmd_reply_msg_data_t *reply = 0;
        reply = reinterpret_cast<sfbs_cmd_reply_msg_data_t*>(ipc_msg->data);

        if(reply->reply_cmd == IPC_CMD_SFBS_GET_INFO)
        {
            bool success = (reply->reply_status && reply->data_size)?(true):(false);

            printDebug(QString("I received device type info message from channel: %1.").arg(_panel->remote_channel_id));

            if(success)
            {
                sfbs_cmd_reply_info_msg_data_t *info = 0;
                info = reinterpret_cast<sfbs_cmd_reply_info_msg_data_t*>(reply->data);

                _panel->changeHighlayerPanel(*info);
                _panel->state = _panel->sfbs_user;

                printDebug(QString("Device type is: %1").arg(info->dev_type));
                _is_exec = false;
            }
            else {
                printDebug("Unfortunately it was corrupt.");
            }            
        }
        else {
            _panel->state = _panel->sfbs_no_state;
            printDebug(QString("Sequence of states are corrupt. [ Cmd: %1, Status: %2, Remote: %3]")
                       .arg(reply->reply_cmd)
                       .arg(reply->reply_status)
                       .arg(_panel->remote_channel_id));
        }

        break;
    }
    case IPC_CMD_SFBS_USER:
    {
        user_ipc_msg_t *user_msg = 0;
        user_msg = reinterpret_cast<user_ipc_msg_t*>(ipc_msg->data);

        if(user_msg->cmd == DSP_IPC_CMD_STATS)
        {
            dsp_ipc_msg_STATS_t *stats = reinterpret_cast<dsp_ipc_msg_STATS_t*>(user_msg->data);

            printInfo(QString("[Rx buff: %1] [Tx buff: %2] "
                              "[Rx spd: %3] [Tx spd: %4] "
                              "[Rx err: %5] [Tx err: %6]")
                      .arg(stats->rx_buffers)
                      .arg(stats->tx_buffers)
                      .arg(stats->rx_speed)
                      .arg(stats->tx_speed)
                      .arg(stats->rx_errors)
                      .arg(stats->tx_errors));
        }
        else {
            printDebug(QString("I received sfbs user command [ %1 ]").arg(user_msg->cmd));
        }
        break;
    }
    default:
        printDebug(QString("Unhandled IPC message command: %1.").arg(ipc_msg->cmd));
        break;
    }

    if(libsfbs_ch_buffer_release(_panel->remote_channel_id, ipc_msg) != SFBS_SUCCESS)
        throw std::runtime_error(toConstChar(QString("Can't release ipc buffer for channel: %1.").arg(_panel->remote_channel_id)));
}
