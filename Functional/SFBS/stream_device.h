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

#ifndef STREAM_DEVICE_H
#define STREAM_DEVICE_H

#include <QStringList>
#include "Functional/IPP/general_functions.h"

/*!
 * \brief Класс StreamDevice реализует интерфейс для 
 *	  работы с потоковыми устройствами.
 */
class StreamDevice : public QObject
{
    Q_OBJECT

public:
    /*! Возможные типы устройств.
     *  Необходимы для фабричных функций.
     */
    enum Type
    {
        Empty = 0, /*!< Пустой тип потока. */
        Channel,   /*!< Тип устройства библиотеки SFBS. */
        User       /*!< Тип пользовательского устройства. */
    };

    /*!
     * \brief	Функция позволяет получить статус 
     *		устройства.
     * \param[in] flag Флаг работы устройства.
     */
    virtual void statusChanged(bool flag) = 0;
    
    /*!
     * \brief	Функция позволяет получить типовое 
     *		сообщение об ошибке, состоянии или исключении,
     *		которое возникло в ходе работы устройства.
     * \param[in] message Информационное сообщение.
     */
    virtual void statusMessage(const QString &message) = 0;
    
    /*!
     * \brief	Функция позволяет отправить объект виджета,
     *		будь то IPC панель или панели управления 
     *		генератором.
     * \param[in] widget Указатель на виджет.
     * \param[in] title  Подпись виджета.
     */
    virtual void widgetChanged(QWidget *widget, const QString &title) = 0;

    /*!
     * \brief	Функция позволяет установить или добавить
     *		новое устройство потока.
     * \param[in] dev Имя устройства (SFBS задача и т.д.).
     */
    virtual void setDeviceName(const QString &dev) = 0;

    /*!
     * \brief	Функция позволяет получить текущий список
     *		устройств.
     * \return  Список активных и доступных устройств.
     */
    virtual QStringList getDeviceList() const = 0;
    
    /*!
     * \brief	Функция позволяет получить тип активного
     *		устройства в виде строкового значения
     *		.
     * \return	Тип устройства в виде строки.
     */
    virtual QString getDeviceType() const = 0;

    /*!
     * \brief	Виртуальный деструктор.
     */
    virtual ~StreamDevice() { }

};

#endif // STREAM_DEVICE_H
