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

#ifndef _SCROLLZOOMER_H
#define _SCROLLZOOMER_H

#include <qglobal.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot.h>

#include <QScopedPointer>

class ScrollData;
class ScrollBar;

/*!
 * \brief Класс ScrollZoomer
 */
class ScrollZoomer: public QwtPlotZoomer
{
    Q_OBJECT

public:
    /*!
     * \brief The ScrollBarPosition enum
     */
    enum ScrollBarPosition
    {
        AttachedToScale,    /*!< */
        OppositeToScale     /*!< */
    };

    /*!
     * \brief ScrollZoomer
     * \param[in] parent
     */
    ScrollZoomer(QWidget *parent);

    /*!
     * \brief ~ScrollZoomer
     */
    virtual ~ScrollZoomer();

    ScrollBar *horizontalScrollBar() const;
    ScrollBar *verticalScrollBar() const;

    void setHScrollBarMode(Qt::ScrollBarPolicy);
    void setVScrollBarMode(Qt::ScrollBarPolicy);

    Qt::ScrollBarPolicy vScrollBarMode() const;
    Qt::ScrollBarPolicy hScrollBarMode() const;

    void setHScrollBarPosition(ScrollBarPosition);
    void setVScrollBarPosition(ScrollBarPosition);

    ScrollBarPosition hScrollBarPosition() const;
    ScrollBarPosition vScrollBarPosition() const;

    QWidget* cornerWidget() const;
    virtual void setCornerWidget(QWidget *);

    virtual bool eventFilter(QObject *, QEvent *);

    virtual void rescale();

protected:
    virtual ScrollBar *scrollBar(Qt::Orientation);
    virtual void updateScrollBars();
    virtual void layoutScrollBars(const QRect &);

private slots:
    void scrollBarMoved(Qt::Orientation o, qreal min, qreal max);

private:
    bool needScrollBar(Qt::Orientation) const;
    qint32 oppositeAxis(qint32) const;

    QScopedPointer<QWidget> d_cornerWidget;
    QScopedPointer<ScrollData> d_hScrollData;
    QScopedPointer<ScrollData> d_vScrollData;

    bool d_inZoom;
    bool d_alignCanvasToScales[QwtPlot::axisCnt];
};

#endif
