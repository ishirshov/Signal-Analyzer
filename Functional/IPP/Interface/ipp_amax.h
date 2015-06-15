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

#ifndef IPP_AMAX_H
#define IPP_AMAX_H

#include "ipp_abs.h"
#include "ipp_add.h"
#include "ipp_sub.h"
#include "ipp_ptr.h"
#include "ipp_div_c.h"

/*!
 * \brief Функция вычисляет максимальные элементы двух массивов X Y
 *        по формуле ((a + b) + |a - b|)/2 и сохраняет результат в массив Z.
 * \param[in] src1 Исходный вектор с 16 разрядными целыми числами X.
 * \param[in] src2 Исходный вектор с 16 разрядными целыми числами X.
 * \param[out] dst  Конечный вектор с 16 разрядными целыми числами Z.
 * \param[in] len  Размер src1, src2 и dst вектора.
 */
inline void ipp_amax(const Ipp16s *src1, const Ipp16s *src2, Ipp16s *dst, int len)
{
    ipp_ptr<Ipp16s> _tmp(ipp_malloc<Ipp16s>(len));
    Ipp16s *tmp = _tmp.get();

    ipp_add(src1, src2, dst, len);
    ipp_sub(src1, src2, tmp, len);
    ipp_abs(tmp, tmp, len);
    ipp_add(dst, tmp, dst, len);
    ipp_div_c(dst, 2, dst, len);
}

/*!
 * \brief Функция вычисляет максимальные элементы двух массивов X Y
 *        по формуле ((a + b) + |a - b|)/2 и сохраняет результат в массив Z.
 * \param[in] src1 Исходный вектор с 32 разрядными целыми числами X.
 * \param[in] src2 Исходный вектор с 32 разрядными целыми числами X.
 * \param[out] dst  Конечный вектор с 32 разрядными целыми числами Z.
 * \param[in] len  Размер src1, src2 и dst вектора.
 */
inline void ipp_amax(const Ipp32s *src1, const Ipp32s *src2, Ipp32s *dst, int len)
{
    ipp_ptr<Ipp32s> _tmp(ipp_malloc<Ipp32s>(len));
    Ipp32s *tmp = _tmp.get();

    ipp_add(src1, src2, dst, len);
    ipp_sub(src1, src2, tmp, len);
    ipp_abs(tmp, tmp, len);
    ipp_add(dst, tmp, dst, len);
    ipp_div_c(dst, 2, dst, len);
}

/*!
 * \brief Функция вычисляет максимальные элементы двух массивов X Y
 *        по формуле ((a + b) + |a - b|)/2 и сохраняет результат в массив Z.
 * \param[in] src1 Исходный вектор с 32 разрядными вещественными числами X.
 * \param[in] src2 Исходный вектор с 32 разрядными вещественными числами X.
 * \param[out] dst  Конечный вектор с 32 разрядными вещественными числами Z.
 * \param[in] len  Размер src1, src2 и dst вектора.
 */
inline void ipp_amax(const Ipp32f *src1, const Ipp32f *src2, Ipp32f *dst, int len)
{
    ipp_ptr<Ipp32f> _tmp(ipp_malloc<Ipp32f>(len));
    Ipp32f *tmp = _tmp.get();

    ipp_add(src1, src2, dst, len);
    ipp_sub(src1, src2, tmp, len);
    ipp_abs(tmp, tmp, len);
    ipp_add(dst, tmp, dst, len);
    ipp_div_c(dst, 2.0, dst, len);
}

/*!
 * \brief Функция вычисляет максимальные элементы двух массивов X Y
 *        по формуле ((a + b) + |a - b|)/2 и сохраняет результат в массив Z.
 * \param[in] src1 Исходный вектор с 64 разрядными вещественными числами X.
 * \param[in] src2 Исходный вектор с 64 разрядными вещественными числами X.
 * \param[out] dst  Конечный вектор с 64 разрядными вещественными числами Z.
 * \param[in] len  Размер src1, src2 и dst вектора.
 */
inline void ipp_amax(const Ipp64f *src1, const Ipp64f *src2, Ipp64f *dst, int len)
{
    ipp_ptr<Ipp64f> _tmp(ipp_malloc<Ipp64f>(len));
    Ipp64f *tmp = _tmp.get();

    ipp_add(src1, src2, dst, len);
    ipp_sub(src1, src2, tmp, len);
    ipp_abs(tmp, tmp, len);
    ipp_add(dst, tmp, dst, len);
    ipp_div_c(dst, 2.0, dst, len);
}

#endif // IPP_AMAX_H
