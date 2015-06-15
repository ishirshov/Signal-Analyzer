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

#ifndef PLAYBACKPLOT_H
#define PLAYBACKPLOT_H

#include "PlaybackCurveData/playbackcurvedata.h"

#include <qwt_plot.h>
#include <qwt_interval.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_directpainter.h>
#include <qwt_wheel.h>

/*!
 * \brief       Класс PlaybackPlot является производным от класс QwtPlot.
 * \detailed    Специально-реализованный 2-D виджет для отображения
 *              ранее записанного сигнала с расширенными возможностями.
 */
class PlaybackPlot : public QwtPlot
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса PlaybackPlot.
     * \param[in] parent Владелец объектом
     *                   (см. http://qt-project.org/doc/qt-4.8/objecttrees.html).
     */
    explicit PlaybackPlot(QWidget *parent = 0);

    /*!
     * \brief Дестркутор класса PlaybackPlot.
     */
    ~PlaybackPlot();

signals:
    /*!
     * \brief   Сигнал инициируется в случае, если
     *          ширина окна графика была изменена.
     * \param[in] width Значение новой ширины окна.
     */
    void windowWidthChanged(quint32 width);

    /*!
     * \brief   Сигнал инициируется, если график
     *          доступен для отображения новой порции
     *          данных. В ином случае, график будет
     *          игнорировать новые данные.
     * \param[in] flag Флаг состояния графика.
     */
    void storeFlagChanged(bool flag);

public slots:
    /*!
     * \brief   Слот позволяет принять новую порцию данных
     *          записанного сигнала в виде вектора QVector.
     * \param[in] data Вектор данных.
     */
    void addNewData(QVector<QPointF> *data);

    /*!
     * \brief   Слот позволяет очистить график от
     *          данных.
     */
    void clearData();

private slots:
    /*!
     * \brief   Слот позволяет перемещаться по графику
     *          по оси абсцисс.
     * \param[in] step Шаг перемещения по оси абсцисс.
     */
    void scrollBottomAxis(double step);

protected:
    /*!
     * \brief Фильтр событий (см. описание QObject::eventFilter).
     * \param[in] object Указатель на объект для фильтрации.
     * \param[in] event Указатель на событие.
     * \return  см. описание QObject::eventFilter
     */
    virtual bool eventFilter(QObject *object, QEvent *event);

    /*!
     * \brief Метод позволяет изменить размер и обновить внутренние
     *        графические слои (см. описание QWidget::resizeEvent).
     * \param[in] event Указатель на структуру QResizeEvent.
     */
    virtual void resizeEvent(QResizeEvent *event);

private:
    /*!
     * \brief Копирующий конструктор класса PlaybackPlot.
     * \param[in] b Ссылка на копируемый объект.
     */
    PlaybackPlot(const PlaybackPlot &b);

    /*!
     * \brief Оператор копирующего присваивания.
     * \param[in] b Ссылка на копируемый объект.
     * \return Ссылка на новый объект.
     */
    PlaybackPlot& operator=(const PlaybackPlot &b);

    /*!
     * \brief   Обновить диапазон данных оси абсцисс
     *          для колеса прокрутки.
     */
    void updateXWheel();

    /*!
     * \brief Функция позволяет обновить значения
     *        оси ординат.
     */
    void updateAxisY();

    QScopedPointer<QwtPlotCurve> d_curve;                   //!< Виджет кривой графика (см. описание QwtPlotCurve).
    QScopedPointer<QwtPlotMarker> d_origin;                 //!< Виджет осей графика (см. описание QwtPlotMarker).
    QScopedPointer<QwtPlotDirectPainter> d_directPainter;   //!< Объект отрисовщика (см. описание QwtPlotDirectPainter).
    QScopedPointer<QwtPlotGrid> d_grid;                     //!< Виджет сетки графика (см. описание QwtPlotGrid).
    QScopedPointer<QwtWheel> dx_wheel;                      //!< Виджет колеса прокрутки графика (см. описание QwtWheel).

    QwtInterval dx_interval;                                //!< Интервал оси абсцисс (см. описание QwtInterval).
    QwtInterval dy_interval;                                //!< Интервал оси ординат.
    qint16 d_cnvsFlag;                                      //!< Флаг канвы.

};

#endif // PLAYBACKPLOT_H
