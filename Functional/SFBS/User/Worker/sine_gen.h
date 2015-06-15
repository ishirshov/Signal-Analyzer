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

#ifndef SINE_GENERATOR_H
#define SINE_GENERATOR_H

#include <QTimer>
#include <QEvent>
#include "Functional/IPP/additional.h"
#include "Functional/SFBS/User/Interface/user_gen.h"

class SineGenerator : public UserGenerator
{
    Q_OBJECT

public:
    SineGenerator();

    quint32 getBufferSize() const { return c_Default_Buffer_sz; }
    ulong getSamplingFrequency() const { return _Fs; }
    qreal getSignalFrequency() const { return _Fn; }
    qreal getSignalAmplitude() const { return _Amp; }
    qreal getNoiseAmplitude() const { return _Noise; }
    qreal getVoltsLevel() const { return c_V_GPP_12bit; }
    const QString& getName() const { return _device_name; }
    const QString& getType() const { return _device_type; }

signals:
    void workerStatusChanged(bool);
    void workerStatusMessage(const QString&);
    void samplingFrequencyChanged(ulong);

    void started();
    void finished();

public slots:
    void start();
    void stop();

    void setSignalSettings(long Fs, double Fn, double Amp, double Noise);

private slots:
    void generate();
    void report();

private:
    // Flags:
    bool _is_work;
    QString _device_name;
    QString _device_type;

    // Generator settings:
    QTimer *_gen_timer;
    Ipp32s _last_pos;

    // Report settings:
    QTimer *_report_timer;
    qint32 _counter;

    // Current signal settings:
    ulong _Fs;        // Sample rate in Hz.
    qreal _Fn;        // Frequency in Hz.
    qreal _Amp;       // Amplitude in levels.
    qreal _Noise;     // Noise amplitude in levels.

    // Data:
    ipp_ptr<IppsRandUniState_32f> _rand_state;
    ipp_vector<Ipp32f> _signal;
    ipp_vector<Ipp32f> _noise;
    ipp_vector<Ipp32f> _buffer;

    void init_signal(long Fs, qreal Fn, qreal Amp);
    void init_rand_state(qreal Noise);
    void init_timer(long Fs);

};

#endif // SINE_GENERATOR_H
