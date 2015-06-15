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

// --------------- Headers of Set Developing -----------//
// ------------------- Graph path ----------------------//

#include "plot.h"
#include "canvas.h"

//------------- Headers of Qt and Qwt Library ----------//

#include <qwt_plot_layout.h>
#include <qwt_curve_fitter.h>
#include <QEvent>

#include "Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/math_modules.h"

//---------------- Define class Plot -------------------//

Plot::Plot(QWidget *parent)
    :QwtPlot(parent)
    ,d_origin(new QwtPlotMarker)
    ,d_curve(new QwtPlotCurve)
    ,d_directPainter(new QwtPlotDirectPainter)
    ,d_grid(new QwtPlotGrid)
    ,d_paintedPoints(0)
    ,dx_interval(0, 1)
    ,dy_interval(-1, 1)
    ,d_timer_hz(-1)
    ,d_refreshRate(13)
    ,d_cnvsFlag(1)
{
    // Setup palette and off autoReplot function.
    setAutoReplot(false);
    setMinimumSize(400,500);

    // Setup canvas.
    QColor maj_cnvs_color = QColor(Qt::green);
    QColor min_cnvs_color = QColor(Qt::green);
#if (QT_VERSION > QT_VERSION_CHECK(4, 6, 3))
    if(QGLFormat::hasOpenGL())
        setCanvas(new GLCanvas);
    else
        setCanvas(new StandartCanvas);

    if(QGLFormat::hasOpenGL()) {
        d_cnvsFlag = 2;
        maj_cnvs_color = QColor(170, 190, 210);
        min_cnvs_color = QColor(110, 108, 108);
    }
#else
    setCanvas(new StandartCanvas);
#endif
    plotLayout()->setAlignCanvasToScales(true);

    // Create curves and attach them to plot.
    d_curve->setStyle(QwtPlotCurve::Lines);
    d_curve->setPen(QPen(QBrush(QColor(127,252,0)), d_cnvsFlag));
    d_curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    d_curve->setPaintAttribute(QwtPlotCurve::ClipPolygons, false);
    d_curve->setData(new CurveData);
    d_curve->attach(this);

    // Configure X axis.
    updateAxisX();
    // Configure Y axis.
    updateAxisY(dy_interval.maxValue());

    // Create and set custom plot grid.
    d_grid->setMajorPen(QPen(maj_cnvs_color, 0.0, Qt::DotLine));
    d_grid->setMinorPen(QPen(min_cnvs_color, 0.0, Qt::DotLine));
    d_grid->enableX(true);
    d_grid->enableXMin(true);
    d_grid->enableY(true);
    d_grid->enableYMin(true);
    d_grid->attach(this);

    // Create markers.
    d_origin->setLineStyle(QwtPlotMarker::Cross);
    d_origin->setValue(dx_interval.minValue()+dx_interval.width()/2.0, 0.0);
    d_origin->setLinePen(QPen(Qt::yellow, 0.0, Qt::DashLine));
    d_origin->attach(this);
}

void Plot::replot()
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());

    data->lock();
    QwtPlot::replot();
    data->unlock();
}

Plot::~Plot()
{
    emit storeFlagChanged(false);
}

void Plot::setPen(const QColor &color)
{
    d_curve->setPen(color, d_cnvsFlag);
}

void Plot::setUpdateTime(short ms)
{
    d_timer_hz = d_refreshRate = ms;

    if(isVisible() && ms > 0) {
        d_timer_hz = startTimer(ms);
    }
}

void Plot::setTimeDivider(int div)
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());
    data->setDivider(div);

    emit mathModuleChanged(data->requestMathModule());

    updateAxisX();
    replot();
}

void Plot::setScanDivider(int freq)
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());
    data->setScanFrequency(freq);

    emit mathModuleChanged(data->requestMathModule());

    updateAxisX();
    replot();
}

void Plot::setPhaseOffset(double offset)
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());
    data->setPhaseOffset(int(offset));
}

void Plot::setVoltsLevel(double lvl)
{
    updateAxisY(lvl);
    replot();
}

void Plot::setSamplingFrequency(ulong freq)
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());
    data->setSamplFrequency(freq);

    emit mathModuleChanged(data->requestMathModule());
}

void Plot::setBufferSize(Ipp32s size)
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());
    data->setBufferSize(size);

    emit mathModuleChanged(data->requestMathModule());
}

void Plot::setPhaseDetect(bool flag)
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());
    data->setPhaseDetect(flag);

    emit mathModuleChanged(data->requestMathModule());
}

