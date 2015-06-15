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

#include "resolution_box.h"

#include <QBoxLayout>

ResolutionBox::ResolutionBox(QWidget *parent)
    :QWidget(parent)
    ,divider_lbl(new QLabel(tr("Divider"), this))
    ,divider_cmb(new QComboBox(this))
    ,frequency_lbl(new QLabel(tr("Scan frequency"), this))
    ,frequency_cmb(new QComboBox(this))
{
    initFreqDevMap();
    initFrequencyCmb();
    initDividerCmb();

    connect(divider_cmb, SIGNAL(currentIndexChanged(int)), SLOT(setDivider(int)));
    connect(frequency_cmb, SIGNAL(currentIndexChanged(int)), SLOT(setFrequency(int)));

    QHBoxLayout *divider_lyt = new QHBoxLayout;
    divider_lyt->addWidget(divider_lbl);
    divider_lyt->addWidget(divider_cmb);
    divider_lyt->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *frequency_lyt = new QHBoxLayout;
    frequency_lyt->addWidget(frequency_lbl);
    frequency_lyt->addWidget(frequency_cmb);
    frequency_lyt->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *main_lyt = new QVBoxLayout;
    main_lyt->addLayout(divider_lyt);
    main_lyt->addLayout(frequency_lyt);
    main_lyt->setSpacing(10);
    main_lyt->setContentsMargins(0, 0, 0, 0);

    setLayout(main_lyt);
}

quint32 ResolutionBox::currentDivider() const
{
    return div_map[divider_cmb->currentIndex()];
}

quint32 ResolutionBox::currentFrequency() const
{
    return freq_map[frequency_cmb->currentIndex()];
}

void ResolutionBox::setDivider(int val)
{
    if(val != -1) {
        emit dividerValueChanged(div_map[val]);
    }
}

void ResolutionBox::setFrequency(int val)
{
    if(val != -1) {
        emit frequencyValueChanged(freq_map[val]);
    }
}

void ResolutionBox::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        divider_lbl->setText(tr("Divider"));
        frequency_lbl->setText(tr("Scan frequency"));

        quint32 freq_indx = frequency_cmb->currentIndex();

        frequency_cmb->clear();
        initFrequencyCmb();

        frequency_cmb->setCurrentIndex(freq_indx);
    }

    QWidget::changeEvent(event);
}

void ResolutionBox::initFreqDevMap()
{
    /* Выполнить инициализацию карты соответствия
     * для значений частот сканирования.
     */
    quint32 freq = 1;
    quint32 i = 0;

    #pragma unroll(10)
    while(i < 10)
    {
        freq_map.insert(i, freq);
        ++i; freq *= 10;
    }

    /* Выполнить инициализацию карты соответствия
     * для значений делителя частоты.
     */
    quint32 div = 1;
    i = 0;

    div_map.insert(i, div);
    ++div;

    #pragma unroll(5)
    while(i < 5)
    {
        div_map.insert(++i, div);
        div += 2;
    }
}

void ResolutionBox::initDividerCmb()
{
    const QList<quint32> &values = div_map.values();
    QList<quint32>::ConstIterator p = values.begin();
    QList<quint32>::ConstIterator end = values.end();

    QStringList items;
    while(p != end) {
        items << QString::number(*p);
        ++p;
    }

    divider_cmb->addItems(items);
}

void ResolutionBox::initFrequencyCmb()
{
    QStringList items;
    QString hz = tr(" Hz"), khz = tr(" KHz"), mhz = tr(" MHz");
    items << "1" + hz << "10" + hz << "100" + hz
          << "1" + khz << "10" + khz << "100" + khz
          << "1" + mhz << "10" + mhz << "100" + mhz
          << "1" + tr(" GHz");

    frequency_cmb->addItems(items);
}
