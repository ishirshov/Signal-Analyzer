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

#ifndef EVENT_BRIDGE_H
#define EVENT_BRIDGE_H

#include <QObject>
#include "Functional/IPP/additional.h"

/*!
 * \brief Класс EventBridge является производным
 *	  от класса QObject и реализует паттерн
 *	  проектирования "Signleton". Данный класс
 *	  выполянет роль передающего, который пересылает
 *	  сообщения из библиотеки SFBS в систему слотов/сигналов
 *	  библиотеки Qt.
 */
class EventBridge : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Функция позволяет получить
     *        доступ к передающему классу.
     * \return Ссылку на статический объект.
     */
    inline static EventBridge& getInstance()
    {
        static EventBridge bridge;
        return bridge;
    }

    /*!
     * \brief 	Функция позволяет передать структуру
     *		события из библиотеки SFBS в систему
     *		слотов/сигналов библиотеки Qt.
     * \param[in] event Тип события в библиотеке SFBS.
     */
    void sendEventData(libsfbs_event_data_t event) {
        emit emitEventData(event);
    }

signals:
    /*!
     * \brief	Сигнал инициируется после вызов его
     *		триггером emit для передачи события
     *		в систему слотов и сигналов библиотеки
     *		Qt.
     * \param[in] event Тип события в библиотеке SFBS.
     */
    void emitEventData(libsfbs_event_data_t event);

private:
    /*!
     * \brief Конструктор по умолчанию класса EventBridge.
     */
    EventBridge() { }
    
    /*!
     * \brief Копирующий конструктор класса EventBridge.
     * \param[in] b Ссылка на копируемый объект.
     */
    EventBridge(const EventBridge &b);
    
    /*!
     * \brief Оператор копирующего присваивания.
     * \param[in] b Ссылка на копируемый объект.
     * \return Ссылка на новый объект.
     */
    EventBridge& operator=(const EventBridge &b);
    
    /*!
     * \brief Дестркутор класса EventBridge.
     */
    ~EventBridge() { }

};

/*!
 * \brief Обратная функция вызова библиотеки SFBS
 *	  для обработки событий.
 * \param[in] _event Указатель на структуру события.
 */
inline void eventCallback(libsfbs_event_data_t *_event)
{
    if(_event)
    {
        if(!_event->event_id || !_event->task_id || !_event->channel_id) return;
        EventBridge::getInstance().sendEventData(*_event);
    }
}

#endif // EVENT_BRIDGE_H
