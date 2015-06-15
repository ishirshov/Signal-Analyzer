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

#ifndef CANVAS_H
#define CANVAS_H

#include <qwt_plot_canvas.h>
#include <qwt_painter.h>

/*!
 * \brief   Класс StandartCanvas является производным
 *          от базового класса QwtPlotCanvas. Реализует
 *          простейшую отрисовку граф. элементов.
 */
class StandartCanvas : public QwtPlotCanvas
{
public:
    /*!
     * \brief   Конструктор класса StandartCanvas.
     * \param[in] parent Владелец объектом
     *                   (см. http://qt-project.org/doc/qt-4.8/objecttrees.html).
     */
    explicit StandartCanvas(QwtPlot *parent = NULL);

private:
    /*!
     * \brief   Функцию устанавливает палитру
     *          цветов для слоя отображения (канвы).
     */
    void setupPalette();

};

#endif // CANVAS_H
