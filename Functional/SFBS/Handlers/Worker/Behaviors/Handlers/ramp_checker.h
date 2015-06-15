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

#ifndef RAMP_CHECKER_H
#define RAMP_CHECKER_H

#include <QTimer>
#include "handler_behavior.h"

class RampChecker : public HandlerBehavior
{
    Q_OBJECT

public:
    explicit RampChecker(QObject *parent = 0);

    Weight behaviorWeight() const;

    ~RampChecker();

signals:
    void checkedBuffersChanged(int);
    void brokenBuffersChanged(int);
    void brokenSequenceChanged(int);
    void durationTimeChanged(const QString&);
    void lostInSession(const QString&);
    void lostInPeriod(const QString&);

    // Unused signals
    void valueChanged(int);
    void dataProcessed(ipp_vector<Ipp16s>);
    void dataProcessed(ipp_vector<Ipp32f>);

public slots:
    void setAcceptToStore(bool);
    void setSamplingFrequency(ulong);

    void receiveData(const ipp_vector<Ipp16s>&);

private slots:
    void outputStatistics();

private:
    void reInitReferencesSignal(quint32);
    void initReferenceSignal();
    void resetCounters();

    quint32 segmt_size;             // Size of segments of input stream
    quint32 refsig_size;            // Size of reference signal

    const Ipp16s min_lmt;           // Minimal limit
    const Ipp16s max_of_min;        // Maximum of minimal limit
    const Ipp16s max_lmt;
    const Ipp16s min_of_max;

    QHash<Ipp16s, int> ref_indx;    // Need index lookup with compl O(1)
    ipp_ptr<Ipp16s> ref_signal;     // Signature of ramp signal

    QTimer timer;                   // Timer for statistic printing
    bool is_accpt_chk;              // Flag to enable or disable checking

    ulong current_freq;
    qulonglong session_samples;
    qulonglong session_errors;
    qulonglong period_samples;
    qulonglong period_errors;

};

#endif // RAMP_CHECKER_H