void Plot::setDecimateSignal(bool flag)
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());
    data->setDecimateSignal(flag);

    emit mathModuleChanged(data->requestMathModule());
}

void Plot::setSignalTransform(bool flag)
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());
    data->setTransformSignal(flag);

    emit mathModuleChanged(data->requestMathModule());
}

void Plot::setFilterType(DenoisedGroupBox::filterType type)
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());
    data->setFilterType(type);

    emit mathModuleChanged(data->requestMathModule());
}

void Plot::addNewData(const ipp_vector<Ipp32f> &_data)
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());
    data->pushData(_data);
}

void Plot::clearData()
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());
    data->clearData();

    replot();
}

bool Plot::eventFilter(QObject *object, QEvent *event)
{
    if(object == canvas() &&
        event->type() == QEvent::PaletteChange)
    {
        d_curve->setPen(canvas()->palette().color(QPalette::WindowText));
    }

    return QwtPlot::eventFilter(object, event);
}

void Plot::changeEvent(QEvent * event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        CurveData *data = static_cast<CurveData*>(d_curve->data());
        data->updateTranslates();

        data->lock();

        setAxisTitle(QwtPlot::yLeft, tr("Amplitude") + " [" + data->titleY(dy_interval.maxValue()) + ']');
        setAxisTitle(QwtPlot::xBottom, tr("Time") + " [" + data->titleX() + ']');

        data->unlock();
    }

    QwtPlot::changeEvent(event);
}

void Plot::resizeEvent(QResizeEvent *event)
{
    d_directPainter->reset();

    updateCurve();
    updateAxisX();

    QwtPlot::resizeEvent(event);
}

void Plot::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == d_timer_hz)
    {
        CurveData *data = static_cast<CurveData*>(d_curve->data());

        if(data->isReadyToUpdate()) {
            data->updateValues();

            data->lock();
            QMetaObject::invokeMethod(canvas(), "repaint", Qt::DirectConnection);
            data->unlock();

            emit storeFlagChanged(true);
        }

        return;
    }

    QwtPlot::timerEvent(event);
}

void Plot::showEvent(QShowEvent *event)
{
    d_timer_hz = d_refreshRate;

    if(d_refreshRate != -1)
        d_timer_hz = startTimer(d_refreshRate);

    QwtPlot::showEvent(event);
}

void Plot::hideEvent(QHideEvent *event)
{
    d_timer_hz = -1;

    QwtPlot::hideEvent(event);
}

void Plot::updateCurve()
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());
    data->updateWidth(width()); // First change width.

    emit mathModuleChanged(data->requestMathModule());

    data->lock();

    const int numPoints = data->size();
    if(numPoints != d_paintedPoints)
    {
        if(!canvas()->testAttribute(Qt::WA_PaintOnScreen))
        {
            /* Depending on the platform setting a clip might be an important
               performance issue. F.e. for Qt Embedded this reduces the
               part of the backing store that has to be copied out - maybe
               to an unaccelerated frame buffer device. */

            const QwtScaleMap xMap = canvasMap(d_curve->xAxis());
            const QwtScaleMap yMap = canvasMap(d_curve->yAxis());

            QRectF br = qwtBoundingRect(*data, 0, numPoints-1);

            const QRect clipRect = QwtScaleMap::transform(xMap, yMap, br).toRect();
            d_directPainter->setClipRegion(clipRect);
        }

        d_paintedPoints = numPoints;
        d_directPainter->drawSeries(d_curve.data(), 0, numPoints-1);
    }

    data->unlock();
}

void Plot::updateAxisX()
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());
    data->lock();

    dx_interval = data->min_maxX();
    setAxisTitle(QwtPlot::xBottom, QObject::tr("Time") + " [" + data->titleX() + ']');

    data->unlock();

    setAxisScale(QwtPlot::xBottom, dx_interval.minValue(), dx_interval.maxValue());
    d_origin->setValue(dx_interval.minValue()+dx_interval.width()/2, 0);
}

void Plot::updateAxisY(double lvl)
{
    CurveData *data = static_cast<CurveData*>(d_curve->data());
    data->lock();

    dy_interval = QwtInterval((-lvl), lvl);

    setAxisTitle(QwtPlot::yLeft, tr("Amplitude") + " [" + data->titleY(lvl) + ']');
    setAxisScale(QwtPlot::yLeft, dy_interval.minValue(), dy_interval.maxValue());

    data->unlock();
}
