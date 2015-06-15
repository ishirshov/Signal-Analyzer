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

#ifndef AMPLITUDE_EXTRACT_H
#define AMPLITUDE_EXTRACT_H

#include "compute_decorator.h"

//-------------------- Declare additional functors for AFC ----------------//

struct dbExtract
{
    virtual void calculate(const int N, Ipp32f *input, Ipp32f *coeff, Ipp32f *output) const = 0;
    virtual ~dbExtract() {}
};

struct DSPExtract : dbExtract
{
    virtual void calculate(const int N, Ipp32f *input, Ipp32f *coeff, Ipp32f *output) const;
};

struct FPGAExtract : dbExtract
{
    virtual void calculate(const int N, Ipp32f *input, Ipp32f *coeff, Ipp32f *output) const;
};

//---------------------- Declare amplitudeExtract class ------------------//

class AmplitudeExtract : public ComputeDecorator
{
    Q_OBJECT

public:
    enum dBModType
    {
        FPGA,
        NORMAL
    };

    explicit AmplitudeExtract(ComputeModule *_module, dBModType mod_type);

    ~AmplitudeExtract();

public slots:
    void handleData(ipp_vector<Ipp32f>&);
    void plotSettingsChanged(quint32);

signals:
    void dataProcessed(const ipp_vector<Ipp32f>&);

private:
    void initArrays();
    void recalcChunks();
    void clearArrays();

    //------------------- Rarely changing data ---------------------//
    /*
       _pdata[0] - For convert from abs to levels.
       _pdata[1] - For vectorized functions (1.f).
       _pdata[2] - For convert from levels to dB.
       _pdata[7] - Additional data for convert levels to dB (+32768).
       _pdata[8] - Additional data for convert levels to dB (+12).
    */
    //----------------- Frequently changing data -------------------//
    /*
       _pdata[3] - For first signal normalize in range [0, 1].
       _pdata[4] - It same ^.
       _pdata[5] - For second signal normalize int range [1, max].
       _pdata[6] - Main afc data.
    */

    static const int dim = 9;
    Ipp32f *_pdata[dim];

    // Scale settings.
    quint32 afc_size;
    quint32 new_size;
    qreal last_data_size;

    // Extremum settings.
    quint32 big_chunk;
    quint32 small_chunk;

    // Device functor.
    dbExtract *db_func;

};

inline void AmplitudeExtract::clearArrays()
{
    #pragma unroll(9)
    for(int i = 0; i < dim; ++i)
        ipp_free(_pdata[i]);
}

inline void AmplitudeExtract::recalcChunks()
{
    // Calculate big chunck size for all afc_size points
    qreal big_dchunk = last_data_size/qreal(afc_size);
    qreal small_dchunk = big_dchunk/2.f;

    // Calculate big chunck size for all afc_size-2 points
    // because small chunck = point
    big_dchunk = (last_data_size - big_dchunk)/qreal(afc_size - 2);

    big_chunk = round(big_dchunk);
    small_chunk = round(small_dchunk);
}

inline void AmplitudeExtract::initArrays()
{
    #pragma unroll(9)
    for(int i = 0; i < dim; ++i)
        _pdata[i] = ipp_malloc<Ipp32f>(afc_size);

    ipp_set(c_B, _pdata[2], afc_size);
    ipp_set(1.f, _pdata[1], afc_size);
    ipp_set(2.f/Ipp32f(last_data_size), _pdata[0], afc_size);
    ipp_set(32768.f, _pdata[7], afc_size);
    ipp_set(12.f, _pdata[8], afc_size);
    ipp_set(0.0, _pdata[6], afc_size);
}

#endif // AMPLITUDE_EXTRACT_H
