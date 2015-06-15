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

#include "set_stream_format.h"
#include "Functional/SFBS/Channels/IPCPanels/fpga_panel.h"
#include "Functional/IPP/additional.h"

#include <stdexcept>

setStreamFormat::setStreamFormat(FPGAPanel *_panel)
    :panel(_panel)
{
    if(!_panel)
        throw std::runtime_error("Can't initialized panel.");
}

void setStreamFormat::sendMessage()
{
    dac_adc_control_ipc_cmd_value_msg_t values;
    values.cmdParamOne = panel->devices->currentIndex();
    values.cmdParamTwo = 0;

    fpga_user_ipc_send(panel->user_channel_id,
                       panel->user_task_id,
                       ADC_CMD_SET_STREAM_FORMAT,
                       &values,
                       sizeof(dac_adc_control_ipc_cmd_value_msg_t));
}

void setStreamFormat::messageReceive(void *msg)
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

        if(fpga_reply->for_cmd == ADC_CMD_SET_STREAM_FORMAT)
        {
            switch (fpga_reply->status) {
            case REPLY_STATUS_OK:
            {
                if(reply_data->replyParamOne == panel->devices->currentIndex())
                {
                    QString format = QObject::tr("Unknown");

                    if(!reply_data->replyParamTwo) {
                        format = QObject::tr("16-bit");
                        QMetaObject::invokeMethod(panel, "voltsLevelChanged", Q_ARG(float, c_V_FPGA_16bit));
                    }
                    else if(reply_data->replyParamTwo == 8) {
                        format = QObject::tr("12-bit");
                        QMetaObject::invokeMethod(panel, "voltsLevelChanged", Q_ARG(float, c_V_FPGA_12bit));
                    }
                    else if(reply_data->replyParamTwo == 10) {
                        format = QObject::tr("32-bit");
                        QMetaObject::invokeMethod(panel, "voltsLevelChanged", Q_ARG(float, c_V_FPGA_32bit));
                    }

                    panel->format->setText(format);
                    panel->state = panel->set_dev_freq;
                }
                break;
            }
            case REPLY_STATUS_ERROR:
            {
                QTextStream(&warning_text) << QObject::tr("Can not set stream format: [ Device: ") << reply_data->replyParamOne
                             << QObject::tr(", Format: ") << reply_data->replyParamTwo << " ]";

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
