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

#ifndef IPP_ROUND_TYPE_H
#define IPP_ROUND_TYPE_H

/*!
 * \brief Типы округления в функциях
 *        синуса, возведения
 *        вектора Y в степень X
 *        (см. документацию Intel PP).
 */
enum roundType
{
    A11, //!< Гарантия округления до 11 разрядов.
    A21, //!< Гарантия округления до 21 разрядов.
    A24, //!< Гарантия округления до 24 разрядов.
    A26, //!< Гарантия округления до 26 разрядов.
    A50, //!< Гарантия округления до 50 разрядов.
    A53  //!< Гарантия округления до 53 разрядов.
};

#endif // IPP_ROUND_TYPE_H
