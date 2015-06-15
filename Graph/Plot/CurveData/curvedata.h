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

#ifndef CURVEDATA_H
#define CURVEDATA_H

// ------------------------------------- Private data --------------------------------- //

#include "curveprivatedata.h"

class MathModule;

/*!
 * \brief       Класс CurveData является производным
 *              от класса QwtSeriesData<QPointF>.
 * \detailed    Данный класс выполняет функцию хранения,
 *              графических данных и позволяет манипулировать ими.
 *              По сути облегчает работу. Класс является потокобезопасным
 *              так как использует блокировки на чтение и запись.
 */
class CurveData : public QwtSeriesData<QPointF>
{
    /*!
     * \brief   Позволяет обновить коэффициенты интервала
     *          оси абсцисс, ограничивающего прямоугольника
     *          при изменении ширины окна и других факторов.
     */
    void updateCoefficients();

public:
    /*!
     * \brief   Конструктор по умолчанию класса CurveData.
     */
    CurveData() { }

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
    const QString& titleX() const;

    /*!
     * \brief   Позволяет получить надпись для
     *          оси ординат (уровень вольт).
     * \return  Константная ссылка на надпись оси ординат.
     */
    const QString titleY(double) const;

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
     * \brief   Фабричный метод для сборки мат.
     *          модулей в зависимости от текущего
     *          состояния данной структуры данных.
     * \return  Указатель на мат. модуль класса MathModule.
     */
    MathModule* requestMathModule() const;

    /*!
     * \brief   После изменения ширины окна
     *          необходимо изменить интервал оси
     *          абсцисс.
     * \param[in] width Новая ширина окна.
     */
    void updateWidth(int width);

    /*!
     * \brief   Позволяет обновить перевод надписей
     *          для осей графика и их префиксов.
     */
    void updateTranslates();

    /*!
     * \brief   Функция обновляет данные в векторе
     *          учитывая смещение графика по фазе.
     */
    void updateValues();

    /*!
     * \brief   Позволяет добавить новые отсчеты к
     *          уже имеющимся.
     * \param[in] data Ссылка на вектор с данными.
     */
    void pushData(const ipp_vector<Ipp32f> &data);

    /*!
     * \brief   Функция позволяет очистить внутренний вектор
     *          от данных.
     */
    void clearData();

    /*!
     * \brief   Функция позволяет установить текущий
     *          делитель частоты.
     * \param value Значение делителя частоты.
     */
    void setDivider(int value);

    /*!
     * \brief   Функция позволяет установить текущую
     *          частоту сканирования.
     * \param value Значение частоты сканирования.
     */
    void setScanFrequency(int value);

    /*!
     * \brief   Функция позволяет установить смещения
     *          для фазы графика.
     * \param value Значение смещения.
     */
    void setPhaseOffset(int value);

    /*!
     * \brief   Функция позволяет установить текущую
     *          частоту дискретизации сигнала.
     * \param value Значение частоты дискретизации.
     */
    void setSamplFrequency(ulong value);

    /*!
     * \brief   Функция позволяет установить текущий
     *          размер буфера данных входного потока.
     * \param value Значение размера буфера данных.
     */
    void setBufferSize(quint32 value);

    /*!
     * \brief   Функция управляет включение/отключением
     *          функции автоматической подстройки фазы.
     * \param[in] flag Значение флага вкл./откл.
     */
    void setPhaseDetect(bool flag);

    /*!
     * \brief   Функция управляет включением/отключением
     *          функции трансформации сигнала.
     * \param[in] flag Значение флага вкл./откл.
     */
    void setTransformSignal(bool flag);

    /*!
     * \brief   Функция управляет включением/отключением
     *          функции прореживания сигнала.
     * \param[in] flag Значение флага вкл./откл.
     */
    void setDecimateSignal(bool flag);

    /*!
     * \brief   Функция позволяет установить фильтр определенного
     *          типа для очистки входного сигнала от шумов.
     * \param[in] type Тип фильтра.
     */
    void setFilterType(DenoisedGroupBox::filterType type);

    /*!
     * \brief   Функция позволяет получить флаг
     *          состояния данных. Можно ли обновить
     *          данные на графике или нет.
     * \return  Состояние данных (есть данные или нет).
     */
    bool isReadyToUpdate() const;

    /*!
     * \brief   Функция взятия блокировки для
     *          данной структуры данных.
     */
    void lock();

    /*!
     * \brief   Функция снятия блокировки с
     *          данной структуры данных.
     */
    void unlock();

protected:
    /*!
     * \brief Копирующий конструктор класса PlaybackCurveData.
     * \param[in] b Ссылка на копируемый объект.
     */
    CurveData(const CurveData &b);

    /*!
     * \brief Оператор копирующего присваивания.
     * \param[in] b Ссылка на копируемый объект.
     * \return Ссылка на новый объект.
     */
    CurveData& operator=(const CurveData &);

    /*!
     * \brief Структура данных, которая содержит
     *        текущую частоту дискретизаци, флаги
     *        и т.д. и. т.п.
     */
    CurvePrivateData data;
    
};

#endif // CURVEDATA_H
