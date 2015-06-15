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

#ifndef IPP_SIGN_H
#define IPP_SIGN_H

#include "ipp_abs.h"
#include "ipp_div.h"

/*!
 * \brief Функция позволяет обнулить отрицательные числа
 *        в векторе X, оставив только положительные и
 *        сохранить результат в вектор Y.
 * \param[in] src Исходный вектор с 16 разрядными целыми числами X.
 * \param[out] dst Конечный вектор с 16 разрядными целыми числами Y.
 * \param[in] len Размер вектора src и dst.
 */
inline void ipp_sign(const Ipp16s *src, Ipp16s *dst, int len)
{
    ipp_abs(src, dst, len);
    ipp_div(src, dst, dst, len);
}

/*!
 * \brief Функция позволяет обнулить отрицательные числа
 *        в векторе X, оставив только положительные и
 *        сохранить результат в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными целыми числами X.
 * \param[out] dst Конечный вектор с 32 разрядными целыми числами Y.
 * \param[in] len Размер вектора src и dst.
 */
inline void ipp_sign(const Ipp32s *src, Ipp32s *dst, int len)
{
    ipp_abs(src, dst, len);
    ipp_div(src, dst, dst, len);
}

/*!
 * \brief Функция позволяет обнулить отрицательные числа
 *        в векторе X, оставив только положительные и
 *        сохранить результат в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными вещественными числами X.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными числами Y.
 * \param[in] len Размер вектора src и dst.
 */
inline void ipp_sign(const Ipp32f *src, Ipp32f *dst, int len)
{
    ipp_abs(src, dst, len);
    ipp_div(src, dst, dst, len);
}

/*!
 * \brief Функция позволяет обнулить отрицательные числа
 *        в векторе X, оставив только положительные и
 *        сохранить результат в вектор Y.
 * \param[in] src Исходный вектор с 64 разрядными вещественными числами X.
 * \param[out] dst Конечный вектор с 64 разрядными вещественными числами Y.
 * \param[in] len Размер вектора src и dst.
 */
inline void ipp_sign(const Ipp64f *src, Ipp64f *dst, int len)
{
    ipp_abs(src, dst, len);
    ipp_div(src, dst, dst, len);
}

#endif // IPP_SIGN_H
