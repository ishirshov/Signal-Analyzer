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

#include "afccurvedata.h"

QPointF AFCCurveData::sample(size_t i) const
{
    return data.values[i];
}

size_t AFCCurveData::size() const
{
    return data.values.size();
}

QRectF AFCCurveData::boundingRect() const
{
    return data.boundingRect;
}

const QString& AFCCurveData::titleAxisX() const
{
    return data.titleAxisX;
}

const QString& AFCCurveData::titleAxisY() const
{
    return data.titleAxisY;
}

QwtInterval AFCCurveData::minMaxAxisX() const
{
    return QwtInterval(minAxisX(), maxAxisX());
}

QwtInterval AFCCurveData::minMaxAxisY() const
{
    // NOTE: minmax hardcode
    qreal min_y = -95.0;
    qreal max_y = 12.0;

    const QPointF *v_data = data.values.data();
    quint32 size = data.values.size();

    for(quint32 i = 0; i < size; ++i)
    {
        qreal curr_y = v_data[i].y();

        if(curr_y < min_y)
            min_y = curr_y;
        if(curr_y > max_y)
            max_y = curr_y;
    }

    return QwtInterval(min_y, max_y);
}

qreal AFCCurveData::maxAxisY() const
{
    qreal max_y = 12.f;

    const QPointF *v_data = data.values.data();
    quint32 size = data.values.size();

    for(quint32 i = 0; i < size; ++i)
        if(v_data[i].y() > max_y)
            max_y = v_data[i].y();

    return max_y;
}

qreal AFCCurveData::minAxisY() const
{
    qreal min_y = -95.f;

    const QPointF *v_data = data.values.data();
    quint32 size = data.values.size();

    for(quint32 i = 0; i < size; ++i)
        if(v_data[i].y() < min_y)
            min_y = v_data[i].y();

    return min_y;
}

qreal AFCCurveData::maxAxisX() const
{
    return (data.values.size())?(data.values[data.values.size()-1].x()):(1);
}

qreal AFCCurveData::minAxisX() const
{
    return (data.values.size())?(data.values[0].x()):(0);
}

ulong AFCCurveData::signalFrequency() const
{
    return data.signalFreq;
}

bool AFCCurveData::readyToUpdate() const
{
    return data.isData;
}

const std::set<QPointF,greatherThen> &AFCCurveData::peaks() const
{
    return data.peaks;
}

#include "peak_detect.h"

void AFCCurveData::addData(const ipp_vector<Ipp32f> &yAFC)
{
    if(yAFC.empty()) return;

    const Ipp32f *yVals = yAFC.data();
    qint32 ySize = yAFC.size();

    // Calculate zone sizes.
    QPointF *values = data.values.data();
    quint32 valSize = data.values.size();

    for(quint32 i = 0; (i < ySize) && (i < valSize); ++i)
        values[i].setY(yVals[i]);

    // Find peak.
    ipp_ptr<Ipp32f> peak_y(get_peaks(yVals, ySize, 5, 1.5, S3));

    // Create peak map.
    peaksSet &peaks = data.peaks;
    peaks.clear();

    // In begin add all peaks into
    // hash map.
    for(quint32 i = 0; i < ySize; ++i)
        if(peak_y[i] != 0.0)
            peaks.insert(values[i]);

    if(data.userPeaks <= peaks.size())
    {
        // Then remove unused peaks from
        // hash map.
        peaksSet::iterator remove_beg = peaks.begin();
        peaksSet::iterator remove_end = peaks.end();
        quint32 n = 0;

        // Find begin of erase range.
        while(remove_beg != remove_end)
        {
            if(n == data.userPeaks)
                break;

            ++remove_beg;
            ++n;
        }

        peaks.erase(remove_beg, remove_end);
    }

    data.isData = true;
}

void AFCCurveData::clearData(Type type)
{
    switch(type)
    {
    case Flags:
    {
        data.isData = false;
        break;
    }
    case Data:
    {
        QPointF *v_data = data.values.data();
        quint32 size = data.values.size();

        qreal y = minAxisY();

        for(quint32 i = 0; i < size; ++i)
            v_data[i].setY(y);

        data.isData = false;
        break;
    }
    default:
        break;
    }
}

void AFCCurveData::updateTranslate()
{
    data.changeTitles();
}

void AFCCurveData::setWidth(int width)
{
    // Change internal data:
    data.changeWidth(width, QPointF(minAxisX(), minAxisY()));
    data.changeAxisX();
    data.changeTitles();
}

void AFCCurveData::setUserPeaksNum(int num)
{
    if(num < 0) num = 0;

    data.userPeaks = num;
}

void AFCCurveData::setSamplingFrequency(long freq)
{
    if(freq <= 0) throw std::runtime_error("Sampling frequency must be positive.");

    data.signalFreq = (freq / 2);
    data.changeAxisX();
    data.changeTitles();
}
