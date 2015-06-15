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

#ifndef DAUBECHIES_H
#define DAUBECHIES_H

#include <ippdefs.h>

//------------------------ Define filter banks ---------------------//

class DB2
{
public:
    static const int _len = 4;
    static const Ipp32f _dec_low[_len];
    static const Ipp32f _dec_high[_len];
    static const Ipp32f _rec_low[_len];
    static const Ipp32f _rec_high[_len];
};

class DB4
{
public:
    static const int _len = 8;
    static const Ipp32f _dec_low[_len];
    static const Ipp32f _dec_high[_len];
    static const Ipp32f _rec_low[_len];
    static const Ipp32f _rec_high[_len];
};

class DB6
{
public:
    static const int _len = 12;
    static const Ipp32f _dec_low[_len];
    static const Ipp32f _dec_high[_len];
    static const Ipp32f _rec_low[_len];
    static const Ipp32f _rec_high[_len];
};

class DB8
{
public:
    static const int _len = 16;
    static const Ipp32f _dec_low[_len];
    static const Ipp32f _dec_high[_len];
    static const Ipp32f _rec_low[_len];
    static const Ipp32f _rec_high[_len];
};

class DB10
{
public:
    static const int _len = 20;
    static const Ipp32f _dec_low[_len];
    static const Ipp32f _dec_high[_len];
    static const Ipp32f _rec_low[_len];
    static const Ipp32f _rec_high[_len];
};

class DB12
{
public:
    static const int _len = 24;
    static const Ipp32f _dec_low[_len];
    static const Ipp32f _dec_high[_len];
    static const Ipp32f _rec_low[_len];
    static const Ipp32f _rec_high[_len];
};

class DB14
{
public:
    static const int _len = 28;
    static const Ipp32f _dec_low[_len];
    static const Ipp32f _dec_high[_len];
    static const Ipp32f _rec_low[_len];
    static const Ipp32f _rec_high[_len];
};

class DB16
{
public:
    static const int _len = 32;
    static const Ipp32f _dec_low[_len];
    static const Ipp32f _dec_high[_len];
    static const Ipp32f _rec_low[_len];
    static const Ipp32f _rec_high[_len];
};

class DB18
{
public:
    static const int _len = 36;
    static const Ipp32f _dec_low[_len];
    static const Ipp32f _dec_high[_len];
    static const Ipp32f _rec_low[_len];
    static const Ipp32f _rec_high[_len];
};

class DB20
{
public:
    static const int _len = 40;
    static const Ipp32f _dec_low[_len];
    static const Ipp32f _dec_high[_len];
    static const Ipp32f _rec_low[_len];
    static const Ipp32f _rec_high[_len];
};

#endif // DAUBECHIES_H
