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

#include "amplitude_extract.h"

#include <mkl_cblas.h>
#include <mkl_vml.h>

//-------------------- Define additional functors for AFC ----------------//

void DSPExtract::calculate(const int N, Ipp32f *input, Ipp32f *coeff, Ipp32f *output) const
{}

void FPGAExtract::calculate(const int N, Ipp32f *input, Ipp32f *coeff, Ipp32f *output) const
{
    if((N <= 0) || (!input || !coeff || !output))
        throw std::runtime_error("FPGA AFC module can't handle null pointers.");

    vsAdd(N, input, coeff, output);
}

//---------------------- Define amplitudeExtract class -------------------//

AmplitudeExtract::AmplitudeExtract(ComputeModule *_module, dBModType mod_type)
    :ComputeDecorator(_module)
    ,afc_size(500)
    ,new_size(afc_size)
    ,last_data_size(2500000.0)
    ,big_chunk(0)
    ,small_chunk(0)
    ,db_func(0)
{
    initArrays();
    recalcChunks();

    switch(mod_type)
    {
    case FPGA:
        db_func = new FPGAExtract;
        break;
    default:
        db_func = new DSPExtract;
        break;
    }
}

void AmplitudeExtract::handleData(ipp_vector<Ipp32f> &afc)
{
    if(afc.empty()) return;

    // Get spectrum.
    module->handleData(afc);

    // Get pointers.
    Ipp32f *_plvl = _pdata[0];
    Ipp32f *_puno = _pdata[1];
    Ipp32f *_pcb = _pdata[2];
    Ipp32f *_pmin = _pdata[3];
    Ipp32f *_pfrng = _pdata[4];
    Ipp32f *_psrng = _pdata[5];
    Ipp32f *_pafc = _pdata[6];
    Ipp32f *_pc_32768 = _pdata[7];
    Ipp32f *_pc_12 = _pdata[8];

    // Check level coefficients.
    Ipp32s data_size = afc.size();
    if(data_size != last_data_size)
    {
        last_data_size = data_size;
        ipp_set(2.f/Ipp32f(last_data_size), _plvl, afc_size);

        recalcChunks();
    }

    // Find local maximum.
    Ipp32f *_pzone = afc.begin();
    quint32 size = small_chunk;

    quint32 cntr_sz = 0;
    for(quint32 i = 0; i < afc_size; ++i)
    {
        Ipp32s index = 0;
        Ipp32f peak = 0.f;

        if((cntr_sz + size) > data_size) break;
        IppStatus status = ippsMaxIndx_32f(_pzone, size, &peak, &index);
        if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

        Ipp32fc *max = (Ipp32fc*)(_pzone + index);
        _pafc[i] = std::sqrt((max->re * max->re) + (max->im * max->im));

        size = ((i + 2) == afc_size)?(small_chunk):(big_chunk);
        _pzone += size;
        cntr_sz += size;
    }

    // Convert absolute values to levels.
    vsMul(afc_size, _pafc, _plvl, _pafc);

    // Normalized signal.
    Ipp32f max = 0.f, min = 0.f;

    IppStatus status = ippsMinMax_32f(_pafc, afc_size, &min, &max);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

    // If need to normalized signal.
    if(min < 1.f)
    {
        Ipp32f f_range = max - min;
        Ipp32f s_range = max - 1.f;

        ipp_set(min, _pmin, afc_size);
        ipp_set(f_range, _pfrng, afc_size);
        ipp_set(s_range, _psrng, afc_size);

        // First in range [0, 1].
        vsSub(afc_size, _pafc, _pmin, _pafc);
        vsDiv(afc_size, _pafc, _pfrng, _pafc);
        // Second in range [1, max].
        vsMul(afc_size, _pafc, _psrng, _pafc);
        vsAdd(afc_size, _pafc, _puno, _pafc);
    }

    // Convert levels to dB.
    vsDiv(afc_size, _pafc, _pc_32768, _pafc);
    vsLog10(afc_size, _pafc, _pafc);
    vsMul(afc_size, _pafc, _pcb, _pafc);
    db_func->calculate(afc_size, _pafc, _pc_12, _pafc);

    // And send data for next observer.
    emit dataProcessed(ipp_vector<Ipp32f>(_pafc, afc_size));

    if(new_size == afc_size)
        ipp_zero(_pdata[6], afc_size);
    else
    {
        afc_size = new_size;

        clearArrays();
        initArrays();
        recalcChunks();
    }
}

void AmplitudeExtract::plotSettingsChanged(quint32 size)
{
    new_size = size;
}

AmplitudeExtract::~AmplitudeExtract()
{
    delete db_func;
    clearArrays();
}
