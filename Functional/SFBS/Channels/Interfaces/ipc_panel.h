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

#ifndef IPC_PANEL_H
#define IPC_PANEL_H

#include <QWidget>
#include "Functional/IPP/additional.h"

/*!
 * \brief   Класс IPCPanel производный от QWidget.
 *          Реализует интерфейс виджета IPC панели.
 */
class IPCPanel : public QWidget
{
    Q_OBJECT

public:
    /*
     * \brief Позволяет получить тип текущей панели IPC.
     * \return Тип IPC панели.
     */
    virtual QString getPanelType() const = 0;

    /*!
     * \brief Функция позволяет получить текущую частоту
     *        дискретизации используемого в генераторе.
     * \param[in] freq Текущая частота дискретизации.
     */
    virtual void samplingFrequencyChanged(ulong freq) = 0;

    /*!
     * \brief Функция позволяет получить текущее значение
     *        для перевода уровней в вольты.
     * \param[in] lvl Значение перевода уровня в вольты.
     */
    virtual void voltsLevelChanged(float lvl) = 0;

    /*!
     * \brief Деструктор класса IPCPanel.
     */
    virtual ~IPCPanel() { }

public slots:
    /*!
     * \brief Слот принимает на обработку IPC сообщение
     *        из библиотеки SFBS.
     * \param[in] msg Указатель на IPC сообщение.
     */
    virtual void ipcDataHandle(void *msg) = 0;

    /*!
     * \brief Слот позволяет инициализировать IPC панель
     *        для работы с IPC интерфейсом устройства.
     * \param[in] user_ch_id   Идентификатор пользовательского IPC канала.
     * \param[in] user_tsk_id  Идентификатор польовательской SFBS задачи.
     * \param[in] panel_ch_id  Идентификатор удаленного IPC канала.
     * \param[in] panel_tsk_id Идентификатор удаленной SFBS задачи.
     */
    virtual void ipcInit(int user_ch_id, int user_tsk_id, int panel_ch_id, int panel_tsk_id) = 0;

    /*!
     * \brief Слот позволяет заблакировать 
     *        функцию по изменению текущей
     *        частоты дискретизации.
     * \param[in] flag Флаг блокировки.
     */
    virtual void blockSamplingFrequency(bool flag) = 0;

};

#endif // IPC_PANEL_H
