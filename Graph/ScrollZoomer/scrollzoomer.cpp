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

#include "scrollbar.h"
#include "scrollzoomer.h"

#include <qevent.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_layout.h>
#include <qwt_scale_engine.h>
#include <qwt_scale_widget.h>

#include <stdexcept>

class ScrollData
{
public:
    ScrollData()
        :position(ScrollZoomer::OppositeToScale)
        ,mode(Qt::ScrollBarAsNeeded)
    {}

    QScopedPointer<ScrollBar> scrollBar;
    ScrollZoomer::ScrollBarPosition position;
    Qt::ScrollBarPolicy mode;
};

ScrollZoomer::ScrollZoomer(QWidget *canvas)
    :QwtPlotZoomer(canvas)
    ,d_hScrollData(new ScrollData)
    ,d_vScrollData(new ScrollData)
    ,d_inZoom(false)
{
    if(!canvas)
        throw std::runtime_error("Cannot initialize canvas.");

    for(qint32 axis = 0; axis < QwtPlot::axisCnt; axis++)
        d_alignCanvasToScales[axis] = false;
}

ScrollZoomer::~ScrollZoomer()
{
}

void ScrollZoomer::rescale()
{
    QwtScaleWidget *xScale = plot()->axisWidget(xAxis());
    QwtScaleWidget *yScale = plot()->axisWidget(yAxis());

    if(zoomRectIndex() <= 0)
    {
        if(d_inZoom)
        {
            xScale->setMinBorderDist(0, 0);
            yScale->setMinBorderDist(0, 0);

            QwtPlotLayout *layout = plot()->plotLayout();

            for (qint32 axis = 0; axis < QwtPlot::axisCnt; axis++)
                layout->setAlignCanvasToScale(axis, d_alignCanvasToScales);

            d_inZoom = false;
        }
    }
    else
    {
        if(!d_inZoom)
        {
            /*
             We set a minimum border distance.
             Otherwise the canvas size changes when scrolling,
             between situations where the major ticks are at
             the canvas borders (requiring extra space for the label)
             and situations where all labels can be paqint32ed below/top
             or left/right of the canvas.
             */
            qint32 start, end;

            xScale->getBorderDistHint(start, end);
            xScale->setMinBorderDist(start, end);

            yScale->getBorderDistHint(start, end);
            yScale->setMinBorderDist(start, end);

            QwtPlotLayout *layout = plot()->plotLayout();

            for (qint32 axis = 0; axis < QwtPlot::axisCnt; axis++) {
                d_alignCanvasToScales[axis] = layout->alignCanvasToScale(axis);
            }

            layout->setAlignCanvasToScales(false);
            d_inZoom = true;
        }
    }

    QwtPlotZoomer::rescale();
    updateScrollBars();
}

ScrollBar* ScrollZoomer::scrollBar(Qt::Orientation orientation)
{
    QScopedPointer<ScrollBar> &sb = (orientation == Qt::Vertical)
        ?(d_vScrollData->scrollBar):(d_hScrollData->scrollBar);

    if(!sb)
    {
        sb.reset(new ScrollBar(orientation, canvas()));
        sb->hide();
        connect(sb.data(),
                SIGNAL(valueChanged(Qt::Orientation, qreal, qreal)),
                SLOT(scrollBarMoved(Qt::Orientation, qreal, qreal)));
    }

    return sb.data();
}

ScrollBar* ScrollZoomer::horizontalScrollBar() const
{
    return d_hScrollData->scrollBar.data();
}

ScrollBar* ScrollZoomer::verticalScrollBar() const
{
    return d_vScrollData->scrollBar.data();
}

void ScrollZoomer::setHScrollBarMode(Qt::ScrollBarPolicy mode)
{
    if(hScrollBarMode() != mode)
    {
        d_hScrollData->mode = mode;
        updateScrollBars();
    }
}

void ScrollZoomer::setVScrollBarMode(Qt::ScrollBarPolicy mode)
{
    if(vScrollBarMode() != mode)
    {
        d_vScrollData->mode = mode;
        updateScrollBars();
    }
}

Qt::ScrollBarPolicy ScrollZoomer::hScrollBarMode() const
{
    return d_hScrollData->mode;
}

Qt::ScrollBarPolicy ScrollZoomer::vScrollBarMode() const
{
    return d_vScrollData->mode;
}

void ScrollZoomer::setHScrollBarPosition(ScrollBarPosition pos)
{
    if(d_hScrollData->position != pos)
    {
        d_hScrollData->position = pos;
        updateScrollBars();
    }
}

