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

#ifndef IPP_ZERO_H
#define IPP_ZERO_H

#include <ipps.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>

/*!
 * \brief Функция позволят установить значение 0 на
 *        всей длине вектора dst.
 * \param[out] dst Конечный вектор с 8 разрядными
 *                 целыми положительными числами val.
 * \param[in] size Размер вектора dst.
 */
inline void ipp_zero(Ipp8u *dst, Ipp32u size)
{
    IppStatus status = ippsZero_8u(dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение 0 на
 *        всей длине вектора dst.
 * \param[out] dst Конечный вектор с 16 разрядными
 *                 целыми числами val.
 * \param[in] size Размер вектора dst.
 */
inline void ipp_zero(Ipp16s *dst, Ipp32u size)
{
    IppStatus status = ippsZero_16s(dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение 0 на
 *        всей длине вектора dst.
 * \param[out] dst Конечный вектор с 32 разрядными
 *                 целыми числами val.
 * \param[in] size Размер вектора dst.
 */
inline void ipp_zero(Ipp32s *dst, Ipp32u size)
{
    IppStatus status = ippsZero_32s(dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение 0 на
 *        всей длине вектора dst.
 * \param[out] dst Конечный вектор с 32 разрядными
 *                 вещественными числами val.
 * \param[in] size Размер вектора dst.
 */
inline void ipp_zero(Ipp32f *dst, Ipp32u size)
{
    IppStatus status = ippsZero_32f(dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение 0 на
 *        всей длине вектора dst.
 * \param[out] dst Конечный вектор с 64 разрядными
 *                 целыми числами val.
 * \param[in] size Размер вектора dst.
 */
inline void ipp_zero(Ipp64s *dst, Ipp32u size)
{
    IppStatus status = ippsZero_64s(dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение 0 на
 *        всей длине вектора dst.
 * \param[out] dst Конечный вектор с 64 разрядными
 *                 вещественными числами val.
 * \param[in] size Размер вектора dst.
 */
inline void ipp_zero(Ipp64f *dst, Ipp32u size)
{
    IppStatus status = ippsZero_64f(dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение 0 на
 *        всей длине вектора dst.
 * \param[out] dst Конечный вектор с 16 разрядными
 *                 комплексными целыми числами val.
 * \param[in] size Размер вектора dst.
 */
inline void ipp_zero(Ipp16sc *dst, Ipp32u size)
{
    IppStatus status = ippsZero_16sc(dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение 0 на
 *        всей длине вектора dst.
 * \param[out] dst Конечный вектор с 32 разрядными
 *                 комплексными целыми числами val.
 * \param[in] size Размер вектора dst.
 */
inline void ipp_zero(Ipp32sc *dst, Ipp32u size)
{
    IppStatus status = ippsZero_32sc(dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение 0 на
 *        всей длине вектора dst.
 * \param[out] dst Конечный вектор с 32 разрядными
 *                 комплексными вещественными числами val.
 * \param[in] size Размер вектора dst.
 */
inline void ipp_zero(Ipp32fc *dst, Ipp32u size)
{
    IppStatus status = ippsZero_32fc(dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение 0 на
 *        всей длине вектора dst.
 * \param[out] dst Конечный вектор с 64 разрядными
 *                 комплексными целыми числами val.
 * \param[in] size Размер вектора dst.
 */
inline void ipp_zero(Ipp64sc *dst, Ipp32u size)
{
    IppStatus status = ippsZero_64sc(dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволят установить значение 0 на
 *        всей длине вектора dst.
 * \param[out] dst Конечный вектор с 64 разрядными
 *                 комплексными вещественными числами val.
 * \param[in] size Размер вектора dst.
 */
inline void ipp_zero(Ipp64fc *dst, Ipp32u size)
{
    IppStatus status = ippsZero_64fc(dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_ZERO_H
