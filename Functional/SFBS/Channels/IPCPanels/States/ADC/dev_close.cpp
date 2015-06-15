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

#include "dev_close.h"
#include "Functional/SFBS/Channels/IPCPanels/fpga_panel.h"
#include <stdexcept>

devClose::devClose(FPGAPanel *_panel)
    :panel(_panel)
{
    if(!_panel)
        throw std::runtime_error("Can't initialized panel.");
}

void devClose::sendMessage()
{
    dac_adc_control_ipc_cmd_value_msg_t values;
    values.cmdParamOne = panel->devices->currentIndex();

    fpga_user_ipc_send(panel->user_channel_id,
                       panel->user_task_id,
                       ADC_CMD_CLOSE_DEV,
                       &values,
                       sizeof(dac_adc_control_ipc_cmd_value_msg_t));
}

void devClose::messageReceive(void *msg)
{
    if(!msg) return;

    dac_adc_control_ipc_msg_t *fpga_msg = 0;
    fpga_msg = static_cast<dac_adc_control_ipc_msg_t*>(msg);

    QString warning_title(QObject::tr("Warning"));
    QString warning_text;

    switch (fpga_msg->cmd) {
    case DAC_ADC_IPC_CMD_REPLY:
    {
        dac_adc_control_ipc_reply_msg_t *fpga_reply = 0;
        fpga_reply = (dac_adc_control_ipc_reply_msg_t*)(fpga_msg->data);

        dac_adc_control_ipc_value_for_reply_msg_t *reply_data = 0;
        reply_data = (dac_adc_control_ipc_value_for_reply_msg_t*)(fpga_reply->data);

        if(fpga_reply->for_cmd == ADC_CMD_CLOSE_DEV)
        {
            switch (fpga_reply->status) {
            case REPLY_STATUS_OK:
            {
                if(reply_data->replyParamOne == panel->devices->currentIndex())
                {
                    // Set graphical elements.
                    panel->devices->setEnabled(true);
                    panel->device_control->setText(QObject::tr("Open"));
                    panel->channel_control->setEnabled(false);
                    panel->channels->setEnabled(false);
                    panel->tasks_control->setEnabled(true);
                }
                break;
            }
            case REPLY_STATUS_ERROR:
            {
                QTextStream(&warning_text) << QObject::tr("Can not close device: [ Device: ") << reply_data->replyParamOne << " ]";
                break;
            }
            case REPLY_STATUS_UNKNOWN_CMD:
            {
                QTextStream(&warning_text) << QObject::tr("[ Device don't known cmd: ") << fpga_reply->for_cmd << " ]";
                break;
            }
            default:
                QTextStream(&warning_text) << QObject::tr("[ Unknown reply status: ") << fpga_reply->status
                                           << QObject::tr(" , Cmd: ") << fpga_reply->for_cmd << " ]";
                break;
            }
        }
        else {
            QTextStream(&warning_text) << QObject::tr("Sequence of states are corrupt. [ Cmd: ")
                                       << fpga_reply->for_cmd << QObject::tr(", Status: ") << fpga_reply->status << " ]";
        }

        break;
    }
    default:
        QTextStream(&warning_text) << QObject::tr("Unhandled FPGA message command: ") << fpga_msg->cmd;
        break;
    }

    panel->state = panel->no_state;

    if(warning_text.size())
        QMessageBox::warning(0, warning_title, warning_text);
}
