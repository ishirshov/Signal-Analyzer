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

#include "playbackplot.h"
#include "canvas.h"

//------------- Headers of Qt and Qwt Library ----------//

#include <qwt_plot_layout.h>
#include <qwt_curve_fitter.h>
#include <qwt_scale_widget.h>

#include <QEvent>

PlaybackPlot::PlaybackPlot(QWidget *parent)
    :QwtPlot(parent)
    ,d_curve(new QwtPlotCurve)
    ,d_origin(new QwtPlotMarker)
    ,d_directPainter(new QwtPlotDirectPainter)
    ,d_grid(new QwtPlotGrid)
    ,dx_interval(0, 1)
    ,dy_interval(dx_interval)
    ,d_cnvsFlag(1)
{
    // Setup palette and off autoReplot function.
    setAutoReplot(false);
    setMinimumSize(400, 500);

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

    QwtScaleDraw *sd = axisScaleDraw(QwtPlot::yLeft);
    sd->setMinimumExtent(sd->extent(axisWidget(QwtPlot::yLeft)->font()));

    canvas()->installEventFilter(this);
    plotLayout()->setAlignCanvasToScales(true);

    // Create curves and attach them to plot.
    d_curve->setStyle(QwtPlotCurve::Lines);
    d_curve->setPen(QPen(QBrush(QColor(127,252,0)), d_cnvsFlag));
    d_curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    d_curve->setPaintAttribute(QwtPlotCurve::ClipPolygons, false);
    d_curve->setData(new PlaybackCurveData);
    d_curve->attach(this);

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

    // Settings Axis.
    setAxisScale(QwtPlot::xBottom, dx_interval.minValue(), dx_interval.maxValue());
    setAxisTitle(QwtPlot::xBottom, tr("Time [ms]"));
    setAxisTitle(QwtPlot::yLeft, tr("Amplitude [Volts]"));

    updateAxisY();

    // Create canvas wheel.
    dx_wheel.reset(new QwtWheel(canvas()));
    dx_wheel->setPalette(QPalette(QColor(Qt::white)));
    dx_wheel->setRange(dx_interval.minValue(), dx_interval.maxValue());
    dx_wheel->setValue(0.0);
    dx_wheel->setMass(0.5);
    dx_wheel->setTotalAngle(4 * 360.0);
    dx_wheel->setVisible(true);

    connect(dx_wheel.data(), SIGNAL(valueChanged(double)), SLOT(scrollBottomAxis(double)));
}

PlaybackPlot::~PlaybackPlot()
{
    emit storeFlagChanged(false);
}

void PlaybackPlot::addNewData(QVector<QPointF> *_data)
{
    PlaybackCurveData *data = static_cast<PlaybackCurveData*>(d_curve->data());
    data->appendData(_data);

    if(data->readyToUpdate())
    {
        updateXWheel();
        replot();
    }
}

void PlaybackPlot::clearData()
{
    PlaybackCurveData *data = static_cast<PlaybackCurveData*>(d_curve->data());
    data->clearData();

    replot();
}

void PlaybackPlot::scrollBottomAxis(double val)
{
    // Setting bottom axis scale.
    setAxisScale(QwtPlot::xBottom, val, val + 1);

    // And replace cross line.
    d_origin->setValue(val + dx_interval.width()/2.0, 0.0);

    replot();
}

bool PlaybackPlot::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::Resize)
    {
        QWidget *plotCanvas = canvas();
        if(object == plotCanvas)
        {
            const int w = 70;
            const int h = 20;

            const QRect cr = plotCanvas->contentsRect();
            dx_wheel->setGeometry(cr.center().x() - w/2, cr.bottom() - h, w, h);
        }
    }

    return QwtPlot::eventFilter(object, event);
}

void PlaybackPlot::resizeEvent(QResizeEvent *event)
{
    d_directPainter->reset();

    emit windowWidthChanged(width());

    QwtPlot::resizeEvent(event);
}

void PlaybackPlot::updateXWheel()
{
    PlaybackCurveData *data = static_cast<PlaybackCurveData*>(d_curve->data());

    QwtInterval new_x = data->min_maxX();

    if(new_x.maxValue() > dx_interval.maxValue())
    {
        dx_wheel->setRange(new_x.minValue(), new_x.maxValue() + 1);
        dx_wheel->setVisible(true);
    }
    else {
        dx_wheel->setRange(dx_interval.minValue(), dx_interval.maxValue());
        dx_wheel->setVisible(false);
    }
}

void PlaybackPlot::updateAxisY()
{
    PlaybackCurveData *data = static_cast<PlaybackCurveData*>(d_curve->data());

    dy_interval = data->min_maxY();
    setAxisScale(QwtPlot::yLeft, dy_interval.minValue(), dy_interval.maxValue());
}
