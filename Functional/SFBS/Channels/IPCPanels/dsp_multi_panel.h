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

#ifndef DSP_MULTI_PANEL_H
#define DSP_MULTI_PANEL_H

#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QRadioButton>

#include "Functional/SFBS/Channels/Interfaces/ipc_panel.h"
#include "Functional/SFBS/Channels/Interfaces/ipc_state.h"

class DSPMultiPanel : public IPCPanel
{
    Q_OBJECT

public:
    DSPMultiPanel(QWidget *parent = 0);
    ~DSPMultiPanel();

    QString getPanelType() const;

signals:
    void samplingFrequencyChanged(ulong);
    void voltsLevelChanged(float);

public slots:
    void ipcDataHandle(void*);
    void ipcInit(int user_ch_id, int user_tsk_id, int panel_ch_id, int panel_tsk_id);
    void blockSamplingFrequency(bool);

private slots:
    void openCloseButtonPushed();
    void bypassButtonPushed(bool);
    void multiplierChanged(int);

protected:
    void changeEvent(QEvent *);

private:
    // IPCStates:
    QSharedPointer<IPCState> state;
    QMap<QString, qint32> mult_vals;

    // Widget child objects:
    // Boxes:
    QComboBox *src_task_box;
    QComboBox *dst_task_box;
    // Buttons:
    QPushButton *stream_bttn;
    QComboBox *multiplier_box;
    QRadioButton *bypass_bttn;
    // Labels:
    QLabel *multiplier_label;
    QLabel *src_task_label;
    QLabel *dst_task_label;

    // Panel settings:
    int user_channel_id;
    int user_task_id;

    int panel_channel_id;
    int panel_task_id;

    int src_task_id;
    int dst_task_id;

};

#endif // DSP_MULTI_PANEL_H
