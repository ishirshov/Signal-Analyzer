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

#include "standart_canvas.h"

StandartCanvas::StandartCanvas(QwtPlot *plot)
    :QwtPlotCanvas(plot)
{
    // The backing store is important, when working with widget
    // overlays ( f.e rubberbands for zooming ).
    // Here we don't have them and the internal
    // backing store of QWidget is good enough.

    setPaintAttribute(QwtPlotCanvas::BackingStore, false);
    setBorderRadius(10);
    setLineWidth(1);

    if(QwtPainter::isX11GraphicsSystem())
    {
    #if QT_VERSION < 0x050000
        // Even if not liked by the Qt development, Qt::WA_PaintOutsidePaintEvent
        // works on X11. This has a nice effect on the performance.

        setAttribute(Qt::WA_PaintOutsidePaintEvent, true);
    #endif

        // Disabling the backing store of Qt improves the performance
        // for the direct painter even more, but the canvas becomes
        // a native window of the window system, receiving paint events
        // for resize and expose operations. Those might be expensive
        // when there are many points and the backing store of
        // the canvas is disabled. So in this application
        // we better don't both backing stores.

        if(testPaintAttribute(QwtPlotCanvas::BackingStore))
        {
            setAttribute(Qt::WA_PaintOnScreen, true);
            setAttribute(Qt::WA_NoSystemBackground, true);
        }
    }

    setupPalette();
}

void StandartCanvas::setupPalette()
{
    QPalette pal = palette();

#if QT_VERSION >= 0x040400
    QLinearGradient gradient;
    gradient.setCoordinateMode(QGradient::StretchToDeviceMode);
    gradient.setColorAt(0.0, QColor(154, 154, 154));
    gradient.setColorAt(1.0, QColor(150, 154, 154));

    pal.setBrush(QPalette::Window, QBrush(gradient));
#else
    pal.setBrush(QPalette::Window, QBrush(color));
#endif

    // QPalette::WindowText is used for the curve color
    pal.setColor(QPalette::WindowText, Qt::green);

    setPalette(pal);
}
