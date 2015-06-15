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

#ifndef DENOISED_GROUP_BOX_H
#define DENOISED_GROUP_BOX_H

// Подключение заголовных файлов библиотеки Qt
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QEvent>

/*!
 * \brief       Класс DenoisedGroupBox является производным от QGroupBox.
 * \detailed    Реализует графический виджет для упрощенного 
 *              управления функциями фильтрации, позволяет выбирать
 *              и создавать тип композитного фильтра. 
 */
class DenoisedGroupBox : public QGroupBox
{
    Q_OBJECT

public:
    enum filterType
    {
        None,               //!< Пустой тип фильтра
        Median,             //!< Медианный фильтр
        Kalman,             //!< Фильтр Каллмана 
        WaveletSoft,        //!< Вейвлетное софт преобразование 
        WaveletHyperbolic   //!< Вейвлетное гиперболическое преобразование
    };

    /*!
     * \brief Конструктор класса DenoisedGroupBox.
     * \param[in] parent Владелец объектом (см. http://qt-project.org/doc/qt-4.8/objecttrees.html)
     */
    explicit DenoisedGroupBox(QWidget *parent = 0);

signals:
    /*!
     * \brief Сигнал вызывается в момент назначения нового фильтра.
     * \param[in] filter_t Новый тип фильтра.
     */
    void filterTypeChanged(DenoisedGroupBox::filterType filter_t);

private slots:
    /*!
     * \brief   Слот реализует функцию влючения\отключения вейвлетных
     *          преобразований.
     * \param[in] flag Выбраны ли вейвлет преобразования.
     */
    void setWaveletTransform(bool flag);

    /*!
     * \brief   Слот реализует функцию по созданию типа фильтра
                в виде типа filterType и активации необходимых
                графических элементов.
     * \param[in] val Тип текущего фильтра.
     */
    void setFilterFunction(int val);

    /*!
     * \brief   Слот реализует функцию по установке банка фильтра
                для вейвлет преобразования.
     * \param[in] val Индекс банка фильтров.
     */
    void setFilterBanks(int val);

    /*!
     * \brief   Слот реализует функцию включения\отключения создания
                композитных фильтров. Срабатывает, когда активируется
                панель.
     * \param[in] flag Состояние панели.
     */
    void checkedToggled(bool flag);

    /*!
     * \brief   Переопределенный метод родительского класса
     *          для обработки событий типа "Изменение".
     * \param[in] event Указатель на структуру QEvent.
     */
    void changeEvent(QEvent *event);

private:
    QCheckBox *chk_wavelet_transf;      //!< Доступные типы вейвлет преобразования.

    QLabel *lbl_filter_func;            //!< Надпись "Фильтры".
    QComboBox *cmb_filter_func;         //!< Доступные функции фильтров.

    QLabel *lbl_filter_bank;            //!< Надпись "Банк фильтров".
    QComboBox *cmb_filter_bank;         //!< Доступные банки фильтров для вейвлет преобразований.

    QLabel *lbl_level_transf;           //!< Надпись "уровень преобразования".
    QSpinBox *spn_level_transf;         //!< Доступные уровни вейвлет преобразований.

    QLabel *lbl_median_kernel;          //!< Надпись "значение K медианы".
    QSpinBox *spn_median_kernel;        //!< Доступные значения "ядра" для медианного фильтра.

    QLabel *lbl_kalman_gain;            //!< Надпись "усиление Каллмана".
    QDoubleSpinBox *spn_kalman_gain;    //!< Доступные значения для фильтра Калламана.

    QMap<int, QString> filter_map;      //!< Используется для преобразования индекса фильтра в текстовое значение.
    QMap<int, QString> wavelet_map;     //!< Используется для преобразования индекса типа вейвлет преобразования в его строковое значение.

};

#endif // DENOISED_GROUP_BOX_H
