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

#ifndef IPP_SIGNAL_PARAMETERS_H
#define IPP_SIGNAL_PARAMETERS_H

#include <ippdefs.h>

/*!
 * \brief Функция реализует алгоритм поиска параметоров
 *        входного сигнала используя CCS формат данных.
 * \param[in] pSrc      Входной вектор с данными спектра сигнала в CCS формате.
 * \param[in] length    Длина вектора pSrc.
 * \param[in] samplFreq Текущая частота дискретизации.
 * \exception std::invalid_argument Ошибка в ходе обработки аргументов функции.
 * \return Параметры сигнала. Вектор с размером в 3 элемента
 *         ([0] - Частота сигнала, [1] - Амплитуда в децибеллах, [2] - Амплитуда в уровнях).
 */
Ipp64f* ipp_find_parameters(const Ipp64fc *pSrc, const Ipp32s length, const Ipp32s samplFreq);

/*!
 * \brief Функция позволяет получить из исходного сигнала,
 *        его спектр и параметры сигнала.
 * \param[in] pSrc      Входной вектор с данными сигнала в 16
 *                      разрядном целочисленном формате.
 * \param[in] length    Длина вектора pSrc.
 * \param[in] samplFreq Текущая частота дискретизации.
 * \return Параметры сигнала.
 */
Ipp64f* ipp_real_to_ccs(const Ipp16s *pSrc, const Ipp32s length, const Ipp32s samplFreq);

/*!
 * \brief Функция позволяет получить из исходного сигнала,
 *        его спектр и параметры сигнала.
 * \param[in] pSrc      Входной вектор с данными сигнала в 64
 *                      разрядном вещественном формате.
 * \param[in] length    Длина вектора pSrc.
 * \param[in] samplFreq Текущая частота дискретизации.
 * \return Параметры сигнала.
 */
Ipp64f* ipp_real_to_ccs(const Ipp64f *pSrc, const Ipp32s length, const Ipp32s samplFreq);

#endif // IPP_SIGNAL_PARAMETERS_H
