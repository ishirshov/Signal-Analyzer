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

#ifndef PEAK_DETECT_H
#define PEAK_DETECT_H

#include "Functional/IPP/additional.h"

/*!
 * \brief Возможные методы поиска
 *        пиков в АЧХ диаграмме.
 */
enum peakFunctionType
{
    S1,     /*!< Функция fS1. */
    S2,     /*!< Функция fS2. */
    S3,     /*!< Функция fS3. */
    S3_mod  /*!< Функция fS3_mod. */
};

/*!
 * \brief Функция осуществляет поиск пиков в АЧХ диаграмме.
 * \param[in] pSrc  Указатель на массив с АЧХ диаграммой.
 * \param[in] n     Размера массива pSrc.
 * \param[in] k     Размер окна вокруг пиков (обычно 3 <= k <= 5, если пик тонкий).
 * \param[in] h     Константа для функции пика (обычно 1 <= h <= 3).
 * \param[in] type  Тип метода для поиска пика.
 * \return          Указатель на массив найденных пиков (размер равен n).
 */
Ipp32f *get_peaks(const Ipp32f* pSrc, int n, int k, Ipp32f h, peakFunctionType type);

/*!
 * \brief   Функция fS1 для данного X в массиве pSrc, рассчитывает
 *          среднее максимальное расстояние до X от его k-ой соседней
 *          точки слева и справа.
 * \param pSrc  Указатель на массив с АЧХ диаграммой.
 * \param n     Размера массива pSrc.
 * \param k     Размер окна вокруг пиков (рекомендуемое = 5).
 * \return      Указатель на массив с усредненными значениями длины между точками.
 */
Ipp32f *fS1(const Ipp32f* pSrc, int n, int k);

/*!
 * \brief   Функция fS2 рассчитывает среднее расстояние X
 *          для i-ого значения от его правой и левой
 *          k-ой соседней точки.
 * \param pSrc  Указатель на массив с АЧХ диаграммой.
 * \param n     Размера массива pSrc.
 * \param k     Размер окна вокруг пиков (рекомендуемое = 5).
 * \return      Указатель на массив с усредненными значениями длины между точками.
 */
Ipp32f* fS2(const Ipp32f* pSrc, int n, int k);

/*!
 * \brief   Функция fS3 рассчитывает среднее расстояние
 *          i-ого значения X в pSrc до среднего значения
 *          его k соседних точек.
 * \param pSrc  Указатель на массив с АЧХ диаграммой.
 * \param n     Размера массива pSrc.
 * \param k     Размер окна вокруг пиков (рекомендуемое = 5).
 * \return      Указатель на массив с усредненными значениями длины между точками.
 */
Ipp32f *fS3(const Ipp32f* pSrc, int n, int k);

/*!
 * \brief Та же функция fS3, но с использованием
 *        IPP функций.
 * \param pSrc  Указатель на массив с АЧХ диаграммой.
 * \param n     Размера массива pSrc.
 * \param k     Размер окна вокруг пиков (рекомендуемое = 5).
 * \return      Указатель на массив с усредненными значениями длины между точками.
 */
Ipp32f* fS3_mod(const Ipp32f* pSrc, int n, int k);

#endif // PEAK_DETECT_H
