QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = signal-analyzer
TEMPLATE = app
TRANSLATIONS = Languages/ru_RU.ts \
               Languages/en_US.ts

linux-icc-32 | linux-icc-64 {

# ---------------------------------- Intel Compiler 14.0.1 flags ---------------------------------------- #

    ICC_OPT = -O3                                       # Optimization options
    ICC_ADV_OPT = -simd -vec-guard-write \              # Advanced optimiaztion options
                  -use-intel-optimized-headers \
                  -ipp=common \
                  -ipp-link=dynamic \
                  -mkl=parallel \
                  -tbb

    ICC_IPO = -ip                                       # Interprocedural Optimization (IPO) Options
    ICC_FLOATP = -fp-model fast=2                       # Floating-Point Options
    ICC_CODEGEN = -xAVX -axAVX                          # Code Generation Options
    ICC_DATA = -fPIC -fstack-protector-all              # Data Options
    ICC_LANG = -restrict                                # Language Options

    ICC_DEBUG = -debug full -g -w2                      # Debug options
    ICC_DIAG = -diag_enable sc-full \                   # Diagnostics options
               -vec-report=5 \
               -opt-report=2 \
               -opt-report-file=report.txt

# ------------------------------------ Configure QMAKE Compiler flags ----------------------------------- #
    CONFIG(debug, debug|release) {
            QMAKE_CXXFLAGS += $${ICC_DEBUG}
                              # $${ICC_DIAG}
    }

    QMAKE_CXXFLAGS += $${ICC_OPT} \
                      $${ICC_ADV_OPT} \
                      $${ICC_IPO} \
                      $${ICC_FLOATP} \
                      $${ICC_CODEGEN} \
                      $${ICC_DATA} \
                      $${ICC_LANG}

    INCLUDEPATH += /opt/intel/ipp/include
    DEPENDPATH += /opt/intel/ipp/include

    INCLUDEPATH += /opt/intel/mkl/include
    DEPENDPATH += /opt/intel/mkl/include

    INCLUDEPATH += /opt/intel/tbb/include
    DEPENDPATH += /opt/intel/tbb/include

    INCLUDEPATH += /opt/intel/include
    DEPENDPATH += /opt/intel/include

    LIBS += -L/opt/intel/ipp/lib/intel64 -lippcore -lippi -lipps -lippvm
    LIBS += -L/opt/intel/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -lpthread -lm
    LIBS += -L/opt/intel/tbb/lib/intel64/gcc4.1 -ltbb
    LIBS += -L/opt/intel/composerxe/lib/intel64 -liomp5

}
else:linux-g++ {

# --------------------------------------- Intel PP and MKL library path --------------------------------- #

    INCLUDEPATH += /opt/intel/ipp/include
    DEPENDPATH += /opt/intel/ipp/include

    INCLUDEPATH += /opt/intel/mkl/include
    DEPENDPATH += /opt/intel/mkl/include

    INCLUDEPATH += /opt/intel/tbb/include
    DEPENDPATH += /opt/intel/tbb/include

    INCLUDEPATH += /opt/intel/include
    DEPENDPATH += /opt/intel/include

    LIBS += -L/opt/intel/ipp/lib/intel64 -lippcore -lippi -lipps -lippvm
    LIBS += -L/opt/intel/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -lpthread -lm
    LIBS += -L/opt/intel/tbb/lib/intel64/gcc4.1 -ltbb
    LIBS += -L/opt/intel/composerxe/lib/intel64 -liomp5

    QMAKE_CXXFLAGS += -fPIC
}

# ------------------------------------ Configure specific project library ------------------------------- #

