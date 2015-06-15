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

#include "user_fbs.h"

#include "Worker/wave_panel.h"
#include "Worker/sine_gen.h"

#include <QTimer>
#include <QThread>

UserStream::UserStream(QObject *parent)
    :_userGenerator(new SineGenerator)
    ,_genThread(new QThread(this))
    ,_ipcpanel_created(false)
{
    // Setup parent for this object
    setParent(parent);

    // Wavegenerator to thread
    _userGenerator->moveToThread(_genThread);
    _genThread->start();

    connect(_userGenerator, SIGNAL(workerStatusMessage(QString)), SIGNAL(statusMessage(QString)), Qt::DirectConnection);
    connect(_userGenerator, SIGNAL(samplingFrequencyChanged(ulong)), &GlobalVariables::getInstance(), SLOT(setSamplingFrequency(ulong)));
    connect(_genThread, SIGNAL(finished()), _userGenerator, SLOT(deleteLater()));

    GlobalVariables::getInstance().setSamplingFrequency(_userGenerator->getSamplingFrequency());
    GlobalVariables::getInstance().setVoltsLevel(_userGenerator->getVoltsLevel());
}

UserStream::~UserStream()
{
    QMetaObject::invokeMethod(_userGenerator, "stop", Qt::QueuedConnection);

    _genThread->quit();

    if(!_genThread->wait(500))
    {
        // May be thread in deadlock
        _genThread->terminate();
        _genThread->wait();
    }
}

QStringList UserStream::getDeviceList() const
{
    return QStringList(_userGenerator->getName());
}

QString UserStream::getDeviceType() const
{
    return _userGenerator->getType();
}

void UserStream::setDeviceName(const QString &dev)
{
    if(!_ipcpanel_created && (_userGenerator->getName() == dev))
    {
        QScopedPointer<UserIPCPanel> genPanel(new WavePanel);
        UserIPCPanel *_genPanel = genPanel.data();

        connect(&GlobalVariables::getInstance(), SIGNAL(blockSamplingFrequencyChanged(bool)), _genPanel, SLOT(setBlockSamplingFrequency(bool)));        
        connect(_genPanel, SIGNAL(signalSettingsChanged(long,double,double,double)), _userGenerator, SLOT(setSignalSettings(long,double,double,double)), Qt::QueuedConnection);
        connect(_genPanel, SIGNAL(startButtonPushed()), _userGenerator, SLOT(start()));
        connect(_genPanel, SIGNAL(stopButtonPushed()), _userGenerator, SLOT(stop()));
        connect(this, SIGNAL(statusChanged(bool)), _genPanel, SLOT(setEnabled(bool)));
        connect(_genPanel, SIGNAL(destroyed()), SLOT(deleteLastPanel()));

        emit widgetChanged(genPanel.take(), _genPanel->getName());

        _ipcpanel_created = true;
    }
}

void UserStream::deleteLastPanel()
{
    _ipcpanel_created = false;
}
