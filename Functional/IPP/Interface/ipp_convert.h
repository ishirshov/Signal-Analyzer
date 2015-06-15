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

#ifndef IPP_CONVERT_H
#define IPP_CONVERT_H

#include <ipps.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>

/*!
 * \brief Функция преобразования вектора данных
 *        из одного типа X в тип Y.
 * \param[in] src   Исходный вектор с 16 разрядными целыми числами X.
 * \param[out] dst  Конечный вектор с 32 разрядными целыми числами Y.
 * \param[in] size  Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_convert(const Ipp16s *src, Ipp32s *dst, Ipp32u size)
{
    IppStatus status = ippsConvert_16s32s(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция преобразования вектора данных
 *        из одного типа X в тип Y.
 * \param[in] src   Исходный вектор с 16 разрядными целыми числами X.
 * \param[out] dst  Конечный вектор с 32 разрядными вещественными числами Y.
 * \param[in] size  Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_convert(const Ipp16s *src, Ipp32f *dst, Ipp32u size)
{
    IppStatus status = ippsConvert_16s32f(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция преобразования вектора данных
 *        из одного типа X в тип Y.
 * \param[in] src   Исходный вектор с 16 разрядными целыми числами X.
 * \param[out] dst   Конечный вектор с 64 разрядными вещественными числами Y.
 * \param[in] size  Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_convert(const Ipp16s *src, Ipp64f *dst, Ipp32u size)
{
    IppStatus status = ippsConvert_16s64f_Sfs(src, dst, size, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция преобразования вектора данных
 *        из одного типа X в тип Y.
 * \param[in] src   Исходный вектор с 32 разрядными целыми числами X.
 * \param[out] dst   Конечный вектор с 16 разрядными целыми числами Y.
 * \param[in] size  Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_convert(const Ipp32s *src, Ipp16s *dst, Ipp32u size)
{
    IppStatus status = ippsConvert_32s16s(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция преобразования вектора данных
 *        из одного типа X в тип Y.
 * \param[in] src   Исходный вектор с 32 разрядными целыми числами X.
 * \param[out] dst   Конечный вектор с 32 разрядными вещественными числами Y.
 * \param[in] size  Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_convert(const Ipp32s *src, Ipp32f *dst, Ipp32u size)
{
    IppStatus status = ippsConvert_32s32f(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция преобразования вектора данных
 *        из одного типа X в тип Y.
 * \param[in] src   Исходный вектор с 32 разрядными целыми числами X.
 * \param[out] dst   Конечный вектор с 64 разрядными вещественными числами Y.
 * \param[in] size  Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_convert(const Ipp32s *src, Ipp64f *dst, Ipp32u size)
{
    IppStatus status = ippsConvert_32s64f(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция преобразования вектора данных
 *        из одного типа X в тип Y.
 * \param[in] src   Исходный вектор с 32 разрядными вещественными числами X.
 * \param[out] dst  Конечный вектор с 16 разрядными целыми числами Y.
 * \param[in] size  Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_convert(const Ipp32f *src, Ipp16s *dst, Ipp32u size)
{
    IppStatus status = ippsConvert_32f16s_Sfs(src, dst, size, ippRndNear, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция преобразования вектора данных
 *        из одного типа X в тип Y.
 * \param[in] src   Исходный вектор с 32 разрядными вещественными числами X.
 * \param[out] dst  Конечный вектор с 32 разрядными целыми числами Y.
 * \param[in] size  Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_convert(const Ipp32f *src, Ipp32s *dst, Ipp32u size)
{
    IppStatus status = ippsConvert_32f32s_Sfs(src, dst, size, ippRndNear, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция преобразования вектора данных
 *        из одного типа X в тип Y.
 * \param[in] src   Исходный вектор с 32 разрядными вещественными числами X.
 * \param[out] dst  Конечный вектор с 64 разрядными вещественными числами Y.
 * \param[in] size  Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_convert(const Ipp32f *src, Ipp64f *dst, Ipp32u size)
{
    IppStatus status = ippsConvert_32f64f(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция преобразования вектора данных
 *        из одного типа X в тип Y.
 * \param[in] src   Исходный вектор с 64 разрядными вещественными числами X.
 * \param[out] dst  Конечный вектор с 16 разрядными целыми числами Y.
 * \param[in] size  Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_convert(const Ipp64f *src, Ipp16s *dst, Ipp32u size)
{
    IppStatus status = ippsConvert_64f16s_Sfs(src, dst, size, ippRndNear, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция преобразования вектора данных
 *        из одного типа X в тип Y.
 * \param[in] src   Исходный вектор с 64 разрядными вещественными числами X.
 * \param[out] dst  Конечный вектор с 32 разрядными целыми числами Y.
 * \param[in] size  Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_convert(const Ipp64f *src, Ipp32s *dst, Ipp32u size)
{
    IppStatus status = ippsConvert_64f32s_Sfs(src, dst, size, ippRndNear, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция преобразования вектора данных
 *        из одного типа X в тип Y.
 * \param[in] src   Исходный вектор с 64 разрядными вещественными числами X.
 * \param[out] dst  Конечный вектор с 32 разрядными вещественными числами Y.
 * \param[in] size  Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_convert(const Ipp64f *src, Ipp32f *dst, Ipp32u size)
{
    IppStatus status = ippsConvert_64f32f(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_CONVERT_H
