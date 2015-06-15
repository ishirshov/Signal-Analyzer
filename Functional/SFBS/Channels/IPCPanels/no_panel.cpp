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

#include "no_panel.h"

#include <QVBoxLayout>
#include <QEvent>

NoPanel::NoPanel(QWidget *parent)
{        
    widget = new QLabel(tr("No IPC control elements\nfor current device."), this);
    widget->setStyleSheet("qproperty-alignment: 'Qt::AlignVCenter|Qt::AlignHCenter'");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(widget);
    layout->setContentsMargins(0, 0, 0, 0);

    GlobalVariables::getInstance().setVoltsLevel(c_V_DSP_12bit);

    setLayout(layout);
    setParent(parent);
}

QString NoPanel::getPanelType() const
{
    return "Empty";
}

void NoPanel::ipcDataHandle(void*)
{
    // Blank function.
    // Nothing do.
}

void NoPanel::ipcInit(int, int, int, int)
{
    // Blank function.
    // Nothing do.
}

void NoPanel::blockSamplingFrequency(bool)
{
    // Blank function.
    // Nothing do.
}

void NoPanel::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange) {
        languageChanged();
    }

    QWidget::changeEvent(event);
}

void NoPanel::languageChanged()
{
    widget->setText(tr("No IPC control elements\nfor current device."));
}
