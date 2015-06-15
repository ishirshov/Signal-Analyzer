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

#ifndef DSP_GEN_PANEL_H
#define DSP_GEN_PANEL_H

#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>

#include "Functional/SFBS/Channels/Interfaces/ipc_panel.h"
#include "Functional/SFBS/Channels/Interfaces/ipc_state.h"

class modifyQDoubleValidator;

class DSPGenPanel : public IPCPanel
{
    Q_OBJECT

public:
    explicit DSPGenPanel(QWidget *parent = 0);

    QString getPanelType() const;

signals:
    void samplingFrequencyChanged(ulong);
    void voltsLevelChanged(float);

public slots:
    void ipcDataHandle(void*);
    void ipcInit(int user_ch_id, int user_tsk_id, int panel_ch_id, int panel_tsk_id);
    void blockSamplingFrequency(bool);

private slots:
    void taskButtonPushed();
    void startButtonPushed();
    void stopButtonPushed();
    void setupButtonPushed();

    void samplingFreqBoxChanged(const QString&);

protected:
    void changeEvent(QEvent*);

private:
    DSPGenPanel(const DSPGenPanel&);
    DSPGenPanel& operator=(const DSPGenPanel&);

    // Task, channel ID and signal settings:
    int user_channel_id;
    dsp_ipc_msg_STREAM_TASK_t user_task_id;

    int panel_channel_id;
    int panel_task_id;
    dsp_ipc_msg_SG_SETUP_t setup_signal;

    // Widget child objects:
    // Boxes:
    QComboBox *tasks_box;
    QLineEdit *sampfreq_box;
    QLineEdit *sigfreq_box;
    modifyQDoubleValidator *sigfreq_vldrt;
    QLineEdit *sigamp_box;
    QLineEdit *noiselvl_box;
    // Labels:
    QLabel *tasks_label;
    QLabel *sampfreq_label;
    QLabel *sigfreq_label;
    QLabel *sigamp_label;
    QLabel *noiselvl_label;
    //Buttons:
    QPushButton *tasks_bttn;
    QPushButton *start_bttn;
    QPushButton *stop_bttn;
    QPushButton *setup_bttn;

    // IPCStates:
    QSharedPointer<IPCState> state;

};

#endif // DSP_GEN_PANEL_H
