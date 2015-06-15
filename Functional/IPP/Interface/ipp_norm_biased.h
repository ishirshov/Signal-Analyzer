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

#ifndef IPP_NORM_BIASED_H
#define IPP_NORM_BIASED_H

#include <ipps.h>
#include <ippdefs.h>
#include <stdexcept>

/*!
 * \brief Функция позволяет избавится от систематической ошибки в векторе X,
 *        которая делает все значения неправильными на определенную
 *        величину (англ. Normalized bias).
 * \param[in] pSrc Исходный вектор с 64 разрядными вещественными числами X.
 * \param[out] pDst Конечный вектор с 64 разрядными вещественными числами Y.
 * \param[in] n Размер вектора pSrc и pDst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_norm_biased(const Ipp64f *pSrc, Ipp64f *pDst, const Ipp32s n)
{
    Ipp64f mean = 0.0;

    IppStatus message = ippsMean_64f(pSrc, n, &mean);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    message = ippsSubC_64f(pSrc, mean, pDst, n);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));
}

/*!
 * \brief Функция позволяет избавится от систематической ошибки в векторе X,
 *        которая делает все значения неправильными на определенную
 *        величину (англ. Normalized bias).
 * \param[in] pSrc Исходный вектор с 32 разрядными вещественными числами X.
 * \param[out] pDst Конечный вектор с 32 разрядными вещественными числами Y.
 * \param[in] n Размер вектора pSrc и pDst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_norm_biased(const Ipp32f *pSrc, Ipp32f *pDst, const Ipp32s n)
{
    Ipp32f mean = 0.0;

    IppStatus message = ippsMean_32f(pSrc, n, &mean, ippAlgHintFast);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    message = ippsSubC_32f(pSrc, mean, pDst, n);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));
}

#endif // IPP_NORM_BIASED_H
