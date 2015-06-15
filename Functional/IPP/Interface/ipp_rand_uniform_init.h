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

#ifndef IPP_RAND_UNIFORM_INIT_H
#define IPP_RAND_UNIFORM_INIT_H

#include "ipp_ptr.h"

/*!
 * \brief Функция инициализирует структуру данных содержащую
 *        все необходимые параметры для ГПСЧ.
 * \param[out] state Структура содержащая параметры для 8
 *                   разрядного целочисленного ГПСЧ.
 * \param[in] low Нижняя граница нормального распределения.
 * \param[in] high Верхняя граница нормального распределения.
 * \param[in] seed Начальное значения для ГПСЧ.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_rand_uniform_init(ipp_ptr<IppsRandUniState_8u> &state, Ipp8u low, Ipp8u high, Ipp32u seed)
{
    int size_bytes = 0;

    IppStatus status = ippsRandGaussGetSize_8u(&size_bytes);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

    state.reset((IppsRandUniState_8u*)ipp_malloc<Ipp8u>(size_bytes));

    status = ippsRandUniformInit_8u(state.get(), low, high, seed);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция инициализирует структуру данных содержащую
 *        все необходимые параметры для ГПСЧ.
 * \param[out] state Структура содержащая параметры для 16
 *                   разрядного целочисленного ГПСЧ.
 * \param[in] low Нижняя граница нормального распределения.
 * \param[in] high Верхняя граница нормального распределения.
 * \param[in] seed Начальное значения для ГПСЧ.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_rand_uniform_init(ipp_ptr<IppsRandUniState_16s> &state, Ipp16s low, Ipp16s high, Ipp32u seed)
{
    int size_bytes = 0;

    IppStatus status = ippsRandGaussGetSize_16s(&size_bytes);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

    state.reset((IppsRandUniState_16s*)ipp_malloc<Ipp8u>(size_bytes));

    status = ippsRandUniformInit_16s(state.get(), low, high, seed);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция инициализирует структуру данных содержащую
 *        все необходимые параметры для ГПСЧ.
 * \param[out] state Структура содержащая параметры для 32
 *                   разрядного вещественного ГПСЧ.
 * \param[in] low Нижняя граница нормального распределения.
 * \param[in] high Верхняя граница нормального распределения.
 * \param[in] seed Начальное значения для ГПСЧ.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_rand_uniform_init(ipp_ptr<IppsRandUniState_32f> &state, Ipp32f low, Ipp32f high, Ipp32u seed)
{
    int size_bytes = 0;

    IppStatus status = ippsRandGaussGetSize_32f(&size_bytes);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

    state.reset((IppsRandUniState_32f*)ipp_malloc<Ipp8u>(size_bytes));

    status = ippsRandUniformInit_32f(state.get(), low, high, seed);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_RAND_UNIFORM_INIT_H