void ScrollZoomer::setVScrollBarPosition(ScrollBarPosition pos)
{
    if(d_vScrollData->position != pos)
    {
        d_vScrollData->position = pos;
        updateScrollBars();
    }
}

ScrollZoomer::ScrollBarPosition ScrollZoomer::hScrollBarPosition() const
{
    return d_hScrollData->position;
}

ScrollZoomer::ScrollBarPosition ScrollZoomer::vScrollBarPosition() const
{
    return d_vScrollData->position;
}

void ScrollZoomer::setCornerWidget(QWidget *w)
{
    if(w != d_cornerWidget.data())
    {
        if(canvas())
        {
            d_cornerWidget.reset(w);

            if(d_cornerWidget->parent() != canvas())
                d_cornerWidget->setParent(canvas());

            updateScrollBars();
        }
    }
}

QWidget* ScrollZoomer::cornerWidget() const
{
    return d_cornerWidget.data();
}

bool ScrollZoomer::eventFilter(QObject *object, QEvent *event)
{
    if(object == canvas())
    {
        switch(event->type())
        {
            case QEvent::Resize:
            {
                qint32 left, top, right, bottom;
                canvas()->getContentsMargins(&left, &top, &right, &bottom);

                QRect rect;
                rect.setSize(static_cast<QResizeEvent*>(event)->size());
                rect.adjust(left, top, -right, -bottom);

                layoutScrollBars(rect);
                break;
            }
            case QEvent::ChildRemoved:
            {
                const QObject *child = static_cast<QChildEvent*>(event)->child();

                if(child == d_cornerWidget.data()) {
                    d_cornerWidget.take();
                }
                else if(child == d_hScrollData->scrollBar.data()) {
                    d_hScrollData->scrollBar.take();
                }
                else if(child == d_vScrollData->scrollBar.data()) {
                    d_vScrollData->scrollBar.take();
                }

                break;
            }
            default:
                break;
        }
    }

    return QwtPlotZoomer::eventFilter(object, event);
}

bool ScrollZoomer::needScrollBar(Qt::Orientation orientation) const
{
    Qt::ScrollBarPolicy mode;
    qreal zoomMin, zoomMax, baseMin, baseMax;

    if(orientation == Qt::Horizontal)
    {
        mode = d_hScrollData->mode;
        baseMin = zoomBase().left();
        baseMax = zoomBase().right();
        zoomMin = zoomRect().left();
        zoomMax = zoomRect().right();
    }
    else
    {
        mode = d_vScrollData->mode;
        baseMin = zoomBase().top();
        baseMax = zoomBase().bottom();
        zoomMin = zoomRect().top();
        zoomMax = zoomRect().bottom();
    }

    bool needed = false;

    switch(mode)
    {
        case Qt::ScrollBarAlwaysOn:
            needed = true;
            break;
        case Qt::ScrollBarAlwaysOff:
            needed = false;
            break;
        default:
        {
            if(baseMin < zoomMin || baseMax > zoomMax)
                needed = true;
            break;
        }
    }

    return needed;
}