unix {
# ----------------------------------------------- Qwt library path -------------------------------------- #

    CONFIG += qwt

    contains(QT_VERSION, ^5\\.2\\.1) {
        QT += opengl
        LIBS += -L$(QWT_5_2_1)/lib -lqwt
        include($(QWT_5_2_1)/features/qwt.prf)
        message("Include QWT library for $${QT_VERSION} Qt version.")
    }
    contains(QT_VERSION, ^4\\.8\\.5) {
        QT += opengl
        LIBS += -L$(QWT_4_8_5)/lib -lqwt
        include($(QWT_4_8_5)/features/qwt.prf)
        message("Include QWT library for $${QT_VERSION} Qt version.")
    }
    contains(QT_VERSION, ^4\\.6\\.3) {
        LIBS += -L$(QWT_4_6_3)/lib -lqwt
        include($(QWT_4_6_3)/features/qwt.prf)
        message("Include QWT library for $${QT_VERSION} Qt version.")
    }

    contains(QT_VERSION, (4.8.[3-5]|5.*.*)) {
        HEADERS += Graph/Canvas/gl_canvas.h
        SOURCES += Graph/Canvas/gl_canvas.cpp
        message("OpenGL canvas is included into the project.")
    }

# ----------------------------------------- SetFabric stream library path ------------------------------- #

    INCLUDEPATH += /usr/local/include/sfb_stream
    DEPENDPATH += /usr/local/include/sfb_stream

    LIBS += -L/usr/local/lib/sfb_stream -lsfbs -lrt

}

# ------------------------------------------ Project files ---------------------------------------------- #

