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

#include "second.h"
#include <stdexcept>

Second::Second(double v, const QString &nm, const QString &sm)
    :val(v), nm(nm), sm(sm)
{
    if(!in_range(v))
    {
        throw std::invalid_argument("Object second is intended for work"
                                    " in the range [femtosecond;petasecond)");
    }
}

Second& default_second()
{
    static Second sd(1.0, "Second", "s");
    return sd;
}

Second::Second()
    :val(default_second().value())
    ,nm(default_second().name())
    ,sm(default_second().symbol())
{}

bool Second::in_range(double v)
{
    // Check range[femtosecond -> petasecond];
    if(v < 0.000000000000001) return false;
    if(v > 1000000000000000) return false;

    return true;
}
