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

#include "wavelet_transformation.h"

WaveletTransformation::WaveletTransformation(MathModule *mmodule, WaveletModule *wmodule)
    :MathDecorators(mmodule)
    ,_wavelet_module(wmodule)
    ,_N_lvl(c_Transform_level)
    ,_coarse_detail(c_Default_Buffer_sz)
    ,_is_haar_transform(false)
{
    if(!wmodule)
        throw std::runtime_error("Wavelet module cannot be null pointer.");

    setFilterBank(c_WaveletFilterBank);
}

ipp_vector<Ipp32f>* WaveletTransformation::signal_data()
{
    // Get signal data
    QScopedPointer<ipp_vector<Ipp32f> > signal(_module->signal_data());

    if(signal && !signal->empty())
    {
        Ipp32f *data = signal->data();
        Ipp32s sz = signal->size();

        Ipp32s buffer_sz = Ipp32s(std::floor(sz/2.0));
        Ipp32s vector_sz  = buffer_sz * 2;

        if(_coarse_detail.capacity() != vector_sz)
            _coarse_detail.reserve(vector_sz);

        Ipp32f *coarse = _coarse_detail.data();
        Ipp32f *detail = _coarse_detail.data() + buffer_sz;

        ipp_zero(coarse, vector_sz);

        if(_is_haar_transform)
        {
            // Decomposition
            ipp_wavelet_fwd_haar(data, sz, coarse, detail);

            _wavelet_module->function(coarse, vector_sz);

            // Reconstruction
            ipp_wavelet_inv_haar(coarse, detail, data, sz);
        }
        else
        {
            // Decomposition
            ipp_wavelet_fwd(data, coarse, detail, buffer_sz, _fwd_state.get());

            _wavelet_module->function(coarse, vector_sz);

            // Reconstruction
            ipp_wavelet_inv(coarse, detail, buffer_sz, data, _inv_state.get());
        }
    }

    return signal.take();
}

void WaveletTransformation::setFilterBank(waveletFilterBanks type)
{
    _is_haar_transform = false;

    switch(type)
    {
    case db2:
    {
        ipp_wavelet_init_fwd(_fwd_state, DB2::_dec_low, DB2::_len, -1,
                                        DB2::_dec_high, DB2::_len, -1);
        ipp_wavelet_init_inv(_inv_state, DB2::_rec_low, DB2::_len, 0,
                                        DB2::_rec_high, DB2::_len, 0);
        break;
    }
    case db4:
    {
        ipp_wavelet_init_fwd(_fwd_state, DB4::_dec_low, DB4::_len, -1,
                                        DB4::_dec_high, DB4::_len, -1);
        ipp_wavelet_init_inv(_inv_state, DB4::_rec_low, DB4::_len, 0,
                                        DB4::_rec_high, DB4::_len, 0);
        break;
    }
    case db6:
    {
        ipp_wavelet_init_fwd(_fwd_state, DB6::_dec_low, DB6::_len, -1,
                                        DB6::_dec_high, DB6::_len, -1);
        ipp_wavelet_init_inv(_inv_state, DB6::_rec_low, DB6::_len, 0,
                                        DB6::_rec_high, DB6::_len, 0);
        break;
    }
    case db8:
    {
        ipp_wavelet_init_fwd(_fwd_state, DB8::_dec_low, DB8::_len, -1,
                                        DB8::_dec_high, DB8::_len, -1);
        ipp_wavelet_init_inv(_inv_state, DB8::_rec_low, DB8::_len, 0,
                                        DB8::_rec_high, DB8::_len, 0);
        break;
    }
    case db10:
    {
        ipp_wavelet_init_fwd(_fwd_state, DB10::_dec_low, DB10::_len, -1,
                                        DB10::_dec_high, DB10::_len, -1);
        ipp_wavelet_init_inv(_inv_state, DB10::_rec_low, DB10::_len, 0,
                                        DB10::_rec_high, DB10::_len, 0);
        break;
    }
    case db12:
    {
        ipp_wavelet_init_fwd(_fwd_state, DB12::_dec_low, DB12::_len, -1,
                                        DB12::_dec_high, DB12::_len, -1);
        ipp_wavelet_init_inv(_inv_state, DB12::_rec_low, DB12::_len, 0,
                                        DB12::_rec_high, DB12::_len, 0);
        break;
    }
    case db14:
    {
        ipp_wavelet_init_fwd(_fwd_state, DB14::_dec_low, DB14::_len, -1,
                                        DB14::_dec_high, DB14::_len, -1);
        ipp_wavelet_init_inv(_inv_state, DB14::_rec_low, DB14::_len, 0,
                                        DB14::_rec_high, DB14::_len, 0);
        break;
    }
    case db16:
    {
        ipp_wavelet_init_fwd(_fwd_state, DB16::_dec_low, DB16::_len, -1,
                                        DB16::_dec_high, DB16::_len, -1);
        ipp_wavelet_init_inv(_inv_state, DB16::_rec_low, DB16::_len, 0,
                                        DB16::_rec_high, DB16::_len, 0);
        break;
    }
    case db18:
    {
        ipp_wavelet_init_fwd(_fwd_state, DB18::_dec_low, DB18::_len, -1,
                                        DB18::_dec_high, DB18::_len, -1);
        ipp_wavelet_init_inv(_inv_state, DB18::_rec_low, DB18::_len, 0,
                                        DB18::_rec_high, DB18::_len, 0);
        break;
    }
    case db20:
    {
        ipp_wavelet_init_fwd(_fwd_state, DB20::_dec_low, DB20::_len, -1,
                                        DB20::_dec_high, DB20::_len, -1);
        ipp_wavelet_init_inv(_inv_state, DB20::_rec_low, DB20::_len, 0,
                                        DB20::_rec_high, DB20::_len, 0);
        break;
    }
    case haar:
    {
        _is_haar_transform = true;
        break;
    }
    default:
        throw std::runtime_error("Wrong Daubechies filter bank type.");
        break;
    };
}

void WaveletTransformation::setTransformationLevel(Ipp32s val)
{
    if(val < 1)
        throw std::runtime_error("Level of wavelet transformation cannot be negative value.");

    _N_lvl = val;
}
