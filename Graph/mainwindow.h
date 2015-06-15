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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Подключение заголовочных файлов "Графической части проекта"
#include "plots.h"
#include "Graph/control_box.h"
#include "Graph/checked_frame.h"
#include "Graph/record_group_box.h"
#include "Graph/denoised_group_box.h"

// Подключение заголовочных файлов "Функциональной части проекта"
#include "Functional/SFBS/stream_device.h"
#include "Functional/SFBS/Handlers/Worker/worker_manager.h"
#include "Functional/SFBS/Handlers/Worker/Behaviors/Handlers/handler_behavior.h"
#include "Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/exchanger_behavior.h"
#include "Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/afcDecorator/amplitude_extract.h"

// Подключение заголовных файлов библиотеки Qt
#include <QMainWindow>
#include <QProgressBar>
#include <QTranslator>
#include <QTimer>

namespace Ui {
    class MainWindow;
}

/*!
 * \brief          Класс MainWindow является производным от QMainWindow.
 * \detailed       Данный класс является основным для графической
 *                 части проекта. Он реализует управление сложными классами
 *                 и различными фабричными функциями для гибкого создания
 *                 сложных классов.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef QPair<QString,QString> langPair;            //!< Синоним, представляет наименование языка и файл qm.
    typedef QMap<QLocale::Language, langPair> langMap;   //!< Синоним для карты языков.
    typedef QMap<QString, QLocale::Language> localeMap;  //!< Синоним для карты локали языков.

    /*! Возможные типы окон.
     *  Необходимы для фабричных функций.
     */
    enum PlotType
    {
        None,          /*!< Пустой тип окна */
        AFC,           /*!< Окно для отображения АЧХ данных */
        Playback,      /*!< Окно для воспроизведения записанного сигнала */
        Standart       /*!< Окно для отображения входного сигнала в реальном режиме */
    };    

    /*!
     * \brief Конструктор класса MainWindow.
     * \param[in] parent Владелец объектом (см. http://qt-project.org/doc/qt-4.8/objecttrees.html)
     */
    explicit MainWindow(QWidget *parent = 0);

    /*!
     * \brief Деструктор класса MainWindow.
     */
    ~MainWindow();

protected:
    /*!
     * \brief Переопределенный метод родительского класса
     *        для обработки событий типа "Изменение".
     * \param[in] event Указатель на структуру QEvent.
     */
    virtual void changeEvent(QEvent *event);

private slots:
    /*!
     * \brief Слот реализует управление для открытия
     *        новых устройств\задач и закрытие посредством
     *        вызова слотов deleteIPCPanels().
     */
    void streamOpenClose();

    /*!
     * \brief Слот реализует включение панели "Проверка рампы".
     * \param[in] val Флаг включения\выключения.
     */
    void setRampHandler(bool val);

    /*!
     * \brief Слот реализует управление объектом "Процесс АЧХ",
     *        который отображает процесс извлечения (в процентах)
     *        АЧХ из входного сигнала.
     * \param[in] val Текущая частота дискретизации.
     */
    void setValRecordBar(ulong val);

    /*!
     * \brief Слот реализует функционал для смены языка, задавая
     *        объекту QTranslator необходимые параметры.
     * \param[in] val Текущий язык.
     */
    void setLanguage(QAction *val);

    /*!
     * \brief Слот реализует создание АЧХ окна на основе
     *        выбранных параметров из графической части
     *        проекта.
     */
    void setAFCWindow();

    /*!
     * \brief Слот реализует создание "Дополнительного" окна
     *        на основе выбранных параметров из графической части
     *        проекта. К примеру, окна проигрывания записанного ранее
     *        сигнала.
     */
    void setFilterWindow();

    /*!
     * \brief Слот реализует функционал для установки IPC виджетов
     *        в новые вкладки на основной графической части проекта.
     *
     * \param[in] widget Виджет IPC панели.
     * \param[in] name   Имя новой вкладки.
     */
    void setIPCWidget(QWidget *widget, const QString& name);

    /*!
     * \brief Слот реализует функционал для включения\отключения
     *        отдельных графических объектов на основном виджете
     *        в зависимости от текущего состояния входного потока.
     *        Т.е. если поток генерируется, то вкладки обработки
     *        становятся активными для работы.
     */
    void setEnableObjects();

signals:
    /*!
     * \brief Сигнал применяется в случае завершения
     *        работы генерации входного потока, т.е. когда
     *        закрываются все устройства и реализует удаление
     *        IPC панелей.
     */
    void deleteIPCPanels();

    /*!
     * \brief Вызывает деструктор специального объекта, который
     *        высчитывает ошибки в сигнале типа "Пила\Рампа".
     */
    void deleteRampHandler();

    /*!
     * \brief Сигнал позволяет очистить данные из всех
     *        графических окон, сбросив их параметры.
     */
    void clearAllData();

