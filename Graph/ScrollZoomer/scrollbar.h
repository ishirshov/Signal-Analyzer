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

#ifndef _SCROLLBAR_H
#define _SCROLLBAR_H

#include <qscrollbar.h>

/*!
 * \brief       Класс ScrollBar является производным от
 *              класса QScrollBar.
 * \detailed    Данный класс реализует графический виджет
 *              для
 */
class ScrollBar : public QScrollBar
{
    Q_OBJECT

public:
    /*!
     * \brief ScrollBar
     * \param[in] parent
     */
    ScrollBar(QWidget *parent = NULL);

    /*!
     * \brief ScrollBar
     * \param[in] o
     * \param[in] parent
     */
    ScrollBar(Qt::Orientation o, QWidget *parent = NULL);

    /*!
     * \brief ScrollBar
     * \param[in] minBase
     * \param[in] maxBase
     * \param[in] o
     * \param[in] parent
     */
    ScrollBar(qreal minBase, qreal maxBase, Qt::Orientation o, QWidget *parent = NULL);

    /*!
     * \brief setInverted
     * \param[in] flag
     */
    void setInverted(bool flag);

    /*!
     * \brief isInverted
     * \return
     */
    bool isInverted() const;

    /*!
     * \brief minBaseValue
     * \return
     */
    double minBaseValue() const;

    /*!
     * \brief maxBaseValue
     * \return
     */
    double maxBaseValue() const;

    /*!
     * \brief minSliderValue
     * \return
     */
    double minSliderValue() const;

    /*!
     * \brief maxSliderValue
     * \return
     */
    double maxSliderValue() const;

    /*!
     * \brief extent
     * \return
     */
    int extent() const;

signals:

    void sliderMoved(Qt::Orientation o, qreal, qreal);
    void valueChanged(Qt::Orientation o, qreal, qreal);

public slots:
    /*!
     * \brief setBase
     * \param[in] min
     * \param[in] max
     */
    virtual void setBase(qreal min, qreal max);

    /*!
     * \brief moveSlider
     * \param[in] min
     * \param[in] max
     */
    virtual void moveSlider(qreal min, qreal max);

protected:
    /*!
     * \brief sliderRange
     * \param[in] value
     * \param[in] min
     * \param[in] max
     */
    void sliderRange(int value, qreal &min, qreal &max) const;

    /*!
     * \brief mapToTick
     * \param[in] value
     * \return
     */
    int mapToTick(qreal value) const;

    /*!
     * \brief mapFromTick
     * \param[in] value
     * \return
     */
    qreal mapFromTick(int value) const;

private slots:
    /*!
     * \brief catchValueChanged
     * \param[in] value
     */
    void catchValueChanged(int value);

    /*!
     * \brief catchSliderMoved
     * \param[in] value
     */
    void catchSliderMoved(int value);

private:
    /*!
     * \brief init
     */
    void init();

    bool d_inverted;    //!<
    double d_minBase;   //!<
    double d_maxBase;   //!<
    int d_baseTicks;    //!<

};

#endif
