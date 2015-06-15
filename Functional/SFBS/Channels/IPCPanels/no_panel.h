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

#ifndef NO_PANEL_H
#define NO_PANEL_H

#include <QLabel>
#include "Functional/SFBS/Channels/Interfaces/ipc_panel.h"

class NoPanel : public IPCPanel
{
    Q_OBJECT

public:
    explicit NoPanel(QWidget *parent = 0);

    QString getPanelType() const;

signals:
    void samplingFrequencyChanged(ulong); // Unused
    void voltsLevelChanged(float); // Unused

public slots:
    void ipcDataHandle(void *msg);
    void ipcInit(int user_ch_id, int user_tsk_id, int panel_ch_id, int panel_tsk_id);
    void blockSamplingFrequency(bool);

protected:
    void changeEvent(QEvent*);

private:
    NoPanel(const NoPanel&);
    NoPanel& operator=(const NoPanel&);

    void languageChanged();

    QLabel *widget;

};


#endif // NO_PANEL_H
