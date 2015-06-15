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

#ifndef WAVE_PANEL_H
#define WAVE_PANEL_H

#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>

#include "Functional/SFBS/User/Interface/user_ipc_panel.h"

class WavePanel : public UserIPCPanel
{
    Q_OBJECT

public:
    explicit WavePanel(QWidget *parent = 0);

    const QString& getName() const { return name; }

    ~WavePanel();

public slots:
    void setBlockSamplingFrequency(bool);

private slots:
    void setupButtonPushed();

signals:
    void signalSettingsChanged(long Fs, double Fn, double Amp, double Noise);

    void startButtonPushed();
    void stopButtonPushed();

protected:
    void changeEvent(QEvent*);

private:
    WavePanel(const WavePanel&);
    WavePanel& operator=(const WavePanel&);

    // Label
    QString name;

    // Widget child objects:
    // Labels:
    QLabel *sampling_freq_label;
    QLabel *signal_freq_label;
    QLabel *amplitude_label;
    QLabel *noise_label;
    // Boxes:
    QLineEdit *sampling_freq_box;
    QLineEdit *signal_freq_box;
    QLineEdit *amplitude_box;
    QLineEdit *noise_box;
    // Buttons:
    QPushButton *start_bttn;
    QPushButton *stop_bttn;
    QPushButton *setup_bttn;

};

#endif // WAVE_PANEL_H
