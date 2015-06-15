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

#ifndef VOLT_BOX_H
#define VOLT_BOX_H

// Подключение заголовных файлов библиотеки Qt
#include <QLCDNumber>
#include <QLabel>
#include <QComboBox>

// Подключение заголовных файлов библиотеки Qwt
#include <qwt_wheel.h>

#include "resolution_box.h"

/*!
 * \brief Класс ControlBox производный от ResolutionBox.
 */
class ControlBox : public ResolutionBox
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса ControlBox.
     * \param[in] parent Владелец объектом (см. http://qt-project.org/doc/qt-4.8/objecttrees.html)
     */
    explicit ControlBox(QWidget *parent = 0);

    /*!
     * \brief   Позволяет получить текущее
     *          значение частоты обновления экрана.
     * \return  Текущая частота обновления [Hz].
     */
    short currentRate() const;

    /*!
     * \brief   Позволяте получить текущее
     *          значение множителя напряжения.
     * \return  Текущий множитель напряжения.
     */
    double currentVolts() const;

    /*!
     * \brief   Позволяет разослать инициализирующие
     *          значения по системе сигналов/слотов Qt.
     */
    void sendInitialValues();

signals:
    /*!
     * \brief   Сигнал будет вызван после изменения
     *          частоты обновления экрана [Hz].
     * \param[in]   Новая частота обновления [Hz].
     */
    void rateValueChanged(short value);

    /*!
     * \brief   Сигнал будет вызван после изменения
     *          множителя напряжения.
     * \param[in]   Новый множитель напряжения.
     */
    void voltValueChanged(double value);

private slots:
    /*!
     * \brief   Слот будет вызван в момент изменения
     *          частоты обновления экрана [Hz].
     * \param[in]   Новая частота обновления [Hz].
     */
    void setRefreshRate(double value);

    /*!
     * \brief   Слот будет вызван в момент изменения
     *          множителя напряжения.
     * \param[in]   Новый множитель напряжения.
     */
    void setVolts(int value);

    /*!
     * \brief   Переопределенный метод родительского класса
     *          для обработки событий типа "Изменение".
     * \param[in] e Указатель на структуру QEvent.
     */
    void changeEvent(QEvent *e);

private:
    QLabel *volt_lbl;               //!< Надпись множителя напряжения.
    QComboBox *volt_cmb;            //!< QComboBox возможных значений множителя напряжения.
    QMap<quint32, qreal> volt_map;  //!< Преобразование индекса множителя напряжения в его значение.

    QLabel *refresh_lbl;            //!< Надпись частоты обновления экрана [Hz].
    QLCDNumber *refresh_lcd;        //!< Доступные значения частоты обновления экрана [Hz].
    QwtWheel *refresh_wheel;        //!< Элемент изменения текущей частоты обновления экрана [Hz] ("колесико").

};

#endif // VOLT_BOX_H
