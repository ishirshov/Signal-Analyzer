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

#include "playback_settings.h"

PlaybackSettings::PlaybackSettings()
    :_samplingf(1)
    ,_divider(1.0)
    ,_frequency(1.0)
    ,_window_width(1)
{
}

PlaybackSettings::PlaybackSettings(long samplingf, double divider,
                                   double frequency, int window_width)
    :_samplingf(1)
    ,_divider(1.0)
    ,_frequency(1.0)
    ,_window_width(1)
{
    set_sampling_frequency(samplingf);
    set_frequency_divider(divider);
    set_scan_frequency(frequency);
    set_window_width(window_width);
}

qreal PlaybackSettings::get_delta_t() const
{
    return (_divider*(_samplingf/_frequency))/_window_width;
}

qreal PlaybackSettings::get_time_dt() const
{
    return 1.0/qreal(_window_width);
}

void PlaybackSettings::set_sampling_frequency(long val)
{
    if(!c_Fs_range.contains(val))
        throw std::runtime_error(toConstChar(QString("Valid sampling frequency from %1 Hz to %2 Hz.")
                                 .arg(c_Fs_range.minValue())
                                 .arg(c_Fs_range.maxValue())));

    _samplingf = val;
}

void PlaybackSettings::set_frequency_divider(double val)
{
    if(val < 1 || val > 10)
        throw std::runtime_error("Frequency divider must be in range from 1x to 10x.");

    _divider = val;
}

void PlaybackSettings::set_scan_frequency(double val)
{
    if(val < 1 || val > 1000000000)
        throw std::runtime_error("Scan frequency must be in range from 1 Hz to 1 GHz.");

    _frequency = val;
}

void PlaybackSettings::set_window_width(int val)
{
    if(val < 1)
        throw std::runtime_error("Window width must be positive.");

    _window_width = val;
}

bool PlaybackSettings::operator ==(const PlaybackSettings& b)
{
    return (_samplingf == b._samplingf) &&
            (_divider == b._divider) &&
            (_frequency == b._frequency) &&
            (_window_width == b._window_width);
}

bool PlaybackSettings::operator !=(const PlaybackSettings& b)
{
    return !(*this == b);
}
