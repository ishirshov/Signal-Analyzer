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

#ifndef IPP_DIV_C_H
#define IPP_DIV_C_H

#include "ipp_ptr.h"
#include "ipp_convert.h"

/*!
 * \brief Функция выполняет поэлементную операцию деления вектора X
 *        и константы Y, результат сохраняет в вектор Z.
 * \param[in] src Исходный вектор с 8 разрядными положительными целыми числами X.
 * \param[in] val Константа сложения Y.
 * \param[out] dst Конечный вектор с 8 разрядными положительными целыми числами Z.
 * \param[in] len Размер src и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div_c(const Ipp8u *src, Ipp8u val, Ipp8u *dst, Ipp32u size)
{
    IppStatus status = ippsDivC_8u_Sfs(src, val, dst, size, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполняет поэлементную операцию деления вектора X
 *        и константы Y, результат сохраняет в вектор Z.
 * \param[in] src Исходный вектор с 16 разрядными целыми числами X.
 * \param[in] val Константа сложения Y.
 * \param[out] dst Конечный вектор с 16 разрядными целыми числами Z.
 * \param[in] len Размер src и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div_c(const Ipp16s *src, Ipp16s val, Ipp16s *dst, Ipp32u size)
{
    IppStatus status = ippsDivC_16s_Sfs(src, val, dst, size, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполняет поэлементную операцию деления вектора X
 *        и константы Y, результат сохраняет в вектор Z.
 * \param[in] src Исходный вектор с 32 разрядными целыми числами X.
 * \param[in] val Константа сложения Y.
 * \param[out] dst Конечный вектор с 32 разрядными целыми числами Z.
 * \param[in] len Размер src и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div_c(const Ipp32s *src, Ipp32s val, Ipp32s *dst, Ipp32u size)
{
    ipp_ptr<Ipp32f> _tmp(ipp_malloc<Ipp32f>(size));
    Ipp32f *tmp = _tmp.get();

    ipp_convert(src, tmp, size);

    IppStatus status = ippsDivC_32f(tmp, Ipp32f(val), tmp, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

    ipp_convert(tmp, dst, size);
}

/*!
 * \brief Функция выполняет поэлементную операцию деления вектора X
 *        и константы Y, результат сохраняет в вектор Z.
 * \param[in] src Исходный вектор с 16 разрядными целыми комплексными числами X.
 * \param[in] val Константа сложения Y.
 * \param[out] dst Конечный вектор с 16 разрядными целыми комплексными числами Z.
 * \param[in] len Размер src и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div_c(const Ipp16sc *src, Ipp16sc val, Ipp16sc *dst, Ipp32u size)
{
    IppStatus status = ippsDivC_16sc_Sfs(src, val, dst, size, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполняет поэлементную операцию деления вектора X
 *        и константы Y, результат сохраняет в вектор Z.
 * \param[in] src Исходный вектор с 16 разрядными положительными целыми числами X.
 * \param[in] val Константа сложения Y.
 * \param[out] dst Конечный вектор с 16 разрядными положительными целыми числами Z.
 * \param[in] len Размер src и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div_c(const Ipp16u *src, Ipp16u val, Ipp16u *dst, Ipp32u size)
{
    IppStatus status = ippsDivC_16u_Sfs(src, val, dst, size, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполняет поэлементную операцию деления вектора X
 *        и константы Y, результат сохраняет в вектор Z.
 * \param[in] src Исходный вектор с 32 разрядными вещественными числами X.
 * \param[in] val Константа сложения Y.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными числами Z.
 * \param[in] len Размер src и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div_c(const Ipp32f *src, Ipp32f val, Ipp32f *dst, Ipp32u size)
{
    IppStatus status = ippsDivC_32f(src, val, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполняет поэлементную операцию деления вектора X
 *        и константы Y, результат сохраняет в вектор Z.
 * \param[in] src Исходный вектор с 32 разрядными вещественными комплексными числами X.
 * \param[in] val Константа сложения Y.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными комплексными числами Z.
 * \param[in] len Размер src и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div_c(const Ipp32fc *src, Ipp32fc val, Ipp32fc *dst, Ipp32u size)
{
    IppStatus status = ippsDivC_32fc(src, val, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполняет поэлементную операцию деления вектора X
 *        и константы Y, результат сохраняет в вектор Z.
 * \param[in] src Исходный вектор с 64 разрядными вещественными числами X.
 * \param[in] val Константа сложения Y.
 * \param[out] dst Конечный вектор с 64 разрядными вещественными числами Z.
 * \param[in] len Размер src и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div_c(const Ipp64f *src, Ipp64f val, Ipp64f *dst, Ipp32u size)
{
    IppStatus status = ippsDivC_64f(src, val, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_DIV_C_H
