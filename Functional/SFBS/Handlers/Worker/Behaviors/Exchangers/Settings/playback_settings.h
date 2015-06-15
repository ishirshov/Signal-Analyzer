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

#ifndef PLAYBACK_SETTINGS_H
#define PLAYBACK_SETTINGS_H

#include "Functional/IPP/additional.h"

class PlaybackSettings
{
    ulong _samplingf;
    qreal _divider;
    qreal _frequency;
    quint32 _window_width;

public:
    PlaybackSettings();
    PlaybackSettings(long samplingf, double divider,
                     double frequency, int window_width);

    qreal get_delta_t() const;
    qreal get_time_dt() const;

    void set_sampling_frequency(long);
    void set_frequency_divider(double);
    void set_scan_frequency(double);
    void set_window_width(int);

    bool operator ==(const PlaybackSettings&);
    bool operator !=(const PlaybackSettings&);

};
#endif // PLAYBACK_SETTINGS_H
