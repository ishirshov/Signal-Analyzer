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

#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H

#include "additional.h"

/*!
 * \brief Функция позволяет выполнить функцию интерполяции
 *        двумерного изображения.
 * \param[in] pSrc Исходное изображение.
 * \param[in] srcLen Длина вектора исходного изображения.
 * \param[out] pDst Конечный вектор с интерполированным изображением.
 * \param[in] dstLen Длина вектора интерполированного изображения.
 */
void interpolate_64f(const Ipp64f *pSrc, Ipp32s srcLen, Ipp64f *pDst, Ipp32s dstLen);

#endif // GENERAL_FUNCTIONS_H
