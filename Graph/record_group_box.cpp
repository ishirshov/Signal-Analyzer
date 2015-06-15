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

#include "record_group_box.h"

#include "resolution_box.h"
#include "Functional/IPP/additional.h"
#include "Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/settings.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>

RecordGroupBox::RecordGroupBox(QWidget *parent)
    :QGroupBox(tr("Record signal"), parent)
    ,record_lbl(new QLabel(tr("Record name"), this))
    ,record_cmb(new QComboBox(this))
    ,res_box(new ResolutionBox(this))
    ,dump_btn(new QPushButton(tr("Dump"), this))
    ,remove_btn(new QPushButton(tr("Remove"), this))
    ,show_btn(new QPushButton(tr("Show"), this))
    ,record_btn(new QPushButton(tr("Start record"), this))
    ,aval_space_lbl(new QLabel(tr("Available space"), this))
    ,aval_space_bar(new QProgressBar(this))
    ,work_prog_lbl(new QLabel(tr("Nothing to do"), this))
    ,work_prog_bar(new QProgressBar(this))
    ,window_size(560)
    ,sampling_freq(c_Default_Fs)
    ,signal_recording(false)
    ,signal_dumping(false)
    ,signal_preparing(false)
{
    QHBoxLayout *record_lyt = new QHBoxLayout;
    record_lyt->addSpacing(15);
    record_lyt->addWidget(record_lbl);
    record_lyt->addWidget(record_cmb);
    record_lyt->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *res_lyt = new QHBoxLayout;
    res_lyt->addSpacing(15);
    res_lyt->addWidget(res_box);

    QHBoxLayout *control_lyt1 = new QHBoxLayout;
    control_lyt1->addSpacing(15);
    control_lyt1->addWidget(dump_btn);
    control_lyt1->addWidget(remove_btn);
    control_lyt1->setContentsMargins(0, 0, 0, 0);
    QHBoxLayout *control_lyt2 = new QHBoxLayout;
    control_lyt2->addSpacing(15);
    control_lyt2->addWidget(show_btn);
    control_lyt2->addWidget(record_btn);
    control_lyt2->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *progress_lyt = new QVBoxLayout;
    progress_lyt->addSpacing(15);
    progress_lyt->addWidget(aval_space_lbl);
    progress_lyt->addWidget(aval_space_bar);
    progress_lyt->addWidget(work_prog_lbl);
    progress_lyt->addWidget(work_prog_bar);
    progress_lyt->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *main_lyt = new QVBoxLayout;
    main_lyt->addSpacerItem(new QSpacerItem(20, 10));
    main_lyt->addLayout(record_lyt);
    main_lyt->addLayout(res_lyt);
    main_lyt->addLayout(control_lyt1);
    main_lyt->addLayout(control_lyt2);
    main_lyt->addLayout(progress_lyt);
    main_lyt->setContentsMargins(0, 0, 0, 0);

    work_prog_lbl->setStyleSheet("qproperty-alignment: 'Qt::AlignVCenter|Qt::AlignHCenter'");
    aval_space_lbl->setStyleSheet("qproperty-alignment: 'Qt::AlignVCenter|Qt::AlignHCenter'");

    aval_space_bar->setValue(0);
    aval_space_bar->setFormat("%v / " + QString::number(aval_space_bar->maximum()));

    danger_stylesheet = "QProgressBar { border: 1px solid black; border-radius: 7px; background: white; text-align: center; }";
    danger_stylesheet += "QProgressBar::chunk { background: red; border-radius: 7px; }";
    safe_stylesheet = "QProgressBar { border: 1px solid black; border-radius: 7px; background: white; text-align: center; }";
    safe_stylesheet += "QProgressBar::chunk { background: green; border-radius: 7px; }";
    aval_space_bar->setStyleSheet(safe_stylesheet);

    record_cmb->setEnabled(false);
    show_btn->setEnabled(false);
    remove_btn->setEnabled(false);
    dump_btn->setEnabled(false);
    work_prog_lbl->setVisible(false);
    work_prog_bar->setVisible(false);

    connect(dump_btn, SIGNAL(clicked()), SLOT(dumpButtonPressed()));
    connect(remove_btn, SIGNAL(clicked()), SLOT(removeButtonPressed()));
    connect(show_btn, SIGNAL(clicked()), SLOT(showButtonPressed()));
    connect(record_btn, SIGNAL(clicked()), SLOT(recordButtonPressed()));
    connect(this, SIGNAL(clicked()), SLOT(hideWorkBar()));

    setLayout(main_lyt);
    setCheckable(true);
    setChecked(false);
}

