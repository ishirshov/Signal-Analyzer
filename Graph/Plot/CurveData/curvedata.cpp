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

#include "curvedata.h"

#include "Functional/IPP/general_functions.h"
#include "Functional/IPP/Interpolation/interpolation.h"
#include "Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/math_modules.h"
#include "Functional/IPP/Additionals/vars.h"

void CurveData::updateCoefficients()
{
    // First change internal data.
    data.clearData();
    data.changeTimeAxis();
    data.bounding_rect = QRectF(0.0, 0.0, -1.0, -1.0);
}

QPointF CurveData::sample(size_t i) const
{
    return data.values[i];
}

size_t CurveData::size() const
{
    return data.values.size();
}

QRectF CurveData::boundingRect() const
{
    return data.bounding_rect;
}

const QString& CurveData::titleX() const
{
    return data.title_time;
}

const QString CurveData::titleY(double lvl) const
{
    return data.amplitude[lvl];
}

QwtInterval CurveData::min_maxX() const
{
    qreal min_x = (data.values.size())?(data.values[0].x()):(0);
    qreal max_x = (data.values.size())?(data.values[data.values.size()-1].x()):(1);

    return QwtInterval(min_x, max_x);
}

QwtInterval CurveData::min_maxY() const
{
    qreal min_y = 0.0;
    qreal max_y = 0.0;

    const QPointF *v_data = data.values.data();
    quint32 size = data.values.size();

    for(quint32 i = 0; i < size; ++i)
    {
        qreal curr_y = v_data[i].y();

        if(curr_y < min_y) min_y = curr_y;
        if(curr_y > max_y) max_y = curr_y;
    }

    return QwtInterval(min_y, max_y);
}

MathModule *CurveData::requestMathModule() const
{
    QScopedPointer<MathModule> module;

    quint32 val_size = data.values.size();

    if(data.is_enable_decimate_sig)
    {
        quint32 fact_points = data.divider * (data.sampling_freq/data.frequency);
        if(fact_points < data.window_with)
        {
            quint32 src_frequency = fact_points * 2;
            quint32 dst_frequency = val_size * 2;
            module.reset(new ResamplingUp(src_frequency, dst_frequency));
        }
        else if(fact_points > data.window_with)
        {
            quint32 factor = std::floor(fact_points/val_size);
            quint32 target_frequency = fact_points * 2;

            module.reset(new ResamplingDown(target_frequency, factor));
        }
    }
    else
    {
        quint32 fact_points = data.sampling_freq/(data.frequency/data.divider);
        bool is_sig_interp = false;
        bool is_sig_approx = false;

        if(data.is_enable_sig_transform && (fact_points > 1))
        {
            if(fact_points > data.window_with)
            {
                is_sig_approx = true;
            }
            else if(fact_points < data.window_with)
            {
                is_sig_interp = true;
                qreal delta_t = (data.divider * (data.sampling_freq/data.frequency))/fact_points;
                module.reset(new InterpSig(new ApproxHighFrequency(fact_points, delta_t), val_size * 2));
            }
        }

        if(!is_sig_interp)
        {
            qreal delta_t = (data.divider * (data.sampling_freq/data.frequency))/val_size;
            qreal payload_array = delta_t/qreal(data.array_size);
            quint32 size_points = val_size * 2;
            qreal size_arrays = std::floor(payload_array * qreal(val_size));

            if(is_sig_approx)
                module.reset(new ApproxLowFrequency(size_points, delta_t));
            else
                module.reset(new ApproxDeltaT(size_points, delta_t, payload_array));
        }
    }

    module.reset(new LevelToVlts(module.take()));
    LevelToVlts *volts_module = static_cast<LevelToVlts*>(module.data());
    volts_module->setVolts(GlobalVariables::getInstance().getVoltsLevel());

    QObject::connect(&GlobalVariables::getInstance(), SIGNAL(voltsLevelChanged(Ipp32f)),
                     volts_module, SLOT(setVolts(Ipp32f)));

    if(data.is_enable_phase_detect)
        module.reset(new PhaseOffset(module.take()));

    switch(data.current_filter_type)
    {
    case DenoisedGroupBox::Median:
    {
        QScopedPointer<MedianFilter> median(new MedianFilter(module.take()));
        QObject::connect(&GlobalVariables::getInstance(), SIGNAL(medianKChanged(Ipp32s)),
                                        median.data(), SLOT(setMedianK(Ipp32s)), Qt::QueuedConnection);

        module.reset(median.take());
        break;
    }
    case DenoisedGroupBox::Kalman:
    {
        QScopedPointer<SimpleKalmanFilter> kalman(new SimpleKalmanFilter(module.take()));
        QObject::connect(&GlobalVariables::getInstance(), SIGNAL(kalmanGainChanged(Ipp32f)),
                                        kalman.data(), SLOT(setKalmanGain(Ipp32f)), Qt::QueuedConnection);

        module.reset(kalman.take());
        break;
    }
    case DenoisedGroupBox::WaveletSoft:
    {
        QScopedPointer<WaveletTransformation> trans(new WaveletTransformation(module.take(), new SoftThresholding));
        QObject::connect(&GlobalVariables::getInstance(), SIGNAL(waveletFilterBankChanged(waveletFilterBanks)),
                         trans.data(), SLOT(setFilterBank(waveletFilterBanks)));

        module.reset(trans.take());
        break;
    }
    case DenoisedGroupBox::WaveletHyperbolic:
    {
        QScopedPointer<WaveletTransformation> trans(new WaveletTransformation(module.take(), new SoftThresholding));
        QObject::connect(&GlobalVariables::getInstance(), SIGNAL(transformLevelChanged(Ipp32s)),
                         trans.data(), SLOT(setTransformationLevel(Ipp32s)));

        module.reset(trans.take());
        break;
    }
    default:
        break;
    };

    return module.take();
}

