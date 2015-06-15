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

// Подключение заголовных файлов "Функциональной части" проекта
#include "denoised_group_box.h"
#include "Functional/IPP/Additionals/vars.h"
#include "Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/math_modules.h"

// Подключение заголовных файлов библиотеки Qt
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

DenoisedGroupBox::DenoisedGroupBox(QWidget *parent)
    :QGroupBox(tr("Composite filters"), parent)
    ,chk_wavelet_transf(new QCheckBox(tr("Wavelet transform"), this))
    ,lbl_filter_func(new QLabel(tr("Shrink function"), this))
    ,cmb_filter_func(new QComboBox(this))
    ,lbl_filter_bank(new QLabel(tr("Filter bank"), this))
    ,cmb_filter_bank(new QComboBox(this))
    ,lbl_level_transf(new QLabel(tr("Transform level"), this))
    ,spn_level_transf(new QSpinBox(this))
    ,lbl_median_kernel(new QLabel(tr("Median kernel (k)"), this))
    ,spn_median_kernel(new QSpinBox(this))
    ,lbl_kalman_gain(new QLabel(tr("Kalman gain (k)"), this))
    ,spn_kalman_gain(new QDoubleSpinBox(this))
{
    /* Создание графических уровней отображения. */
    QHBoxLayout *filter_func_lyt = new QHBoxLayout;
    filter_func_lyt->addSpacing(15);
    filter_func_lyt->addWidget(lbl_filter_func);
    filter_func_lyt->addWidget(cmb_filter_func);
    filter_func_lyt->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *filter_bank_lyt = new QHBoxLayout;
    filter_bank_lyt->addSpacing(15);
    filter_bank_lyt->addWidget(lbl_filter_bank);
    filter_bank_lyt->addWidget(cmb_filter_bank);
    filter_bank_lyt->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *level_transf_lyt = new QHBoxLayout;
    level_transf_lyt->addSpacing(15);
    level_transf_lyt->addWidget(lbl_level_transf);
    level_transf_lyt->addWidget(spn_level_transf);
    level_transf_lyt->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *median_kernel_lyt = new QHBoxLayout;
    median_kernel_lyt->addSpacing(15);
    median_kernel_lyt->addWidget(lbl_median_kernel);
    median_kernel_lyt->addWidget(spn_median_kernel);
    median_kernel_lyt->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *kalman_gain_lyt = new QHBoxLayout;
    kalman_gain_lyt->addSpacing(15);
    kalman_gain_lyt->addWidget(lbl_kalman_gain);
    kalman_gain_lyt->addWidget(spn_kalman_gain);
    kalman_gain_lyt->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *main_lyt = new QVBoxLayout;
    main_lyt->addSpacerItem(new QSpacerItem(20, 10));
    main_lyt->addWidget(chk_wavelet_transf);
    main_lyt->addLayout(filter_func_lyt);
    main_lyt->addLayout(filter_bank_lyt);
    main_lyt->addLayout(level_transf_lyt);
    main_lyt->addLayout(median_kernel_lyt);
    main_lyt->addLayout(kalman_gain_lyt);

    /* Инициализация типов фильтров. */
    filter_map[0] = "Median";
    filter_map[1] = "Kalman";
    wavelet_map[0] = "Donoho's soft";
    wavelet_map[1] = "Hyperbolic";

    /*  Установка видимости графических элементов
        на панели.  */
    chk_wavelet_transf->setChecked(false);
    spn_level_transf->setEnabled(false);
    spn_level_transf->setVisible(false);
    lbl_level_transf->setVisible(false);
    cmb_filter_bank->setEnabled(false);
    spn_kalman_gain->setEnabled(false);
    cmb_filter_func->addItems(filter_map.values());
    cmb_filter_bank->addItems(GlobalVariables::getInstance().getWaveletFilterBanks());
    spn_level_transf->setRange(1, 11);
    spn_median_kernel->setRange(1, 301);
    spn_median_kernel->setSingleStep(2);
    spn_kalman_gain->setRange(0.001, 1.0);
    spn_kalman_gain->setDecimals(3);
    spn_kalman_gain->setSingleStep(0.001);
    spn_kalman_gain->setValue(0.070);

    connect(chk_wavelet_transf, SIGNAL(toggled(bool)), SLOT(setWaveletTransform(bool)));
    connect(spn_level_transf, SIGNAL(valueChanged(int)), &GlobalVariables::getInstance(), SLOT(setTransformLevel(int)));
    connect(spn_median_kernel, SIGNAL(valueChanged(int)), &GlobalVariables::getInstance(), SLOT(setMedianK(int)));
    connect(spn_kalman_gain, SIGNAL(valueChanged(double)), &GlobalVariables::getInstance(), SLOT(setKalmanGain(double)));
    connect(cmb_filter_bank, SIGNAL(currentIndexChanged(int)), SLOT(setFilterBanks(int)));
    connect(this, SIGNAL(toggled(bool)), this, SLOT(checkedToggled(bool)));
    connect(chk_wavelet_transf, SIGNAL(toggled(bool)), spn_level_transf, SLOT(setEnabled(bool)));
    connect(chk_wavelet_transf, SIGNAL(toggled(bool)), cmb_filter_bank, SLOT(setEnabled(bool)));
    connect(cmb_filter_func, SIGNAL(currentIndexChanged(int)), SLOT(setFilterFunction(int)));

    /* Инициализация параметров панели. */
    setLayout(main_lyt);
    setCheckable(true);
    setChecked(false);
}

