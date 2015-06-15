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

#ifndef KNOBBOX_H
#define KNOBBOX_H

// Подключение заголовных файлов библиотеки Qt
#include <QWidget>
#include <QLabel>

// Подключение заголовных файлов библиотеки Qwt
#include <qwt_knob.h>

/*!
 * \brief		Класс KnobBox является производным от QWidget.
 * \detailed	Реализует графический виджет в виде поворотной ручки
 *				для плавной установки значений. Легко конфигурируются
 *				значения прокрутки и деления. 
 */
class KnobBox : public QWidget
{
    Q_OBJECT

public:
	/*!
     * \brief Конструктор класса KnobBox.
     * \param[in] parent Владелец объектом (см. http://qt-project.org/doc/qt-4.8/objecttrees.html)
     */
    explicit KnobBox(QWidget *parent = 0);
    
signals:
	/*!
	 * \brief Сигнал позволяет установить значение виджета.
	 * \param[in] value Устанавливаемое значение.
	 */
    void setValue(double value);

    /*!
	 * \brief Сигнал вызывается при изменении текущего значения.
	 * \param[in] value Новое значение.
	 */
    void valueChanged(double value);

public slots:
	/*!
	 * \brief Позволяет установить собственную шкалу для виджета.
	 * \param[in] interval Новая шкала.
	 */
    void setScale(const QwtInterval &interval);

private slots:
	/*!
	 * \brief При изменении значения, изменяется и подпись
	 *	      под виджетом.
	 * \param[in] v Новое значение для подписи виджета.
	 */
    void setNum(double v);

private:
    QwtKnob *d_knob; 	//!< Виджет прокрутки.
    QLabel *d_blabel;	//!< Виджет подписи.

};

#endif // KNOBBOX_H
