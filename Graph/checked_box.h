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

#ifndef CHECKED_BOX_H
#define CHECKED_BOX_H

// Подключение заголовных файлов библиотеки Qt
#include <QComboBox>
#include <QStandardItem>

/*!
 * \brief       Класс CheckedBox производный от QComboBox.
 * \detailed    Данный класс предназначен для реализации
 *              графического виджета в виде QComboBox с функцией
 *              множественного выбора данных.
 */
class CheckedBox : public QComboBox
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса CheckedBox.
     * \param[in] parent Владелец объектом (см. http://qt-project.org/doc/qt-4.8/objecttrees.html)
     */
    explicit CheckedBox(QWidget *parent = 0);

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
     * \brief       Замещенный метод, позволяет добавить
     *              множестов элементов в текущий виджет.
     * \param[in] items Список добавляемых элементов.
     */
    void addItems(const QStringList& items);

    /*!
     * \brief addItem   Замещенный метод, позволяет добавить
     *                  единичный элемент в текущий виджет.
     * \param[in] icon  Иконка элемента.
     * \param[in] item  Имя элемента.
     * \param[in] data  Данные элемента (контейнер для данных).
     */
    void addItem(const QIcon& icon, const QString& item, const QVariant& data);

    /*!
     * \brief addItem   Замещенный метод, позволяет добавить
     *                  единичный элемент в текущий виджет.
     * \param[in] item  Имя элемента.
     * \param[in] data  Данные элемента (контейнер для данных).
     */
    void addItem(const QString& item, const QVariant& data);

    /*!
     * \brief   Удалить все текущие элементы из
     *          виджета.
     */
    void clear();

protected:
    /*!
     * \brief   Переопределенный метод родительского класса
     *          для отрисовки надписи в QComboBox.
     * \param[in] e Событие отрисовки.
     */
    void paintEvent(QPaintEvent *e);

    /*!
     * \brief   Переопределенный метод родительского класса
     *          для отрисовки измененной, по размеру, надписи в QComboBox.
     * \param[in] e Событие изменения размера виджета.
     */
    void resizeEvent(QResizeEvent *e);

private slots:
    /*!
     * \brief   Слот вызывается при изменении количества
     *          выбранных элементов.
     */
    void collectSellectedItems();

    /*!
     * \brief   Слот вызывается при изменении надписи или
     *          изменении её размера.
     */
    void editBoxTitle();

    /*!
     * \brief   Слот вызывается при добавлении новых
     *          элементов в модель отобржения.
     * \param[in] parent Родительский элемент, от которого начинается добавление.
     * \param[in] start  Позиция, с которой начинается вставка.
     * \param[in] end    Позиция, на которой заканчивается.
     */
    void insertRows(const QModelIndex &parent, int start, int end);

    /*!
     * \brief   Слот вызывается при удалении элементов
     *          из модели отображения.
     * \param[in] parent Родительский элемент, от которого начинается удаление.
     * \param[in] start  Позиция, с которой начинается вставка.
     * \param[in] end    Позиция, на которой заканчивается.
     */
    void removeRows(const QModelIndex &parent, int start, int end);

    /*!
     * \brief   Слот вызывается при выборе элементов,
     *          который обновит список выбранных элементов.
     * \param[in] item  Элемент из модели отображения.
     */
    void changeItems(QStandardItem *item);

private:
    QStringList checked_items;  //!< Список выбранных элементов.
    QStringList all_items;      //!< Список всех элементов.
    QString box_title;          //!< Текст надписи виджета.

    const QRect title_rect;     //!< Размеры надписи.

};

#endif // CHECKED_BOX_H