HEADERS += \
    Functional/IPP/Additionals/console_handler.h \
    Functional/IPP/Additionals/helpers.h \
    Functional/IPP/Additionals/second.h \
    Functional/IPP/Additionals/vars.h \
    Functional/IPP/Interface/DFT/ipp_dft_fwd_r2css.h \
    Functional/IPP/Interface/DFT/ipp_dft_init.h \
    Functional/IPP/Interface/DFT/ipp_dft_inv_ccs2r.h \
    Functional/IPP/Interface/DFT/ipp_dft_resampl.h \
    Functional/IPP/Interface/FFT/ipp_fft_fwd_r2ccs.h \
    Functional/IPP/Interface/FFT/ipp_fft_init.h \
    Functional/IPP/Interface/FFT/ipp_fft_inv_ccs2r.h \
    Functional/IPP/Interface/FFT/ipp_fft_resampl.h \
    Functional/IPP/Interface/Wavelet/Banks/daubechies.h \
    Functional/IPP/Interface/Wavelet/ipp_wavelet_fwd.h \
    Functional/IPP/Interface/Wavelet/ipp_wavelet_fwd_haar.h \
    Functional/IPP/Interface/Wavelet/ipp_wavelet_init_fwd.h \
    Functional/IPP/Interface/Wavelet/ipp_wavelet_init_inv.h \
    Functional/IPP/Interface/Wavelet/ipp_wavelet_inv.h \
    Functional/IPP/Interface/Wavelet/ipp_wavelet_inv_haar.h \
    Functional/IPP/Interface/ipp_abs.h \
    Functional/IPP/Interface/ipp_add.h \
    Functional/IPP/Interface/ipp_add_c.h \
    Functional/IPP/Interface/ipp_allocator.h \
    Functional/IPP/Interface/ipp_amax.h \
    Functional/IPP/Interface/ipp_autocorr_norm.h \
    Functional/IPP/Interface/ipp_convert.h \
    Functional/IPP/Interface/ipp_copy.h \
    Functional/IPP/Interface/ipp_div.h \
    Functional/IPP/Interface/ipp_div_c.h \
    Functional/IPP/Interface/ipp_mean.h \
    Functional/IPP/Interface/ipp_median.h \
    Functional/IPP/Interface/ipp_move.h \
    Functional/IPP/Interface/ipp_mul.h \
    Functional/IPP/Interface/ipp_mul_c.h \
    Functional/IPP/Interface/ipp_norm_biased.h \
    Functional/IPP/Interface/ipp_phase_angle.h \
    Functional/IPP/Interface/ipp_phase_offset.h \
    Functional/IPP/Interface/ipp_pow_x.h \
    Functional/IPP/Interface/ipp_ptr.h \
    Functional/IPP/Interface/ipp_rand_uniform.h \
    Functional/IPP/Interface/ipp_rand_uniform_init.h \
    Functional/IPP/Interface/ipp_round_type.h \
    Functional/IPP/Interface/ipp_sample_down.h \
    Functional/IPP/Interface/ipp_sample_up.h \
    Functional/IPP/Interface/ipp_set_value.h \
    Functional/IPP/Interface/ipp_sign.h \
    Functional/IPP/Interface/ipp_signal_parameters.h \
    Functional/IPP/Interface/ipp_sin.h \
    Functional/IPP/Interface/ipp_sqrt.h \
    Functional/IPP/Interface/ipp_sub.h \
    Functional/IPP/Interface/ipp_sub_c.h \
    Functional/IPP/Interface/ipp_sum.h \
    Functional/IPP/Interface/ipp_vector.h \
    Functional/IPP/Interface/ipp_zero.h \
    Functional/IPP/Interpolation/interpolation.h \
    Functional/IPP/Interpolation/interpolation_basic.h \
    Functional/IPP/Interpolation/interpolation_interface.h \
    Functional/IPP/Interpolation/interpolation_linear.h \
    Functional/IPP/additional.h \
    Functional/IPP/general_functions.h \
    Functional/SFBS/Channels/Interfaces/ipc_panel.h \
    Functional/SFBS/Channels/Interfaces/ipc_state.h \
    Functional/SFBS/Channels/IPCPanels/States/ADC/apply_config.h \
    Functional/SFBS/Channels/IPCPanels/States/ADC/ch_close.h \
    Functional/SFBS/Channels/IPCPanels/States/ADC/ch_open.h \
    Functional/SFBS/Channels/IPCPanels/States/ADC/dev_close.h \
    Functional/SFBS/Channels/IPCPanels/States/ADC/dev_open.h \
    Functional/SFBS/Channels/IPCPanels/States/ADC/get_ch_per_one_device.h \
    Functional/SFBS/Channels/IPCPanels/States/ADC/get_dev_freq.h \
    Functional/SFBS/Channels/IPCPanels/States/ADC/get_dev_numbers.h \
    Functional/SFBS/Channels/IPCPanels/States/ADC/get_stream_type.h \
    Functional/SFBS/Channels/IPCPanels/States/ADC/set_dev_freq.h \
    Functional/SFBS/Channels/IPCPanels/States/ADC/set_stream_format.h \
    Functional/SFBS/Channels/IPCPanels/States/ADC/set_stream_type.h \
    Functional/SFBS/Channels/IPCPanels/States/ADC/stream_disable.h \
    Functional/SFBS/Channels/IPCPanels/States/ADC/stream_enable.h \
    Functional/SFBS/Channels/IPCPanels/States/IPC/sfbs_get_info.h \
    Functional/SFBS/Channels/IPCPanels/States/IPC/sfbs_hello.h \
    Functional/SFBS/Channels/IPCPanels/States/IPC/sfbs_no_state.h \
    Functional/SFBS/Channels/IPCPanels/States/IPC/sfbs_user.h \
    Functional/SFBS/Channels/IPCPanels/States/adc_states.h \
    Functional/SFBS/Channels/IPCPanels/States/ipc_states.h \
    Functional/SFBS/Channels/IPCPanels/States/no_ipc_state.h \
    Functional/SFBS/Channels/IPCPanels/dsp_gen_panel.h \
    Functional/SFBS/Channels/IPCPanels/dsp_multi_panel.h \
    Functional/SFBS/Channels/IPCPanels/fpga_panel.h \
    Functional/SFBS/Channels/IPCPanels/isomorph_panel.h \
    Functional/SFBS/Channels/IPCPanels/no_panel.h \
    Functional/SFBS/Channels/Observer/event_bridge.h \
    Functional/SFBS/Channels/Observer/thread_bridge_rx.h \
    Functional/SFBS/Channels/sfbs_channels.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Decorators/forwading.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Decorators/purging.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/approx_delta_t.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/approx_high_frequency.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/approx_low_frequency.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/autocorr_norm.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/empty_mod.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/hyperbolic_thresholding.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/interp_sig.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/levels_to_vlts.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/math_decorators.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/math_module.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/median_filter.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/phase_offset.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/resampling_down.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/resampling_up.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/simple_kalman_filter.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/soft_thresholding.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/wavelet_modules.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/wavelet_transformation.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Settings/playback_settings.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/empty_exchanger.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/exchanger_behavior.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/math_modules.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/playback_exchanger.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/playback_record.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/settings.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/standart_exchanger.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/afcDecorator/amplitude_extract.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/afcDecorator/compute_decorator.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/afcDecorator/compute_module.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/afcDecorator/ipp_fft_fwd.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/afcDecorator/mkl_fft_fwd.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/afcDecorator/param_extract.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/afcDecorator/window_function.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/short_range_afc.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/wide_range_afc.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/empty_handler.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/handler_behavior.h \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/ramp_checker.h \
    Functional/SFBS/Handlers/Worker/Behaviors/decorators.h \
    Functional/SFBS/Handlers/Worker/Behaviors/exchangers.h \
    Functional/SFBS/Handlers/Worker/Behaviors/handlers.h \
    Functional/SFBS/Handlers/Worker/Behaviors/worker_behavior.h \
    Functional/SFBS/Handlers/Worker/Behaviors/worker_decorator.h \
    Functional/SFBS/Handlers/Worker/data_multiplier.h \
    Functional/SFBS/Handlers/Worker/empty_manager.h \
    Functional/SFBS/Handlers/Worker/worker_manager.h \
    Functional/SFBS/Handlers/Worker/worker_pipeline.h \
    Functional/SFBS/Handlers/managers.h \
    Functional/SFBS/NoStream/empty_panel.h \
    Functional/SFBS/NoStream/no_stream.h \
    Functional/SFBS/streams.h \    
    Graph/Canvas/standart_canvas.h \
    Graph/Plot/AFCCurveData/afccurvedata.h \
    Graph/Plot/AFCCurveData/afcprivatedata.h \
    Graph/Plot/AFCCurveData/peak_detect.h \
    Graph/Plot/CurveData/curvedata.h \
    Graph/Plot/CurveData/curveprivatedata.h \
    Graph/Plot/PlaybackCurveData/playbackcurvedata.h \
    Graph/Plot/afcplot.h \
    Graph/Plot/canvas.h \
    Graph/Plot/playbackplot.h \
    Graph/Plot/plot.h \
    Graph/ScrollZoomer/scrollbar.h \
    Graph/ScrollZoomer/scrollzoomer.h \
    Graph/application.h \
    Graph/checked_box.h \
    Graph/checked_frame.h \
    Graph/control_box.h \
    Graph/denoised_group_box.h \
    Graph/knob_box.h \
    Graph/mainwindow.h \
    Graph/plots.h \
    Graph/record_group_box.h \
    Graph/resolution_box.h \
    Functional/SFBS/User/Worker/wave_panel.h \
    Functional/SFBS/User/user_fbs.h \
    Functional/SFBS/stream_device.h \
    Functional/SFBS/User/Interface/user_ipc_panel.h \
    Functional/SFBS/User/Interface/user_gen.h \
    Functional/SFBS/User/Worker/sine_gen.h

