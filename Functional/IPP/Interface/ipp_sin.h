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

#ifndef IPP_SIN_H
#define IPP_SIN_H

#include <ippvm.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>
#include "ipp_round_type.h"

/*!
 * \brief Функция вычисляет функцию синуса для вектора X
 *        и сохраняет результат в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными вещественными числами X.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными числами Y.
 * \param[in] len Размер вектора src и dst.
 * \param[in] type Тип функции синуса.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sin(const Ipp32f *src, Ipp32f *dst, Ipp32s len, roundType type)
{
    IppStatus status = ippStsNoErr;

    switch(type)
    {
    case A11:
        status = ippsSin_32f_A11(src, dst, len);
        break;
    case A21:
        status = ippsSin_32f_A21(src, dst, len);
        break;
    case A24:
        status = ippsSin_32f_A24(src, dst, len);
        break;
    default:
        throw std::runtime_error("Undefined round type for Ipp32f pow");
    }

    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция вычисляет функцию синуса для вектора X
 *        и сохраняет результат в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными вещественными
 *                комплексными числами X.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными
 *                 комплексными числами Y.
 * \param[in] len Размер вектора src и dst.
 * \param[in] type Тип функции синуса.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_pow_x(const Ipp32fc *src, Ipp32fc *dst, Ipp32s len, roundType type)
{
    IppStatus status = ippStsNoErr;

    switch(type)
    {
    case A11:
        status = ippsSin_32fc_A11(src, dst, len);
        break;
    case A21:
        status = ippsSin_32fc_A21(src, dst, len);
        break;
    case A24:
        status = ippsSin_32fc_A24(src, dst, len);
        break;
    default:
        throw std::runtime_error("Undefined round type for Ipp32f pow");
    }

    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция вычисляет функцию синуса для вектора X
 *        и сохраняет результат в вектор Y.
 * \param[in] src Исходный вектор с 64 разрядными вещественными числами X.
 * \param[out] dst Конечный вектор с 64 разрядными вещественными числами Y.
 * \param[in] len Размер вектора src и dst.
 * \param[in] type Тип функции синуса.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_pow_x(const Ipp64f *src, Ipp64f *dst, Ipp32s len, roundType type)
{
    IppStatus status = ippStsNoErr;

    switch(type)
    {
    case A26:
        status = ippsSin_64f_A26(src, dst, len);
        break;
    case A50:
        status = ippsSin_64f_A50(src, dst, len);
        break;
    case A53:
        status = ippsSin_64f_A53(src, dst, len);
        break;
    default:
        throw std::runtime_error("Undefined round type for Ipp64f pow");
    }

    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция вычисляет функцию синуса для вектора X
 *        и сохраняет результат в вектор Y.
 * \param[in] src Исходный вектор с 64 разрядными вещественными
 *                комплексными числами X.
 * \param[out] dst Конечный вектор с 64 разрядными вещественными
 *                 комплексными числами Y.
 * \param[in] len Размер вектора src и dst.
 * \param[in] type Тип функции синуса.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_pow_x(const Ipp64fc *src, Ipp64fc *dst, Ipp32s len, roundType type)
{
    IppStatus status = ippStsNoErr;

    switch(type)
    {
    case A26:
        status = ippsSin_64fc_A26(src, dst, len);
        break;
    case A50:
        status = ippsSin_64fc_A50(src, dst, len);
        break;
    case A53:
        status = ippsSin_64fc_A53(src, dst, len);
        break;
    default:
        throw std::runtime_error("Undefined round type for Ipp64f pow");
    }

    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_SIN_H
