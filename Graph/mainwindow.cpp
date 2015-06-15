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

// Подключение заголовочных файлов "Функциональной части проекта"
#include "Functional/SFBS/streams.h"
#include "Functional/SFBS/Handlers/managers.h"
#include "Functional/SFBS/Channels/IPCPanels/fpga_panel.h"
#include "Functional/SFBS/Handlers/Worker/Behaviors/handlers.h"
#include "Functional/SFBS/Handlers/Worker/Behaviors/exchangers.h"
#include "Functional/SFBS/Channels/Observer/thread_bridge_rx.h"

// Подключение заголовочных файлов "Графической части проекта"
#include "mainwindow.h"
#include "ui_mainwindow.h"

// Подключение заголовных файлов библиотеки Qwt
#include <qwt_wheel.h>
#include <qwt_text_label.h>

// Подключение заголовных файлов библиотеки Intel MKL
#include <mkl_service.h>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,record_grp_bx(new RecordGroupBox(this))
    ,denoised_grp_bx(new DenoisedGroupBox(this))
    ,control_box(new ControlBox(this))
    ,device_list(new CheckedFrame(this))
    ,main_window(0)
    ,optional_window(0)
    ,afc_window(0)
    ,signal_stream(0)
    ,worker_stream(0)
{
    /* Первичная инициализация графических объектов на главное форме.
     * Должна быть самой первой, т.к. от этого объекта зависят все остальные. */
    ui->setupUi(this);

    /* Создание объектов по управлению потоковых устройств
     * и объектами обработки данных. */
    signal_stream = createStream(StreamDevice::Channel);
    worker_stream = createManager(WorkerManager::Multiplier);

    /* Дальнейшая инициализация класса MainWindow. */
    initLanguages();
    initGraphics();
    initOthers();
}

MainWindow::~MainWindow()
{
    /* Необходимо удалять, т.к. объект не имеет родителя.
     * Остальные объекты класса, будут удалены после удаления родителя. */
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    /* Обработка события по смене языка. */
    if(event->type() == QEvent::LanguageChange)
        checkDevices();

    QMainWindow::changeEvent(event);
}

void MainWindow::streamOpenClose()
{
    /* В случае, если список устройств активен,
     * что означает, что потоковая обработка не запущена
     * можно создавать новые устройства. */
    if(device_list->isEnabled())
    {
        QStringList tasks = device_list->getCheckedItems();

        if(tasks.size())
        {
            /* Если список устройств не пуст. */
            if(tasks[0] != tr("No device"))
            {
                /* Поочередное создание устройств */
                quint32 tasks_size = tasks.size();
                for(int i = 0; i < tasks_size; ++i)
                    signal_stream->setDeviceName(tasks[i]);
            }
            else checkDevices();
        }
    }
    else {
        /* В ином случае, необходимо закрыть все открытые
         * устройства и удалить все созданные IPC панели. */
        emit deleteIPCPanels();
    }
}

void MainWindow::setRampHandler(bool flag)
{
    /* Включение QFrame объекта, где распологается панель
     * отображения результатов подсчета ошибок в сигнале типа "Пила". */
    ui->chk_frame->setEnabled(flag);
    ui->chk_frame->setVisible(flag);

    if(flag)
    {
        /* Создание обработчика для подсчета ошибок в сигнале типа "Пила". */
        HandlerBehavior *behavior = createHandler(HandlerBehavior::RampChecker);

        connect(this, SIGNAL(deleteRampHandler()), behavior, SLOT(deleteLater()), Qt::QueuedConnection);

        worker_stream->addWorker(behavior);
    }
    else emit deleteRampHandler();
}

void MainWindow::setValRecordBar(ulong freq)
{
    ui->progressBar->setMaximum(int(freq/2));
}

void MainWindow::setLanguage(QAction *action)
{
    /* Получение QLocacle::Language типа из карты соответствия языков. */
    QLocale::Language lang = to_qlocale[action->text()];
    QString lang_file = support_languages[lang].second;
    statusBar()->setLocale(lang);

    /* Установка нового языка. */
    translator.load(lang_file, language_path);
    ui->retranslateUi(this);    
}

