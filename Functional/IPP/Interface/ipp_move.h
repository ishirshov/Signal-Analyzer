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

#ifndef IPP_MOVE_H
#define IPP_MOVE_H

#include <ipps.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>

/*!
 * \brief Функция позволяет перемещать данные из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 8 разрядными положительными целыми числами X.
 * \param[out] dst Конечный вектор с 8 разрядными положительными целыми числами Y.
 * \param[in] size Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_move(const Ipp8u *src, Ipp8u *dst, Ipp32u size)
{
    IppStatus status = ippsMove_8u(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет перемещать данные из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 16 разрядными целыми числами X.
 * \param[out] dst Конечный вектор с 16 разрядными целыми числами Y.
 * \param[in] size Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_move(const Ipp16s *src, Ipp16s *dst, Ipp32u size)
{
    IppStatus status = ippsMove_16s(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет перемещать данные из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными целыми числами X.
 * \param[out] dst Конечный вектор с 32 разрядными целыми числами Y.
 * \param[in] size Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_move(const Ipp32s *src, Ipp32s *dst, Ipp32u size)
{
    IppStatus status = ippsMove_32s(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет перемещать данные из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными вещественными числами X.
 * \param[out] dst Конечный вектор с 32 разрядными вещественными числами Y.
 * \param[in] size Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_move(const Ipp32f *src, Ipp32f *dst, Ipp32u size)
{
    IppStatus status = ippsMove_32f(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет перемещать данные из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 16 разрядными целыми числами X.
 * \param[out] dst Конечный вектор с 16 разрядными целыми числами Y.
 * \param[in] size Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_move(const Ipp64s *src, Ipp64s *dst, Ipp32u size)
{
    IppStatus status = ippsMove_64s(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет перемещать данные из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 64 разрядными вещественными числами X.
 * \param[out] dst Конечный вектор с 64 разрядными вещественными числами Y.
 * \param[in] size Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_move(const Ipp64f *src, Ipp64f *dst, Ipp32u size)
{
    IppStatus status = ippsMove_64f(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет перемещать данные из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 16 разрядными комплексными целыми числами X.
 * \param[out] dst Конечный вектор с 16 разрядными комплексными целыми числами Y.
 * \param[in] size Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_move(const Ipp16sc *src, Ipp16sc *dst, Ipp32u size)
{
    IppStatus status = ippsMove_16sc(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет перемещать данные из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными комплексными целыми числами X.
 * \param[out] dst Конечный вектор с 32 разрядными комплексными целыми числами Y.
 * \param[in] size Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_move(const Ipp32sc *src, Ipp32sc *dst, Ipp32u size)
{
    IppStatus status = ippsMove_32sc(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет перемещать данные из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 32 разрядными комплексными вещественными числами X.
 * \param[out] dst Конечный вектор с 32 разрядными комплексными вещественными числами Y.
 * \param[in] size Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_move(const Ipp32fc *src, Ipp32fc *dst, Ipp32u size)
{
    IppStatus status = ippsMove_32fc(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет перемещать данные из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 64 разрядными комплексными целыми числами X.
 * \param[out] dst Конечный вектор с 64 разрядными комплексными целыми числами Y.
 * \param[in] size Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_move(const Ipp64sc *src, Ipp64sc *dst, Ipp32u size)
{
    IppStatus status = ippsMove_64sc(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет перемещать данные из вектора X в вектор Y.
 * \param[in] src Исходный вектор с 64 разрядными комплексными вещественными числами X.
 * \param[out] dst Конечный вектор с 64 разрядными комплексными вещественными числами Y.
 * \param[in] size Размер вектора src и dst.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_move(const Ipp64fc *src, Ipp64fc *dst, Ipp32u size)
{
    IppStatus status = ippsMove_64fc(src, dst, size);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif  // IPP_MOVE_H
