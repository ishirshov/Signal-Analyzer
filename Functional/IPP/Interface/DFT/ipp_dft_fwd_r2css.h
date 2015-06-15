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

#ifndef IPP_DFT_FWD_R2CSS_H
#define IPP_DFT_FWD_R2CSS_H

#include <ipps.h>
#include <ippcore.h>
#include <ippdefs.h>
#include <stdexcept>

/*!
 * \brief Функция дискретного преобразования Фурье.
 * \param[in] pSrc      Исходный вектор с 64 разрядным вещественным сигналом.
 * \param[out] pDst     Конечный вектор с данными спектра в формате CCS.
 * \param[in] pSpec     Структура с параметрами функции ДПФ.
 * \param[in] pBuffer   Внешний буфер для работы ДПФ.
 */
inline void ipp_dft_fwd_r2ccs(const Ipp64f *pSrc, Ipp64f *pDst,
                              const IppsDFTSpec_R_64f *pSpec, Ipp8u *pBuffer)
{
    IppStatus message = ippsDFTFwd_RToCCS_64f(pSrc, pDst, pSpec, pBuffer);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));
}

/*!
 * \brief Функция дискретного преобразования Фурье.
 * \param[in] pSrc      Исходный вектор с 32 разрядным вещественным сигналом.
 * \param[out] pDst     Конечный вектор с данными спектра в формате CCS.
 * \param[in] pSpec     Структура с параметрами функции ДПФ.
 * \param[in] pBuffer   Внешний буфер для работы ДПФ.
 */
inline void ipp_dft_fwd_r2ccs(const Ipp32f *pSrc, Ipp32f *pDst,
                              const IppsDFTSpec_R_32f *pSpec, Ipp8u *pBuffer)
{
    IppStatus message = ippsDFTFwd_RToCCS_32f(pSrc, pDst, pSpec, pBuffer);
    if(message != ippStsNoErr) throw std::runtime_error(ippGetStatusString(message));
}

#endif // IPP_DFT_FWD_R2CSS_H
