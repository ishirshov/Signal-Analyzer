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

#include "sine_gen.h"
#include "Functional/SFBS/Channels/Observer/thread_bridge_rx.h"

SineGenerator::SineGenerator()
    :_is_work(false)
    ,_device_name("Sine")
    ,_device_type("GPP")
    ,_gen_timer(new QTimer(this))
    ,_report_timer(new QTimer(this))
    ,_counter(0)
    ,_Fs(0), _Fn(0.0), _Amp(0.0), _Noise(0.0)
    ,_noise(c_Default_Buffer_sz)
    ,_buffer(c_Default_Buffer_sz)
    ,_last_pos(0)
{
    _report_timer->setInterval(1000);

    connect(_gen_timer, SIGNAL(timeout()), SLOT(generate()));
    connect(_report_timer, SIGNAL(timeout()), SLOT(report()));

    init_signal(c_Default_Fs, c_Default_Fn, c_Default_Amp);
    init_rand_state(c_Default_Noise);
    init_timer(c_Default_Fs);
}

void SineGenerator::start()
{
    if(!_is_work)
    {
        _is_work = true;
        _gen_timer->start();
        _report_timer->start();

        emit workerStatusChanged(_is_work);
        emit started();
    }
}

void SineGenerator::stop()
{
    if(_is_work)
    {
        _is_work = false;
        _gen_timer->stop();
        _report_timer->stop();

        emit workerStatusChanged(_is_work);
        emit finished();
    }
}

void SineGenerator::setSignalSettings(long Fs, double Fn, double Amp, double Noise)
{
    if(c_Fs_range.contains(Fs) && (Fs/2 >= Fn))
        if(c_Fn_range.contains(Fn))
            if(c_Amp_range.contains(Amp))
                if((_Fs != Fs) || (_Fn != Fn) || (_Amp != Amp))
                {
                    if(_is_work) _gen_timer->stop();
                    init_signal(Fs, Fn, Amp);
                    init_timer(Fs);
                    if(_is_work) _gen_timer->start();
                }

    if(c_Noise_range.contains(Noise))
        if(Noise != _Noise)
            init_rand_state(Noise);
}

void SineGenerator::generate()
{
    if(_is_work)
    {
        int space = _signal.size() - _last_pos;
        if(space <= 0) _last_pos = 0;

        ipp_copy(_signal.data() + _last_pos, _buffer.data(), _buffer.size());
        _last_pos += c_Default_Buffer_sz;

        ipp_rand_uniform(_noise.data(), _noise.size(), _rand_state.get());
        ipp_add(_buffer.data(), _noise.data(), _buffer.data(), _buffer.size());

        threadRxCallback(_buffer);

        _counter++;
    }
}

void SineGenerator::report()
{
    qreal bytes = _counter * _buffer.size() * sizeof(Ipp16s) / 1024.0 / 1024.0;
    printInfo(QString("Sending buffers %1 in MBytes.").arg(bytes));

    _counter = 0;
}

void SineGenerator::init_signal(long Fs, qreal Fn, qreal Amp)
{
    qint32 round_Fs = std::ceil(qreal(Fs)/qreal(_buffer.size())) * _buffer.size();
    qint32 size_rest = round_Fs - Fs;

    _signal.resize(round_Fs);
    _signal.clear();

    // Create time line for sine signal
    qreal T = 1.0;
    qreal t_inc = T/Fs;

    for(qreal t = 0.0; t < T; t += t_inc)
        _signal.push_back(t);    

    Ipp32f *data = _signal.data();
    quint32 size = _signal.size();

    // Create sin wave without estimate
    ipp_mul_c(data, IPP_2PI, data, size);
    ipp_mul_c(data, Fn, data, size);
    ipp_sin(data, data, size, A11);
    ipp_mul_c(data, Amp, data, size);

    // Append rest if exists
    if(size_rest > 0)
    {
        ipp_vector<Ipp32f> rest_data(data, size_rest);
        _signal.push_back(rest_data, size_rest);
    }
    _signal.resize(round_Fs);

    _last_pos = 0;

    if(_Fs != Fs)
        emit samplingFrequencyChanged(Fs);

    _Fs = Fs;
    _Fn = Fn;
    _Amp = Amp;
}

void SineGenerator::init_rand_state(qreal Noise)
{
    ipp_rand_uniform_init(_rand_state, -Noise, Noise, 0);

    _Noise = Noise;
}

void SineGenerator::init_timer(long Fs)
{    
    qint32 power = 0;
    qint32 tm_interv = round(Fs / _buffer.size());

    /*
     * Compute how mach buffers with length c_Basic_arr_sz
     * can sended at 1 minute. Then compute interval for timer (msec).
     */
    do {
        tm_interv = qint32(round(1000.0 / tm_interv));
        ++power;
    } while(tm_interv == 0);

    _gen_timer->setInterval(tm_interv);
}
