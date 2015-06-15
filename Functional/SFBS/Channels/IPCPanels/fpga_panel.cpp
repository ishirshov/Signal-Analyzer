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

#include "fpga_panel.h"
#include "States/adc_states.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QEvent>

#include <stdexcept>

FPGAPanel::FPGAPanel(QWidget *parent)
    :panel_channel_id(0)
    ,panel_task_id(0)
    ,user_channel_id(0)
    ,user_task_id(0)
{
    // Prepare buttons.
    tasks_control = new QPushButton(tr("Open"), this);
    device_control = new QPushButton(tr("Open"), this);
    channel_control = new QPushButton(tr("Open"), this);
    stream_control = new QPushButton(tr("Enable"), this);
    apply_control = new QPushButton(tr("Apply"), this);

    // Button settings.
    device_control->setEnabled(false);
    stream_control->setEnabled(false);
    apply_control->setEnabled(false);
    channel_control->setEnabled(false);

    // Prepare boxes.
    tasks = new QComboBox(this);
    devices = new QComboBox(this);
    channels = new QComboBox(this);
    types = new QComboBox(this);
    format = new QLineEdit(this);
    sampfreq_box = new QLineEdit(this);

    // Box settings.
    tasks->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    devices->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    devices->setEnabled(false);
    channels->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    channels->setEnabled(false);
    types->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    types->setEnabled(false);
    types->addItem("normal", 0);
    types->addItem("ramp", 4);
    format->setText(tr("Not set"));
    format->setEnabled(false);
    sampfreq_box->setValidator(new QIntValidator(10000000, 250000000, this));
    sampfreq_box->setText(QString("%1").arg(10000000));
    sampfreq_box->setEnabled(false);

    // Prepare labels.
    tasks_label = new QLabel(tr("Tasks: "), this);
    device_label = new QLabel(tr("Devices: "), this);
    channel_label = new QLabel(tr("Channels: "), this);
    type_label = new QLabel(tr("Stream type: "), this);
    format_label = new QLabel(tr("Stream format: "), this);
    sampfreq_label = new QLabel(tr("Sampling frequency [Hz]: "), this);

    // Create layouts.
    QHBoxLayout *tasks_hl = new QHBoxLayout;
    tasks_hl->addWidget(tasks);
    tasks_hl->addWidget(tasks_control);
    tasks_hl->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout *tasks_vl = new QVBoxLayout;
    tasks_vl->addWidget(tasks_label);
    tasks_vl->addLayout(tasks_hl);
    tasks_vl->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *device_hl = new QHBoxLayout;
    device_hl->addWidget(devices);
    device_hl->addWidget(device_control);
    device_hl->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout *device_vl = new QVBoxLayout;
    device_vl->addWidget(device_label);
    device_vl->addLayout(device_hl);
    device_vl->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *channel_hl = new QHBoxLayout;
    channel_hl->addWidget(channels);
    channel_hl->addWidget(channel_control);
    channel_hl->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *channel_vl = new QVBoxLayout;
    channel_vl->addWidget(channel_label);
    channel_vl->addLayout(channel_hl);
    channel_vl->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *type_hl = new QHBoxLayout;
    type_hl->addWidget(type_label);
    type_hl->addWidget(types);
    type_hl->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *format_hl = new QHBoxLayout;
    format_hl->addWidget(format_label);
    format_hl->addWidget(format);
    format_hl->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *sampfreq_vl = new QVBoxLayout;
    sampfreq_vl->addWidget(sampfreq_label);
    sampfreq_vl->addWidget(sampfreq_box);
    sampfreq_vl->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *control_hl = new QHBoxLayout;
    control_hl->addWidget(stream_control);
    control_hl->addWidget(apply_control);
    control_hl->setContentsMargins(0, 0, 0, 0);
    control_hl->setEnabled(false);

    QVBoxLayout *main = new QVBoxLayout;
    main->addLayout(tasks_vl);
    main->addLayout(device_vl);
    main->addLayout(channel_vl);
    main->addLayout(format_hl);
    main->addLayout(type_hl);
    main->addLayout(sampfreq_vl);
    main->addLayout(control_hl);
    main->setSpacing(10);
    main->setContentsMargins(0, 0, 0, 0);

    // Initialization states
    apply_config = QSharedPointer<IPCState>(new applyConfig(this));
    ch_close = QSharedPointer<IPCState>(new chClose(this));
    ch_open = QSharedPointer<IPCState>(new chOpen(this));
    dev_close = QSharedPointer<IPCState>(new devClose(this));
    dev_open = QSharedPointer<IPCState>(new devOpen(this));
    get_ch_per_one_dev = QSharedPointer<IPCState>(new getChPerOneDevice(this));
    get_dev_num = QSharedPointer<IPCState>(new getDevNumbers(this));
    get_dev_freq = QSharedPointer<IPCState>(new getDevFreq(this));
    get_stream_t = QSharedPointer<IPCState>(new getStreamType(this));
    set_stream_f = QSharedPointer<IPCState>(new setStreamFormat(this));
    set_stream_t = QSharedPointer<IPCState>(new setStreamType(this));
    set_dev_freq = QSharedPointer<IPCState>(new setDevFreq(this));
    stream_disable = QSharedPointer<IPCState>(new streamDisable(this));
    stream_enable = QSharedPointer<IPCState>(new streamEnable(this));
    no_state = QSharedPointer<IPCState>(new noIPCState);

    // Set current state
    state = get_dev_num;

    // Create connections
    connect(tasks_control, SIGNAL(clicked()), this, SLOT(tasksOpenCloseButtonPushed()));
    connect(device_control, SIGNAL(clicked()), this, SLOT(deviceOpenCloseButtonPushed()));
    connect(channel_control, SIGNAL(clicked()), this, SLOT(channelOpenCloseButtonPushed()));
    connect(apply_control, SIGNAL(clicked()), this, SLOT(applyButtonPushed()));
    connect(stream_control, SIGNAL(clicked()), this, SLOT(streamEnableDisableButtonPushed()));
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    connect(types, SIGNAL(currentIndexChanged(QString)), this, SLOT(streamTypeChanged(QString)));
#else
    connect(types, SIGNAL(currentTextChanged(QString)), this, SLOT(streamTypeChanged(QString)));
#endif

    // Set layout and parent object
    setLayout(main);
    setParent(parent);    
}

