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

#include "wave_panel.h"

#include "Functional/IPP/additional.h"

#include <QVBoxLayout>
#include <QValidator>
#include <QEvent>
#include <QMessageBox>

#include <qwt_interval.h>

WavePanel::WavePanel(QWidget *parent)
    :name("SINE_IPC")
{    
    // Create boxes.
    sampling_freq_box = new QLineEdit(this);
    signal_freq_box = new QLineEdit(this);
    amplitude_box = new QLineEdit(this);
    noise_box = new QLineEdit(this);

    // Create box labels.
    sampling_freq_label = new QLabel(tr("Sampling frequency [Hz]: "), this);
    signal_freq_label = new QLabel(tr("Signal frequency [Hz]: "), this);
    amplitude_label = new QLabel(tr("Signal amplitude [level]: "), this);
    noise_label = new QLabel(tr("Noise level [level]: "), this);

    // Create control units.
    start_bttn = new QPushButton(tr("Start stream"), this);
    stop_bttn = new QPushButton(tr("Stop stream"), this);
    setup_bttn = new QPushButton(tr("Setup"), this);

    // Prepare boxes.
    sampling_freq_box->setValidator(new QIntValidator(c_Fs_range.minValue(), c_Fs_range.maxValue()/5, sampling_freq_box));
    signal_freq_box->setValidator(new QIntValidator(c_Fn_range.minValue(), c_Fn_range.maxValue(), signal_freq_box));
    amplitude_box->setValidator(new QIntValidator(c_Amp_range.minValue(), c_Amp_range.maxValue(), amplitude_box));
    noise_box->setValidator(new QIntValidator(c_Noise_range.minValue(), c_Noise_range.maxValue(), noise_box));

    sampling_freq_box->setText(QString("%1").arg(c_Default_Fs));
    signal_freq_box->setText(QString("%1").arg(c_Default_Fn));
    amplitude_box->setText(QString("%1").arg(c_Default_Amp));
    noise_box->setText(QString("%1").arg(c_Default_Noise));

    // Create layouts.
    QVBoxLayout *sampfreq_layout = new QVBoxLayout;
    QVBoxLayout *sigfreq_layout = new QVBoxLayout;
    QVBoxLayout *sigamp_layout = new QVBoxLayout;
    QVBoxLayout *noiselvl_layout = new QVBoxLayout;
    QGridLayout *control_layout = new QGridLayout;
    QVBoxLayout *main = new QVBoxLayout;

    // Prepare layout (Sampling frequency).
    sampfreq_layout->addWidget(sampling_freq_label);
    sampfreq_layout->addWidget(sampling_freq_box);
    sampfreq_layout->setContentsMargins(0, 0, 0, 0);

    // Prepare layout (Signal frequency).
    sigfreq_layout->addWidget(signal_freq_label);
    sigfreq_layout->addWidget(signal_freq_box);
    sigfreq_layout->setContentsMargins(0, 0, 0, 0);

    // Prepare layout (Signal amplitude).
    sigamp_layout->addWidget(amplitude_label);
    sigamp_layout->addWidget(amplitude_box);
    sigamp_layout->setContentsMargins(0, 0, 0, 0);

    // Prepare layout (Noise amplitude).
    noiselvl_layout->addWidget(noise_label);
    noiselvl_layout->addWidget(noise_box);
    noiselvl_layout->setContentsMargins(0, 0, 0, 0);

    // Prepare layout (Control buttons).
    control_layout->addWidget(start_bttn, 0, 0);
    control_layout->addWidget(stop_bttn, 0, 1);
    control_layout->setContentsMargins(0, 0, 0, 0);

    // Prepare main layout.
    main->addLayout(sampfreq_layout);
    main->addLayout(sigfreq_layout);
    main->addLayout(sigamp_layout);
    main->addLayout(noiselvl_layout);
    main->addWidget(setup_bttn);
    main->addLayout(control_layout);
    main->setSpacing(10);
    main->setContentsMargins(0, 0, 0, 0);

    // Create connections between graphical elements and panel.
    connect(start_bttn, SIGNAL(clicked()), SIGNAL(startButtonPushed()));
    connect(stop_bttn, SIGNAL(clicked()), SIGNAL(stopButtonPushed()));
    connect(setup_bttn, SIGNAL(clicked()), SLOT(setupButtonPushed()));

    setLayout(main);
    setParent(parent);
}

WavePanel::~WavePanel()
{
    emit stopButtonPushed();
}

void WavePanel::setBlockSamplingFrequency(bool flag)
{
    sampling_freq_box->setEnabled(flag);
}

void WavePanel::setupButtonPushed()
{
    long fs = sampling_freq_box->text().toLong();
    double fn = signal_freq_box->text().toDouble();
    double amp = amplitude_box->text().toDouble();
    double noise = noise_box->text().toDouble();

    if(c_Fs_range.contains(fs))
        if(c_Fn_range.contains(fn))
            if(fs/2 >= fn)
            {
                if(c_Amp_range.contains(amp))
                    if(c_Noise_range.contains(noise))
                        emit signalSettingsChanged(fs, fn, amp, noise);
            }
            else {
                QMessageBox::warning(0, tr("Warning"),
                                        tr("Wrong frequency of signal."));
            }
}

void WavePanel::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        start_bttn->setText(tr("Start stream"));
        stop_bttn->setText(tr("Stop stream"));
        setup_bttn->setText(tr("Setup"));
        sampling_freq_label->setText(tr("Sampling frequency [Hz]: "));
        signal_freq_label->setText(tr("Sampling frequency [Hz]: "));
        amplitude_label->setText(tr("Signal amplitude [level]: "));
        noise_label->setText(tr("Noise level [level]: "));
    }

    QWidget::changeEvent(event);
}
