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

#ifndef SFBS_CHANNELS_H
#define SFBS_CHANNELS_H

#include "Functional/SFBS/stream_device.h"
#include <QMap>

/*!
 * \brief Класс SFBSChannels предоставляет 
 *	  интерфейс по управлению SFBS задачами и
 *	  каналами. Позволяет создавать IPC панели.
 */
class SFBSChannels : public StreamDevice
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса SFBSChannels.
     * \param[in] parent Владелец объектом (см. http://qt-project.org/doc/qt-4.8/objecttrees.html).
     */
    explicit SFBSChannels(QObject *parent = 0);

    QStringList getDeviceList() const;
    QString getDeviceType() const;

    /*!
     * \brief Деструктор класса SFBSChannels.
     */
    ~SFBSChannels();

signals:
    /*!
     * \brief Функция позволяет получить статус устройства. 
     * \param[in] flag Флаг работы устройства. 
     */
    void statusChanged(bool flag);
    
    /*!
     * \brief Функция позволяет получить типовое сообщение об ошибке, 
     *	      состоянии или исключении, которое возникло в ходе работы устройства. 
     * \param[in] message Информационное сообщение.
     */
    void statusMessage(const QString &message);
    
    /*!
     * \brief Функция позволяет отправить объект виджета, 
     *	      будь то IPC панель или панели управления генератором. 
     * \param[in] widget Указатель на виджет.
     * \param[in] title  Подпись виджета. 
     */
    void widgetChanged(QWidget *widget, const QString &title);

public slots:
    /*!
     * \brief Функция позволяет установить или добавить новое устройство потока.
     * \param[in] dev Имя устройства (SFBS задача и т.д.).
     */
    void setDeviceName(const QString &dev);

private:
    /*!
     * \brief Копирующий конструктор класса SFBSChannels.
     * \param[in] b Ссылка на копируемый объект.
     */
    SFBSChannels(const SFBSChannels &b);
    
    /*!
     * \brief Оператор копирующего присваивания.
     * \param[in] b Ссылка на копируемый объект.
     * \return Ссылка на новый объект.
     */
    SFBSChannels& operator=(const SFBSChannels &b);

    qint32 local_task_id;				//!< Локальный идентификатор задачи.
    QMap<QString, libsfbs_task_info_t> task_list;	//!< Список SFBS задач доступных для подключения.

};

#endif // SFBS_CHANNELS_H
