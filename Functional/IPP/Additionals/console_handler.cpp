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

#include "console_handler.h"

#include <QStringList>
#include <QRegExp>

bool arguments_handler(int argc, char *argv[])
{
    std::istringstream iss;

    if(argc == 2){
        iss.str(argv[1]);

        if(iss.str() == "?" || iss.str() == "help"){
            std::cout << "\nUsage: " << argv[0] << " [command]\n\n"
                      << "Available commands:\n"
                      << "\t -MF     \tDisable Intel median filter\n"
                      << "\t -IAC    \tDisable Intel autocorrelation\n"
                      << "\t -SAC    \tDisable SET autocorrelation\n"
                      << "\t -FPP    \tDisable to find the parameters of the peak\n\n"
                      << "Example:\n"
                      << "\t " << argv[0] << " -IAC\n"
                      << "\t " << argv[0] << " -IAC -SAC -FPP\n\n";
            return false;
        }
    }
    else if(argc > 5){
        std::cout << "\nYou have entered too many arguments.\nPlease recheck your arguments...\n\n";
        return false;
    }

    return true;
}

long memFree()
{
    long space = 0;
    QFile meminfo("/proc/meminfo");

    if(meminfo.open(QIODevice::ReadOnly))
    {
        QString strings = meminfo.readAll();
        QRegExp mem_free("(\\bMemFree\\b).+(\\d+).+(\\b[Kk][Bb]\\b)");
        QStringList list = strings.split('\n').filter(mem_free);

        if(!list.empty()) {
            mem_free.indexIn(list.front());
            space = mem_free.cap(2).toLong()/1024;
        }
    }

    return space;
}

const QString eventEnumToString(int event, int task_id, int channel_id)
{
    QString char_event;

    switch(event)
    {
    case SFBS_EVT_TASK_CREATED:
        char_event = QString("Task %1 created.").arg(task_id);
        break;
    case SFBS_EVT_TASK_DESTROYED:
        char_event = QString("Task %1 destroyed.").arg(task_id);
        break;
    case SFBS_EVT_CH_CREATED:
        char_event = QString("Channel %1 created.").arg(channel_id);
        break;
    case SFBS_EVT_CH_DESTROYED:
        char_event = QString("Channel %1 destroyed.").arg(channel_id);
        break;
    case SFBS_EVT_CH_ATTACHED:
        char_event = QString("Channel %1 attached to SFBS task.").arg(channel_id);
        break;
    case SFBS_EVT_CH_DETACHED:
        char_event = QString("Channel %1 detached to SFBS task.").arg(channel_id);
        break;
    default:
        char_event = QString("Unknown event (%1)").arg(event);
        break;
    }

    return char_event;
}
