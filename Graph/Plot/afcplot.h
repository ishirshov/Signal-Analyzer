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

#ifndef AFCPLOT_H
#define AFCPLOT_H

#include "AFCCurveData/afccurvedata.h"

#include <qwt_plot.h>
#include <qwt_interval.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_directpainter.h>

/*!
 * \brief       Класс AFCPlot является производным от класс QwtPlot.
 * \detailed    Специально-реализованный 2-D виджет для отображения
 *              графиков АЧХ с расширенными возможностями.
 */
class AFCPlot : public QwtPlot
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса AFCPlot.
     * \param[in] parent Владелец объектом
     *                   (см. http://qt-project.org/doc/qt-4.8/objecttrees.html).
     */
    explicit AFCPlot(QWidget *parent = 0);

    /*!
     * \brief Дестркутор класса AFCPlot.
     */
    ~AFCPlot();

public slots:
    /*!
     * \brief   Слот позволяет установить частоту
     *          обновления графика в миллисекундах.
     * \param[in] value Значение частоты обновления.
     */
    void setUpdateTime(short ms);

    /*!
     * \brief   Слот позволяет установить текущую
     *          частоту дискретизации.
     * \param[in] value Значение частоты дискретизации.
     */
    void setSamplingFrequency(ulong freq);

    /*!
     * \brief   Слот позволяет установить кол-во
     *          отображаемых пиков на АЧХ графике.
     * \param[in] num Значение кол-ва отображаемых пиков.
     */
    void setNumberPeaks(int num);

    /*!
     * \brief   Слот позволяет "выслать" начальные
     *          настройки графика АЧХ.
     */
    void sendInitialSettings();

    /*!
     * \brief   Слот позволяет принять новую порцию
     *          АЧХ данных после преобразования Фурье
     *          в виде вектора IPP.
     * \param[in] data Вектор данных.
     */
    void addNewData(const ipp_vector<Ipp32f>& data);

    /*!
     * \brief   Слот позволяет очистить график от
     *          данных.
     */
    void clearData();

signals:
    /*!
     * \brief   После вызова функции sendInitialSettings
     *          данный сигнала отправляет необходимые
     *          данные третьему объекту.
     * \param size Ширина окна АЧХ.
     */
    void settingsChanged(quint32 size);

    /*!
     * \brief   Сигнал инициируется, если график
     *          доступен для отображения новой порции
     *          данных. В ином случае, график будет
     *          игнорировать новые данные.
     * \param[in] flag Флаг состояния графика.
     */
    void storeFlagChanged(bool flag);

protected:
    /*!
     * \brief Фильтр событий (см. описание QObject::eventFilter).
     * \param[in] object Указатель на объект для фильтрации.
     * \param[in] event Указатель на событие.
     * \return  см. описание QObject::eventFilter
     */
    virtual bool eventFilter(QObject *object, QEvent *event);

    /*!
     * \brief Переопределенный метод родительского класса
     *        для обработки событий типа "Изменение".
     * \param[in] event Указатель на структуру QEvent.
     */
    virtual void changeEvent(QEvent *event);

    /*!
     * \brief Метод позволяет изменить размер и обновить внутренние
     *        графические слои (см. описание QWidget::resizeEvent).
     * \param[in] event Указатель на структуру QResizeEvent.
     */
    virtual void resizeEvent(QResizeEvent *event);

    /*!
     * \brief Метод позволяет обрабатывать события, которые
     *        приходят от таймера для текущего объекта (см.
     *        описание QObject::timerEvent).
     * \param[in] event Указатель на структуру события таймера.
     */
    virtual void timerEvent(QTimerEvent *event);

    /*!
     * \brief Метод позволяет обрабатывать события о
     *        видимости графика.
     * \detailed В данном случае обрабатываются события
     *           о видимости (см. описание QWidget::showEvent).
     * \param[in] event Указатель на структуру QShowEvent.
     */
    virtual void showEvent(QShowEvent *event);

    /*!
     * \brief Метод позволяет обрабатывать события о
     *        видимости графика.
     * \detailed В данном случае обрабатываются события
     *           о невидимости (см. описание QWidget::hideEvent).
     * \param[in] event Указатель на структуру QHideEvent.
     */
    virtual void hideEvent(QHideEvent *event);

private:
    /*!
     * \brief Копирующий конструктор класса AFCPlot.
     * \param[in] b Ссылка на копируемый объект.
     */
    AFCPlot(const AFCPlot &b);

    /*!
     * \brief Оператор копирующего присваивания.
     * \param[in] b Ссылка на копируемый объект.
     * \return Ссылка на новый объект.
     */
    AFCPlot& operator=(const AFCPlot &b);

    /*!
     * \brief Функция позволяет отобразить найденные
     *        пики на графике АЧХ в виде маркеров.
     */
    void showPeaks();

    /*!
     * \brief Функция позволяет очистить график АЧХ
     *        от маркеров найденных пиков.
     */
    void deleteMarkers();

    /*!
     * \brief Функция позволяет произвести обновление
     *        кривой графика.
     * \detailed Под обновлением подразумевается: изменение
     *           размера, ширины линии, цвета и т.д. и т.п.
     *           После изменения размера окна графика, следует
     *           изменение размера кривой и её свойств.
     */
    void updateCurve();

    /*!
     * \brief Функция позволяет обновить значения
     *        оси абсцисс.
     */
    void updateAxisX();

    /*!
     * \brief Функция позволяет обновить значения
     *        оси ординат.
     */
    void updateAxisY();

    QwtPlotCurve *d_curve;                  //!< Виджет кривой графика (см. описание QwtPlotCurve).
    QwtPlotDirectPainter *d_directPainter;  //!< Объект отрисовщика (см. описание QwtPlotDirectPainter).
    QwtPlotGrid *d_grid;                    //!< Виджет сетки графика (см. описание QwtPlotGrid).
    QList<QwtPlotMarker*> d_markers;        //!< Список маркеров для отображения пиков на графике (см. описание QwtPlotMarker).

    QwtInterval dx_interval;                //!< Интервал оси абсцисс (см. описание QwtInterval).
    QwtInterval dy_interval;                //!< Интервал оси ординат.
    qint32 d_paintedPoints;                 //!< Кол-во точек на графике.
    qint32 d_timer_hz;                      //!< ИД таймера.
    qint16 d_refreshRate;                   //!< Частота обновления графика.
    qint16 d_cnvsFlag;                      //!< Флаг канвы.

};

#endif // AFCPLOT_H