SOURCES += \
    Functional/IPP/Additionals/console_handler.cpp \
    Functional/IPP/Additionals/second.cpp \
    Functional/IPP/Additionals/vars.cpp \
    Functional/IPP/Interface/DFT/ipp_dft_init.cpp \
    Functional/IPP/Interface/DFT/ipp_dft_resampl.cpp \
    Functional/IPP/Interface/FFT/ipp_fft_init.cpp \
    Functional/IPP/Interface/FFT/ipp_fft_resampl.cpp \
    Functional/IPP/Interface/Wavelet/Banks/daubechies.cpp \
    Functional/IPP/Interface/ipp_phase_offset.cpp \
    Functional/IPP/Interface/ipp_signal_parameters.cpp \
    Functional/IPP/Interpolation/interpolation.cpp \
    Functional/IPP/Interpolation/interpolation_basic.cpp \
    Functional/IPP/Interpolation/interpolation_interface.cpp \
    Functional/IPP/Interpolation/interpolation_linear.cpp \
    Functional/IPP/general_functions.cpp \
    Functional/SFBS/Channels/IPCPanels/States/ADC/apply_config.cpp \
    Functional/SFBS/Channels/IPCPanels/States/ADC/ch_close.cpp \
    Functional/SFBS/Channels/IPCPanels/States/ADC/ch_open.cpp \
    Functional/SFBS/Channels/IPCPanels/States/ADC/dev_close.cpp \
    Functional/SFBS/Channels/IPCPanels/States/ADC/dev_open.cpp \
    Functional/SFBS/Channels/IPCPanels/States/ADC/get_ch_per_one_device.cpp \
    Functional/SFBS/Channels/IPCPanels/States/ADC/get_dev_freq.cpp \
    Functional/SFBS/Channels/IPCPanels/States/ADC/get_dev_numbers.cpp \
    Functional/SFBS/Channels/IPCPanels/States/ADC/get_stream_type.cpp \
    Functional/SFBS/Channels/IPCPanels/States/ADC/set_dev_freq.cpp \
    Functional/SFBS/Channels/IPCPanels/States/ADC/set_stream_format.cpp \
    Functional/SFBS/Channels/IPCPanels/States/ADC/set_stream_type.cpp \
    Functional/SFBS/Channels/IPCPanels/States/ADC/stream_disable.cpp \
    Functional/SFBS/Channels/IPCPanels/States/ADC/stream_enable.cpp \
    Functional/SFBS/Channels/IPCPanels/States/IPC/sfbs_get_info.cpp \
    Functional/SFBS/Channels/IPCPanels/States/IPC/sfbs_hello.cpp \
    Functional/SFBS/Channels/IPCPanels/States/IPC/sfbs_no_state.cpp \
    Functional/SFBS/Channels/IPCPanels/States/IPC/sfbs_user.cpp \
    Functional/SFBS/Channels/IPCPanels/dsp_gen_panel.cpp \
    Functional/SFBS/Channels/IPCPanels/dsp_multi_panel.cpp \
    Functional/SFBS/Channels/IPCPanels/fpga_panel.cpp \
    Functional/SFBS/Channels/IPCPanels/isomorph_panel.cpp \
    Functional/SFBS/Channels/IPCPanels/no_panel.cpp \
    Functional/SFBS/Channels/sfbs_channels.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/approx_delta_t.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/approx_high_frequency.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/approx_low_frequency.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/autocorr_norm.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/hyperbolic_thresholding.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/interp_sig.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/median_filter.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/phase_offset.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/resampling_down.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/resampling_up.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/simple_kalman_filter.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/soft_thresholding.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Modules/wavelet_transformation.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/Settings/playback_settings.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/playback_exchanger.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/playback_record.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Exchangers/standart_exchanger.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/afcDecorator/amplitude_extract.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/afcDecorator/ipp_fft_fwd.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/afcDecorator/mkl_fft_fwd.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/afcDecorator/param_extract.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/afcDecorator/window_function.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/short_range_afc.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/afc/wide_range_afc.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/Handlers/ramp_checker.cpp \
    Functional/SFBS/Handlers/Worker/Behaviors/worker_decorator.cpp \
    Functional/SFBS/Handlers/Worker/data_multiplier.cpp \
    Functional/SFBS/Handlers/Worker/worker_pipeline.cpp \
    Functional/SFBS/NoStream/empty_panel.cpp \
    Functional/SFBS/NoStream/no_stream.cpp \    
    Graph/Canvas/standart_canvas.cpp \
    Graph/Plot/AFCCurveData/afccurvedata.cpp \
    Graph/Plot/AFCCurveData/afcprivatedata.cpp \
    Graph/Plot/AFCCurveData/peak_detect.cpp \
    Graph/Plot/CurveData/curvedata.cpp \
    Graph/Plot/CurveData/curveprivatedata.cpp \
    Graph/Plot/PlaybackCurveData/playbackcurvedata.cpp \
    Graph/Plot/afcplot.cpp \
    Graph/Plot/playbackplot.cpp \
    Graph/Plot/plot.cpp \
    Graph/ScrollZoomer/scrollbar.cpp \
    Graph/ScrollZoomer/scrollzoomer.cpp \
    Graph/application.cpp \
    Graph/checked_box.cpp \
    Graph/checked_frame.cpp \
    Graph/control_box.cpp \
    Graph/denoised_group_box.cpp \
    Graph/knob_box.cpp \
    Graph/mainwindow.cpp \
    Graph/record_group_box.cpp \
    Graph/resolution_box.cpp \
    main.cpp \
    Functional/SFBS/User/Worker/wave_panel.cpp \
    Functional/SFBS/User/user_fbs.cpp \
    Functional/SFBS/User/Worker/sine_gen.cpp

FORMS += \
    mainwindow.ui

# ------------------------------------------ Post operation --------------------------------------------- #

unix {
    QMAKE_POST_LINK += mkdir -p $$OUT_PWD/languages ;
    QMAKE_POST_LINK += cp -r $$_PRO_FILE_PWD_/Languages/* $$OUT_PWD/languages ;
    QMAKE_POST_LINK += cp  $$_PRO_FILE_PWD_/icon.png $$OUT_PWD/icon.png
}
