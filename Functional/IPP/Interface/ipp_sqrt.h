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

#ifndef IPP_SQRT_H
#define IPP_SQRT_H

#include <ipps.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>

/*!
 * \brief Функция возводит в квадрат все значения в
 *        векторе X и сохраняет результат в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными вещественными числами X.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными числами Y.
 * \param[in] len Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sqrt(const Ipp32f *src, Ipp32f *dst, int len)
{
    IppStatus status = ippsSqrt_32f(src, dst, len);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция возводит в квадрат все значения в
 *        векторе X и сохраняет результат в вектор Y.
 * \param[in] src Исходный вектор с 64 разрядными вещественными числами X.
 * \param[out] dst Конечный вектор с 64 разрядными вещественными числами Y.
 * \param[in] len Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sqrt(const Ipp64f *src, Ipp64f *dst, int len)
{
    IppStatus status = ippsSqrt_64f(src, dst, len);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция возводит в квадрат все значения в
 *        векторе X и сохраняет результат в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными вещественными
 *                комплексными числами X.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными
 *                 комплексными числами Y.
 * \param[in] len Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sqrt(const Ipp32fc *src, Ipp32fc *dst, int len)
{
    IppStatus status = ippsSqrt_32fc(src, dst, len);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция возводит в квадрат все значения в
 *        векторе X и сохраняет результат в вектор Y.
 * \param[in] src Исходный вектор с 64 разрядными вещественными
 *                комплексными числами X.
 * \param[out] dst Конечный вектор с 64 разрядными вещественными
 *                 комплексными числами Y.
 * \param[in] len Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sqrt(const Ipp64fc *src, Ipp64fc *dst, int len)
{
    IppStatus status = ippsSqrt_64fc(src, dst, len);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция возводит в квадрат все значения в
 *        векторе X и сохраняет результат в вектор Y.
 * \param[in] src Исходный вектор с 8 разрядными положительными целыми числами X.
 * \param[out] dst Конечный вектор с 8 разрядными положительными целыми числами Y.
 * \param[in] len Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sqrt(const Ipp8u *src, Ipp8u *dst, int len)
{
    IppStatus status = ippsSqrt_8u_Sfs(src, dst, len, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция возводит в квадрат все значения в
 *        векторе X и сохраняет результат в вектор Y.
 * \param[in] src Исходный вектор с 16 разрядными целыми числами X.
 * \param[out] dst Конечный вектор с 16 разрядными целыми числами Y.
 * \param[in] len Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sqrt(const Ipp16s *src, Ipp16s *dst, int len)
{
    IppStatus status = ippsSqrt_16s_Sfs(src, dst, len, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция возводит в квадрат все значения в
 *        векторе X и сохраняет результат в вектор Y.
 * \param[in] src Исходный вектор с 16 разрядными положительными целыми числами X.
 * \param[out] dst Конечный вектор с 16 разрядными положительными целыми числами Y.
 * \param[in] len Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sqrt(const Ipp16u *src, Ipp16u *dst, int len)
{
    IppStatus status = ippsSqrt_16u_Sfs(src, dst, len, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция возводит в квадрат все значения в
 *        векторе X и сохраняет результат в вектор Y.
 * \param[in] src Исходный вектор с 16 разрядными целыми комплексными числами X.
 * \param[out] dst Конечный вектор с 16 разрядными целыми комплексными числами Y.
 * \param[in] len Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sqrt(const Ipp16sc *src, Ipp16sc *dst, int len)
{
    IppStatus status = ippsSqrt_16sc_Sfs(src, dst, len, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция возводит в квадрат все значения в
 *        векторе X и сохраняет результат в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными целыми числами X.
 * \param[out] dst Конечный вектор с 32 разрядными целыми числами Y.
 * \param[in] len Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sqrt(const Ipp32s *src, Ipp16s *dst, int len)
{
    IppStatus status = ippsSqrt_32s16s_Sfs(src, dst, len, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_SQRT_H
