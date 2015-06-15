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

#ifndef CONSOLE_HANDLER_H
#define CONSOLE_HANDLER_H

//-------------- Headers of Qt library --------------------//

#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QTextStream>

//------------- Headers of STDC++ library -----------------//

#include <sstream>
#include <iostream>
#include <stdexcept>
#include <libsfbs.h>

//---------- Declaration of console function --------------//

/*!
 * \brief Обработчик аргументов консоли.
 * \param[in] argc Количество аргументов.
 * \param[in] argv Двумерный массив аргументов.
 * \return Результат обработки аргументов.
 */
bool arguments_handler(int argc, char *argv[]);

/*!
 * \brief Функция возвращает текущее кол-во
 *        свободной памяти RAM.
 * \return Количество памяти RAM (Мб).
 */
long memFree();

/*!
 * \brief Функция позволяет перевести код события
 *        библиотеки SFBS в его строковое представление.
 * \param[in] event Код события.
 * \param[in] task_id Идентификатор SFBS задачи.
 * \param[in] channel_id Идентификатор SFBS канала.
 * \return Строковое представление кода события.
 */
const QString eventEnumToString(int event, int task_id, int channel_id);

/*!
 * \brief Функция позволяет записать данные из
 *        массива data на диск.
 * \param[in] data Данные для записи.
 * \param[in] size Размер массива data.
 * \param[in] name Имя файла.
 * \param[in] mode Режим записи в файл (см. флаги QIODevice).
 */
template<class T> void dumpToFile(T *data, ulong size,
                                  const char *name = 0,
                                  QIODevice::OpenModeFlag mode = QIODevice::WriteOnly)
{
	if(!data) return;

    QString filename;

    if(!name)
        filename = QString("dump_%1.txt").arg(QDateTime::currentDateTime().toTime_t());
    else
        filename = name;

    QFile file(filename);

    if(!file.open(mode)) return;

    QTextStream out(&file);

    for(ulong i = 0; i < size; ++i)
        out << data[i] << '\n';
}

/*!
 * \brief Функция для отображения отладочных
 *        сообщений.
 * \param message Отладочное сообщение.
 */
inline void printDebug(const QString &message)
{
#ifdef QT_DEBUG
    qDebug() << "DEBUG INFO:" << message;
#endif
}

/*!
 * \brief Функция для отображения информационных
 *        сообщений.
 * \param message Информационное сообщение.
 */
inline void printInfo(const QString &message)
{
#ifdef QT_DEBUG
    qDebug() << "COMMON INFO:" << message;
#endif
}

/*!
 * \brief Функция для отображения сообщений
 *        исключения.
 * \param message Сообщение исключения.
 */
inline void printException(const QString &message)
{
#ifdef QT_DEBUG
    qDebug() << "EXCEPTION INFO:" << message;
#endif
}

/*!
 * \brief Функция позволяет преобразовать тип
 *        QString в char* в зависимости от
 *        используемой библиотеки Qt.
 * \param message Сообщение для преобразования.
 * \return Преобразованное сообщение.
 */
inline const char* toConstChar(const QString &message)
{
#if (QT_VERSION < QT_VERSION_CHECK(4, 8, 0))
    return message.toAscii().constData();
#else
    return message.toStdString().c_str();
#endif
}

#endif // CONSOLE_HANDLER_H
