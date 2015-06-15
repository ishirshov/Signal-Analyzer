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

#ifndef AFCCURVEDATA_H
#define AFCCURVEDATA_H

#include <qwt_series_data.h>

#include "afcprivatedata.h"

/*!
 * \brief       Класс AFCCurveData является производным
 *              от класса QwtSeriesData<QPointF>.
 * \detailed    Данный класс выполняет функцию хранения,
 *              графических АЧХ данных и позволяет манипулировать
 *              ими. По сути облегчает работу.
 */
class AFCCurveData : public QwtSeriesData<QPointF>
{
public:
    typedef AFCPrivateData::peaksSet peaksSet;

    /*!
     * \brief   Типы данных для удаления.
     */
    enum Type
    {
        Flags,  /*!< Сброс флагов. */
        Data    /*!< Очистка векторов от данных. */
    };

    /*!
     * \brief   Конструктор по умолчанию класса AFCCurveData.
     */
    AFCCurveData() { }

    /*!
     * \brief   Переопределенный метод для возможности
     *          доступа к отсчетам, которые находятся
     *          внутри вектора values.
     * \param[in] i Индекс элемента вектора.
     * \return  Значение отсчета.
     */
    virtual QPointF sample(size_t i) const;

    /*!
     * \brief   Позволяет получить размер одномерного
     *          вектора.
     * \return  Кол-во элементов в векторе.
     */
    virtual size_t size() const;

    /*!
     * \brief   Позволяет получить информацию по
     *          ограничению отображения в графическом
     *          окне.
     * \return  Ограничивающий прямоугольник.
     */
    virtual QRectF boundingRect() const;

    /*!
     * \brief   Позволяет получить надпись для
     *          оси абсцисс (время).
     * \return  Константная ссылка на надпись оси абсцисс.
     */
    const QString& titleAxisX() const;

    /*!
     * \brief   Позволяет получить надпись для
     *          оси ординат (уровень вольт).
     * \return  Константная ссылка на надпись оси ординат.
     */
    const QString& titleAxisY() const;

    /*!
     * \brief   Функция позволяет получить интервал оси
     *          абсцисс из вектора values.
     * \return  Интервал значений оси абсцисс.
     */
    QwtInterval minMaxAxisX() const;

    /*!
     * \brief   Функция позволяет получить интервал оси
     *          ординат из вектора values.
     * \return  Интервал значений оси ординат.
     */
    QwtInterval minMaxAxisY() const;

    /*!
     * \brief   Позволяет получить максимальное значение
     *          на интервале оси ординат.
     * \return  Максимальное значение оси ординат.
     */
    qreal maxAxisY() const;

    /*!
     * \brief   Позволяет получить минимальное значение
     *          на интервале оси ординат.
     * \return  Минимальное значение оси ординат.
     */
    qreal minAxisY() const;

    /*!
     * \brief   Позволяет получить максимальное значение
     *          на интервале оси абсцисс.
     * \return  Максимальное значение оси абсцисс.
     */
    qreal maxAxisX() const;

    /*!
     * \brief   Позволяет получить минимальное значение
     *          на интервале оси абсцисс.
     * \return  Минимальное значение оси абсцисс.
     */
    qreal minAxisX() const;

    /*!
     * \brief   Позволяет получить текущее значение
     *          частоты дискретизации сигнала.
     * \return  Текущее значение частоты дискретизации.
     */
    ulong signalFrequency() const;

    /*!
     * \brief   Функция позволяет получить флаг
     *          состояния данных. Можно ли обновить
     *          данные на графике или нет.
     * \return  Состояние данных (есть данные или нет).
     */
    bool readyToUpdate() const;

    /*!
     * \brief   Функция позволяет получить найденные
     *          пики в АЧХ данных
     * \return  Множество значений пиков.
     */
    const peaksSet& peaks() const;

    /*!
     * \brief   Позволяет добавить новые отсчеты к
     *          уже имеющимся.
     * \param[in] data Ссылка на ipp вектор с АЧХ данными.
     */
    void addData(const ipp_vector<Ipp32f> &data);

    /*!
     * \brief   Функция позволяет очистить внутренний вектор
     *          от данных.
     * \param[in] type Тип данных для удаления.
     */
    void clearData(Type type);

    /*!
     * \brief   Позволяет обновить перевод надписей
     *          для осей графика и их префиксов.
     */
    void updateTranslate();

    /*!
     * \brief   После изменения ширины окна
     *          необходимо изменить интервал оси
     *          абсцисс, подпись и размер вектора данных.
     * \param[in] width Новая ширина окна.
     */
    void setWidth(int width);

    /*!
     * \brief   Функция позволяет установить
     *          искомое количество пиков на графике АЧХ.
     * \param[in] num Кол-во пиков на графике АЧХ.
     */
    void setUserPeaksNum(int num);

    /*!
     * \brief   Функция позволяет установить текущую
     *          частоту дискретизации сигнала.
     * \param value Значение частоты дискретизации.
     */
    void setSamplingFrequency(long value);

private:
    /*!
     * \brief Структура данных, которая содержит
     *        текущую частоту дискретизаци, флаги
     *        и т.д. и. т.п.
     */
    AFCPrivateData data;

};

#endif // AFCCURVEDATA_H