void ScrollZoomer::updateScrollBars()
{
    if(!canvas()) return;

    const qint32 xAxis = QwtPlotZoomer::xAxis();
    const qint32 yAxis = QwtPlotZoomer::yAxis();

    qint32 xScrollBarAxis = xAxis;
    if(hScrollBarPosition() == OppositeToScale)
        xScrollBarAxis = oppositeAxis(xScrollBarAxis);

    qint32 yScrollBarAxis = yAxis;
    if(vScrollBarPosition() == OppositeToScale)
        yScrollBarAxis = oppositeAxis(yScrollBarAxis);

    QwtPlotLayout *layout = plot()->plotLayout();

    bool showHScrollBar = needScrollBar(Qt::Horizontal);
    if(showHScrollBar)
    {
        ScrollBar *sb = scrollBar(Qt::Horizontal);
        sb->setPalette(plot()->palette());
        sb->setInverted(!plot()->axisScaleDiv(xAxis).isIncreasing());
        sb->setBase(zoomBase().left(), zoomBase().right());
        sb->moveSlider(zoomRect().left(), zoomRect().right());

        if(!sb->isVisibleTo(canvas()))
        {
            sb->show();
            layout->setCanvasMargin(layout->canvasMargin(xScrollBarAxis)
                                    + sb->extent(), xScrollBarAxis);
        }
    }
    else
    {
        if(horizontalScrollBar())
        {
            horizontalScrollBar()->hide();
            layout->setCanvasMargin(layout->canvasMargin(xScrollBarAxis)
                                    - horizontalScrollBar()->extent(), xScrollBarAxis);
        }
    }

    bool showVScrollBar = needScrollBar(Qt::Vertical);
    if(showVScrollBar)
    {
        ScrollBar *sb = scrollBar(Qt::Vertical);
        sb->setPalette(plot()->palette());
        sb->setInverted(!plot()->axisScaleDiv(yAxis).isIncreasing());
        sb->setBase(zoomBase().bottom(), zoomBase().top());
        sb->moveSlider(zoomRect().bottom(), zoomRect().top());

        if(!sb->isVisibleTo(canvas()))
        {
            sb->show();
            layout->setCanvasMargin(layout->canvasMargin(yScrollBarAxis)
                                    + sb->extent(), yScrollBarAxis);
        }
    }
    else
    {
        if(verticalScrollBar())
        {
            verticalScrollBar()->hide();
            layout->setCanvasMargin(layout->canvasMargin(yScrollBarAxis)
                                    - verticalScrollBar()->extent(), yScrollBarAxis);
        }
    }

    if(showHScrollBar && showVScrollBar)
    {
        if(!d_cornerWidget)
        {
            d_cornerWidget.reset(new QWidget(canvas()));
            d_cornerWidget->setAutoFillBackground(true);
            d_cornerWidget->setPalette(plot()->palette());
        }
        d_cornerWidget->show();
    }
    else
    {
        if(d_cornerWidget)
            d_cornerWidget->hide();
    }

    layoutScrollBars(canvas()->contentsRect());
    plot()->updateLayout();
}

void ScrollZoomer::layoutScrollBars(const QRect &rect)
{
    qint32 hPos = xAxis();
    if(hScrollBarPosition() == OppositeToScale)
        hPos = oppositeAxis(hPos);

    qint32 vPos = yAxis();
    if(vScrollBarPosition() == OppositeToScale)
        vPos = oppositeAxis(vPos);

    ScrollBar *hScrollBar = horizontalScrollBar();
    ScrollBar *vScrollBar = verticalScrollBar();

    const qint32 hdim = (hScrollBar)?(hScrollBar->extent()):(0);
    const qint32 vdim = (vScrollBar)?(vScrollBar->extent()):(0);

    if(hScrollBar && hScrollBar->isVisible())
    {
        qint32 x = rect.x();
        qint32 y = (hPos == QwtPlot::xTop)?(rect.top()):(rect.bottom() - hdim + 1);
        qint32 w = rect.width();

        if(vScrollBar && vScrollBar->isVisible())
        {
            if(vPos == QwtPlot::yLeft) x += vdim;
            w -= vdim;
        }

        hScrollBar->setGeometry(x, y, w, hdim);
    }

    if(vScrollBar && vScrollBar->isVisible())
    {
        qint32 pos = yAxis();

        if(vScrollBarPosition() == OppositeToScale) pos = oppositeAxis(pos);

        qint32 x = (vPos == QwtPlot::yLeft)?(rect.left()):(rect.right() - vdim + 1);
        qint32 y = rect.y();

        qint32 h = rect.height();

        if(hScrollBar && hScrollBar->isVisible())
        {
            if(hPos == QwtPlot::xTop) y += hdim;
            h -= hdim;
        }

        vScrollBar->setGeometry(x, y, vdim, h);
    }

    if(hScrollBar && hScrollBar->isVisible() &&
        vScrollBar && vScrollBar->isVisible())
    {
        if(d_cornerWidget)
        {
            QRect cornerRect(vScrollBar->pos().x(), hScrollBar->pos().y(), vdim, hdim);
            d_cornerWidget->setGeometry(cornerRect);
        }
    }
}

void ScrollZoomer::scrollBarMoved(Qt::Orientation o, qreal min, qreal max)
{
    Q_UNUSED(max);

    if(o == Qt::Horizontal) {
        moveTo(QPointF(min, zoomRect().top()));
    }
    else if(o == Qt::Vertical) {
        moveTo(QPointF(zoomRect().left(), max));
    }

    Q_EMIT zoomed(zoomRect());
}

qint32 ScrollZoomer::oppositeAxis(qint32 axis) const
{
    switch(axis)
    {
        case QwtPlot::xBottom:
            return QwtPlot::xTop;
        case QwtPlot::xTop:
            return QwtPlot::xBottom;
        case QwtPlot::yLeft:
            return QwtPlot::yRight;
        case QwtPlot::yRight:
            return QwtPlot::yLeft;
        default:
            break;
    }

    return axis;
}
