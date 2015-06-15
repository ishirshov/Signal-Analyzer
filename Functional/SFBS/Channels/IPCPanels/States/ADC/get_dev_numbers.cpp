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

#include "get_dev_numbers.h"
#include "Functional/SFBS/Channels/IPCPanels/fpga_panel.h"
#include <stdexcept>

getDevNumbers::getDevNumbers(FPGAPanel *_panel)
    :panel(_panel)
{
    if(!_panel)
        throw std::runtime_error("Can't initialized panel.");
}

void getDevNumbers::sendMessage()
{
    fpga_user_ipc_send(panel->user_channel_id,
                       panel->user_task_id,
                       ADC_CMD_GET_DEV_NUMBERS, 0, 0);
}

void getDevNumbers::messageReceive(void *msg)
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

        if(fpga_reply->for_cmd == ADC_CMD_GET_DEV_NUMBERS)
        {
            switch (fpga_reply->status) {
            case REPLY_STATUS_OK:
            {
                for(int i = 0; i < reply_data->replyParamOne; ++i)
                    panel->devices->addItem(QString("%1").arg(i), i);

                panel->state = panel->get_ch_per_one_dev;
                break;
            }
            case REPLY_STATUS_ERROR:
            {
                QTextStream(&warning_text) << QObject::tr("[ Device can not give device numbers. ]");

                panel->state = panel->no_state;
                break;
            }
            case REPLY_STATUS_UNKNOWN_CMD:
            {
                QTextStream(&warning_text) << QObject::tr("[ Device don't known cmd: ") << fpga_reply->for_cmd << " ]";

                panel->state = panel->no_state;
                break;
            }
            default:
                QTextStream(&warning_text) << QObject::tr("[ Unknown reply status: ") << fpga_reply->status
                                           << QObject::tr(" , Cmd: ") << fpga_reply->for_cmd << " ]";

                panel->state = panel->no_state;
                break;
            }
        }
        else {
            QTextStream(&warning_text) << QObject::tr("Sequence of states are corrupt. [ Cmd: ")
                                       << fpga_reply->for_cmd << QObject::tr(", Status: ") << fpga_reply->status << " ]";

            panel->state = panel->no_state;
        }

        break;
    }
    default:
        QTextStream(&warning_text) << QObject::tr("Unhandled FPGA message command: ") << fpga_msg->cmd;

        panel->state = panel->no_state;
        break;
    }

    if(warning_text.size())
        QMessageBox::warning(0, warning_title, warning_text);
}