void MainWindow::setAFCWindow()
{
    delete afc_window;
    afc_window = 0;

    /* Сценарий создания АЧХ окна. */
    if(ui->afc_frame->isChecked())
    {
        /* В зависимости от генерирующего устройства, необходимо
         * устанавить определенные критерии извлечения АЧХ сигнала. */
        QString dev_t = signal_stream->getDeviceType();
        AmplitudeExtract::dBModType mod_t = (dev_t == "FPGA")?
                                            (AmplitudeExtract::FPGA):
                                            (AmplitudeExtract::NORMAL);

        /* Определить тип функции извлечения АЧХ сигнала (широкий диапазон или короткий). */
        HandlerBehavior::Type behavior_t = (ui->btn_short_range->isChecked())?
                                           (HandlerBehavior::ShortAFC):
                                           (HandlerBehavior::WideAFC);

        /* Создать окно АЧХ. */
        afc_window = static_cast<AFCPlot*>(createPlot(AFC, behavior_t, mod_t));

        /* Прикрепить окно к виджету MainWindow. */
        QHBoxLayout *frame_layout = dynamic_cast<QHBoxLayout*>(ui->plot_frame->layout());
        frame_layout->addWidget(afc_window, 10);

        /* Установка значения по умолчанию для оконной функции (альфа). */
        ui->spnbox_window_alpha->setValue(0.16);

        /* В зависимости от типа функции АЧХ, включается и выключается прогресс бар. */
        ui->afc_progress_frame->setVisible((behavior_t == HandlerBehavior::WideAFC)?(true):(false));
    }
    else {
        ui->afc_progress_frame->setVisible(false);
    }
}

void MainWindow::setFilterWindow()
{
    delete optional_window;
    optional_window = 0;

    /* Если выбрана функция записи сигнала. */
    if(record_grp_bx->isChecked())
    {
       /* Создать окно проигрывания сигнала. */
       optional_window = createPlot(Playback);

       /* Прикрепить окно к виджету MainWindow. */
       QHBoxLayout *frame_layout = dynamic_cast<QHBoxLayout*>(ui->plot_frame->layout());
       frame_layout->addWidget(optional_window, 10);
    }

    this->repaint();
}

void MainWindow::setIPCWidget(QWidget *ipc_widget, const QString& ipc_name)
{
    if(!ipc_widget) return;

    /* Новый IPC виджет будет помещен в объект для
     * корректного отображения на вкладке. tab_widget служит объектом
     * QFrame. */
    QWidget *tab_widget = new QWidget(this);
    QVBoxLayout *tab_layout = new QVBoxLayout;
    tab_layout->addWidget(ipc_widget);
    tab_layout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding));

    /* Добавить новый IPC виджет на вкладку окна MainWindow. */
    tab_widget->setLayout(tab_layout);
    ui->filter->addTab(tab_widget, ipc_name);

    connect(this, SIGNAL(deleteIPCPanels()), tab_widget, SLOT(deleteLater()));
    connect(tab_widget, SIGNAL(destroyed()), SLOT(setEnableObjects()), Qt::QueuedConnection);

    setEnableObjects();
}

void MainWindow::setEnableObjects()
{
    bool is_enable = false;
    /* Если кол-во вкладок > 3, значит можно
     * активировать вкладки остальные вкладки
     * и объекты обработки данных */
    if(ui->filter->count() > 3)
        is_enable = true;

    device_list->setEnabled(!is_enable);
    control_box->setEnabled(is_enable);
    ui->advanced_tab->setEnabled(is_enable);
    ui->denoised_tab->setEnabled(is_enable);

    if(is_enable)
        ui->open_close_stream->setText(tr("Detach from task"));
    else
    {
        /* В ином случае избавляемся от
         * всех созданных вкладок и данных в окнах. */
        emit clearAllData();
        emit deleteIPCPanels();

        ui->open_close_stream->setText(tr("Attach to task"));
    }
}

void MainWindow::checkDevices()
{
    /* Получаем список доступных для работы устройств. */
    QStringList devs = signal_stream->getDeviceList();

    device_list->clear();
    device_list->addItems(devs);

    /* Определение роли кнопки. */
    if(!devs.size() || (devs[0] == tr("No device")))
    {
        device_list->setEnabled(false);
        ui->open_close_stream->setText(tr("Refresh"));
    }
    else
    {
        device_list->setEnabled(true);
        ui->open_close_stream->setText((device_list->isEnabled())?(tr("Attach to task")):(tr("Detach from task")));
    }
}