QString FPGAPanel::getPanelType() const
{
    return "FPGA";
}

void FPGAPanel::ipcDataHandle(void *msg)
{
    state->messageReceive(msg);
    state->sendMessage();
}

void FPGAPanel::ipcInit(int user_ch_id, int user_tsk_id, int panel_ch_id, int panel_tsk_id)
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
            tasks->addItem(QString("%1 (%2)").arg(tasks_list[i].id).arg(tasks_list[i].name));

    state->sendMessage();
}

void FPGAPanel::blockSamplingFrequency(bool enabled)
{
    sampfreq_box->setEnabled(!enabled);
}

FPGAPanel::~FPGAPanel()
{
    emit rampStreamTypeDetect(false);

    resetDevice();
}

void FPGAPanel::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        if(devices->isEnabled())
            device_control->setText(tr("Open"));
        else device_control->setText(tr("Close"));

        if(channels->isEnabled())
            channel_control->setText(tr("Open"));
        else channel_control->setText(tr("Close"));

        if(apply_control->isEnabled())
            stream_control->setText(tr("Enable"));
        else stream_control->setText(tr("Disable"));

        apply_control->setText(tr("Apply"));
        format->setText(tr("Not set"));

        device_label->setText(tr("Devices: "));
        channel_label->setText(tr("Channels: "));
        type_label->setText(tr("Stream type: "));
        format_label->setText(tr("Stream format: "));
        sampfreq_label->setText(tr("Sampling frequency [Hz]: "));
    }

    QWidget::changeEvent(event);
}

void FPGAPanel::tasksOpenCloseButtonPushed()
{
    QRegExp rx("(\\d+).");
    int pos = rx.indexIn(tasks->itemText(tasks->currentIndex()));

    if(pos > -1) {
        user_task_id = rx.cap(0).toInt();

        if(tasks->isEnabled())
        {
            device_control->setEnabled(true);
            devices->setEnabled(true);
            tasks_control->setText(tr("Close"));
            tasks->setEnabled(false);
        }
        else
        {
            device_control->setEnabled(false);
            devices->setEnabled(false);
            tasks->setEnabled(true);
            tasks_control->setText(tr("Open"));
        }
    }
}

void FPGAPanel::deviceOpenCloseButtonPushed()
{
    state = (devices->isEnabled())?(dev_open):(dev_close);
    state->sendMessage();
}

void FPGAPanel::channelOpenCloseButtonPushed()
{
    state = (channels->isEnabled())?(ch_open):(ch_close);
    state->sendMessage();
}

void FPGAPanel::applyButtonPushed()
{
    state = set_stream_t;
    state->sendMessage();
}

void FPGAPanel::streamEnableDisableButtonPushed()
{
    state = (apply_control->isEnabled())?(stream_enable):(stream_disable);
    state->sendMessage();
}

void FPGAPanel::streamTypeChanged(const QString &type)
{
    emit rampStreamTypeDetect((type == "ramp")?(true):(false));
}

void FPGAPanel::resetDevice()
{
    if(!apply_control->isEnabled())
    {
        state = stream_disable;
        state->sendMessage();
    }

    if(!channels->isEnabled())
    {
        state = ch_close;
        state->sendMessage();
    }

    if(!devices->isEnabled())
    {
        state = dev_close;
        state->sendMessage();
    }
}
