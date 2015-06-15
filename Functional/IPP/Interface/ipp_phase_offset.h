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

#ifndef IPP_PHASE_OFFSET_H
#define IPP_PHASE_OFFSET_H

#include "ipp_ptr.h"
#include "ipp_convert.h"

/*!
 * \brief Ссылка на прототип функции вычисления фазы сигналов.
 */
typedef Ipp64f (ipp_phase_offset_t) (const Ipp64f*, Ipp32s, const Ipp64f*, Ipp32s);

/*!
 * \brief Функция позволяет вычислить разницу в фазах между двумя сигналами.
 *        Ресурсы функции постоянно освобождаются и выделяются.
 * \param[in] pOrig Исходный вектор с 32 разрядными вещественными числами X.
 * \param[in] origLen Размер вектора pOrig.
 * \param[in] pSrc Исходный вектор с 32 разрядными вещественными числами Y.
 * \param[in] srcLen Размер вектора pSrc (= origLen x 2).
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 * \return Значение смещения фазы.
 */
Ipp64f ipp_phase_offset_rellc(const Ipp64f *pOrig, Ipp32s origLen,
                              const Ipp64f *pSrc, Ipp32s srcLen);

/*!
 * \brief Функция позволяет вычислить разницу в фазах между двумя сигналами.
 *        Ресурсы функции постоянно статичны.
 * \param[in] pOrig Исходный вектор с 32 разрядными вещественными числами X.
 * \param[in] origLen Размер вектора pOrig.
 * \param[in] pSrc Исходный вектор с 32 разрядными вещественными числами Y.
 * \param[in] srcLen Размер вектора pSrc (= origLen x 2).
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 * \return Значение смещения фазы.
 */
Ipp64f ipp_phase_offset_stat(const Ipp64f *pOrig, Ipp32s origLen,
                             const Ipp64f *pSrc, Ipp32s srcLen);

/*!
 * \brief Функция вычисления фазы сигнала Y на основе сигнала X.
 * \param[in] pOrig Исходный вектор с 32 разрядными вещественными числами X.
 * \param[in] origLen Размер вектора pOrig.
 * \param[in] pSrc Исходный вектор с 32 разрядными вещественными числами Y.
 * \param[in] srcLen Размер вектора pSrc (= origLen x 2).
 * \param[in] phaseFunc Функция вычисления фазы угла между двумя сигналами.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 * \return Разница в фазах двух сигналов X и Y.
 */
inline Ipp64f ipp_phase_offset(const Ipp32f *pOrig, Ipp32s origLen,
                               const Ipp32f *pSrc,  Ipp32s srcLen,
                               ipp_phase_offset_t *phaseFunc)
{
    if(!pOrig || !pSrc) throw std::runtime_error("Pointers cannot be null.");
    if(origLen < 1) throw std::runtime_error("The lengths must be positive.");
    if(origLen > srcLen) throw std::runtime_error("Length of source signal must be greater than original.");
    if(!phaseFunc) throw std::runtime_error("Phase function can\'t be null.");

    ipp_ptr<Ipp64f> tmp_orig(ipp_malloc<Ipp64f>(origLen));
    ipp_ptr<Ipp64f> tmp_src(ipp_malloc<Ipp64f>(srcLen));

    Ipp64f *_orig_64f = tmp_orig.get();
    Ipp64f *_src_64f = tmp_src.get();

    ipp_convert(pOrig, _orig_64f, origLen);
    ipp_convert(pSrc, _src_64f, srcLen);

    return phaseFunc(_orig_64f, origLen, _src_64f, srcLen);
}

#endif // IPP_PHASE_OFFSET_H
