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

#ifndef IPP_PHASE_ANGLE_H
#define IPP_PHASE_ANGLE_H

#include "ipp_ptr.h"
#include <cmath>

/*!
 * \brief Функция позволяет определить лаг угла фазы.
 * \param[in] t_estimate1 Тетта оценка первого сигнала.
 * \param[in] t_estimate2 Тетта оценка второго сигнала.
 * return Лаг фазы.
 */
template<class T>
T lag_detect(T t_estimate1, T t_estimate2)
{
    T lag = t_estimate2 - t_estimate1;
    lag = (lag < 0)?(-lag):(lag);

    T phase = t_estimate1 / lag;
    lag = IPP_2PI / lag;

    if(phase > 0)
        phase = phase - lag;

    return (-phase);
}

/*!
 * \brief Функция позволяет определить угл фазы сигнала в векторе X.
 * \param[in] pSrc Исходный вектор с 64 разрядными вещественными комплексными числами X.
 * \param[in] length Размер вектора pSrc.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 * \return Угл фазы сигнала.
 */
inline Ipp64f ipp_phase_angle(const Ipp64fc *pSrc, const Ipp32s length)
{
    ipp_ptr<Ipp64f> mag(ippsMalloc_64f(length));

    IppStatus message = ippsMagnitude_64fc(pSrc, mag.get(), length);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    Ipp64f max = 0.0;
    Ipp32s indx = 0;

    // Determine the max value and max point.
    // This is where the sinusoidal is located.
    message = ippsMaxIndx_64f(mag.get(), length, &max, &indx);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    // Determine phase angle.
    return atan2(pSrc[indx].im, pSrc[indx].re);
}


/*!
 * \brief Функция позволяет определить угл фазы сигнала в векторе X.
 * \param[in] pSrc Исходный вектор с 32 разрядными вещественными комплексными числами X.
 * \param[in] length Размер вектора pSrc.
 * \exception std::runtime_error Ошибка в ходе выполнения функции.
 * \return Угл фазы сигнала.
 */
inline Ipp64f ipp_phase_angle(const Ipp32fc *pSrc, const Ipp32s length)
{
    ipp_ptr<Ipp32f> mag(ippsMalloc_32f(length));

    IppStatus message = ippsMagnitude_32fc(pSrc, mag.get(), length);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    Ipp32f max = 0.0;
    Ipp32s indx = 0;

    // Determine the max value and max point.
    // This is where the sinusoidal is located.
    message = ippsMaxIndx_32f(mag.get(), length, &max, &indx);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));

    // Determine phase angle.
    return atan2(pSrc[indx].im, pSrc[indx].re);
}

#endif // IPP_PHASE_ANGLE_H
