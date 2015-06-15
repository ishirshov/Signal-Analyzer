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

#ifndef CHECKED_FRAME_H
#define CHECKED_FRAME_H

// Подключение заголовных файлов библиотеки Qt
#include <QMap>
#include <QFrame>
#include <QCheckBox>
#include <QScrollArea>
#include <QStringList>

/*!
 * \brief       Класс CheckedFrame производный от QScrollArea.
 * \detailed    Данный класс предназначен для реализации
 *              графического виджета в виде QScrollArea и
 *              множества QCheckBox элеметов, для реализации
 *              множественного выбора данных (аналог CheckedBox).
 */
class CheckedFrame : public QScrollArea
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса CheckedFrame.
     * \param[in] parent Владелец объектом (см. http://qt-project.org/doc/qt-4.8/objecttrees.html)
     */
    explicit CheckedFrame(QWidget *parent = 0);

    /*!
     * \brief   Позволяет получить выбранные
     *          элементы виджета.
     * \return  Список выбранных элементов.
     */
    const QStringList& getCheckedItems() const;

    /*!
     * \brief   Позволяет получить все элементы
     *          из виджета.
     * \return  Список всех элементов.
     */
    const QStringList& getAllItems() const;

    /*!
     * \brief   Замещенный метод, позволяет добавить
     *          множестов элементов в текущий виджет.
     * \param[in] items Список добавляемых элементов.
     */
    void addItems(const QStringList& items);

    /*!
     * \brief addItem   Замещенный метод, позволяет добавить
     *                  единичный элемент в текущий виджет.
     * \param[in] item  Имя элемента.
     */
    void addItem(const QString& item);

    /*!
     * \brief   Удалить все текущие элементы из
     *          виджета.
     */
    void clear();

private slots:
    /*!
     * \brief   Слот вызывается при изменении состояния
     *          одного из QCheckBox.
     * \param[in] i Индекс измененного QCheckBox.
     */
    void boxStateChanged(int i);

protected:
    /*!
     * \brief   Переопределенный метод родительского класса
     *          для изменения размера объекта QFrame.
     * \param[in] e Событие изменения размера виджета.
     */
    void resizeEvent(QResizeEvent *e);

private:
    /*!
     * \brief   Метод реализует функционал по
     *          добавлению нового QCheckBox элемента
     *          в объект QFrame.
     * \param[in] item  Имя нового элемента.
     */
    void addCheckBox(const QString& item);

    QStringList checked_items;          //!< Список выбранных элементов.
    QStringList all_items;              //!< Список всех элементов.

    QMap<QString,QCheckBox*> boxes;     //!< Карта соответствия для преобразования имени элемента в объект.
    QFrame *frame;                      //!< Фрейм, который содержит элементы QCheckBox.

};

#endif // CHECKED_FRAME_H
