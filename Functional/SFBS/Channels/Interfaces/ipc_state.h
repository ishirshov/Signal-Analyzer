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

#ifndef IPC_STATE_H
#define IPC_STATE_H

#include <QMessageBox>

class IsomorphPanel;
class FPGAPanel;

/*!
 * \brief   Класс IPCState реализует интерфейс
 *          состояний для машины состояний.
 */
class IPCState
{
public:
    /*!
     * \brief Обработчик IPC функции. Предназначен
     *        для выполнения IPC функций и обработки статуса.
     */
    virtual void sendMessage() = 0;

    /*!
     * \brief Обработчик результатов выполнения IPC функций.
     * \param[in] msg Результат выполнения IPC функции.
     */
    virtual void messageReceive(void* msg) = 0;

    /*!
     * \brief Деструктор класса IPCState.
     */
    virtual ~IPCState() {}
};

#endif // IPC_STATE_H
