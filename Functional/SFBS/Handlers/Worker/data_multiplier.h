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

#ifndef DATA_MULTIPLIER_H
#define DATA_MULTIPLIER_H

#include <QThread>
#include "worker_manager.h"

/*!
 * \brief Класс DataMultiplier является производным классом
 *        от базового класса WorkerManager и реализует функционал
 *        по управлению объектами типа Worker. Выполняет
 *	  функции удаления, добавления, следит за состоянием
 *	  Worker объектов и их потоков выполения.
 */
class DataMultiplier : public WorkerManager
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор по умолчанию класса DataMultiplier.
     * \param[in] parent Владелец объектом (см. http://qt-project.org/doc/qt-4.8/objecttrees.html)
     */
    explicit DataMultiplier(QObject *parent = 0);

    /*!
     * \brief Метод добавления объекта типа WorkerBehavior 
     *        в цепочку по обработке пакетов.
     * \param[in] worker Указатель на объект типа WorkerBehavior.
     */
    void addWorker(WorkerBehavior *worker);
    
    /*!
     * \brief Метод удаления объекта типа WorkerBehavior 
              из цепочки по обработке пакетов 
     */
    void removeWorker(WorkerBehavior *);

    ~DataMultiplier();

signals:
    void receiveData(const ipp_vector<Ipp16s>&);

private slots:
    void workerDestroyed(QObject*);
    void threadDestroyed(QObject*);

private:
    typedef QList<QThread*> thread_lst;
    typedef QList<WorkerBehavior*> worker_lst;
    typedef QMap<QThread*, quint32> thread_map;
    typedef QMap<WorkerBehavior*, QThread*> worker_map;

    DataMultiplier(const DataMultiplier&);
    DataMultiplier& operator=(const DataMultiplier&);

    QThread* createThread();

    thread_map threads;
    worker_map workers;

    bool multipl_is_permit;

};

#endif // DATA_MULTIPLIER_H
