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

#ifndef IPP_DIV_H
#define IPP_DIV_H

#include <ipps.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>

/*!
 * \brief Функция выполненяет операцию деления двух векторов X Y и
 *        результат сохраняет в вектор Z.
 * \param[in] src1 Исходный вектор с 8 разрядными положительными целыми числами X.
 * \param[in] src2 Исходный вектор с 8 разрядными положительными целыми числами Y.
 * \param[out] dst Конечный вектор с 8 разрядными положительными целыми числами Z.
 * \param[in] size Размер src1, src2 и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div(const Ipp8u *src1, const Ipp8u *src2, Ipp8u *dst, Ipp32u size)
{
    IppStatus status = ippsDiv_8u_Sfs(src1, src2, dst, size, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполненяет операцию деления двух векторов X Y и
 *        результат сохраняет в вектор Z.
 * \param[in] src1 Исходный вектор с 16 разрядными положительными целыми числами X.
 * \param[in] src2 Исходный вектор с 16 разрядными положительными целыми числами Y.
 * \param[out] dst Конечный вектор с 16 разрядными положительными целыми числами Z.
 * \param[in] size Размер src1, src2 и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div(const Ipp16u *src1, const Ipp16u *src2, Ipp16u *dst, Ipp32u size)
{
    IppStatus status = ippsDiv_16u_Sfs(src1, src2, dst, size, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполненяет операцию деления двух векторов X Y и
 *        результат сохраняет в вектор Z.
 * \param[in] src1 Исходный вектор с 16 разрядными целыми числами X.
 * \param[in] src2 Исходный вектор с 16 разрядными целыми числами Y.
 * \param[out] dst Конечный вектор с 16 разрядными целыми числами Z.
 * \param[in] size Размер src1, src2 и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div(const Ipp16s *src1, const Ipp16s *src2, Ipp16s *dst, Ipp32u size)
{
    IppStatus status = ippsDiv_16s_Sfs(src1, src2, dst, size, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполненяет операцию деления двух векторов X Y и
 *        результат сохраняет в вектор Z.
 * \param[in] src1 Исходный вектор с 32 разрядными целыми числами X.
 * \param[in] src2 Исходный вектор с 32 разрядными целыми числами Y.
 * \param[out] dst Конечный вектор с 32 разрядными целыми числами Z.
 * \param[in] size Размер src1, src2 и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div(const Ipp32s *src1, const Ipp32s *src2, Ipp32s *dst, Ipp32u size)
{
    IppStatus status = ippsDiv_32s_Sfs(src1, src2, dst, size, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполненяет операцию деления двух векторов X Y и
 *        результат сохраняет в вектор Z.
 * \param[in] src1 Исходный вектор с 16 разрядными целыми комплексными числами X.
 * \param[in] src2 Исходный вектор с 16 разрядными целыми комплексными числами Y.
 * \param[out] dst Конечный вектор с 16 разрядными целыми комплексными числами Z.
 * \param[in] size Размер src1, src2 и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div(const Ipp16sc *src1, const Ipp16sc *src2, Ipp16sc *dst, Ipp32u size)
{
    IppStatus status = ippsDiv_16sc_Sfs(src1, src2, dst, size, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполненяет операцию деления двух векторов X Y и
 *        результат сохраняет в вектор Z.
 * \param[in] src1 Исходный вектор с 16 разрядными целыми числами X.
 * \param[in] src2 Исходный вектор с 32 разрядными целыми числами Y.
 * \param[out] dst Конечный вектор с 16 разрядными целыми числами Z.
 * \param[in] size Размер src1, src2 и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div(const Ipp16s *src1, const Ipp32s *src2, Ipp16s *dst, Ipp32u size)
{
    IppStatus status = ippsDiv_32s16s_Sfs(src1, src2, dst, size, 0);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполненяет операцию деления двух векторов X Y и
 *        результат сохраняет в вектор Z.
 * \param[in] src1 Исходный вектор с 32 разрядными вещественными числами X.
 * \param[in] src2 Исходный вектор с 32 разрядными вещественными числами Y.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными числами Z.
 * \param[in] size Размер src1, src2 и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div(const Ipp32f *src1, const Ipp32f *src2, Ipp32f *dst, Ipp32u size)
{
    IppStatus status = ippsDiv_32f(src1, src2, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполненяет операцию деления двух векторов X Y и
 *        результат сохраняет в вектор Z.
 * \param[in] src1 Исходный вектор с 64 разрядными вещественными числами X.
 * \param[in] src2 Исходный вектор с 64 разрядными вещественными числами Y.
 * \param[out] dst Конечный вектор с 64 разрядными вещественными числами Z.
 * \param[in] size Размер src1, src2 и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div(const Ipp64f *src1, const Ipp64f *src2, Ipp64f *dst, Ipp32u size)
{
    IppStatus status = ippsDiv_64f(src1, src2, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполненяет операцию деления двух векторов X Y и
 *        результат сохраняет в вектор Z.
 * \param[in] src1 Исходный вектор с 32 разрядными вещественными комплексными числами X.
 * \param[in] src2 Исходный вектор с 32 разрядными вещественными комплексными числами Y.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными комплексными числами Z.
 * \param[in] size Размер src1, src2 и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div(const Ipp32fc *src1, const Ipp32fc *src2, Ipp32fc *dst, Ipp32u size)
{
    IppStatus status = ippsDiv_32fc(src1, src2, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция выполненяет операцию деления двух векторов X Y и
 *        результат сохраняет в вектор Z.
 * \param[in] src1 Исходный вектор с 64 разрядными вещественными комплексными числами X.
 * \param[in] src2 Исходный вектор с 64 разрядными вещественными комплексными числами Y.
 * \param[out] dst Конечный вектор с 64 разрядными вещественными комплексными числами Z.
 * \param[in] size Размер src1, src2 и dst вектора.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_div(const Ipp64fc *src1, const Ipp64fc *src2, Ipp64fc *dst, Ipp32u size)
{
    IppStatus status = ippsDiv_64fc(src1, src2, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_DIV_H
