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

﻿#ifndef IPP_ALLOCATOR_H
#define IPP_ALLOCATOR_H

#include <ipps.h>
#include <ippdefs.h>
#include <stdexcept>

/*!
 * \brief Функция выполняет освобождение занятых
 *        IPP ресурсов.
 * \param[in] Указатель на ресурс.
 */
template<class T>
inline void ipp_free(T *&_memory)
{
    if(_memory)
        ippsFree((void*)_memory);
    _memory = 0;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для типа T данных.
 * \param[in] size Размер вектора данных.
 * \exception std::runtime_error Ошибка в хое выполнения функции.
 * \return Указатель на новый ресурс.
 */
template<class T>
T* ipp_malloc(Ipp32u size)
{
    throw std::runtime_error("Use ipp_malloc only for Intel PP types.");
    return 0;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 8 разрядных положительных целых чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp8u* ipp_malloc<Ipp8u>(Ipp32u size)
{
    Ipp8u *p = ippsMalloc_8u(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 16 разрядных положительных целых чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp16u* ipp_malloc<Ipp16u>(Ipp32u size)
{
    Ipp16u *p = ippsMalloc_16u(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 32 разрядных положительных целых чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp32u* ipp_malloc<Ipp32u>(Ipp32u size)
{
    Ipp32u *p = ippsMalloc_32u(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 8 разрядных целых чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp8s* ipp_malloc<Ipp8s>(Ipp32u size)
{
    Ipp8s *p = ippsMalloc_8s(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 16 разрядных целых чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp16s* ipp_malloc<Ipp16s>(Ipp32u size)
{
    Ipp16s *p = ippsMalloc_16s(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 32 разрядных целых чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp32s* ipp_malloc<Ipp32s>(Ipp32u size)
{
    Ipp32s *p = ippsMalloc_32s(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 64 разрядных целых чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp64s* ipp_malloc<Ipp64s>(Ipp32u size)
{
    Ipp64s *p = ippsMalloc_64s(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 32 разрядных вещественных чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp32f* ipp_malloc<Ipp32f>(Ipp32u size)
{
    Ipp32f *p = ippsMalloc_32f(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 64 разрядных вещественных чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp64f* ipp_malloc<Ipp64f>(Ipp32u size)
{
    Ipp64f *p = ippsMalloc_64f(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 8 разрядных целых коплексных чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp8sc* ipp_malloc<Ipp8sc>(Ipp32u size)
{
    Ipp8sc *p = ippsMalloc_8sc(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 16 разрядных целых коплексных чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp16sc* ipp_malloc<Ipp16sc>(Ipp32u size)
{
    Ipp16sc *p = ippsMalloc_16sc(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 32 разрядных целых коплексных чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp32sc* ipp_malloc<Ipp32sc>(Ipp32u size)
{
    Ipp32sc *p = ippsMalloc_32sc(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 64 разрядных целых коплексных чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp64sc* ipp_malloc<Ipp64sc>(Ipp32u size)
{
    Ipp64sc *p = ippsMalloc_64sc(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 32 разрядных вещественных коплексных чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp32fc* ipp_malloc<Ipp32fc>(Ipp32u size)
{
    Ipp32fc *p = ippsMalloc_32fc(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

/*!
 * \brief Функция выполняет выделение IPP ресурсов
 *        для 64 разрядных вещественных коплексных чисел.
 * \param[in] size Размер вектора данных.
 * \exception std::bad_alloc Ошибка выделения ресурсов.
 * \return Указатель на новый ресурс.
 */
template<>
inline Ipp64fc* ipp_malloc<Ipp64fc>(Ipp32u size)
{
    Ipp64fc *p = ippsMalloc_64fc(size);

    if(p == 0) throw std::bad_alloc();

    return p;
}

#endif  // IPP_ALLOCATOR_H
