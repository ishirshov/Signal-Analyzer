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

#ifndef CURVEPRIVATEDATA_H
#define CURVEPRIVATEDATA_H

#include <QMap>
#include <QRectF>
#include <QPointF>
#include <QObject>
#include <QVector>
#include <QReadWriteLock>
#include <QMutex>

#include <qwt_series_data.h>

#include "Functional/IPP/additional.h"
#include "Graph/denoised_group_box.h"

/*!
 * \brief   Класс CurvePrivateData является
 *          структурой данных для хранения
 *          текущей частоты дискретизации,
 *          флагов обработки и т.д. и т.п.
 */
class CurvePrivateData
{
    QVector<Second> time;                               //!< Вектор единиц времени.

    /*!
     * \brief   Функция инициализации вектора
     *          времени (C обозначение ед. времени).
     */
    void initTimeVector();

    /*!
     * \brief   Функция инициализации карты соответствия
     *          значений амлитуды сигнала.
     */
    void initAmplitudeMap();

public:
    /*!
     * \brief   Конструктор по умолчанию класса
     *          CurvePrivateData.
     */
    CurvePrivateData();

    /*!
     * \brief   Функция в зависимости от размера
     *          окна изменяет размер вектора данных.
     * \param[in] fact_width Фактическая ширина окна.
     */
    void changeWidth(int fact_width);

    /*!
     * \brief   Функция изменяет шкалу оси абсцисс
     *          вычесляя шаг шкалы взависимости от
     *          текущей частоты дискретизации и других
     *          параметров.
     */
    void changeTimeAxis();

    /*!
     * \brief   Функция обновляет обозначения C для
     *          единиц времени. Необходимо, если
     *          был изменен язык.
     */
    void updateTimeVector();

    /*!
     * \brief   Функция обновляет обозначения C для
     *          единиц вольт. Необходимо, если
     *          был изменен язык.
     */
    void updateAmplitudeMap();

    /*!
     * \brief   Функция позволяет очистить внутренний вектор
     *          от данных.
     */
    void clearData();

    mutable QMutex pend_guard;                          //!< Мьютекс используется для защиты pending вектора.
    ipp_vector<Ipp32f> pending;                         //!< Вектор содержит данные, которые ожидают обработку.

    mutable QReadWriteLock lock;                        //!< Блокировка используется для защиты остальных данных в текущей структуре.
    QVector<QPointF> values;                            //!< Текущий вектор с отображаемыми данными.

    qreal divider;                                      //!< Делитель частоты.
    qreal frequency;                                    //!< Частота сканирования.
    quint32 array_size;                                 //!< Размер входного буфера.
    quint32 window_with;                                //!< Ширина окна графика.
    qint32 offset;                                      //!< Смещение фазы сигнала.
    quint64 sampling_freq;                              //!< Частота дискретизации.

    QRectF bounding_rect;                               //!< Ограничивающий прямоугольник для графика.
    QString title_time;                                 //!< Текущаяя надпись шкалы времени (ось абсцисс).
    QMap<qreal,QString> amplitude;                      //!< Карта соответствия для шкалы амплитуды.

    bool is_enable_phase_detect;                        //!< Флаг включения/отключения функции подстройки фазы.
    bool is_enable_sig_transform;                       //!< Флаг включения/отключения функции преобразования сигнала.
    bool is_enable_decimate_sig;                        //!< Флаг включения/отключения функции прореживания сигнала.
    DenoisedGroupBox::filterType current_filter_type;   //!< Тип текущего фильтра для очистки сигнала от шума.

};

#endif // CURVEPRIVATEDATA_H
