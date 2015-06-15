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

#include <qstyle.h>
#include <qstyleoption.h>
#include "scrollbar.h"

ScrollBar::ScrollBar(QWidget * parent)
    :QScrollBar(parent)
{
    init();
}

ScrollBar::ScrollBar(Qt::Orientation o, QWidget *parent)
    :QScrollBar(o, parent)
{
    init();
}

ScrollBar::ScrollBar(qreal minBase, qreal maxBase,
        Qt::Orientation o, QWidget *parent):
    QScrollBar(o, parent)
{
    init();
    setBase(minBase, maxBase);
    moveSlider(minBase, maxBase);
}

void ScrollBar::init()
{
    d_inverted = orientation() == Qt::Vertical;
    d_baseTicks = 1000000;
    d_minBase = 0.0;
    d_maxBase = 1.0;
    moveSlider(d_minBase, d_maxBase);

    connect(this, SIGNAL(sliderMoved(int)), SLOT(catchSliderMoved(int)));
    connect(this, SIGNAL(valueChanged(int)), SLOT(catchValueChanged(int)));
}

void ScrollBar::setInverted(bool inverted)
{
    if(d_inverted != inverted)
    {
        d_inverted = inverted;
        moveSlider(minSliderValue(), maxSliderValue());
    }
}

bool ScrollBar::isInverted() const
{
    return d_inverted;
}

void ScrollBar::setBase(qreal min, qreal max)
{
    if(min != d_minBase || max != d_maxBase)
    {
        d_minBase = min;
        d_maxBase = max;

        moveSlider(minSliderValue(), maxSliderValue());
    }
}

void ScrollBar::moveSlider(qreal min, qreal max)
{
    const int sliderTicks = qRound((max - min) /
        (d_maxBase - d_minBase) * d_baseTicks);

    // setRange initiates a valueChanged of the scrollbars
    // in some situations. So we block
    // and unblock the signals.

    blockSignals(true);

    setRange(sliderTicks / 2, d_baseTicks - sliderTicks / 2);
    int steps = sliderTicks / 200;

    if(steps <= 0)
        steps = 1;

    setSingleStep(steps);
    setPageStep(sliderTicks);

    int tick = mapToTick(min + (max - min) / 2);

    if(isInverted())
        tick = d_baseTicks - tick;

    setSliderPosition(tick);
    blockSignals(false);
}

qreal ScrollBar::minBaseValue() const
{
    return d_minBase;
}

qreal ScrollBar::maxBaseValue() const
{
    return d_maxBase;
}

void ScrollBar::sliderRange(int value, qreal &min, qreal &max) const
{
    if(isInverted())
        value = d_baseTicks - value;

    const int visibleTicks = pageStep();

    min = mapFromTick(value - visibleTicks / 2);
    max = mapFromTick(value + visibleTicks / 2);
}

qreal ScrollBar::minSliderValue() const
{
    qreal min, dummy;
    sliderRange(value(), min, dummy);

    return min;
}

qreal ScrollBar::maxSliderValue() const
{
    qreal max, dummy;
    sliderRange(value(), dummy, max);

    return max;
}

int ScrollBar::mapToTick(qreal v) const
{
    const qreal pos = (v - d_minBase) / (d_maxBase - d_minBase) * d_baseTicks;
    return static_cast<int>(pos);
}

qreal ScrollBar::mapFromTick(int tick) const
{
    return d_minBase + (d_maxBase - d_minBase) * tick / d_baseTicks;
}

void ScrollBar::catchValueChanged(int value)
{
    qreal min, max;
    sliderRange(value, min, max);
    Q_EMIT valueChanged(orientation(), min, max);
}

void ScrollBar::catchSliderMoved(int value)
{
    qreal min, max;
    sliderRange(value, min, max);
    Q_EMIT sliderMoved(orientation(), min, max);
}

int ScrollBar::extent() const
{
    QStyleOptionSlider opt;
    opt.init(this);
    opt.subControls = QStyle::SC_None;
    opt.activeSubControls = QStyle::SC_None;
    opt.orientation = orientation();
    opt.minimum = minimum();
    opt.maximum = maximum();
    opt.sliderPosition = sliderPosition();
    opt.sliderValue = value();
    opt.singleStep = singleStep();
    opt.pageStep = pageStep();
    opt.upsideDown = invertedAppearance();

    if(orientation() == Qt::Horizontal)
        opt.state |= QStyle::State_Horizontal;

    return style()->pixelMetric(QStyle::PM_ScrollBarExtent, &opt, this);
}