void MainWindow::initGraphics()
{
    /* Создаем сетки для графических окон.
     * Т.к. изначально её несуществует. */
    ui->plot_frame->setLayout(new QHBoxLayout(ui->plot_frame));
    ui->plot_frame->layout()->setSizeConstraint(QLayout::SetNoConstraint);
    ui->afc_progress_frame->setVisible(false);
    ui->chk_frame->setVisible(false);

    /* Деактивация всех вкладок на этапе инициализации. */
    control_box->setEnabled(false);
    ui->advanced_tab->setEnabled(false);
    ui->denoised_tab->setEnabled(false);

    /* Добавление кастомных графических объектов
     * на свои места. */
    QLayout *layout = ui->record_frame->layout();
    layout->addWidget(record_grp_bx);
    layout = ui->control_frame->layout();
    layout->addWidget(control_box);
    layout = ui->denoised_frame->layout();
    layout->addWidget(denoised_grp_bx);
    layout = ui->devices_frame->layout();
    layout->addWidget(device_list);

    /* Создание главного окна для отображения данных. */
    main_window = createPlot(Standart);

    QHBoxLayout *frame_layout = dynamic_cast<QHBoxLayout*>(ui->plot_frame->layout());
    frame_layout->insertWidget(0, main_window, 10);

    connect(&GlobalVariables::getInstance(), SIGNAL(rampSignalStyleDetected(bool)), SLOT(setRampHandler(bool)));
    connect(&GlobalVariables::getInstance(), SIGNAL(samplingFrequencyChanged(ulong)), record_grp_bx, SLOT(setSamplingFrequency(ulong)));
    connect(&GlobalVariables::getInstance(), SIGNAL(samplingFrequencyChanged(ulong)), SLOT(setValRecordBar(ulong)));
    connect(record_grp_bx, SIGNAL(clicked()), SLOT(setFilterWindow()));
}

void MainWindow::initOthers()
{
    /* Информация о Qt. */
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    /* Инициализация библиотеки Intel PP. */
    ippInit();

    // Get info.
    const int len = 198;
    char mkl_version[len];
    MKL_Get_Version_String(mkl_version, len);

    const IppLibraryVersion *ipp_version = ippsGetLibVersion();

    printInfo(QString("Intel MKL version: %1.").arg(mkl_version));
    printInfo(QString("Intel PP version: %2.").arg(ipp_version->Version));
}

void MainWindow::initLanguages()
{
    /* Инициализация карты доступных языков.
     * Необходимо только добавить пару значений:
     * <Language ID,<Language description,Language file>>
     * а сценарий сам выполнит добавление.
     */
    support_languages.insert(QLocale::English,langPair("English","en_US.qm"));
    support_languages.insert(QLocale::Russian,langPair("Русский","ru_RU.qm"));

    QScopedPointer<QMenu> langMenu_guard(new QMenu(this));
    QScopedPointer<QActionGroup> langGroup_guard(new QActionGroup(ui->actionLanguage));

    /* Можно выбрать только один язык из группы. */
    langGroup_guard->setExclusive(true);

    /* Определяем путь к директории языков. */
    language_path = QApplication::applicationDirPath();
    language_path.append("/languages");
    langPair lang_file = support_languages[QLocale::system().language()];

    /* Если язык не поддерживается проектов,
     * то загрузиться стандартный язык. */
    if(lang_file == langPair())
        lang_file = support_languages[QLocale::English];

    QMenu *lang_menu = langMenu_guard.data();
    QActionGroup *lang_group = langGroup_guard.data();

    connect(lang_group, SIGNAL(triggered(QAction*)), SLOT(setLanguage(QAction*)));

    langMap::Iterator lang_iter = support_languages.begin();
    langMap::Iterator lang_end = support_languages.end();

    /* Инициализация языковой группы. */
    for(; lang_iter != lang_end; ++lang_iter)
    {
        /* Получить текущий язык из итератора. */
        langPair lang = lang_iter.value();

        /* Находим иконку для языка. */
        QString ico_name = "ico/" + lang.second;
        ico_name.remove(6, ico_name.size());
        ico_name = QString("%1/%2.png").arg(language_path).arg(ico_name);

        /* Добавляем в карту соответствия пару значения для преобразования. */
        to_qlocale.insert(lang.first, lang_iter.key());

        /* Создаем новую опцию языка или выбор. */
        QScopedPointer<QAction> action(new QAction(QIcon(ico_name), lang.first, lang_menu));
        action->setCheckable(true);

        /* Если язык из итератора является текущим языком, то ставим галочку. */
        if(lang.first == lang_file.first)
            action->setChecked(true);

        /* И добавляем выбор языка в общую группу языков. */
        lang_group->addAction(action.take());
    }

    /* Далее группа добавляется в меню языков. */
    lang_menu->addActions(lang_group->actions());

    ui->actionLanguage->setMenu(langMenu_guard.take());
    ui->actionLanguage->setActionGroup(langGroup_guard.take());

    translator.load(lang_file.second,language_path);
    qApp->installTranslator(&translator);    
    ui->retranslateUi(this);
}

