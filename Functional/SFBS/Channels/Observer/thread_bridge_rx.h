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

#ifndef THREAD_BRIDGE_RX_H
#define THREAD_BRIDGE_RX_H

#include <QObject>
#include "Functional/IPP/additional.h"

/*!
 * \irief Класс ThreadRxBridge является производным
 *        от класса Qbject и реализует паттерн
 *        пnоекnирования "Signleton". Данный класс
 *        выполянет роль передающего, который пересылает
 *        данные из библиотеки SFBS в систему слотов/сигналов
 *        библиотеки Qt.
 */
class ThreadRxBridge : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Функция позволяет получить
     *        доступ к передающему классу.
     * \return Ссылку на статический объект.
     */ 
    inline static ThreadRxBridge& getInstance()
    {
        static ThreadRxBridge bridge;
        return bridge;
    }

    /*!
     * \brief   Функция позволяет передать вектор с 16
     *          разрядными данными из библиотеки SFBS в систему
     *          слотов/сигналов библиотеки Qt.
     * \param[in] data Вектор с 16 разрядными целыми числами.
     */
    void sendBufferData(ipp_vector<Ipp16s> data) {
        if(!_ignore_packets)
            emit emitSendBufferData(data);
    }

signals:
    /*!
     * \brief   Сигнал инициируется после вызов его
     *          триггером emit для передачи вектора с данными
     *          в систему слотов и сигналов библиотеки
     *          Qt.
     * \param[in] event Вектор с 16 разрядными целыми числами.
     */
    void emitSendBufferData(ipp_vector<Ipp16s> data);

public slots:
    /*!
     * \brief   Слот позволяет выставить флаг для пропуска
     *		данных.
     * \param[in] val Флаг пропуска.	 
     */
    void setRejectData(bool val) {
        _ignore_packets = val;
    }

private:
    /*!
     * \brief Копирующий конструктор класса ThreadRxBridge.
     * \param[in] b Ссылка на копируемый объект.
     */
    ThreadRxBridge(const ThreadRxBridge &b);

    /*!
     * \brief Оператор копирующего присваивания.
     * \param[in] b Ссылка на копируемый объект.
     * \return Ссылка на новый объект.
     */
    ThreadRxBridge& operator=(const ThreadRxBridge &b);

    /*!
     * \brief Дестркутор класса ThreadRxBridge.
     */
    ~ThreadRxBridge(){}

    /*!
     * \brief Конструктор по умолчанию класса ThreadRxBridge.
     */
    ThreadRxBridge()
        :_ignore_packets(false)
    {}

    bool _ignore_packets;	//<! Флаг пропуска данных.

};

/*!
 * \brief Обратная функция вызова библиотеки SFBS для
 *        обработки потока данных.
 * \param[in] _data Указатель на структуру потока данных.
 */
inline void threadRxCallback(libsfbs_rx_data_t *_data)
{
    if(_data)
    {
        int size = _data->buffer_size/sizeof(Ipp16s);
        Ipp16s *buffer = static_cast<Ipp16s*>(_data->buffer);

        ThreadRxBridge::getInstance().sendBufferData(ipp_vector<Ipp16s>(buffer, size));
    }
}

/*!
 * \brief Обратная функция вызова пользовательского генератора для
 *        обработки потока данных.
 * \param[in] _data Вектор с 32 разрядными вещественными числами.
 */
inline void threadRxCallback(ipp_vector<Ipp32f> _data)
{
    if(_data.size())
        ThreadRxBridge::getInstance().sendBufferData(_data);
}

#endif // THREAD_BRIDGE_RX_H
