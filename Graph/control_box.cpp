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

#include "control_box.h"

#include <cmath>
#include <QBoxLayout>

ControlBox::ControlBox(QWidget *parent)
    :ResolutionBox(parent)
    ,volt_lbl(new QLabel(tr("Volts multiply"), this))
    ,volt_cmb(new QComboBox(this))
    ,refresh_lbl(new QLabel(tr("Refresh rate [Hz]"), this))
    ,refresh_lcd(new QLCDNumber(this))
    ,refresh_wheel(new QwtWheel(this))
{
    /* Инициализация значений множителя напряжения. */
    volt_map.insert(0, 1);
    volt_map.insert(1, 0.5);
    volt_map.insert(2, 0.2);
    volt_map.insert(3, 0.1);
    volt_map.insert(4, 0.05);
    volt_map.insert(5, 0.02);
    volt_map.insert(6, 0.01);
    volt_map.insert(7, 0.005);
    volt_map.insert(8, 0.002);
    volt_map.insert(9, 0.001);
    volt_map.insert(10, 0.0005);

    const QList<qreal> &values = volt_map.values();
    QList<qreal>::ConstIterator p = values.begin();
    QList<qreal>::ConstIterator end = values.end();

    /* Перевод множителей в строковое значение. */
    QStringList items;
    while(p != end) {
        items << QString::number(*p);
        ++p;
    }
    /* Пополнение списка допустимых множителей. */
    volt_cmb->addItems(items);

    refresh_wheel->setMinimum(0.0);
    refresh_wheel->setMaximum(75.0);
    refresh_wheel->setSingleStep(1.0);
    refresh_wheel->setTracking(true);
    refresh_wheel->setOrientation(Qt::Vertical);

    refresh_lcd->setStyleSheet("color: rgb(0, 255, 0);\nbackground-color: rgb(0, 0, 0);");
    refresh_lcd->setSegmentStyle(QLCDNumber::Flat);
    refresh_lbl->setStyleSheet("qproperty-alignment: 'Qt::AlignVCenter|Qt::AlignHCenter'");

    connect(volt_cmb, SIGNAL(currentIndexChanged(int)), SLOT(setVolts(int)));
    connect(refresh_wheel, SIGNAL(valueChanged(double)), refresh_lcd, SLOT(display(double)));
    connect(refresh_wheel, SIGNAL(valueChanged(double)), SLOT(setRefreshRate(double)));

    QVBoxLayout *refresh_main = new QVBoxLayout;
    refresh_main->addWidget(refresh_lbl);
    refresh_main->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *refresh_lyt = new QHBoxLayout;
    refresh_lyt->addWidget(refresh_lcd);
    refresh_lyt->addWidget(refresh_wheel);
    refresh_lyt->setContentsMargins(0, 0, 0, 0);
    refresh_main->addLayout(refresh_lyt);

    QHBoxLayout *volt_lyt = new QHBoxLayout;
    volt_lyt->addWidget(volt_lbl);
    volt_lyt->addWidget(volt_cmb);
    volt_lyt->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *main_lyt = static_cast<QVBoxLayout*>(layout());
    main_lyt->insertLayout(0, refresh_main);
    main_lyt->addLayout(volt_lyt);
}

short ControlBox::currentRate() const
{
    double ms = 1000.0/refresh_lcd->value();
    ms = (isinf(ms))?(-1.0):(ms);

    return short(std::floor(ms));
}

double ControlBox::currentVolts() const
{
    return volt_map[volt_cmb->currentIndex()];
}

void ControlBox::sendInitialValues()
{
    emit dividerValueChanged(currentDivider());
    emit frequencyValueChanged(currentFrequency());
    emit voltValueChanged(currentVolts());
    emit rateValueChanged(currentRate());
}

void ControlBox::setRefreshRate(double value)
{
    double ms = 1000.0/value;
    ms = (isinf(ms))?(-1.0):(ms);

    emit rateValueChanged(short(std::floor(ms)));
}

void ControlBox::setVolts(int val)
{
    if(val != -1) {
        emit voltValueChanged(volt_map[volt_cmb->currentIndex()]);
    }
}

void ControlBox::changeEvent(QEvent *event)
{
    /* Перевести текст. */
    if(event->type() == QEvent::LanguageChange) {
        volt_lbl->setText(tr("Volts multiply"));
        refresh_lbl->setText(tr("Refresh rate [Hz]"));
    }

    /* Установить значения по умолчанию. */
    if(event->type() == QEvent::EnabledChange) {
        if(isEnabled()) /* Если виджет включен. */
            refresh_wheel->setValue(refresh_wheel->maximum());
        else
            refresh_wheel->setValue(refresh_wheel->minimum());
    }

    ResolutionBox::changeEvent(event);
}