ExchangerBehavior* MainWindow::createExchanger(ExchangerBehavior::Type type)
{
    switch(type)
    {
    case ExchangerBehavior::Standart:
        return new StandartExchanger;
    case ExchangerBehavior::Playback:
        return new PlaybackExchanger;
    default:
        return new EmptyExchanger;
    };
}

HandlerBehavior* MainWindow::createHandler(HandlerBehavior::Type type, AmplitudeExtract::dBModType mod_type, QwtPlot *plot)
{
    /* Фабричный метод позволяет собрать гибкий класс для решения задачи по извлечению
     * АЧХ данных. Классы, все до единого реализуют паттерн "Декоратор", что позволяет
     * наделить декорируемый класс новыми возможностями. */
    QScopedPointer<ComputeModule> mod(new WindowFunction);

    /* Все начинается с класса WindowFunction, т.к. он является 
     * декорируемым классом. */
    WindowFunction *win_ptr = static_cast<WindowFunction*>(mod.data());
    connect(ui->cmb_window_function, SIGNAL(currentIndexChanged(int)), win_ptr, SLOT(setWindowType(int)), Qt::QueuedConnection);
    connect(ui->spnbox_window_alpha, SIGNAL(valueChanged(double)), win_ptr, SLOT(setWindowAlpha(double)), Qt::QueuedConnection);

    QScopedPointer<HandlerBehavior> behavior;

    /* Далее в зависимости от выбранного типа АЧХ функции
     * создаются декоративные модули. Важно понимать, что здесь
     * создаются обработчики данных, а не обработчики для преобразования
     * данных. */
    switch(type)
    {
    case HandlerBehavior::ShortAFC:
    {
        AFCPlot *afc_plot = static_cast<AFCPlot*>(plot);

        /* При создании выходит так, что один модуль вкладывается в другой модуль,
         * что позволяет расширить базовые возможности класса. */
        mod.reset(new AmplitudeExtract(new ippFFTFWD(mod.take()), mod_type));
        connect(afc_plot, SIGNAL(settingsChanged(quint32)), mod.data(), SLOT(plotSettingsChanged(quint32)), Qt::QueuedConnection);
        afc_plot->sendInitialSettings();
        behavior.reset(new ShortRangeAfc(mod.take()));
        break;
    }
    case HandlerBehavior::WideAFC:
    {
        AFCPlot *afc_plot = static_cast<AFCPlot*>(plot);

        mod.reset(new AmplitudeExtract(new mklFFTFWD(mod.take()), mod_type));
        connect(afc_plot, SIGNAL(settingsChanged(quint32)), mod.data(), SLOT(plotSettingsChanged(quint32)), Qt::QueuedConnection);
        afc_plot->sendInitialSettings();

        behavior.reset(new WideRangeAfc(mod.take()));
        connect(&GlobalVariables::getInstance(), SIGNAL(samplingFrequencyChanged(ulong)), behavior.data(), SLOT(setSamplingFrequency(ulong)), Qt::QueuedConnection);
        connect(behavior.data(), SIGNAL(valueChanged(int)), ui->progressBar, SLOT(setValue(int)), Qt::QueuedConnection);
        break;
    }
    case HandlerBehavior::RampChecker:
    {
        /* Кроме этого класса, конечно. Он не реализует
         * паттерн проектирования "Декоратор". Он просто имплементирует
         * общий интерфейс. */
        behavior.reset(new RampChecker);

        connect(&GlobalVariables::getInstance(), SIGNAL(samplingFrequencyChanged(ulong)), behavior.data(), SLOT(setSamplingFrequency(ulong)), Qt::QueuedConnection);
        connect(ui->chk_frame, SIGNAL(clicked(bool)), behavior.data(), SLOT(setAcceptToStore(bool)), Qt::QueuedConnection);

        RampChecker *rmp_checker = static_cast<RampChecker*>(behavior.data());
        connect(rmp_checker, SIGNAL(checkedBuffersChanged(int)), ui->lcd_num_chk_buff, SLOT(display(int)), Qt::QueuedConnection);
        connect(rmp_checker, SIGNAL(brokenBuffersChanged(int)), ui->lcd_num_err_buff, SLOT(display(int)), Qt::QueuedConnection);
        connect(rmp_checker, SIGNAL(durationTimeChanged(QString)), ui->lcd_duration_tm, SLOT(display(QString)), Qt::QueuedConnection);
        connect(rmp_checker, SIGNAL(lostInSession(QString)), ui->lcd_lost_session, SLOT(display(QString)), Qt::QueuedConnection);
        connect(rmp_checker, SIGNAL(lostInPeriod(QString)), ui->lcd_lost_period, SLOT(display(QString)), Qt::QueuedConnection);
        break;
    }
    default:
        /* Каждый интерфейс должен иметь класс пустышку,
         * чтобы избежать проблемы с нулевыми указателями. */
        behavior.reset(new EmptyHandler);
        break;
    };

    /* Первичная инициализация модулей. */
    behavior->setSamplingFrequency(GlobalVariables::getInstance().getSamplingFrequency());
    return behavior.take();
}

