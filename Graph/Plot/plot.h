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

#ifndef PLOT_H
#define PLOT_H

#include "CurveData/curvedata.h"

#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_interval.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_directpainter.h>

class MathDecorators;

/*!
 * \brief       Класс Plot является производным от класс QwtPlot.
 * \detailed    Специально-реализованный 2-D виджет для отображения
 *              графиков с расширенными возможностями.
 */
class Plot : public QwtPlot
{
    Q_OBJECT

public:
    /*!
     * \brief   Конструктор класса Plot.
     * \param[in] parent Владелец объектом
     *                   (см. http://qt-project.org/doc/qt-4.8/objecttrees.html).
     */
    explicit Plot(QWidget *parent = 0);

    /*!
     * \brief   Функция обновления данных виджета.
     */
    virtual void replot();

    /*!
     * \brief Деструктор класса Plot.
     */
    ~Plot();

public slots:
    /*!
     * \brief   Слот позволяет установить цвет для
     *          линий графика (не для оси и решетки).
     * \param[in] value Значение цвета.
     */
    void setPen(const QColor &value);

    /*!
     * \brief   Слот позволяет установить частоту
     *          обновления графика в миллисекундах.
     * \param[in] value Значение частоты обновления.
     */
    void setUpdateTime(short value);

    /*!
     * \brief   Слот позволяет установить делитель
     *          текущей частоты.
     * \param[in] value Значение делителя частоты.
     */
    void setTimeDivider(int value);

    /*!
     * \brief   Слот позволяет установить частоту
     *          сканированиях для текущего сигнала.
     * \param[in] value Значение частоты сканирования.
     */
    void setScanDivider(int value);

    /*!
     * \brief   Слот позволяет установить смещение
     *          фазы сигнала на N/-N семплов.
     * \param[in] value Значение смещение фазы.
     */
    void setPhaseOffset(double value);

    /*!
     * \brief   Слот позволяет установить уровень
     *          вольтов по оси Y для графика.
     * \param[in] value Значение уровня вольта.
     */
    void setVoltsLevel(double value);

    /*!
     * \brief   Слот позволяет установить текущую
     *          частоту дискретизации.
     * \param[in] value Значение частоты дискретизации.
     */
    void setSamplingFrequency(ulong value);

    /*!
     * \brief   Слот позволяет установить текущий
     *          размер буфера данных входного потока.
     * \param[in] value Значение размера буфера данных.
     */
    void setBufferSize(Ipp32s value);

    /*!
     * \brief   Слот управляет включение/отключением
     *          функции автоматической подстройки фазы.
     * \param[in] flag Значение флага вкл./откл.
     */
    void setPhaseDetect(bool flag);

    /*!
     * \brief   Слот управляет включением/отключением
     *          функции прореживания сигнала.
     * \param[in] flag Значение флага вкл./откл.
     */
    void setDecimateSignal(bool flag);

    /*!
     * \brief   Слот управляет включением/отключением
     *          функции трансформации сигнала.
     * \param[in] flag Значение флага вкл./откл.
     */
    void setSignalTransform(bool flag);

    /*!
     * \brief   Слот позволяет установить фильтр определенного
     *          типа для очистки входного сигнала от шумов.
     * \param[in] value Тип фильтра.
     */
    void setFilterType(DenoisedGroupBox::filterType value);

    /*!
     * \brief   Слот позволяет принять новую порцию данных
     *          дискретного сигнала в виде вектора IPP.
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
     * \brief   Сигнал инициируется после того, как
     *          был создан новый мат. модуль.
     * \param[in] module Указатель на новый мат. модуль.
     */
    void mathModuleChanged(MathModule *module);

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
     * \brief Копирующий конструктор класса Plot.
     * \param[in] b Ссылка на копируемый объект.
     */
    Plot(const Plot &b);

    /*!
     * \brief Оператор копирующего присваивания.
     * \param[in] b Ссылка на копируемый объект.
     * \return Ссылка на новый объект.
     */
    Plot& operator=(const Plot &b);

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
     * \brief Функция позволяет установить значения
     *        оси ординат.
     * \param[in] lvl Новое значение оси ординат.
     */
    void updateAxisY(double lvl);

    QScopedPointer<QwtPlotCurve> d_curve;                   //!< Виджет кривой графика (см. описание QwtPlotCurve).
    QScopedPointer<QwtPlotMarker> d_origin;                 //!< Виджет осей графика (см. описание QwtPlotMarker).
    QScopedPointer<QwtPlotDirectPainter> d_directPainter;   //!< Объект отрисовщика (см. описание QwtPlotDirectPainter).
    QScopedPointer<QwtPlotGrid> d_grid;                     //!< Виджет сетки графика (см. описание QwtPlotGrid).

    QwtInterval dx_interval;                                //!< Интервал оси абсцисс (см. описание QwtInterval).
    QwtInterval dy_interval;                                //!< Интервал оси ординат.
    qint32 d_paintedPoints;                                 //!< Кол-во точек на графике.
    qint32 d_timer_hz;                                      //!< ИД таймера.
    qint16 d_refreshRate;                                   //!< Частота обновления графика.
    qint16 d_cnvsFlag;                                      //!< Флаг канвы.

};

#endif // PLOT_H
