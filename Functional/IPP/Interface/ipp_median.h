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

#ifndef IPP_MEDIAN_H
#define IPP_MEDIAN_H

#include <ipps.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>

/*!
 * \brief Функция медианного фильтра выполняет очистку вектора X, а
 *        результат работы сохраняет в вектор Y.
 * \param[in] src Исходный вектор с 8 разрядными положительными целыми числами X.
 * \param[out] dst Конечный вектор с 8 разрядными положительными целыми числами Y.
 * \param[in] len Размер вектора src и dst.
 * \param[in] kernel Коэффициент медианного фильтра.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_median(const Ipp8u *src, Ipp8u *dst, int len, int kernel)
{
    IppStatus status = ippsFilterMedian_8u(src, dst, len, kernel);
    if(status != ippStsNoErr && status != ippStsEvenMedianMaskSize)
        throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция медианного фильтра выполняет очистку вектора X, а
 *        результат работы сохраняет в вектор Y.
 * \param[in] src Исходный вектор с 16 разрядными целыми числами X.
 * \param[out] dst Конечный вектор с 16 разрядными целыми числами Y.
 * \param[in] len Размер вектора src и dst.
 * \param[in] kernel Коэффициент медианного фильтра.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_median(const Ipp16s *src, Ipp16s *dst, int len, int kernel)
{
    IppStatus status = ippsFilterMedian_16s(src, dst, len, kernel);
    if(status != ippStsNoErr && status != ippStsEvenMedianMaskSize)
        throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция медианного фильтра выполняет очистку вектора X, а
 *        результат работы сохраняет в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными целыми числами X.
 * \param[out] dst Конечный вектор с 32 разрядными целыми числами Y.
 * \param[in] len Размер вектора src и dst.
 * \param[in] kernel Коэффициент медианного фильтра.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_median(const Ipp32s *src, Ipp32s *dst, int len, int kernel)
{
    IppStatus status = ippsFilterMedian_32s(src, dst, len, kernel);
    if(status != ippStsNoErr && status != ippStsEvenMedianMaskSize)
        throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция медианного фильтра выполняет очистку вектора X, а
 *        результат работы сохраняет в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными вещественными числами X.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными числами Y.
 * \param[in] len Размер вектора src и dst.
 * \param[in] kernel Коэффициент медианного фильтра.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_median(const Ipp32f *src, Ipp32f *dst, int len, int kernel)
{
    IppStatus status = ippsFilterMedian_32f(src, dst, len, kernel);
    if(status != ippStsNoErr && status != ippStsEvenMedianMaskSize)
        throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция медианного фильтра выполняет очистку вектора X, а
 *        результат работы сохраняет в вектор Y.
 * \param[in] src Исходный вектор с 64 разрядными вещественными числами X.
 * \param[out] dst Конечный вектор с 64 разрядными вещественными числами Y.
 * \param[in] len Размер вектора src и dst.
 * \param[in] kernel Коэффициент медианного фильтра.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_median(const Ipp64f *src, Ipp64f *dst, int len, int kernel)
{
    IppStatus status = ippsFilterMedian_64f(src, dst, len, kernel);
    if(status != ippStsNoErr && status != ippStsEvenMedianMaskSize)
        throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_MEDIAN_H