WorkerManager* MainWindow::createManager(WorkerManager::Type type)
{
    QScopedPointer<WorkerManager> manager;

    switch (type)
    {
    case WorkerManager::Pipeline:
        manager.reset(new WorkerPipeline(this));
        break;
    case WorkerManager::Multiplier:
        manager.reset(new DataMultiplier(this));
        break;
    default:
        manager.reset(new EmptyManager(this));
        break;
    };

    /* Подключение объекта ThreadRxBridge к менеджеру объектов для передачи
     * входного потока обработчикам данных и преобразователям. */
    connect(&ThreadRxBridge::getInstance(), SIGNAL(emitSendBufferData(ipp_vector<Ipp16s>)),
                            manager.data(), SIGNAL(receiveData(ipp_vector<Ipp16s>)), Qt::QueuedConnection);

    /* Функция отброса данных. Отключает обработку. */
    connect(ui->chk_reject_data, SIGNAL(toggled(bool)),
            &ThreadRxBridge::getInstance(), SLOT(setRejectData(bool)), Qt::QueuedConnection);

    return manager.take();
}

StreamDevice* MainWindow::createStream(StreamDevice::Type type)
{
    QScopedPointer<StreamDevice> stream;

    try {
        switch(type)
        {
        case StreamDevice::Channel:
            stream.reset(new SFBSChannels(this));
            break;
        case StreamDevice::User:
            stream.reset(new UserStream(this));
            break;
        default:
            stream.reset(new NoStream(this));
            break;
        }

        /* Создание класса для управления потоковыми устройствам, как раз он и
         * является тем классом, который создает новые IPC панели. */
        connect(stream.data(), SIGNAL(statusMessage(QString)), statusBar(), SLOT(showMessage(QString)));
        connect(stream.data(), SIGNAL(widgetChanged(QWidget*, QString)), SLOT(setIPCWidget(QWidget*, QString)));
    }
    catch(std::runtime_error &e) {
        /* Обработка исключения. Если не удалось создать класс SFBSChannels,
         * то необходимо его чем-то заменить. */
        stream.reset(createStream(StreamDevice::User));
    }

    return stream.take();
}

