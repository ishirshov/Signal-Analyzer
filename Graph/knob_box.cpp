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

// Подключение заголовных файлов библиотеки Qt
#include <QLayout>

// Подключение заголовных файлов библиотеки Qwt
#include <qwt_scale_engine.h>
#include <qwt_transform.h>

// Подключение локальных заголовных файлов
#include "knob_box.h"

KnobBox::KnobBox(QWidget *parent)
    :QWidget(parent)
    ,d_knob(new QwtKnob(this))
    ,d_blabel(new QLabel(this))
{
    d_knob->setTracking(true);
    d_knob->setKnobStyle(QwtKnob::Styled);
    d_knob->setMarkerStyle(QwtKnob::Triangle);
    d_knob->setKnobWidth(150);
    d_blabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->addWidget(d_knob, 1);
    layout->addWidget(d_blabel);
    layout->addStretch(2);

    connect(d_knob, SIGNAL(valueChanged(double)), this, SLOT(setNum(double)));
    connect(this, SIGNAL(setValue(double)), d_knob, SLOT(setValue(double)));
    setNum(d_knob->value());
}

void KnobBox::setNum(double v)
{
    d_blabel->setText(QString("%1").arg(v, 0, 'f', 2));
    emit valueChanged(v);
}

void KnobBox::setScale(const QwtInterval &min_max)
{
    QList<qreal> ticks[QwtScaleDiv::NTickTypes];
    
    ticks[QwtScaleDiv::MajorTick] << min_max.minValue() 
                                  << min_max.maxValue();

    d_knob->setScale(QwtScaleDiv(min_max.minValue(), min_max.maxValue(), ticks));
}
