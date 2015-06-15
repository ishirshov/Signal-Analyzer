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

#include "checked_frame.h"

// Подключение заголовных файлов библиотеки Qt
#include <QLayout>

CheckedFrame::CheckedFrame(QWidget *parent)
    :QScrollArea(parent)
    ,frame(new QFrame)
{
    frame->setLayout(new QVBoxLayout);
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    setMinimumHeight(100);
    setWidget(frame);
}

const QStringList& CheckedFrame::getCheckedItems() const
{
    return checked_items;
}

const QStringList& CheckedFrame::getAllItems() const
{
    return all_items;
}

void CheckedFrame::addItems(const QStringList &items)
{
    quint32 items_size = items.size();
    for(quint32 i = 0; i < items_size; ++i)
        addItem(items[i]);
}

void CheckedFrame::addItem(const QString &item)
{
    all_items << item;
    addCheckBox(item);
}

void CheckedFrame::clear()
{
    /* Алгоритм корректного удаления элементов. */
    QLayout *frame_layout = frame->layout();
    QLayoutItem *child = 0;

    /* Удаление элементов из зоны отображения QFrame
       происходит до тех пор пока количество элементов
       не будет равно нулю. */
    while ((child = frame_layout->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }

    /* Очиста карт и списков. */
    checked_items.clear();
    all_items.clear();
    boxes.clear();
}

void CheckedFrame::boxStateChanged(int)
{
    typedef QMap<QString, QCheckBox*>::Iterator box_iter;
    box_iter p = boxes.begin();
    box_iter end = boxes.end();

    /* Выбран новый элемент или наооборот. */
    checked_items.clear();
    for(; p != end; ++p) {
        /* Добавление всех выбранных элементов в список. */
        if(p.value()->isChecked())
            checked_items << p.key();
    }
}

void CheckedFrame::resizeEvent(QResizeEvent *event)
{
    /* Определение нового размера QFrame. */
    QSize frame_size = size();
    frame_size.setWidth(frame_size.width() - 20);

    /* Изменение размера QFrame. */
    frame->resize(frame_size);

    QScrollArea::resizeEvent(event);
}

void CheckedFrame::addCheckBox(const QString &name)
{
    QLayout *frame_layout = frame->layout();
    QCheckBox *box = new QCheckBox(name, this);
    boxes[name] = box;

    connect(box, SIGNAL(stateChanged(int)), SLOT(boxStateChanged(int)));

    /* Добавления нового элемента
     * в QFrame. */
    frame_layout->addWidget(box);
}