QwtPlot* MainWindow::createPlot(PlotType plot_t, HandlerBehavior::Type behavior_t, AmplitudeExtract::dBModType mod_t)
{
    QScopedPointer<QwtPlot> window;

    /* Одна из самых больших фабричных функций в проекте.
     * Реализует создание окон для отображения данных, использует
     * другие фабричные методы для конфигурации окон. */
    switch(plot_t)
    {
    case AFC:
    {
        /* Создание окна. */
        AFCPlot *plot = new AFCPlot(this);

        /* Как уже говорилось раньше, есть обработчики данных, а есть их
         * преобразователи. Так вот, каждое окно снабжается своим обработчиком данных или 
         * преобразователем. В конечном итоге данные будут переданы в окно с помощью этих обработчкиов. */
        QScopedPointer<HandlerBehavior> behavior(createHandler(behavior_t, mod_t, plot));

        /* Создание связей между обработчиком, глобальными данными и т.д. и т.п. */
        connect(&GlobalVariables::getInstance(), SIGNAL(samplingFrequencyChanged(ulong)), plot, SLOT(setSamplingFrequency(ulong)));
        connect(control_box, SIGNAL(rateValueChanged(short)), plot, SLOT(setUpdateTime(short)));
        connect(ui->box_num_peaks, SIGNAL(valueChanged(int)), plot, SLOT(setNumberPeaks(int)));
        connect(behavior.data(), SIGNAL(dataProcessed(ipp_vector<Ipp32f>)), plot, SLOT(addNewData(ipp_vector<Ipp32f>)), Qt::QueuedConnection);

        connect(plot, SIGNAL(destroyed()), behavior.data(), SLOT(deleteLater()), Qt::QueuedConnection);
        connect(plot, SIGNAL(storeFlagChanged(bool)), behavior.data(), SLOT(setAcceptToStore(bool)), Qt::QueuedConnection);
        connect(this, SIGNAL(clearAllData()), plot, SLOT(clearData()));

        /* Начальная инициализация. */
        plot->setNumberPeaks(ui->box_num_peaks->value());
        plot->setSamplingFrequency(GlobalVariables::getInstance().getSamplingFrequency());

        control_box->sendInitialValues();

        /* В конечном шаге, обработчик данных передается для
         * управления в менеджер таких объектов. */
        worker_stream->addWorker(behavior.take());

        static bool ok = false;
        if(behavior_t == HandlerBehavior::ShortAFC && !ok) {
            QMessageBox::warning(0, tr("Warning"), tr("In this mode, the definition of \nAFC short range from 1 KHz to 125 MHz."));
            ok = true;
        }

        window.reset(plot);
        break;
    }
    case Standart:
    {
        Plot *plot = new Plot(this);

        QScopedPointer<ExchangerBehavior> behavior(createExchanger(ExchangerBehavior::Standart));
        StandartExchanger *exchanger = static_cast<StandartExchanger*>(behavior.data());

        connect(control_box, SIGNAL(frequencyValueChanged(int)), plot, SLOT(setScanDivider(int)));
        connect(control_box, SIGNAL(dividerValueChanged(int)), plot, SLOT(setTimeDivider(int)));
        connect(control_box, SIGNAL(voltValueChanged(double)), plot, SLOT(setVoltsLevel(double)));
        connect(ui->offset_slider, SIGNAL(valueChanged(double)), plot, SLOT(setPhaseOffset(double)));
        connect(ui->phase_offset, SIGNAL(toggled(bool)), plot, SLOT(setPhaseDetect(bool)));
        connect(ui->chk_sig_transform, SIGNAL(toggled(bool)), plot, SLOT(setSignalTransform(bool)));
        connect(ui->chk_resampling_method, SIGNAL(toggled(bool)), plot, SLOT(setDecimateSignal(bool)));
        connect(&GlobalVariables::getInstance(), SIGNAL(samplingFrequencyChanged(ulong)), plot, SLOT(setSamplingFrequency(ulong)));
        connect(&GlobalVariables::getInstance(), SIGNAL(bufferSizeChanged(Ipp32s)), plot, SLOT(setBufferSize(Ipp32s)));
        connect(control_box, SIGNAL(rateValueChanged(short)), plot, SLOT(setUpdateTime(short)));
        connect(exchanger, SIGNAL(dataProcessed(ipp_vector<Ipp32f>)), plot, SLOT(addNewData(ipp_vector<Ipp32f>)), Qt::QueuedConnection);
        connect(denoised_grp_bx, SIGNAL(filterTypeChanged(DenoisedGroupBox::filterType)), plot, SLOT(setFilterType(DenoisedGroupBox::filterType)));

        connect(plot, SIGNAL(destroyed()), exchanger, SLOT(deleteLater()), Qt::QueuedConnection);
        connect(plot, SIGNAL(storeFlagChanged(bool)), exchanger, SLOT(setAcceptToStore(bool)), Qt::QueuedConnection);
        connect(plot, SIGNAL(mathModuleChanged(MathModule*)), exchanger, SLOT(setMathModule(MathModule*)), Qt::QueuedConnection);
        connect(this, SIGNAL(clearAllData()), plot, SLOT(clearData()));

        plot->setSamplingFrequency(GlobalVariables::getInstance().getSamplingFrequency());
        plot->setPhaseDetect(ui->phase_offset->isChecked());

        control_box->sendInitialValues();
        worker_stream->addWorker(behavior.take());

        window.reset(plot);
        break;
    }
    case Playback:
    {
        PlaybackPlot *plot = new PlaybackPlot(this);

        QScopedPointer<ExchangerBehavior> behavior(createExchanger(ExchangerBehavior::Playback));
        PlaybackExchanger *exchanger = static_cast<PlaybackExchanger*>(behavior.data());

        connect(record_grp_bx, SIGNAL(dumpToFile(QString)), exchanger, SLOT(dumpData(QString)), Qt::QueuedConnection);
        connect(record_grp_bx, SIGNAL(removeRecord(QString)), exchanger, SLOT(removeData(QString)), Qt::QueuedConnection);
        connect(record_grp_bx, SIGNAL(showRecord(QString,PlaybackSettings*)), exchanger, SLOT(requestData(QString,PlaybackSettings*)), Qt::QueuedConnection);
        connect(record_grp_bx, SIGNAL(recordSignal(bool, ulong)), exchanger, SLOT(setAcceptToStore(bool, ulong)), Qt::QueuedConnection);

        connect(plot, SIGNAL(windowWidthChanged(quint32)), record_grp_bx, SLOT(setWindowWidth(quint32)), Qt::QueuedConnection);
        connect(exchanger, SIGNAL(recordsListChanged(QStringList)), record_grp_bx, SLOT(setRecordList(QStringList)), Qt::QueuedConnection);
        connect(exchanger, SIGNAL(blockSamplingFrequency(bool)), record_grp_bx, SLOT(setRecordFlag(bool)), Qt::QueuedConnection);
        connect(exchanger, SIGNAL(blockSamplingFrequency(bool)), &GlobalVariables::getInstance(), SLOT(setBlockSamplingFrequency(bool)), Qt::QueuedConnection);
        connect(exchanger, SIGNAL(workValueChanged(int)), record_grp_bx, SLOT(setWorkBarValue(int)), Qt::QueuedConnection);
        connect(exchanger, SIGNAL(spaceValueChanged(int)), record_grp_bx, SLOT(setSpaceValue(int)), Qt::QueuedConnection);
        connect(exchanger, SIGNAL(maxWorkValueChanged(int)), record_grp_bx, SLOT(setWorkBarMaximum(int)), Qt::QueuedConnection);
        connect(exchanger, SIGNAL(minWorkValueChanged(int)), record_grp_bx, SLOT(setWorkBarMinimum(int)), Qt::QueuedConnection);
        connect(exchanger, SIGNAL(workValueChanged(int)), record_grp_bx, SLOT(setWorkBarValue(int)), Qt::QueuedConnection);

        connect(exchanger, SIGNAL(dataProcessed(QVector<QPointF>*)), plot, SLOT(addNewData(QVector<QPointF>*)), Qt::QueuedConnection);
        connect(plot, SIGNAL(destroyed()), exchanger, SLOT(deleteLater()), Qt::QueuedConnection);
        connect(this, SIGNAL(clearAllData()), plot, SLOT(clearData()));

        /* Устанавливается ограничение по использованию памяти. */
        record_grp_bx->setAvailableSpace(exchanger->availableMemory());

        worker_stream->addWorker(behavior.take());

        window.reset(plot);
        break;
    }
    default:
        throw std::runtime_error("Cannot find this plot type.");
    };

    /* Созданное окно отправляется для дальнейших манипуляций
     * над ним. */
    return window.take();
}
