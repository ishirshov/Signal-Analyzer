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

#include "ramp_checker.h"

RampChecker::RampChecker(QObject *parent)
    :segmt_size(c_Default_Buffer_sz)
    ,refsig_size(0)
    ,min_lmt(0x8003)
    ,max_of_min(0xffff)
    ,max_lmt(0x7ffc)
    ,min_of_max(0x0000)
    ,is_accpt_chk(false)
    ,current_freq(c_Default_Fs)
    ,session_samples(0)
    ,session_errors(0)
    ,period_samples(0)
    ,period_errors(0)
{
    setParent(parent);
    initReferenceSignal();

    connect(&timer, SIGNAL(timeout()), SLOT(outputStatistics()), Qt::QueuedConnection);
    timer.start(5000);
}

RampChecker::Weight RampChecker::behaviorWeight() const
{
    return WorkerBehavior::Light;
}

RampChecker::~RampChecker()
{
    // Stop data checking
    is_accpt_chk = false;

    // Stop timer and clear counters
    resetCounters();
    timer.stop();

    // Last invoke statistics method
    QMetaObject::invokeMethod(this, "outputStatistics", Qt::DirectConnection);
}

void RampChecker::setAcceptToStore(bool flag)
{
    is_accpt_chk = flag;
    resetCounters();
}

void RampChecker::setSamplingFrequency(ulong freq)
{
    if(freq > 0)
    {
        // Change settings and clear stats
        current_freq = freq;
        resetCounters();
    }
}

void RampChecker::receiveData(const ipp_vector<Ipp16s> &segment)
{
    if(segment.empty() || !is_accpt_chk) return;

    qint32 size = segment.size();

    if(ref_indx.contains(segment[0]))
    {
        if(size > segmt_size)
            reInitReferencesSignal(size);
        else
        {
            Ipp16s *ref_data = ref_signal.get();
            quint32 i = ref_indx[segment[0]];

            Ipp32f diff = 0.0;

            IppStatus status = ippsNormDiff_L1_16s32f(segment.data(), ref_data + i, size, &diff);
            if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

            if(diff != 0.0)
                ++period_errors;
            period_samples += size;
        }
    }
}

void RampChecker::outputStatistics()
{
    session_errors += period_errors;
    session_samples += period_samples;

    qreal percent_all = (session_errors > 0)?(qreal(session_errors)*100.0/qreal(session_samples/segmt_size)):(0.0);
    qreal percent_period = (period_errors > 0)?(qreal(period_errors)*100.0/qreal(period_samples/segmt_size)):(0.0);

    emit checkedBuffersChanged(session_samples/segmt_size);
    emit brokenBuffersChanged(session_errors);
    emit durationTimeChanged(QString("%1").arg(float(session_samples)/float(current_freq), 0, 'f', 2));
    emit lostInSession(QString("%1").arg(percent_all, 0, 'f', 2));
    emit lostInPeriod(QString("%1").arg(percent_period, 0, 'f', 2));

    period_samples = period_errors = 0;
}

void RampChecker::reInitReferencesSignal(quint32 new_sz)
{
    if(new_sz > 1)
    {
        segmt_size = new_sz;
        ref_indx.clear();

        resetCounters();
        initReferenceSignal();
    }
}

void RampChecker::initReferenceSignal()
{
    // Prepare container for ramp
    refsig_size = std::ceil(qreal(segmt_size) * 1.5);
    ref_signal.reset(ippsMalloc_16s(refsig_size));

    // And create signal with range from min_lmt to max_lmt
    ref_signal[0] = min_lmt;
    ref_indx.insert(min_lmt, 0);

    for(quint32 i = 1; i < refsig_size; ++i)
    {
        Ipp16s sample = ref_signal[i - 1];

        if(sample >= max_lmt)
            sample = min_lmt;
        else
            sample = (sample == max_of_min)?(min_of_max):(sample + 4);

        ref_signal[i] = sample;

        // Need only first indexes in sampling
        if(!ref_indx.contains(sample))
            ref_indx.insert(sample, i);
    }
}

void RampChecker::resetCounters()
{
    period_errors = period_samples = 0;
    session_errors = session_samples = 0;
}
