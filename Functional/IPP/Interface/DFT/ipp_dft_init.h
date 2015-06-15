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

#ifndef IPP_DFT_INIT_H
#define IPP_DFT_INIT_H

#include "../ipp_ptr.h"

/*!
 * \brief ipp_dft_init      Функция выполняет инициализацию специальной структуры для
 *                          ДПФ функции и выделяет внешний буфер.
 * \param spec              Специальная структура ДПФ для 64 разрядных вещественных чисел.
 * \param buff              Внешний буфер для ДПФ.
 * \param length            Длина входных данных.
 */
void ipp_dft_init(ipp_ptr<IppsDFTSpec_R_64f> &spec, ipp_ptr<Ipp8u> &buff, const Ipp32s length);

/*!
 * \brief ipp_dft_init      Функция выполняет инициализацию специальной структуры для
 *                          ДПФ функции и выделяет внешний буфер.
 * \param spec              Специальная структура ДПФ для 32 разрядных вещественных чисел.
 * \param buff              Внешний буфер для ДПФ.
 * \param length            Длина входных данных.
 */
void ipp_dft_init(ipp_ptr<IppsDFTSpec_R_32f> &spec, ipp_ptr<Ipp8u> &buff, const Ipp32s length);

#endif // IPP_DFT_INIT_H
