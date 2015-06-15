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

#include "checked_box.h"

// Подключение заголовных файлов библиотеки Qt
#include <QStylePainter>
#include <QStandardItemModel>

CheckedBox::CheckedBox(QWidget *parent)
    :QComboBox(parent)
    ,title_rect(4, 1, -25, 0)
{
    /* Необходимо устанавливать стиль принудительно. Баг GTK+. */
    setStyleSheet("QComboBox { combobox-popup: 1px }");

    QStandardItemModel *std_model = qobject_cast<QStandardItemModel*>(model());

    connect(std_model, SIGNAL(rowsInserted(QModelIndex,int,int)), SLOT(insertRows(QModelIndex,int,int)));
    connect(std_model, SIGNAL(rowsRemoved(QModelIndex,int,int)), SLOT(removeRows(QModelIndex,int,int)));
    connect(std_model, SIGNAL(itemChanged(QStandardItem*)), SLOT(changeItems(QStandardItem*)));
}

const QStringList& CheckedBox::getCheckedItems() const
{
    return checked_items;
}

const QStringList& CheckedBox::getAllItems() const
{
    return all_items;
}

void CheckedBox::addItems(const QStringList &items)
{
    all_items.append(items);

    QComboBox::addItems(items);
}

void CheckedBox::addItem(const QString &text, const QVariant &userData)
{
    all_items << text;

    QComboBox::addItem(text, userData);
}

void CheckedBox::addItem(const QIcon &icon, const QString &text, const QVariant &userData)
{
    all_items << text;

    QComboBox::addItem(icon, text, userData);
}

void CheckedBox::clear()
{
    all_items.clear();
    checked_items.clear();

    QComboBox::clear();
}

void CheckedBox::paintEvent(QPaintEvent *e)
{
    QStylePainter painter(this);

    painter.setPen(palette().color(QPalette::Text));

    QStyleOptionComboBox option;

    initStyleOption(&option);

    /* Зарисовка базовой части виджета QComboBox. */
    painter.drawComplexControl(QStyle::CC_ComboBox, option);

    /* Определение границ текста в онке надписи. */
    QRect text_rect = rect().adjusted(title_rect.left(), title_rect.top(),
                                      title_rect.right(), title_rect.bottom());

    /* Отрисовка текста. */
    painter.drawText(text_rect, Qt::AlignVCenter, box_title);

    QComboBox::paintEvent(e);
}

void CheckedBox::resizeEvent(QResizeEvent *e)
{
    editBoxTitle();

    QComboBox::resizeEvent(e);
}

void CheckedBox::collectSellectedItems()
{
    /* Получаем объект отображения. */
    QStandardItemModel *std_model = qobject_cast<QStandardItemModel*>(model());

    /* Удаляем старые элементы. */
    checked_items.clear();

    /* Количество текущих элементов. */
    quint32 item_size = count();
    for(int i = 0; i < item_size; ++i)
    {
        /* Получаем элемент из объекта отображения. */
        QStandardItem *model_item = std_model->item(i);
        Qt::CheckState state = Qt::CheckState(model_item->data(Qt::CheckStateRole).toInt());

        /* Проверка состояния элемента. */
        if(state == Qt::Checked)
            checked_items << model_item->text(); /* Добавление элемента в список, если он был выбран. */
    }

    editBoxTitle();
    repaint();
}

void CheckedBox::editBoxTitle()
{
    QRect text_rect = rect().adjusted(title_rect.left(), title_rect.top(),
                                      title_rect.right(), title_rect.bottom());

    /* Формирование текста надписи, исходя из выбранных элементов. */
    box_title = checked_items.join(", ");

    /* Определение размера текста, под текущий размер надписи. */
    box_title = fontMetrics().elidedText(box_title, Qt::ElideRight, text_rect.width());
    if(box_title.length())
        box_title += "...";
}

void CheckedBox::insertRows(const QModelIndex &parent, int start, int end)
{
    QStandardItemModel *std_model = qobject_cast<QStandardItemModel*>(model());

    /* Блокировка текущих сигналов. */
    blockSignals(true);

    for (int i = start; i <= end; ++i)
    {
        /* Установка параметров элемента при добавлении. */
        std_model->item(i)->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        std_model->item(i)->setData(Qt::Unchecked, Qt::CheckStateRole);
    }

    blockSignals(false);
}

void CheckedBox::removeRows(const QModelIndex &parent, int start, int end)
{
    /* Пересобрать текущее количество выбранных элементов. */
    collectSellectedItems();
}

void CheckedBox::changeItems(QStandardItem *item)
{
    /* Пересобрать текущее количество выбранных элементов. */
    collectSellectedItems();
}
