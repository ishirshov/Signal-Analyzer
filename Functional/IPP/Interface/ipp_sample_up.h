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

#ifndef IPP_SAMPLE_UP_H
#define IPP_SAMPLE_UP_H

#include <ipps.h>
#include <ippdefs.h>
#include <stdexcept>

/*!
 * \brief Функция позволяет повысить частоту дискретизации сигнала X
 *        до частоты дискретизации сигнала Y.
 * \param[in] src       Исходный 16 разрядный целочисленный вектор с сигналом X.
 * \param[in] src_sz    Размер вектора src.
 * \param[out] dst      Конечный 16 разрядный целочисленный вектор с сигналов Y.
 * \param[in] dst_sz    Размер вектора dst.
 * \param[in] factor    Значение фактора повышения частоты дискретизации.
 * \param[out] phase    Указатель на значение фазы сигнала, который в ходе
 *                      выполнения функции будет скопирован в вектор Y.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sample_up(const Ipp16s *src, Ipp32u src_sz,
                          Ipp16s *dst, Ipp32s *dst_sz,
                          Ipp32s factor, Ipp32s *phase)
{
    IppStatus status = ippsSampleUp_16s(src, src_sz, dst, dst_sz, factor, phase);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет повысить частоту дискретизации сигнала X
 *        до частоты дискретизации сигнала Y.
 * \param[in] src       Исходный 32 разрядный вещественный вектор с сигналом X.
 * \param[in] src_sz    Размер вектора src.
 * \param[out] dst      Конечный 32 разрядный вещественный вектор с сигналов Y.
 * \param[in] dst_sz    Размер вектора dst.
 * \param[in] factor    Значение фактора повышения частоты дискретизации.
 * \param[out] phase    Указатель на значение фазы сигнала, который в ходе
 *                      выполнения функции будет скопирован в вектор Y.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sample_up(const Ipp32f *src, Ipp32u src_sz,
                          Ipp32f *dst, Ipp32s *dst_sz,
                          Ipp32s factor, Ipp32s *phase)
{
    IppStatus status = ippsSampleUp_32f(src, src_sz, dst, dst_sz, factor, phase);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет повысить частоту дискретизации сигнала X
 *        до частоты дискретизации сигнала Y.
 * \param[in] src       Исходный 64 разрядный вещественный вектор с сигналом X.
 * \param[in] src_sz    Размер вектора src.
 * \param[out] dst      Конечный 64 разрядный вещественный вектор с сигналов Y.
 * \param[in] dst_sz    Размер вектора dst.
 * \param[in] factor    Значение фактора повышения частоты дискретизации.
 * \param[out] phase    Указатель на значение фазы сигнала, который в ходе
 *                      выполнения функции будет скопирован в вектор Y.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sample_up(const Ipp64f *src, Ipp32u src_sz,
                          Ipp64f *dst, Ipp32s *dst_sz,
                          Ipp32s factor, Ipp32s *phase)
{
    IppStatus status = ippsSampleUp_64f(src, src_sz, dst, dst_sz, factor, phase);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет повысить частоту дискретизации сигнала X
 *        до частоты дискретизации сигнала Y.
 * \param[in] src       Исходный 16 разрядный комплексный целочисленный
 *                      вектор с сигналом X.
 * \param[in] src_sz    Размер вектора src.
 * \param[out] dst      Конечный 16 разрядный комплексный целочисленный
 *                      вектор с сигналов Y.
 * \param[in] dst_sz    Размер вектора dst.
 * \param[in] factor    Значение фактора повышения частоты дискретизации.
 * \param[out] phase    Указатель на значение фазы сигнала, который в ходе
 *                      выполнения функции будет скопирован в вектор Y.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sample_up(const Ipp16sc *src, Ipp32u src_sz,
                          Ipp16sc *dst, Ipp32s *dst_sz,
                          Ipp32s factor, Ipp32s *phase)
{
    IppStatus status = ippsSampleUp_16sc(src, src_sz, dst, dst_sz, factor, phase);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет повысить частоту дискретизации сигнала X
 *        до частоты дискретизации сигнала Y.
 * \param[in] src       Исходный 32 разрядный комплексный вещественный
 *                      вектор с сигналом X.
 * \param[in] src_sz    Размер вектора src.
 * \param[out] dst      Конечный 32 разрядный комплексный вещественный
 *                      вектор с сигналов Y.
 * \param[in] dst_sz    Размер вектора dst.
 * \param[in] factor    Значение фактора повышения частоты дискретизации.
 * \param[out] phase    Указатель на значение фазы сигнала, который в ходе
 *                      выполнения функции будет скопирован в вектор Y.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sample_up(const Ipp32fc *src, Ipp32u src_sz,
                          Ipp32fc *dst, Ipp32s *dst_sz,
                          Ipp32s factor, Ipp32s *phase)
{
    IppStatus status = ippsSampleUp_32fc(src, src_sz, dst, dst_sz, factor, phase);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

/*!
 * \brief Функция позволяет повысить частоту дискретизации сигнала X
 *        до частоты дискретизации сигнала Y.
 * \param[in] src       Исходный 64 разрядный комплексный вещественный
 *                      вектор с сигналом X.
 * \param[in] src_sz    Размер вектора src.
 * \param[out] dst      Конечный 64 разрядный комплексный вещественный
 *                      вектор с сигналов Y.
 * \param[in] dst_sz    Размер вектора dst.
 * \param[in] factor    Значение фактора повышения частоты дискретизации.
 * \param[out] phase    Указатель на значение фазы сигнала, который в ходе
 *                      выполнения функции будет скопирован в вектор Y.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 */
inline void ipp_sample_up(const Ipp64fc *src, Ipp32u src_sz,
                          Ipp64fc *dst, Ipp32s *dst_sz,
                          Ipp32s factor, Ipp32s *phase)
{
    IppStatus status = ippsSampleUp_64fc(src, src_sz, dst, dst_sz, factor, phase);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));
}

#endif // IPP_SAMPLE_UP_H
