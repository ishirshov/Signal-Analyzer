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

#include "gl_canvas.h"
#include "qwt_plot.h"

GLCanvas::GLCanvas(QwtPlot *plot)
    :QwtPlotGLCanvas(plot)
{
    setContentsMargins(1, 1, 1, 1);
    setPalette(QColor(63, 63, 63));

    if(QwtPainter::isX11GraphicsSystem())
    {
#if QT_VERSION < 0x050000
        setAttribute(Qt::WA_PaintOutsidePaintEvent, true);
#endif
        setAttribute(Qt::WA_PaintOnScreen, true);
    }
}

void GLCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setClipRegion(event->region());

    QwtPlot *plot = qobject_cast<QwtPlot*>(parent());
    if(plot) plot->drawCanvas(&painter);

    painter.setPen(palette().foreground().color());
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
}

void GLCanvas::setupPalette()
{
    QPalette pal = palette();

#if QT_VERSION >= 0x040400
    QLinearGradient gradient;
    gradient.setCoordinateMode(QGradient::StretchToDeviceMode);
    gradient.setColorAt(0.0, QColor(0, 0, 0));
    gradient.setColorAt(1.0, QColor(154, 154, 154));

    pal.setBrush(QPalette::Window, QBrush(gradient));
#else
    pal.setBrush(QPalette::Window, QBrush(color));
#endif

    // QPalette::WindowText is used for the curve color
    pal.setColor(QPalette::WindowText, QColor(154, 154, 154));

    setPalette(pal);
}
