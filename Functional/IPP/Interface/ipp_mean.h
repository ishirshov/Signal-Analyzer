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

#ifndef IPP_MEAN_H
#define IPP_MEAN_H

#include <ipps.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>

/*!
 * \brief Функция позволяет вычислить среднее арифметическое вектора X.
 * \param[in] src Исходный вектор с 32 разрядными вещественными числами X.
 * \param[in] len Размер вектора src.
 * \param[out] mean Переменная для результата.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_mean(const Ipp32f *src, int len, Ipp32f &mean)
{
    IppStatus status = ippsMean_32f(src, len, &mean, ippAlgHintFast);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет вычислить среднее арифметическое вектора X.
 * \param[in] src Исходный вектор с 32 разрядными вещественными комплексными числами X.
 * \param[in] len Размер вектора src.
 * \param[out] mean Переменная для результата.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_mean(const Ipp32fc *src, int len, Ipp32fc &mean)
{
    IppStatus status = ippsMean_32fc(src, len, &mean, ippAlgHintFast);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет вычислить среднее арифметическое вектора X.
 * \param[in] src Исходный вектор с 64 разрядными вещественными числами X.
 * \param[in] len Размер вектора src.
 * \param[out] mean Переменная для результата.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_mean(const Ipp64f *src, int len, Ipp64f &mean)
{
    IppStatus status = ippsMean_64f(src, len, &mean);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет вычислить среднее арифметическое вектора X.
 * \param[in] src Исходный вектор с 64 разрядными вещественными комплексными числами X.
 * \param[in] len Размер вектора src.
 * \param[out] mean Переменная для результата.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_mean(const Ipp64fc *src, int len, Ipp64fc &mean)
{
    IppStatus status = ippsMean_64fc(src, len, &mean);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет вычислить среднее арифметическое вектора X.
 * \param[in] src Исходный вектор с 16 разрядными вещественными числами X.
 * \param[in] len Размер вектора src.
 * \param[out] mean Переменная для результата.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_mean(const Ipp16s *src, int len, Ipp16s &mean)
{
    IppStatus status = ippsMean_16s_Sfs(src, len, &mean, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет вычислить среднее арифметическое вектора X.
 * \param[in] src Исходный вектор с 32 разрядными целыми числами X.
 * \param[in] len Размер вектора src.
 * \param[out] mean Переменная для результата.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_mean(const Ipp32s *src, int len, Ipp32s &mean)
{
    IppStatus status = ippsMean_32s_Sfs(src, len, &mean, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет вычислить среднее арифметическое вектора X.
 * \param[in] src Исходный вектор с 16 разрядными целыми комплексными числами X.
 * \param[in] len Размер вектора src.
 * \param[out] mean Переменная для результата.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_mean(const Ipp16sc *src, int len, Ipp16sc &mean)
{
    IppStatus status = ippsMean_16sc_Sfs(src, len, &mean, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_MEAN_H
