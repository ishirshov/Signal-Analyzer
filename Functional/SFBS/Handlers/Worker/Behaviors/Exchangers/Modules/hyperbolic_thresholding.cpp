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

#include "hyperbolic_thresholding.h"

HyperbolicThresholding::HyperbolicThresholding()
    :_zeros(c_Default_Buffer_sz, 0.f)
    ,_tmp(_zeros)
    ,_tmp2(_zeros)
{
}

void HyperbolicThresholding::function(Ipp32f *data, int size)
{
    if(!data || size < 1) return;

    compute(data, size);
}

void HyperbolicThresholding::compute(Ipp32f *src, int size)
{
    // Check sizes
    if(size > _zeros.size())
    {
        _zeros.resize(size, 0.f);
        _tmp.reserve(size);
        _tmp2.reserve(size);
    }

    // Clear old results
    _tmp.clear();
    _tmp2.clear();

    // Calculate delta for thresholding function
    qint32 delta_sz = size / 2 + 1;
    Ipp32f mean = 0.0;
    Ipp32f sum = 0.0;
    Ipp32f delta = 0.0;

    _tmp.push_back(src + delta_sz, delta_sz);
    Ipp32f *delta_buff_p = _tmp.data();

    ipp_mean(delta_buff_p, delta_sz, mean);
    ipp_sub_c(delta_buff_p, mean, delta_buff_p, delta_sz);
    ipp_pow_x(delta_buff_p, 2.0, delta_buff_p, delta_sz, A21);
    ipp_sum(delta_buff_p, delta_sz, sum);
    delta = std::sqrt(2 * std::log10(size) * (sum/(size/2 - 1)));

    // Compute hyperbolic thresholding function
    Ipp32f *sign_p = _tmp.data();
    Ipp32f *amax_p = _tmp2.data();

    ipp_sign(src, sign_p, size);
    ipp_pow_x(src, 2.0, amax_p, size, A21);
    ipp_sub_c(amax_p, std::pow(delta, Ipp32f(2.0)), amax_p, size);
    ipp_amax(amax_p, _zeros.data(), amax_p, size);
    ipp_sqrt(amax_p, amax_p, size);
    ipp_mul(sign_p, amax_p, src, size);
}
