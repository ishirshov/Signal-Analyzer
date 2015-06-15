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

#include "dsp_gen_panel.h"
#include "States/no_ipc_state.h"
#include "Functional/IPP/additional.h"

#include <QVBoxLayout>
#include <QValidator>
#include <QEvent>

class modifyQDoubleValidator : public QDoubleValidator
{
public:
    modifyQDoubleValidator(qreal bottom, qreal top, int decimals, QObject *parent)
        :QDoubleValidator(bottom, top, decimals, parent)
    {
    }

    QValidator::State validate(QString &s, int &i) const
    {
        if (s.isEmpty() || s == "-") {
            return QValidator::Intermediate;
        }

        bool ok;
        double d = s.toDouble(&ok);

        if (ok && d >= bottom() && d <= top()) {
            return QValidator::Acceptable;
        } else {
            return QValidator::Invalid;
        }
    }

};

DSPGenPanel::DSPGenPanel(QWidget *parent)
    :user_channel_id(0)
    ,panel_channel_id(0)
    ,panel_task_id(0)
    ,state(new noIPCState)
{
    user_task_id.stream_task_id = 0;

    // Signal parameter init.
    setup_signal.sampling_frequency = 5000000;
    setup_signal.signal_frequency = 1000000.0;
    setup_signal.signal_level = 2048.0;
    setup_signal.noise_level = 256.0;

    user_task_id.stream_task_id = 0;

    // Prepare sampling frequency box.
    sampfreq_box = new QLineEdit(this);
    sampfreq_box->setValidator(new QIntValidator(1, 250000000, sampfreq_box));
    sampfreq_box->setText(QString("%1").arg(setup_signal.sampling_frequency));

    // Prepare signal frequency box.
    sigfreq_box = new QLineEdit(this);
    sigfreq_vldrt = new modifyQDoubleValidator(1.0, setup_signal.sampling_frequency/2.f, 1, sigfreq_box);
    sigfreq_box->setValidator(sigfreq_vldrt);
    sigfreq_box->setText(QString("%1").arg(setup_signal.signal_frequency, 0, 'f', 1));

    // Prepare signal amplitude box.
    sigamp_box = new QLineEdit(this);
    sigamp_box->setValidator(new modifyQDoubleValidator(0.0, 4095.0, 1, sigamp_box));
    sigamp_box->setText(QString("%1").arg(setup_signal.signal_level, 0, 'f', 1));

    // Prepare noise amplitude box.
    noiselvl_box = new QLineEdit(this);
    noiselvl_box->setValidator(new modifyQDoubleValidator(0.0, 4095.0, 1, noiselvl_box));
    noiselvl_box->setText(QString("%1").arg(setup_signal.noise_level, 0, 'f', 1));

    tasks_box = new QComboBox(this);
    tasks_box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    // Prepare control units.
    tasks_bttn = new QPushButton(tr("Open"), this);
    start_bttn = new QPushButton(tr("Start stream"), this);
    stop_bttn = new QPushButton(tr("Stop stream"), this);
    setup_bttn = new QPushButton(tr("Setup"), this);

    // Prepare labels.
    tasks_label = new QLabel(tr("Tasks: "), this);
    sampfreq_label = new QLabel(tr("Sampling frequency [Hz]: "), this);
    sigfreq_label = new QLabel(tr("Signal frequency [Hz]: "), this);
    sigamp_label = new QLabel(tr("Signal amplitude [level]: "), this);
    noiselvl_label = new QLabel(tr("Noise level [level]: "), this);

    // Button settings.
    start_bttn->setEnabled(false);
    stop_bttn->setEnabled(false);

    // Create layouts.
    QHBoxLayout *tasks_hl = new QHBoxLayout;
    tasks_hl->addWidget(tasks_box);
    tasks_hl->addWidget(tasks_bttn);
    tasks_hl->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout *tasks_vl = new QVBoxLayout;
    tasks_vl->addWidget(tasks_label);
    tasks_vl->addLayout(tasks_hl);
    tasks_vl->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *sampfreq_layout = new QVBoxLayout;
    sampfreq_layout->addWidget(sampfreq_label);
    sampfreq_layout->addWidget(sampfreq_box);
    sampfreq_layout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *sigfreq_layout = new QVBoxLayout;
    sigfreq_layout->addWidget(sigfreq_label);
    sigfreq_layout->addWidget(sigfreq_box);
    sigfreq_layout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *sigamp_layout = new QVBoxLayout;
    sigamp_layout->addWidget(sigamp_label);
    sigamp_layout->addWidget(sigamp_box);
    sigamp_layout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *noiselvl_layout = new QVBoxLayout;
    noiselvl_layout->addWidget(noiselvl_label);
    noiselvl_layout->addWidget(noiselvl_box);
    noiselvl_layout->setContentsMargins(0, 0, 0, 0);

    QGridLayout *control_layout = new QGridLayout;
    control_layout->addWidget(start_bttn, 0, 0);
    control_layout->addWidget(stop_bttn, 0, 1);
    control_layout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *main = new QVBoxLayout;
    main->addLayout(tasks_vl);
    main->addLayout(sampfreq_layout);
    main->addLayout(sigfreq_layout);
    main->addLayout(sigamp_layout);
    main->addLayout(noiselvl_layout);
    main->addWidget(setup_bttn);
    main->addLayout(control_layout);
    main->setSpacing(10);
    main->setContentsMargins(0, 0, 0, 0);

    connect(tasks_bttn, SIGNAL(clicked()), SLOT(taskButtonPushed()));
    connect(setup_bttn, SIGNAL(clicked()), SLOT(setupButtonPushed()));
    connect(start_bttn, SIGNAL(clicked()), SLOT(startButtonPushed()));
    connect(stop_bttn, SIGNAL(clicked()), SLOT(stopButtonPushed()));
    connect(sampfreq_box, SIGNAL(textChanged(QString)), SLOT(samplingFreqBoxChanged(QString)));

    setLayout(main);
    setParent(parent);
}

