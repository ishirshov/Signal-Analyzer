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

// -------------------------------- Graph path ----------------------------------------//

#include "afcplot.h"
#include "canvas.h"

//--------------------------- Headers of Qt and Qwt Library ---------------------------//

#include <qwt_plot_layout.h>
#include <qwt_curve_fitter.h>
#include <qwt_symbol.h>
#include <QEvent>

//-------------------------------- Define class AFCPlot -------------------------------//

AFCPlot::AFCPlot(QWidget *parent)
    :QwtPlot(parent)
    ,d_curve(new QwtPlotCurve)
    ,d_directPainter(new QwtPlotDirectPainter(this))
    ,d_grid(new QwtPlotGrid)
    ,d_paintedPoints(0)
    ,dx_interval(0, 1)
    ,dy_interval(-1, 1)
    ,d_timer_hz(-1)
    ,d_refreshRate(-1)
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
    d_curve->setPen(QPen(QBrush(QColor(204,0,204)), d_cnvsFlag));
    d_curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    d_curve->setPaintAttribute(QwtPlotCurve::ClipPolygons, false);
    d_curve->setData(new AFCCurveData);
    d_curve->attach(this);

    // Configure X axis.
    updateAxisX();
    // Configure Y axis.
    updateAxisY();

    // Create and set custom plot grid.
    d_grid->setMajorPen(QPen(maj_cnvs_color, 0.0, Qt::DotLine));
    d_grid->setMinorPen(QPen(min_cnvs_color, 0.0, Qt::DotLine));
    d_grid->enableX(true);
    d_grid->enableXMin(true);
    d_grid->enableY(true);
    d_grid->enableYMin(true);
    d_grid->attach(this);   
}

AFCPlot::~AFCPlot()
{
    emit storeFlagChanged(false);
}

void AFCPlot::setUpdateTime(short ms)
{
    d_timer_hz = d_refreshRate = ms;

    if(isVisible() && ms > 0)
        d_timer_hz = startTimer(ms);
}

void AFCPlot::setSamplingFrequency(ulong freq)
{
    AFCCurveData *data = static_cast<AFCCurveData*>(d_curve->data());
    data->setSamplingFrequency(freq);

    updateAxisX();
    replot();
}

void AFCPlot::setNumberPeaks(int num)
{
    AFCCurveData *data = static_cast<AFCCurveData*>(d_curve->data());
    data->setUserPeaksNum(num);
}

void AFCPlot::addNewData(const ipp_vector<Ipp32f> &data)
{
    AFCCurveData *afcdata = static_cast<AFCCurveData*>(d_curve->data());
    afcdata->addData(data);
}

void AFCPlot::sendInitialSettings()
{
    AFCCurveData *data = static_cast<AFCCurveData*>(d_curve->data());
    emit settingsChanged(data->size());
}

void AFCPlot::clearData()
{
    AFCCurveData *data = static_cast<AFCCurveData*>(d_curve->data());
    data->clearData(AFCCurveData::Data);

    deleteMarkers();
    replot();
}

bool AFCPlot::eventFilter(QObject *object, QEvent *event)
{
    if(object == canvas() && (event->type() == QEvent::PaletteChange))
        d_curve->setPen(canvas()->palette().color(QPalette::WindowText));

    return QwtPlot::eventFilter(object, event);
}

void AFCPlot::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        AFCCurveData *data = static_cast<AFCCurveData*>(d_curve->data());
        data->updateTranslate();

        QString titleX = tr("Frequency [ ") + data->titleAxisX() + " ]";
        QString titleY = tr("Amplitude [ ") + data->titleAxisY() + " ]";

        setAxisTitle(QwtPlot::xBottom, titleX);
        setAxisTitle(QwtPlot::yLeft, titleY);
    }

    QwtPlot::changeEvent(event);
}

