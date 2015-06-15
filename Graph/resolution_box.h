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

#ifndef RESOLUTION_BOX_H
#define RESOLUTION_BOX_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QEvent>

/*!
 * \brief       Класс ResolutionBox является производным от QWidget.
 * \detailed    Реализует графический виджет для упрощенного
 *              управления делителем частоты и частотой сканирования.
 */
class ResolutionBox : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief   Конструктор класса ResolutionBox.
     * \param[in] parent Владелец объектом (см. http://qt-project.org/doc/qt-4.8/objecttrees.html)
     */
    explicit ResolutionBox(QWidget *parent = 0);

    /*!
     * \brief   Функция позволяет получить текущий
     *          делитель частоты, выставленный на
     *          графическом виджете.
     * \return  Значения делителя частоты.
     */
    quint32 currentDivider() const;

    /*!
     * \brief   Функция позволяет получить текущую
     *          частоту сканирования, выставленную
     *          на графическом виджете.
     * \return  Значение частоты сканирования.
     */
    quint32 currentFrequency() const;

signals:
    /*!
     * \brief   Сигнал инициируется после изменения
     *          текущего делителя частоты.
     * \param[in] value Новый делитель частоты.
     */
    void dividerValueChanged(int value);

    /*!
     * \brief   Сигнал инициируется после изменения
     *          текущей частоты сканирования.
     * \param[in] value Новый частота сканирования.
     */
    void frequencyValueChanged(int value);

protected slots:
    /*!
     * \brief   Переопределенный метод родительского класса
     *          для обработки событий типа "Изменение".
     * \param[in] event Указатель на структуру QEvent.
     */
    virtual void changeEvent(QEvent *event);

private slots:
    /*!
     * \brief   Слот позволяет выставить новый
     *          делитель частоты.
     * \param[in] value Значение делителя частоты.
     */
    void setDivider(int value);

    /*!
     * \brief   Слот позволяет выставить новую
     *          частоту сканирования.
     * \param[in] value Значение частоты сканирования.
     */
    void setFrequency(int value);

private:
    /*!
     * \brief   Функция инициализирует возможные
     *          значения делителей частоты и частот
     *          сканирования в соответствующих им картах.
     */
    void initFreqDevMap();

    /*!
     * \brief   Инициализация графических списков
     *          частот сканирования.
     */
    void initFrequencyCmb();

    /*!
     * \brief   Инициализация графических списков
     *          делителей частот.
     */
    void initDividerCmb();

    QLabel *divider_lbl;            //!< Виджет надписи "Делитель частоты".
    QComboBox *divider_cmb;         //!< Виджет списка для делителей частот.
    QLabel *frequency_lbl;          //!< Виджет надписи "Частота сканирования".
    QComboBox *frequency_cmb;       //!< Виджет списка для частот сканирования.

    QMap<quint32,quint32> freq_map; //!< Карты соответствия для частот сканирования.
    QMap<quint32,quint32> div_map;  //!< Карты соответствия для делителей частот.

};

#endif // RESOLUTION_BOX_H