QString DSPGenPanel::getPanelType() const
{
    return "DSP_GEN";
}

void DSPGenPanel::ipcDataHandle(void *msg)
{
    if(!msg) return;

    state->messageReceive(msg);
    state->sendMessage();
}

void DSPGenPanel::ipcInit(int user_ch_id, int user_tsk_id, int panel_ch_id, int panel_tsk_id)
{
    if((user_ch_id < 0) || (user_tsk_id < 0) ||
       (panel_ch_id < 0) || (panel_tsk_id < 0))
        throw std::runtime_error("Invalid ipc settings.");

    if((user_channel_id != 0) || (user_task_id.stream_task_id != 0))
        throw std::runtime_error("Twice initialization is not accepted.");

    user_channel_id = user_ch_id;
    user_task_id.stream_task_id = user_tsk_id;
    panel_channel_id = panel_ch_id;
    panel_task_id = panel_tsk_id;

    // Fill tasks box
    libsfbs_task_info_t *tasks_list = 0;
    quint32 list_size = 0;

    if(libsfbs_task_get_list(&tasks_list, &list_size) != SFBS_SUCCESS)
        throw std::runtime_error(toConstChar(tr("Can not get tasks list.")));

    for(int i = 0; i < list_size; ++i)
        if(tasks_list[i].id != panel_task_id)
            tasks_box->addItem(QString("%1 (%2)").arg(tasks_list[i].id).arg(tasks_list[i].name));

    user_ipc_send(user_channel_id,
                  DSP_IPC_CMD_SG_SETUP,
                  (void*)&setup_signal,
                  sizeof(dsp_ipc_msg_SG_SETUP_t));

    emit voltsLevelChanged(c_V_DSP_12bit);
    emit samplingFrequencyChanged(setup_signal.sampling_frequency);
}

void DSPGenPanel::blockSamplingFrequency(bool enabled)
{
    sampfreq_box->setEnabled(!enabled);
}

void DSPGenPanel::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        if(tasks_box->isEnabled())
            tasks_bttn->setText(tr("Close"));
        else
            tasks_bttn->setText(tr("Open"));

        start_bttn->setText(tr("Start stream"));
        stop_bttn->setText(tr("Stop stream"));
        setup_bttn->setText(tr("Setup"));

        sampfreq_label->setText(tr("Sampling frequency [Hz]: "));
        sigfreq_label->setText(tr("Signal frequency [Hz]: "));
        sigamp_label->setText(tr("Signal amplitude [level]: "));
        noiselvl_label->setText(tr("Noise level [level]: "));
    }
}

void DSPGenPanel::taskButtonPushed()
{
    QRegExp rx("(\\d+).");
    int pos = rx.indexIn(tasks_box->itemText(tasks_box->currentIndex()));

    if(pos > -1) {
        user_task_id.stream_task_id = rx.cap(0).toInt();

        if(tasks_box->isEnabled())
        {
            user_ipc_send(user_channel_id,
                          DSP_IPC_CMD_STREAM_TASK,
                          (void*)&user_task_id,
                          sizeof(dsp_ipc_msg_STREAM_TASK_t));

            tasks_box->setEnabled(false);
            start_bttn->setEnabled(true);
            stop_bttn->setEnabled(true);
            tasks_bttn->setText(tr("Close"));
        }
        else
        {
            tasks_box->setEnabled(true);
            start_bttn->setEnabled(false);
            stop_bttn->setEnabled(false);
            tasks_bttn->setText(tr("Open"));
        }
    }
}

void DSPGenPanel::startButtonPushed()
{
    user_ipc_send(user_channel_id,
                  DSP_IPC_CMD_SG_START,
                  &user_task_id,
                  sizeof(dsp_ipc_msg_STREAM_TASK_t));

    tasks_bttn->setEnabled(false);
}

void DSPGenPanel::stopButtonPushed()
{
    user_ipc_send(user_channel_id,
                  DSP_IPC_CMD_SG_STOP,
                  &user_task_id,
                  sizeof(dsp_ipc_msg_STREAM_TASK_t));

    tasks_bttn->setEnabled(true);
}

void DSPGenPanel::setupButtonPushed()
{
    ulong current_freq = sampfreq_box->text().toInt();

    if(current_freq != setup_signal.sampling_frequency)
    {
        setup_signal.sampling_frequency = current_freq;
        emit samplingFrequencyChanged(setup_signal.sampling_frequency);
    }

    setup_signal.signal_frequency = sigfreq_box->text().toDouble();
    setup_signal.signal_level = sigamp_box->text().toDouble();
    setup_signal.noise_level = noiselvl_box->text().toDouble();

    user_ipc_send(user_channel_id,
                  DSP_IPC_CMD_SG_SETUP,
                  &setup_signal,
                  sizeof(dsp_ipc_msg_SG_SETUP_t));    
}

void DSPGenPanel::samplingFreqBoxChanged(const QString &text)
{
    qreal top = text.toDouble()/2.f;
    qreal current_sigfreq = sigfreq_box->text().toDouble();

    if(current_sigfreq > top)
        current_sigfreq = top;

    sigfreq_vldrt->setTop(top);
    sigfreq_box->setText(QString("%1").arg(current_sigfreq, 0, 'f', 1));
}
