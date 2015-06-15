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

#ifndef HELPERS_H
#define HELPERS_H

#include <ipp.h>

#include <iostream>
#include <cmath>
#include <stdexcept>

#include <QPointF>
#include <QString>
#include <QHash>
#include <QtGlobal>

/*!
 * \brief Функция позволяет обнулить младшую
 *        часть битов числа (необходимо для БПФ
 *        библиотеки MKL).
 * \param[in] x
 * \return Число с о
 */
inline ulong zero_pad_freq(ulong x)
{
    ulong z = x;

    if(x > 50000000)
    {
        int digit = x % 1000000;
        z -= digit;
    }

    return z;
}

/*!
 * \brief Внутренняя функция для округления
 *        вещественных чисел.
 * \param[in] val Вещественное число.
 * \return Округленное вещественное число.
 */
template<class T> T round(T val)
{
    T diff = val - long(val);
    if(diff < 0) diff = -(diff);

    return (diff <= 0.5)?(std::floor(val)):(std::ceil(val));
}

/*!
 * \brief Линейный метод для возведения
 *        числа в степень двойки.
 * \param[in] x Число для возведения.
 * \return Число возведенное в степень двойки.
 */
inline ulong topwr_of_2(ulong x)
{
    if(x !=0)
    {
        if((x & (x-1)) != 0)
        {
            --x;
            x |= x >> 1;
            x |= x >> 2;
            x |= x >> 4;
            x |= x >> 8;
            x |= x >> 16;
            ++x;
        }
    }

    return x;
}

#ifdef Q_OS_WIN32
#include <math.h>

template<class T>
T log2(T x)
{
    return log(x)/log(2);
}

template<class T>
T isinf(T x)
{
    return (!_finite(x));
}
#endif

/*!
 * \brief Перегруженный оператор для сравнения '<'
 *        двух объектов типа QPointF по оси ординат.
 * \param[in] a Точка А.
 * \param[in] b Точка Б.
 * \return Результат сравнения.
 */
inline bool operator<(const QPointF &a, const QPointF &b)
{
    return (a.y() < b.y());
}

/*!
 * \brief Перегруженный оператор для сравнения '>'
 *        двух объектов типа QPointF по оси ординат.
 * \param[in] a Точка А.
 * \param[in] b Точка Б.
 * \return Результат сравнения.
 */
inline bool operator>(const QPointF &a, const QPointF &b)
{
    return !(a < b);
}

/*!
 * \brief Функция необходима для подсчета хэш-функции
 *        объекта типа QPointF.
 * \param[in] p Точка.
 * \return Хэш-строка.
 */
inline uint qHash(const QPointF &p)
{
    return qHash(QString("%1,%2").arg(p.x()).arg(p.y()));
}

/*!
 * \brief Предикат сравнения для объектов типа QPointF.
 */
struct greatherThen
{
    /*!
     * \brief Оператор сравнения '>' объектов типа QPointF.
     * \param[in] a Точка А.
     * \param[in] b Точка Б.
     * \return Результат сравнения.
     */
    bool operator()(const QPointF &a, const QPointF &b) const
    {
        return a > b;
    }
};

#endif // HELPERS_H
