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

#ifndef IPP_COPY_H
#define IPP_COPY_H

#include <ipps.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>

/*!
 * \brief Функция копирования данных из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 8 разрядными целыми числами X.
 * \param[out] dst Конечный вектор с 8 разрядными целыми числами Y.
 * \param[in] size Размер src1 и src2 вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_copy(const Ipp8u *src, Ipp8u *dst, Ipp32u size)
{
    IppStatus status = ippsCopy_8u(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция копирования данных из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 16 разрядными целыми числами X.
 * \param[out] dst Конечный вектор с 16 разрядными целыми числами Y.
 * \param[in] size Размер src1 и src2 вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_copy(const Ipp16s *src, Ipp16s *dst, Ipp32u size)
{
    IppStatus status = ippsCopy_16s(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция копирования данных из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными целыми числами X.
 * \param[out] dst Конечный вектор с 32 разрядными целыми числами Y.
 * \param[in] size Размер src1 и src2 вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_copy(const Ipp32s *src, Ipp32s *dst, Ipp32u size)
{
    IppStatus status = ippsCopy_32s(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция копирования данных из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными вещественными числами X.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными числами Y.
 * \param[in] size Размер src1 и src2 вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_copy(const Ipp32f *src, Ipp32f *dst, Ipp32u size)
{
    IppStatus status = ippsCopy_32f(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция копирования данных из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 64 разрядными целыми числами X.
 * \param[out] dst Конечный вектор с 64 разрядными целыми числами Y.
 * \param[in] size Размер src1 и src2 вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_copy(const Ipp64s *src, Ipp64s *dst, Ipp32u size)
{
    IppStatus status = ippsCopy_64s(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция копирования данных из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 64 разрядными вещественными числами X.
 * \param[out] dst Конечный вектор с 64 разрядными вещественными числами Y.
 * \param[in] size Размер src1 и src2 вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_copy(const Ipp64f *src, Ipp64f *dst, Ipp32u size)
{
    IppStatus status = ippsCopy_64f(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция копирования данных из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 16 разрядными целыми комплексными числами X.
 * \param[out] dst Конечный вектор с 16 разрядными целыми комплексными числами Y.
 * \param[in] size Размер src1 и src2 вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_copy(const Ipp16sc *src, Ipp16sc *dst, Ipp32u size)
{
    IppStatus status = ippsCopy_16sc(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция копирования данных из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными целыми комплексными числами X.
 * \param[out] dst Конечный вектор с 32 разрядными целыми комплексными числами Y.
 * \param[in] size Размер src1 и src2 вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_copy(const Ipp32sc *src, Ipp32sc *dst, Ipp32u size)
{
    IppStatus status = ippsCopy_32sc(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция копирования данных из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными вещественными комплексными числами X.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными комплексными числами Y.
 * \param[in] size Размер src1 и src2 вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_copy(const Ipp32fc *src, Ipp32fc *dst, Ipp32u size)
{
    IppStatus status = ippsCopy_32fc(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция копирования данных из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 64 разрядными целыми комплексными числами X.
 * \param[out] dst Конечный вектор с 64 разрядными целыми комплексными числами Y.
 * \param[in] size Размер src1 и src2 вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_copy(const Ipp64sc *src, Ipp64sc *dst, Ipp32u size)
{
    IppStatus status = ippsCopy_64sc(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция копирования данных из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 64 разрядными вещественными комплексными числами X.
 * \param[out] dst Конечный вектор с 64 разрядными вещественными комплексными числами Y.
 * \param[in] size Размер src1 и src2 вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_copy(const Ipp64fc *src, Ipp64fc *dst, Ipp32u size)
{
    IppStatus status = ippsCopy_64fc(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_COPY_H