void CurveData::updateWidth(int width)
{
    QWriteLocker locker(&data.lock);

    // First change internal data.
    data.changeWidth(width);

    updateCoefficients();
}

void CurveData::updateTranslates()
{
    QWriteLocker locker(&data.lock);

    data.updateTimeVector();
    data.updateAmplitudeMap();
}

void CurveData::updateValues()
{
    QMutexLocker mlocker(&data.pend_guard);

    if(data.pending.empty()) return;

    // New data for graph plot
    Ipp32f *pendData = data.pending.data();
    qint32 pendSize = data.pending.size();

    QWriteLocker locker(&data.lock);

    // Original data on to graph plot
    QPointF *valData = data.values.data();
    qint32 valSize = data.values.size();

    // Determine index of signal shift
    qint32 offset = data.offset;
    if(offset >= valSize)
        offset = offset - valSize;
    else if(offset < 0)
        offset = valSize - (-offset);

    // Execute user shift.
    for(quint32 i = 0; i < pendSize; ++i)
    {
        valData[offset].setY(pendData[i]);
        if((++offset) == valSize) offset = 0;
    }

    data.pending.clear();
    data.bounding_rect = QRect(0.0, 0.0, -1.0, -1.0);
}

void CurveData::pushData(const ipp_vector<Ipp32f> &_data)
{
    if(_data.empty()) return;

    if(data.pending.empty()) {
       QMutexLocker mlocker(&data.pend_guard);
       data.pending.push_back(_data, _data.size());
    }
}

void CurveData::clearData()
{
    QWriteLocker locker(&data.lock);

    data.clearData();
}

void CurveData::setDivider(int div)
{
    QWriteLocker locker(&data.lock);

    data.divider = div;

    printDebug(QString("Time divider changed: %1").arg(data.divider));
    updateCoefficients();
}

void CurveData::setScanFrequency(int freq)
{
    QWriteLocker locker(&data.lock);

    data.frequency = freq;

    printDebug(QString("Scan divider changed: %1").arg(data.frequency));
    updateCoefficients();
}

void CurveData::setPhaseOffset(int offst)
{
    QWriteLocker locker(&data.lock);

    data.offset = offst;
}

void CurveData::setSamplFrequency(ulong freq)
{
    QWriteLocker locker(&data.lock);

    data.sampling_freq = freq;
}

void CurveData::setBufferSize(quint32 size)
{
    QWriteLocker locker(&data.lock);

    data.array_size = size;
}

void CurveData::setPhaseDetect(bool flag)
{
    QWriteLocker locker(&data.lock);

    data.is_enable_phase_detect = flag;
}

void CurveData::setTransformSignal(bool flag)
{
    QWriteLocker locker(&data.lock);

    data.is_enable_sig_transform = flag;
}

void CurveData::setFilterType(DenoisedGroupBox::filterType type)
{
    QWriteLocker locker(&data.lock);

    data.current_filter_type = type;
}

void CurveData::setDecimateSignal(bool flag)
{
    QWriteLocker locker(&data.lock);

    data.is_enable_decimate_sig = flag;
}

bool CurveData::isReadyToUpdate() const
{
    return !data.pending.empty();
}

void CurveData::lock()
{
    data.lock.lockForRead();
}

void CurveData::unlock()
{
    data.lock.unlock();
}
