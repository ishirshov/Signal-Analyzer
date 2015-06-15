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

#ifndef IPP_SUM_H
#define IPP_SUM_H

#include <ipps.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>

/*!
 * \brief Функция позволяет получить сумму вектора X.
 * \param[in] src Исходный вектор с 16 разрядными целыми числами X.
 * \param[in] len Размер вектора src.
 * \param[out] sum Сумма вектора.
 */
inline void ipp_sum(const Ipp16s *src, int len, Ipp32s &sum)
{
    IppStatus status = ippsSum_16s32s_Sfs(src, len, &sum, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет получить сумму вектора X.
 * \param[in] src Исходный вектор с 16 разрядными комплексными
 *                целыми числами X.
 * \param[in] len Размер вектора src.
 * \param[out] sum Сумма вектора.
 */
inline void ipp_sum(const Ipp16sc *src, int len, Ipp16sc &sum)
{
    IppStatus status = ippsSum_16sc_Sfs(src, len, &sum, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет получить сумму вектора X.
 * \param[in] src Исходный вектор с 16 разрядными целыми числами X.
 * \param[in] len Размер вектора src.
 * \param[out] sum Сумма вектора.
 */
inline void ipp_sum(const Ipp16s *src, int len, Ipp16s &sum)
{
    IppStatus status = ippsSum_16s_Sfs(src, len, &sum, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет получить сумму вектора X.
 * \param[in] src Исходный вектор с 32 разрядными вещественными числами X.
 * \param[in] len Размер вектора src.
 * \param[out] sum Сумма вектора.
 */
inline void ipp_sum(const Ipp32f *src, int len, Ipp32f &sum)
{
    IppStatus status = ippsSum_32f(src, len, &sum, ippAlgHintFast);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет получить сумму вектора X.
 * \param[in] src Исходный вектор с 32 разрядными комплексными
 *                вещественными числами X.
 * \param[in] len Размер вектора src.
 * \param[out] sum Сумма вектора.
 */
inline void ipp_sum(const Ipp32fc *src, int len, Ipp32fc &sum)
{
    IppStatus status = ippsSum_32fc(src, len, &sum, ippAlgHintFast);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет получить сумму вектора X.
 * \param[in] src Исходный вектор с 32 разрядными целыми числами X.
 * \param[in] len Размер вектора src.
 * \param[out] sum Сумма вектора.
 */
inline void ipp_sum(const Ipp32s *src, int len, Ipp32s &sum)
{
    IppStatus status = ippsSum_32s_Sfs(src, len, &sum, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет получить сумму вектора X.
 * \param[in] src Исходный вектор с 64 разрядными вещественными числами X.
 * \param[in] len Размер вектора src.
 * \param[out] sum Сумма вектора.
 */
inline void ipp_sum(const Ipp64f *src, int len, Ipp64f &sum)
{
    IppStatus status = ippsSum_64f(src, len, &sum);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет получить сумму вектора X.
 * \param[in] src Исходный вектор с 64 разрядными комплексными
 *                вещественными числами X.
 * \param[in] len Размер вектора src.
 * \param[out] sum Сумма вектора.
 */
inline void ipp_sum(const Ipp64fc *src, int len, Ipp64fc &sum)
{
    IppStatus status = ippsSum_64fc(src, len, &sum);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_SUM_H
