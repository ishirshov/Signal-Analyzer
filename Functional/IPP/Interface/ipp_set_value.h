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

#ifndef IPP_SET_VALUE_H
#define IPP_SET_VALUE_H

#include <ipps.h>
#include <ippdefs.h>
#include <stdexcept>

/*!
 * \brief Функция позволят установить значение val на
 *        всей длине вектора dst.
 * \param[in] val Устанавливаемое значение.
 * \param[out] dst Конечный вектор с 8 разрядными
 *                 целыми положительными числами val.
 * \param[in] size Размер вектора dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_set(Ipp8u val, Ipp8u *dst, Ipp32u size)
{
    IppStatus status = ippsSet_8u(val, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение val на
 *        всей длине вектора dst.
 * \param[in] val Устанавливаемое значение.
 * \param[out] dst Конечный вектор с 16 разрядными целыми числами val.
 * \param[in] size Размер вектора dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_set(Ipp16s val, Ipp16s *dst, Ipp32u size)
{
    IppStatus status = ippsSet_16s(val, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение val на
 *        всей длине вектора dst.
 * \param[in] val Устанавливаемое значение.
 * \param[out] dst Конечный вектор с 32 разрядными целыми числами val.
 * \param[in] size Размер вектора dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_set(Ipp32s val, Ipp32s *dst, Ipp32u size)
{
    IppStatus status = ippsSet_32s(val, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение val на
 *        всей длине вектора dst.
 * \param[in] val Устанавливаемое значение.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными числами val.
 * \param[in] size Размер вектора dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_set(Ipp32f val, Ipp32f *dst, Ipp32u size)
{
    IppStatus status = ippsSet_32f(val, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение val на
 *        всей длине вектора dst.
 * \param[in] val Устанавливаемое значение.
 * \param[out] dst Конечный вектор с 64 разрядными целыми числами val.
 * \param[in] size Размер вектора dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_set(Ipp64s val, Ipp64s *dst, Ipp32u size)
{
    IppStatus status = ippsSet_64s(val, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение val на
 *        всей длине вектора dst.
 * \param[in] val Устанавливаемое значение.
 * \param[out] dst Конечный вектор с 64 разрядными вещественными числами val.
 * \param[in] size Размер вектора dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_set(Ipp64f val, Ipp64f *dst, Ipp32u size)
{
    IppStatus status = ippsSet_64f(val, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение val на
 *        всей длине вектора dst.
 * \param[in] val Устанавливаемое значение.
 * \param[out] dst Конечный вектор с 16 разрядными
 *                 комплексными целыми числами val.
 * \param[in] size Размер вектора dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_set(Ipp16sc val, Ipp16sc *dst, Ipp32u size)
{
    IppStatus status = ippsSet_16sc(val, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение val на
 *        всей длине вектора dst.
 * \param[in] val Устанавливаемое значение.
 * \param[out] dst Конечный вектор с 32 разрядными
 *                 комплексными целыми числами val.
 * \param[in] size Размер вектора dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_set(Ipp32sc val, Ipp32sc *dst, Ipp32u size)
{
    IppStatus status = ippsSet_32sc(val, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение val на
 *        всей длине вектора dst.
 * \param[in] val Устанавливаемое значение.
 * \param[out] dst Конечный вектор с 32 разрядными
 *                 комплексными вещественными числами val.
 * \param[in] size Размер вектора dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_set(Ipp32fc val, Ipp32fc *dst, Ipp32u size)
{
    IppStatus status = ippsSet_32fc(val, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение val на
 *        всей длине вектора dst.
 * \param[in] val Устанавливаемое значение.
 * \param[out] dst Конечный вектор с 64 разрядными
 *                 комплексными целыми числами val.
 * \param[in] size Размер вектора dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_set(Ipp64sc val, Ipp64sc *dst, Ipp32u size)
{
    IppStatus status = ippsSet_64sc(val, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение val на
 *        всей длине вектора dst.
 * \param[in] val Устанавливаемое значение.
 * \param[out] dst Конечный вектор с 64 разрядными
 *                 комплексными вещественными числами val.
 * \param[in] size Размер вектора dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_set(Ipp64fc val, Ipp64fc *dst, Ipp32u size)
{
    IppStatus status = ippsSet_64fc(val, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_SET_VALUE_H