void RecordGroupBox::setRecordList(const QStringList &rcd_lst)
{
    record_cmb->clear();
    bool enable_flag = (!rcd_lst.isEmpty())?(true):(false);

    record_cmb->addItems(rcd_lst);
    record_cmb->setEnabled(enable_flag);
    record_cmb->setEnabled(enable_flag);
    dump_btn->setEnabled(enable_flag);
    remove_btn->setEnabled(enable_flag);
    show_btn->setEnabled(enable_flag);
}

void RecordGroupBox::setWindowWidth(quint32 size)
{
    window_size = size;
}

void RecordGroupBox::setSamplingFrequency(ulong freq)
{
    if(c_Fs_range.contains(freq))
        sampling_freq = freq;
}

void RecordGroupBox::setRecordFlag(bool flag)
{
    signal_recording = flag;
    record_btn->setText((signal_recording)?(tr("Stop record")):(tr("Start record")));
}

void RecordGroupBox::setAvailableSpace(int val)
{
    aval_space_bar->setMaximum(val);
    aval_space_bar->setFormat("%v / " + QString::number(val));
}

void RecordGroupBox::setWorkBarMinimum(int val)
{
    work_prog_bar->setMinimum(val);
}

void RecordGroupBox::setWorkBarMaximum(int val)
{
    work_prog_bar->setMaximum(val);
}

void RecordGroupBox::setWorkBarValue(int val)
{
    work_prog_bar->setValue(val);

    if(val == work_prog_bar->maximum()) {
        work_prog_lbl->setText(tr("Nothing to do"));
        work_prog_bar->setVisible(false);
        work_prog_lbl->setVisible(false);

        signal_dumping = signal_recording = false;
    }
}

void RecordGroupBox::setSpaceValue(int val)
{
    aval_space_bar->setValue(val);

    /* Получаем, в процентах кол-во свободного места. */
    qreal percent_space = (val > 0)?((qreal(val)/qreal(aval_space_bar->maximum()))*100.0):(0.0);

    /* В зависимости от кол-ва свободного места индикатор, будет
     * иметь красный или зеленый цвет заполнения.
     */
    aval_space_bar->setStyleSheet(((percent_space < 80)?(safe_stylesheet):(danger_stylesheet)));

    record_btn->setEnabled((percent_space >= 100)?(false):(true));
}

void RecordGroupBox::dumpButtonPressed()
{
    const QString &current_record = record_cmb->currentText();

    if(!current_record.isEmpty())
    {
        emit dumpToFile(current_record);

        work_prog_lbl->setText(tr("Dumping signal to disk"));
        signal_dumping = true;
    }

    work_prog_lbl->setVisible(signal_dumping);
    work_prog_bar->setVisible(signal_dumping);
}

void RecordGroupBox::removeButtonPressed()
{
    const QString &current_record = record_cmb->currentText();

    if(!current_record.isEmpty())
        emit removeRecord(current_record);
}

void RecordGroupBox::showButtonPressed()
{
    const QString &current_record = record_cmb->currentText();

    if(!current_record.isEmpty()) {
        emit showRecord(current_record, new PlaybackSettings(sampling_freq, res_box->currentDivider(),
                                                             res_box->currentFrequency(), window_size));

        work_prog_lbl->setText(tr("Prepare signal to show"));
        signal_preparing = true;
    }

    work_prog_lbl->setVisible(signal_preparing);
    work_prog_bar->setVisible(signal_preparing);
}

void RecordGroupBox::recordButtonPressed()
{
    emit recordSignal(!signal_recording, sampling_freq);
}

void RecordGroupBox::hideWorkBar()
{
    work_prog_lbl->setVisible(false);
    work_prog_bar->setVisible(false);

    work_prog_lbl->setText(tr("Nothing to do"));
    work_prog_bar->setValue(0);
    aval_space_bar->setValue(0);
}

void RecordGroupBox::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        setTitle(tr("Record signal"));

        record_lbl->setText(tr("Record name"));
        dump_btn->setText(tr("Dump"));
        remove_btn->setText(tr("Remove"));
        show_btn->setText(tr("Show"));
        record_btn->setText(tr("Start record"));
        aval_space_lbl->setText(tr("Available space"));

        if(signal_dumping)
            work_prog_lbl->setText(tr("Dumping signal to disk"));
        else if(signal_preparing)
            work_prog_lbl->setText(tr("Prepare signal to show"));
        else
            work_prog_lbl->setText(tr("Nothing to do"));
    }

    QGroupBox::changeEvent(event);
}