private:
    /*!
     * \brief Копирующий конструктор класса MainWindow.
     * \param[in] b Ссылка на копируемый объект.
     */
    MainWindow(const MainWindow& b);

    /*!
     * \brief Оператор копирующего присваивания.
     * \param[in] b Ссылка на копируемый объект.
     * \return Ссылка на новый объект.
     */
    MainWindow& operator=(const MainWindow& b);

    /*!
     * \brief Метод необходим для проверки доступных
     *        устройств в системе и добавления их
     *        в объект CheckedFrame.
     */
    void checkDevices();

    /*!
     * \brief Метод реализует функции по инициализации
     *        графической части проекта и созданию
     *        связей между объектами.
     */
    void initGraphics();

    /*!
     * \brief Дополнительный метод, который инциализирует
     *        библиотеку Intel PP и Intel MKL.
     */
    void initOthers();

    /*!
     * \brief Метод реализует сценарий для добавления
     *        доступных языков в объект QTranslator.
     */
    void initLanguages();

    /*!
     * \brief Фабричный метод для создания графических окон.
     * \param[in] plot_t    Тип создаваемого окна.
     * \param[in] handler_t Тип обработчика данных для окна.
     * \param[in] ampl_t    Тип дополнительного обработчика АЧХ данных.
     * \return              Графическое окно типа PlotType.
     */
    QwtPlot* createPlot(PlotType plot_t = Standart,
                        HandlerBehavior::Type handler_t = HandlerBehavior::ShortAFC,
                        AmplitudeExtract::dBModType ampl_t = AmplitudeExtract::NORMAL);

    /*!
     * \brief Фабричный метод для создания обработчика данных
     *        для графических окон.
     * \param[in] handler_t Тип обработчика данных.
     * \param[in] mod_t     Тип дополнительного обработчика АЧХ данных.
     * \param[in] plot      Объект графического окна для создания необходимых связей
     *                      между обработчиком и окном.
     * \return              Обработчик данных типа HandlerBehavior::Type.
     */
    HandlerBehavior* createHandler(HandlerBehavior::Type handler_t,
                                   AmplitudeExtract::dBModType mod_t = AmplitudeExtract::NORMAL,
                                   QwtPlot *plot = 0);

    /*!
     * \brief Фабричный метод для создания обработчика данных, который
     *        выполняет различные преобразования над данными. К примеру,
     *        переводит уровни в вольты.
     * \param[in] exchange_t    Тип обработчика данных.
     * \return                  Обработчик данных типа ExchangerBehavior::Type.
     */
    ExchangerBehavior* createExchanger(ExchangerBehavior::Type exchange_t);

    /*!
     * \brief Фабричный метод для создания класса по управлению
     *        объектами типа WorkerBehavior.
     * \param[in] worker_t  Тип менеджера объектов.
     * \return              Менеджер объектов типа WorkerManager::Type.
     */
    WorkerManager* createManager(WorkerManager::Type worker_t = WorkerManager::Empty);

    /*!
     * \brief Фабричный метод для создания класса по управлению
     *        входным потоком данных.
     * \param[in] stream_t  Тип управляющего класса.
     * \return              Класс управления входным потоком данных типа StreamDevice::Type.
     */
    StreamDevice* createStream(StreamDevice::Type stream_t = StreamDevice::Empty);

    Ui::MainWindow *ui;                 //!< Класс хранит и управляет объектами в главного графического окна.
    RecordGroupBox *record_grp_bx;      //!< Объект управляет процессом записи входного сигнала.
    DenoisedGroupBox *denoised_grp_bx;  //!< Объект предостаялет управление для создания фильтров входного сигнала.
    ControlBox *control_box;            //!< Объект управляет процессом установки частоты обновления данных в окнах и многим другим.
    CheckedFrame *device_list;          //!< Объект позволяет выбирать устройства для потока данных.
    QwtPlot *main_window;               //!< Главное окно для отображения входных данных.
    QwtPlot *optional_window;           //!< Дополнительные окна.
    AFCPlot *afc_window;                //!< Окно для отображения АЧХ данных.

    StreamDevice *signal_stream;        //!< Объект для управления входным потоком.
    WorkerManager *worker_stream;       //!< Объект управляет обработчиками данных.

    langMap support_languages;          //!< Доступные языки.
    localeMap to_qlocale;               //!< Структура позволяет выполнять преобразования из QString в QLocale::Language.
    QTranslator translator;             //!< Объект предоставляет управление языками в проекте.
    QString language_path;              //!< Пути к файлам поддерживаемых языков.

};

#endif // MAINWINDOW_H
