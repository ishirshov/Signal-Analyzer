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

#ifndef IPP_RAND_UNIFORM_H
#define IPP_RAND_UNIFORM_H

#include "ipp_ptr.h"

/*!
 * \brief Функция позволяет сгенерировать псевдо-случайные числа
 *        на основе нормального распределения в вектор X.
 * \param[out] dst Конечный вектор с 8 разрядными целыми числами X.
 * \param[in] len Размер вектора dst.
 * \param[in] state Структура содержащая параметры для ГПСЧ.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_rand_uniform(Ipp8u *dst, int len, IppsRandUniState_8u *state)
{
    IppStatus status = ippsRandUniform_8u(dst, len, state);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет сгенерировать псевдо-случайные числа
 *        на основе нормального распределения в вектор X.
 * \param[out] dst Конечный вектор с 16 разрядными целыми числами X.
 * \param[in] len Размер вектора dst.
 * \param[in] state Структура содержащая параметры для ГПСЧ.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_rand_uniform(Ipp16s *dst, int len, IppsRandUniState_16s *state)
{
    IppStatus status = ippsRandUniform_16s(dst, len, state);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет сгенерировать псевдо-случайные числа
 *        на основе нормального распределения в вектор X.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными числами X.
 * \param[in] len Размер вектора dst.
 * \param[in] state Структура содержащая параметры для ГПСЧ.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_rand_uniform(Ipp32f *dst, int len, IppsRandUniState_32f *state)
{
    IppStatus status = ippsRandUniform_32f(dst, len, state);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_RAND_UNIFORM_H
