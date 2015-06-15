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

#include "dsp_multi_panel.h"
#include "States/no_ipc_state.h"

#include <QVBoxLayout>
#include <QEvent>

DSPMultiPanel::DSPMultiPanel(QWidget *parent)
    :state(new noIPCState)
    ,src_task_box(new QComboBox(this))
    ,dst_task_box(new QComboBox(this))
    ,stream_bttn(new QPushButton(tr("Open"), this))
    ,multiplier_box(new QComboBox(this))
    ,bypass_bttn(new QRadioButton(tr("Enable bypass"), this))
    ,multiplier_label(new QLabel(tr("Multiplier: "), this))
    ,src_task_label(new QLabel(tr("Source task: "), this))
    ,dst_task_label(new QLabel(tr("Destination task: "), this))
    ,user_channel_id(0)
    ,user_task_id(0)
    ,panel_channel_id(0)
    ,panel_task_id(0)
    ,src_task_id(0)
    ,dst_task_id(0)
{
    for(qreal mult = 0.1; mult < 1.0; mult += 0.1)
        mult_vals[QString::number(mult)] = mult * 100;
    multiplier_box->addItems(mult_vals.keys());

    multiplier_box->setCurrentIndex(mult_vals.size()/2 - 1);
    src_task_box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    dst_task_box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    multiplier_box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    // Create layouts.
    QHBoxLayout *src_task_layout = new QHBoxLayout;
    src_task_layout->addWidget(src_task_label);
    src_task_layout->addWidget(src_task_box);
    src_task_layout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *dst_task_layout = new QHBoxLayout;
    dst_task_layout->addWidget(dst_task_label);
    dst_task_layout->addWidget(dst_task_box);
    dst_task_layout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *multiplier_layout = new QHBoxLayout;
    multiplier_layout->addWidget(multiplier_label);
    multiplier_layout->addWidget(multiplier_box);
    multiplier_layout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->addLayout(src_task_layout);
    main_layout->addLayout(dst_task_layout);
    main_layout->addLayout(multiplier_layout);
    main_layout->addWidget(bypass_bttn);
    main_layout->addWidget(stream_bttn);
    main_layout->setSpacing(10);
    main_layout->setContentsMargins(0, 0, 0, 0);

    connect(multiplier_box, SIGNAL(currentIndexChanged(int)), SLOT(multiplierChanged(int)));
    connect(bypass_bttn, SIGNAL(clicked(bool)), SLOT(bypassButtonPushed(bool)));
    connect(stream_bttn, SIGNAL(clicked()), SLOT(openCloseButtonPushed()));

    setLayout(main_layout);
    setParent(parent);
}

DSPMultiPanel::~DSPMultiPanel()
{
    dsp_mult_ipc_msg_route_t route;
    route.src_task_id = 0;
    route.dst_task_id = 0;

    user_ipc_send(user_channel_id,
                  DSP_MULT_IPC_CMD_SET_ROUTE,
                  (void*)&route,
                  sizeof(dsp_mult_ipc_msg_route_t));
}

QString DSPMultiPanel::getPanelType() const
{
    return "DSP_MULTI";
}

void DSPMultiPanel::ipcDataHandle(void *msg)
{
    if(!msg) return;

    state->messageReceive(msg);
    state->sendMessage();
}

void DSPMultiPanel::ipcInit(int user_ch_id, int user_tsk_id, int panel_ch_id, int panel_tsk_id)
{
    if((user_ch_id < 0) || (user_tsk_id < 0) ||
       (panel_ch_id < 0) || (panel_tsk_id < 0))
        throw std::runtime_error("Invalid ipc settings.");

    if((user_channel_id != 0) || (user_task_id != 0))
        throw std::runtime_error("Twice initialization is not accepted.");

    user_channel_id = user_ch_id;
    user_task_id = user_tsk_id;
    panel_channel_id = panel_ch_id;
    panel_task_id = panel_tsk_id;

    // Fill tasks box
    libsfbs_task_info_t *tasks_list = 0;
    quint32 list_size = 0;

    if(libsfbs_task_get_list(&tasks_list, &list_size) != SFBS_SUCCESS)
        throw std::runtime_error(toConstChar(tr("Can not get tasks list.")));

    for(int i = 0; i < list_size; ++i)
        if(tasks_list[i].id != panel_task_id)
        {
            src_task_box->addItem(QString("%1 (%2)").arg(tasks_list[i].id).arg(tasks_list[i].name));
            dst_task_box->addItem(QString("%1 (%2)").arg(tasks_list[i].id).arg(tasks_list[i].name));
        }
}

void DSPMultiPanel::blockSamplingFrequency(bool)
{
}

void DSPMultiPanel::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        if(src_task_box->isEnabled())
            stream_bttn->setText(tr("Close"));
        else
            stream_bttn->setText(tr("Open"));

        src_task_label->setText(tr("Source task: "));
        dst_task_label->setText(tr("Destination task: "));
        bypass_bttn->setText(tr("Enable bypass"));
    }
}

void DSPMultiPanel::openCloseButtonPushed()
{
    QRegExp rx("(\\d+).");

    int pos = rx.indexIn(src_task_box->itemText(src_task_box->currentIndex()));

    src_task_id = (pos > -1) ? (rx.cap(0).toInt()) : (0);

    pos = rx.indexIn(dst_task_box->itemText(dst_task_box->currentIndex()));

    dst_task_id = (pos > -1) ? (rx.cap(0).toInt()) : (0);

    if((src_task_id != 0) && (dst_task_id != 0))
    {
        dsp_mult_ipc_msg_route_t route;
        route.src_task_id = src_task_id;

        if(src_task_box->isEnabled())
        {
            route.dst_task_id = dst_task_id;

            stream_bttn->setText(tr("Close"));
            src_task_box->setEnabled(false);
            dst_task_box->setEnabled(false);
        }
        else
        {
            route.dst_task_id = 0;

            stream_bttn->setText(tr("Open"));
            src_task_box->setEnabled(true);
            dst_task_box->setEnabled(true);
        }

        user_ipc_send(user_channel_id,
                      DSP_MULT_IPC_CMD_SET_ROUTE,
                      (void*)&route,
                      sizeof(dsp_mult_ipc_msg_route_t));
    }
}

void DSPMultiPanel::bypassButtonPushed(bool flag)
{
    dsp_mult_ipc_msg_bypass_t bypass;
    bypass.bypass = int(flag);

    user_ipc_send(user_channel_id,
                  DSP_MULT_IPC_CMD_SET_BYPASS,
                  (void*)&bypass,
                  sizeof(dsp_mult_ipc_msg_bypass_t));
}

void DSPMultiPanel::multiplierChanged(int indx)
{
    dsp_mult_ipc_msg_mult_t muliplier;
    muliplier.mult = mult_vals[multiplier_box->itemText(indx)];

    user_ipc_send(user_channel_id,
                  DSP_MULT_IPC_CMD_SET_MULT,
                  (void*)&muliplier,
                  sizeof(dsp_mult_ipc_msg_mult_t));
}
