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

#ifndef FPGAPANEL_H
#define FPGAPANEL_H

#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>

#include "Functional/SFBS/Channels/Interfaces/ipc_panel.h"
#include "Functional/SFBS/Channels/Interfaces/ipc_state.h"

class FPGAPanel : public IPCPanel
{
    Q_OBJECT

public:
    explicit FPGAPanel(QWidget *parent = 0);

    QString getPanelType() const;

    ~FPGAPanel();

signals:
    void samplingFrequencyChanged(ulong);
    void voltsLevelChanged(float);

public slots:
    void ipcDataHandle(void *msg);
    void ipcInit(int user_ch_id, int user_tsk_id, int panel_ch_id, int panel_tsk_id);
    void blockSamplingFrequency(bool);

private slots:
    void tasksOpenCloseButtonPushed();
    void deviceOpenCloseButtonPushed();
    void channelOpenCloseButtonPushed();
    void applyButtonPushed();
    void streamEnableDisableButtonPushed();

    void streamTypeChanged(const QString&);

signals:
    void rampStreamTypeDetect(bool);

protected:
    void changeEvent(QEvent *);

private:
    FPGAPanel(const FPGAPanel&);
    FPGAPanel& operator=(const FPGAPanel&);

    void resetDevice();

    // Task ID of this panel
    int panel_channel_id;
    quint32 panel_task_id;

    // Task and channel ID:
    int user_channel_id;
    quint32 user_task_id;

    // Widget child objects:
    // Buttons:
    QPushButton *tasks_control;
    QPushButton *device_control;
    QPushButton *channel_control;
    QPushButton *stream_control;
    QPushButton *apply_control;
    // ComboBoxes:
    QComboBox *tasks;
    QComboBox *devices;
    QComboBox *channels;
    QComboBox *types;
    QLineEdit *format;
    QLineEdit *sampfreq_box;
    // Labels:
    QLabel *tasks_label;
    QLabel *device_label;
    QLabel *channel_label;
    QLabel *type_label;
    QLabel *format_label;
    QLabel *sampfreq_label;

    friend class applyConfig;
    friend class chOpen;
    friend class chClose;
    friend class devOpen;
    friend class devClose;
    friend class getChPerOneDevice;
    friend class getDevFreq;
    friend class getDevNumbers;
    friend class getStreamType;
    friend class setDevFreq;
    friend class setStreamFormat;
    friend class setStreamType;
    friend class streamDisable;
    friend class streamEnable;

    QSharedPointer<IPCState> state;
    // IPCStates:
    QSharedPointer<IPCState> apply_config;
    QSharedPointer<IPCState> ch_close;
    QSharedPointer<IPCState> ch_open;
    QSharedPointer<IPCState> dev_close;
    QSharedPointer<IPCState> dev_open;
    QSharedPointer<IPCState> get_ch_per_one_dev;
    QSharedPointer<IPCState> get_dev_freq;
    QSharedPointer<IPCState> get_dev_num;
    QSharedPointer<IPCState> get_stream_t;
    QSharedPointer<IPCState> set_dev_freq;
    QSharedPointer<IPCState> set_stream_f;
    QSharedPointer<IPCState> set_stream_t;
    QSharedPointer<IPCState> stream_disable;
    QSharedPointer<IPCState> stream_enable;
    QSharedPointer<IPCState> no_state;

};

#endif // FPGAPANEL_H
