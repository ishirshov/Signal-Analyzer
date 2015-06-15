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

#ifndef IPP_AUTOCORR_NORM_H
#define IPP_AUTOCORR_NORM_H

#include "ipp_allocator.h"
#include <stdexcept>

/*!
 * \brief Функция позволяет получить рабочий буфер для
 *        функции автокорреляции из библиотеки Intel PP.
 * \param[in] src_len Размер исходного вектора src.
 * \param[in] dst_len Размер конечного вектора dst.
 * \param[in] data_t Тип данных функции автокорреляции.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 * \return Буфер для функции автокорреляции.
 */
inline Ipp8u* ipp_autocorr_norm_get_buff(int src_len, int dst_len, IppDataType data_t)
{
    int buff_sz = 0;

    IppStatus status = ippsAutoCorrNormGetBufferSize(src_len, dst_len, data_t, IppEnum(ippAlgAuto&ippsNormB), &buff_sz);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

    return ipp_malloc<Ipp8u>(buff_sz);
}

/*!
 * \brief Функция автокорреляции из библотеки Intel PP.
 * \param[in] src       Исходный вектор с 32 разрядными вещественными числами X.
 * \param[in] src_len   Размер вектора src.
 * \param[out] dst       Исходный вектор с 32 разрядными вещественными числами X.
 * \param[in] dst_len   Размер вектора dst.
 * \param[in] buff      Указатель на рабочий буфер для функции автокорреляции.
 */
inline void ipp_autocorr_norm(const Ipp32f *src, int src_len, Ipp32f *dst, int dst_len, Ipp8u *buff)
{
    IppStatus status = ippsAutoCorrNorm_32f(src, src_len, dst, dst_len, IppEnum(ippAlgAuto&ippsNormB), buff);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция автокорреляции из библотеки Intel PP.
 * \param[in] src       Исходный вектор с 64 разрядными вещественными числами X.
 * \param[in] src_len   Размер вектора src.
 * \param[out] dst       Исходный вектор с 64 разрядными вещественными числами X.
 * \param[in] dst_len   Размер вектора dst.
 * \param[in] buff      Указатель на рабочий буфер для функции автокорреляции.
 */
inline void ipp_autocorr_norm(const Ipp64f *src, int src_len, Ipp64f *dst, int dst_len, Ipp8u *buff)
{
    IppStatus status = ippsAutoCorrNorm_64f(src, src_len, dst, dst_len, IppEnum(ippAlgAuto&ippsNormB), buff);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция автокорреляции из библотеки Intel PP.
 * \param[in] src       Исходный вектор с 32 разрядными вещественными комплексными числами X.
 * \param[in] src_len   Размер вектора src.
 * \param[out] dst       Исходный вектор с 32 разрядными вещественными комплексными числами X.
 * \param[in] dst_len   Размер вектора dst.
 * \param[in] buff      Указатель на рабочий буфер для функции автокорреляции.
 */
inline void ipp_autocorr_norm(const Ipp32fc *src, int src_len, Ipp32fc *dst, int dst_len, Ipp8u *buff)
{
    IppStatus status = ippsAutoCorrNorm_32fc(src, src_len, dst, dst_len, IppEnum(ippAlgAuto&ippsNormB), buff);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция автокорреляции из библотеки Intel PP.
 * \param[in] src       Исходный вектор с 64 разрядными вещественными комплексными числами X.
 * \param[in] src_len   Размер вектора src.
 * \param[out] dst       Исходный вектор с 64 разрядными вещественными комплексными числами X.
 * \param[in] dst_len   Размер вектора dst.
 * \param[in] buff      Указатель на рабочий буфер для функции автокорреляции.
 */
inline void ipp_autocorr_norm(const Ipp64fc *src, int src_len, Ipp64fc *dst, int dst_len, Ipp8u *buff)
{
    IppStatus status = ippsAutoCorrNorm_64fc(src, src_len, dst, dst_len, IppEnum(ippAlgAuto&ippsNormB), buff);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_AUTOCORR_NORM_H
