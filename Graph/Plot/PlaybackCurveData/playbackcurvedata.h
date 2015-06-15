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

#ifndef PLAYBACKCURVEDATA_H
#define PLAYBACKCURVEDATA_H

#include <qwt_series_data.h>
#include "Functional/IPP/additional.h"

/*!
 * \brief       Класс PlaybackCurveData является производным
 *              от класса QwtSeriesData<QPointF>.
 * \detailed    Данный класс выполняет функцию хранения,
 *              графических данных и позволяет манипулировать ими.
 *              По сути облегчает работу.
 */
class PlaybackCurveData : public QwtSeriesData<QPointF>
{
    /*!
     * \brief Копирующий конструктор класса PlaybackCurveData.
     * \param[in] b Ссылка на копируемый объект.
     */
    PlaybackCurveData(const PlaybackCurveData &b);

    /*!
     * \brief Оператор копирующего присваивания.
     * \param[in] b Ссылка на копируемый объект.
     * \return Ссылка на новый объект.
     */
    PlaybackCurveData& operator=(const PlaybackCurveData &b);

public:
    /*!
     * \brief Конструктор по умолчанию для класса PlaybackCurveData.
     */
    PlaybackCurveData();

    /*!
     * \brief   Переопределенный метод для возможности
     *          доступа к отсчетам, которые находятся
     *          внутри вектора values.
     * \param[in] i Индекс элемента вектора.
     * \return  Значение отсчета.
     */
    virtual QPointF sample(size_t i) const { return values->at(i); }

    /*!
     * \brief   Позволяет получить размер одномерного
     *          вектора.
     * \return  Кол-во элементов в векторе.
     */
    virtual size_t size() const { return values->size(); }

    /*!
     * \brief   Позволяет получить информацию по
     *          ограничению отображения в графическом
     *          окне.
     * \return  Ограничивающий прямоугольник.
     */
    virtual QRectF boundingRect() const { return bndngRct; }

    /*!
     * \brief   Позволяет добавить новые отсчеты к
     *          уже имеющимся.
     * \param[in] samples Указатель на вектор с новыми отсчетами.
     */
    void appendData(QVector<QPointF> *samples);

    /*!
     * \brief   Функция позволяет очистить внутренний вектор
     *          от данных.
     */
    void clearData();

    /*!
     * \brief   Функция позволяет получить интервал оси
     *          абсцисс из вектора values.
     * \return  Интервал значений оси абсцисс.
     */
    QwtInterval min_maxX() const;

    /*!
     * \brief   Функция позволяет получить интервал оси
     *          ординат из вектора values.
     * \return  Интервал значений оси ординат.
     */
    QwtInterval min_maxY() const;

    /*!
     * \brief   Функция позволяет получить флаг
     *          состояния данных. Можно ли обновить
     *          данные на графике или нет.
     * \return  Состояние данных (есть данные или нет).
     */
    bool readyToUpdate() const;

private:    
    QRectF bndngRct;                            //!< Ограничивающий прямоугольник.
    QScopedPointer<QVector<QPointF> > values;   //!< Вектор с данными.

};

#endif // PLAYBACKCURVEDATA_H
