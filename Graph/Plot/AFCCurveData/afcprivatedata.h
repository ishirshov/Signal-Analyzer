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

#ifndef AFCPRIVATEDATA_H
#define AFCPRIVATEDATA_H

#include <QRectF>
#include <QVector>
#include <set>
#include <QPointF>

#include "Functional/IPP/additional.h"

/*!
 * \brief Класс AFCPrivateData является
 *        структурой данных для хранения
 *        текущей частоты дискретизации,
 *        флагов обработки и т.д. и т.п.
 */
class AFCPrivateData
{
public:
    typedef std::set<QPointF, greatherThen> peaksSet; //!< Тип контейнера для хранения пиков АЧХ.

    /*!
     * \brief   Конструктор по умолчанию класса
     *          AFCPrivateData.
     */
    AFCPrivateData();

    /*!
     * \brief   Функция в зависимости от размера
     *          окна изменяет размер вектора данных.
     * \param[in] fact_width    Фактическая ширина окна.
     * \param[in] point         Значение по умолчанию, для новых точек.
     */
    void changeWidth(int fact_width, QPointF point);

    /*!
     * \brief   Функция изменяет значение на интервали
     *          по оси абсцисс.
     */
    void changeAxisX();    

    /*!
     * \brief   Функция изменяет надпись на оси абсцисс.
     */
    void changeTitles();

    peaksSet peaks;             //!< Множество, где хранятся найденные пики.
    QVector<QPointF> values;    //!< Вектор с АЧХ данными.

    ulong signalFreq;           //!< Текущая частота сигнала.
    quint32 userPeaks;          //!< Количество отображаемых пиков.
    QString titleAxisX;         //!< Надпись оси абсцисс.
    QString titleAxisY;         //!< Надпись оси ординат.

    QRectF boundingRect;        //!< Ограничивающий прямоугольник для графика.
    bool isData;                //!< Флаг готовности данных для отображения.

};

#endif // AFCPRIVATEDATA_H
