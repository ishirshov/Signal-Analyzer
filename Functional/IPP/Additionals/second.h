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

#ifndef SECOND_H
#define SECOND_H

#include <QString>

/*!
 * \brief   Класс Second реализует
 *          представление едицин времени
 *          относительно секунды.
 */
class Second
{
    double val; //!< Значение единицы.
    QString nm; //!< Название единицы.
    QString sm; //!< Обозначение в системе C.

    /*!
     * \brief Функция проверяет допустимость
     *        значения единицы для представления.
     * \param[in] v Значение единицы времени.
     * \return Результат проверки.
     */
    bool in_range(double v);

public:
    /*!
     * \brief Конструктор поумолачнию класса Second.
     */
    Second();

    /*!
     * \brief Конструктор класса Second.
     * \param[in] val Единица времени.
     * \param[in] nm Название.
     * \param[in] sm Обозначение в системе C.
     */
    Second(double val, const QString& nm, const QString& sm);

    /*!
     * \brief Функция позволяет получить значение
     *        текущей единицы времени.
     * \return Текущее значение единицы времени.
     */
    double value() const { return val; }

    /*!
     * \brief Установка нового значения
     *        текущей единицы времени.
     * \param[in] v Новое значение единицы времени.
     */
    void value(double v) { val = v; }

    /*!
     * \brief Функция позволяет получить название
     *        текущей единицы времени.
     * \return Текущее название единицы времени.
     */
    QString name() const { return nm; }

    /*!
     * \brief Установка нового названия
     *        текущей единицы времени.
     * \param[in] name Новое название единицы времени.
     */
    void name(const QString &name) { nm = name; }

    /*!
     * \brief Функция позволяет получить обозначение
     *        текущей единицы времени.
     * \return Текущее значение единицы времени.
     */
    QString symbol() const { return sm; }

    /*!
     * \brief Установка нового обозначения
     *        текущей единицы времени.
     * \param[in] symb Новое обозначение единицы времени.
     */
    void symbol(const QString &symb) { sm = symb; }

};

#endif // SECOND_H