void AFCPlot::resizeEvent(QResizeEvent *event)
{
    d_directPainter->reset();

    updateCurve();
    updateAxisX();
    updateAxisY();

    deleteMarkers();

    QwtPlot::resizeEvent(event);
}

void AFCPlot::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == d_timer_hz)
    {
        AFCCurveData *data = static_cast<AFCCurveData*>(d_curve->data());

        if(data->readyToUpdate()) {
            updateAxisY();
            showPeaks();

            QMetaObject::invokeMethod(canvas(), "repaint", Qt::DirectConnection);

            data->clearData(AFCCurveData::Flags);
            emit storeFlagChanged(true);
        }

        return;
    }

    QwtPlot::timerEvent(event);
}

void AFCPlot::showEvent(QShowEvent *event)
{
    d_timer_hz = d_refreshRate;

    if(d_refreshRate != -1)
        d_timer_hz = startTimer(d_refreshRate);

    QwtPlot::showEvent(event);
}

void AFCPlot::hideEvent(QHideEvent *event)
{
    d_timer_hz = -1;

    QwtPlot::hideEvent(event);
}

void AFCPlot::showPeaks()
{
    deleteMarkers();
    AFCCurveData *data = static_cast<AFCCurveData*>(d_curve->data());

    QString preX = " " + data->titleAxisX();
    QString preY = " " + data->titleAxisY();

    const AFCCurveData::peaksSet &peaks = data->peaks();
    AFCCurveData::peaksSet::const_iterator peak = peaks.begin();
    AFCCurveData::peaksSet::const_iterator end = peaks.end();

    for(; peak != end; ++peak)
    {
        QScopedPointer<QwtPlotMarker> marker(new QwtPlotMarker);

        // Prepare label for current peak.
        QString label;
        QTextStream stream(&label);
        stream.setRealNumberPrecision(4);

        stream << tr("Frequency: ") << peak->x() << preX << '\n'
               << tr("Peak: ") << peak->y() << preY;

        QwtText text(label);
        text.setFont(QFont("Helvetica", 10, QFont::Bold));
        text.setColor(QColor(200, 150, 0));

        // Settings plot marker.
        marker->setValue(*peak);
        marker->setLabel(text);
        marker->setLabelAlignment(Qt::AlignCenter | Qt::AlignTop);
        marker->setSymbol(new QwtSymbol(QwtSymbol::Diamond,
                                      QColor(Qt::yellow),
                                      QColor(Qt::green), QSize(8, 8)));
        marker->attach(this);

        d_markers.push_back(marker.take());
    }
}

void AFCPlot::deleteMarkers()
{
    while(d_markers.size())
    {
        QwtPlotMarker *marker = d_markers.back();
        d_markers.pop_back();

        marker->detach();
        delete marker;
    }
}

void AFCPlot::updateCurve()
{
    AFCCurveData *data = static_cast<AFCCurveData*>(d_curve->data());
    data->setWidth(width());

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
        d_directPainter->drawSeries(d_curve, 0, numPoints-1);
    }

    emit settingsChanged(numPoints);
}

void AFCPlot::updateAxisX()
{
    AFCCurveData *data = static_cast<AFCCurveData*>(d_curve->data());

    dx_interval = data->minMaxAxisX();
    QString title = tr("Frequency [ ") + data->titleAxisX() + " ]";

    setAxisTitle(QwtPlot::xBottom, title);
    setAxisScale(QwtPlot::xBottom, dx_interval.minValue(), dx_interval.maxValue());
}

void AFCPlot::updateAxisY()
{
    AFCCurveData *data = static_cast<AFCCurveData*>(d_curve->data());

    QwtInterval dy_new = data->minMaxAxisY();

    if(dy_new != dy_interval)
    {
        dy_interval = dy_new;
        QString title = tr("Amplitude [ ") + data->titleAxisY() + " ]";

        setAxisTitle(QwtPlot::yLeft, title);
        setAxisScale(QwtPlot::yLeft, dy_interval.minValue(), dy_interval.maxValue());

        replot();
    }
}