void DenoisedGroupBox::checkedToggled(bool checked)
{
    if(checked)
        QMetaObject::invokeMethod(this, "setFilterFunction", Q_ARG(int, cmb_filter_func->currentIndex()));
    else
        emit filterTypeChanged(None);
}

void DenoisedGroupBox::setWaveletTransform(bool checked)
{
    /* Очистить список доступных фильтров. */
    cmb_filter_func->clear();

    /* Если включено вейвлет преобразование. */
    if(checked) {
        cmb_filter_func->addItems(wavelet_map.values());

        /* Исключить использование медианного фильтра и
        фильтра Каллмана. */
        spn_median_kernel->setEnabled(false);
        spn_kalman_gain->setEnabled(false);
    }
    else /* В ином случае, добавить стандартные методы фильтрации. */
        cmb_filter_func->addItems(filter_map.values());
}

void DenoisedGroupBox::setFilterFunction(int id)
{
    bool is_median_exists = !chk_wavelet_transf->isChecked();
    QString name_func;

    /* Если выбраны простые функции фильтров.
    Без применения вейвлет преобразования. */
    if(is_median_exists) {
        if(!filter_map.contains(id)) return;

        name_func = filter_map[id];
        if(name_func == "Median")
        {
            spn_median_kernel->setEnabled(true);
            emit filterTypeChanged(Median);
        }
        else spn_median_kernel->setEnabled(false);

        if(name_func == "Kalman")
        {
            spn_kalman_gain->setEnabled(true);
            emit filterTypeChanged(Kalman);
        }
        else spn_kalman_gain->setEnabled(false);
    }
    else {
        if(!wavelet_map.contains(id)) return;

        name_func = wavelet_map[id];

        if(name_func == "Donoho's soft")
            emit filterTypeChanged(WaveletSoft);
        else if(name_func == "Hyperbolic")
            emit filterTypeChanged(WaveletHyperbolic);
    }
}

void DenoisedGroupBox::setFilterBanks(int indx)
{
    /* Глобально установить новый тип банка фильтров
    для вейвлет преобразования. */
    GlobalVariables::getInstance().setFilterBank(cmb_filter_bank->itemText(indx));
}

void DenoisedGroupBox::changeEvent(QEvent *event)
{
    /* Перевести надписи на панели. */
    if(event->type() == QEvent::LanguageChange)
    {
        setTitle(tr("Composite filters"));

        chk_wavelet_transf->setText(tr("Wavelet transform"));
        lbl_filter_func->setText(tr("Shrink function"));
        lbl_filter_bank->setText(tr("Filter bank"));
        lbl_level_transf->setText(tr("Transform level"));
        lbl_median_kernel->setText(tr("Median kernel (k)"));
        lbl_kalman_gain->setText(tr("Kalman gain (k)"));
    }
    else if(event->type() == QEvent::EnabledChange)
    {
        /* Отслеживание состояние панели. */
        if(isEnabled() && isChecked())
            QMetaObject::invokeMethod(this, "setFilterFunction", Q_ARG(int, cmb_filter_func->currentIndex()));
        else
            emit filterTypeChanged(None);
    }

    QGroupBox::changeEvent(event);
}
