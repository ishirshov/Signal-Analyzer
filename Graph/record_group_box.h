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

#ifndef RECORD_GROUP_BOX_H
#define RECORD_GROUP_BOX_H

// Подключение заголовных файлов библиотеки Qt
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>
#include <QEvent>
#include <QProgressBar>

class ResolutionBox;
class PlaybackSettings;

/*!
 * \brief       Класс RecordGroupBox является производным от QGroupBox.
 * \detailed    Реализует графический виджет для упрощенного 
 *              управления функциями записи, позволяет манипулировать
 *              текущими записями, отслеживать состояние памяти и 
 *              выводить результат в окно отображения. 
 */
class RecordGroupBox : public QGroupBox
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса RecordGroupBox.
     * \param[in] parent Владелец объектом (см. http://qt-project.org/doc/qt-4.8/objecttrees.html)
     */
    explicit RecordGroupBox(QWidget *parent = 0);

signals:
    /*!
     * \brief   Сигнал реализует функцию по записи 
     *          выбранной записи сигнала на диск.
     * \param[in] name Имя записи.
     */
    void dumpToFile(const QString& name);

    /*!
     * \brief   Сигнал реализует функцию по удалению
     *          выбранной записи сигнала.
     * \param[in] name Имя записи.
     */
    void removeRecord(const QString& name);

    /*!
     * \brief   Сигнал реализует функцию по отображению
     *          выбранной записи сигнала в окне отображения.
     * \param[in] name Имя записи.
     * \param[in] params Параметры отображения выбранного сигнала.
     */
    void showRecord(const QString& name, PlaybackSettings* params);
    
    /*!
     * \brief   Сигнал реализует функцию по записи текущего
     *          входного потока в выделенную память.
     * \param[in] flag Состояние записи.
     * \param[in] freq Текущая частота дискретизации.
     */
    void recordSignal(bool flag, ulong freq);

public slots:
    /*!
     * \brief   Слот позволяет обновить список доступных
     *          записей сигнала для дальнейших манипуляций.
     * \param[in] rcd_list Список с именами записей.
     */
    void setRecordList(const QStringList &rcd_list);
    
    /*!
     * \brief   Слот устанавливает текущую ширину
     *          окна отображения графиков.
     * \param[in] width Ширина окна.
     */
    void setWindowWidth(quint32 width);
    
    /*!
     * \brief   Слот устанавливает текущую частоту
     *          дискретизации сигнала.
     * \param[in] name Частота дискретизации сигнала.
     */
    void setSamplingFrequency(ulong);
    
    /*!
     * \brief   В случае, если запись сигнала была
     *          начата, то данный слот принимает
     *          флаг о начале/конце записи и меняет
     *          надпись кнопки.
     * \param[in] flag Состояние функции записи (записывает/не записывает).
     */
    void setRecordFlag(bool flag);
    
    /*!
     * \brief   Слот управляет объектом aval_space_bar,
     *          который в свою очередь отображает объём доступного
     *          места для хранения записи.
     * \param[in] space Кол-во свободного места.
     */
    void setAvailableSpace(int space);
    
    /*!
     * \brief   Слот управляет объектом work_prog_bar,
     *          который в свою очередь отображает процесс
     *          подготовки записи для отображения/дампа.
     * \param[in] min Минимальное значение для индикатора процесса.
     */
    void setWorkBarMinimum(int min);
    
    /*!
     * \brief   Слот управляет объектом work_prog_bar,
     *          который в свою очередь отображает процесс
     *          подготовки записи для отображения/дампа.
     * \param[in] max Максимальное значение для индикатора процесса.
     */
    void setWorkBarMaximum(int max);

    /*!
     * \brief   Слот управляет объектом work_prog_bar,
     *          который в свою очередь отображает процесс
     *          подготовки записи для отображения/дампа.
     * \param[in] curr Текущее значение процесса для индикатора процесса.
     */
    void setWorkBarValue(int curr);

    /*!
     * \brief   Слот управляет объектом aval_space_bar,
     *          который в свою очередь отображает объём доступного
     *          места для хранения записи.
     * \param[in] space Текущее кол-во свободного места.
     */
    void setSpaceValue(int space);

private slots:
    /*!
     * \brief   Слот инициируется в момент нажатия кнопки
     *          "Write to disk". Позволяет выполнить запись
     *          текущего сигнала на диск.
     */
    void dumpButtonPressed();

    /*!
     * \brief   Слот инициируется в момент нажатия кнопки
     *          "Remove". Позволяет удалить текущую запись.
     */
    void removeButtonPressed();

    /*!
     * \brief   Слот инициируется в момент нажатия кнопки
     *          "Show". Позволяет вывести текущую запись
     *          на графическое окно.
     */
    void showButtonPressed();

    /*!
     * \brief   Слот инициируется в момент нажатия кнопки
     *          "Start record". Позволяет выполнить запись
     *          сигнала с текущей частотой дискретизации.
     */
    void recordButtonPressed();

    /*!
     * \brief   Слот позволяет скрыть индикатор процесса
     *          подготовки записи, после выполнения
     *          работы.
     */
    void hideWorkBar();

    /**
     * \brief Переопределенный метод родительского класса
     *        для обработки событий типа "Изменение".
     * \param[in] event Указатель на структуру QEvent.
     */
    void changeEvent(QEvent *event);

private:
    QLabel *record_lbl;             //!< Надпись "Название записи".
    QComboBox *record_cmb;          //!< Список с доступными записями.
    ResolutionBox *res_box;         //!< Виджет делителя частоты и частоты сканирования.

    QPushButton *dump_btn;          //!< Кнопка записи сигнала на диск.
    QPushButton *remove_btn;        //!< Кнопка удаления записи сигнала из Heap.
    QPushButton *show_btn;          //!< Кнопка отображения записи сигнала.
    QPushButton *record_btn;        //!< Кнопка записи сигнала.

    QLabel *aval_space_lbl;         //!< Надпись "Доступное место".
    QProgressBar *aval_space_bar;   //!< Индикатора доступного места.
    QLabel *work_prog_lbl;          //!< Виджет надписи для инидкатора процесса.
    QProgressBar *work_prog_bar;    //!< Индикатор процесса.

    quint32 window_size;            //!< Текущая ширина граф. окна.
    ulong sampling_freq;            //!< Текущая частота дискретизации.
    bool signal_recording;          //!< Флаг записи сигнал.
    bool signal_dumping;            //!< Флаг записи выбранной записи сигнала на диск.
    bool signal_preparing;          //!< Флаг подготовки отображения сигнала.

    QString danger_stylesheet;      //!< Таблица стилей для индикатора доступного места (красный индикатор).
    QString safe_stylesheet;        //!< Таблица стилей для индикатора доступного места (зеленый индикатор).

};

#endif // RECORD_GROUP_BOX_H
