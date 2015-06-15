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

#ifndef APPLICATION_H
#define APPLICATION_H

// Подключение заголовных файлов библиотеки Qt
#include <QtGui>
#include <QApplication>

// Подключение заголовочных файлов "Функциональной части проекта"
#include "Functional/IPP/Additionals/console_handler.h"

/*!
 * \brief       Класс Application является производным от QApplication.
 * \detailed    См. описание к классу QApplication.
 */
class Application : public QApplication
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктов класса Application.
     * \param[in] argc Количество аргументов argv.
     * \param[in] argv Аргументы командной строки.
     */
    Application(int& argc, char **argv);
    
    /*!
     * \brief Переопределенный метод родительского класса
     *        для обработки исключений.
     * \param[in] receiver Получатель события.
     * \param[in] event Событие для обработки.
     * \return Состояние от обработчика событий объекта receiver.
     */
    bool notify(QObject *receiver, QEvent *event);

};

#endif // APPLICATION_H
