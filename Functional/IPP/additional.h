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

#ifndef ADDITIONAL_H
#define ADDITIONAL_H

//------------------------ SetFabric stream library --------------------------//

#include <sfb_stream/libsfbs.h>
#include <sfb_stream/user_ipc/user_ipc.h>

//------------------------------ Additional headers --------------------------//

#include "Additionals/vars.h"
#include "Additionals/second.h"
#include "Additionals/helpers.h"
#include "Additionals/console_handler.h"

//-------------------------- IPP Overloaded functions ------------------------//

#include "Interface/ipp_abs.h"
#include "Interface/ipp_add_c.h"
#include "Interface/ipp_allocator.h"
#include "Interface/ipp_amax.h"
#include "Interface/ipp_autocorr_norm.h"
#include "Interface/ipp_convert.h"
#include "Interface/ipp_copy.h"
#include "Interface/DFT/ipp_dft_init.h"
#include "Interface/DFT/ipp_dft_fwd_r2css.h"
#include "Interface/DFT/ipp_dft_inv_ccs2r.h"
#include "Interface/DFT/ipp_dft_resampl.h"
#include "Interface/ipp_div.h"
#include "Interface/ipp_div_c.h"
#include "Interface/FFT/ipp_fft_init.h"
#include "Interface/FFT/ipp_fft_fwd_r2ccs.h"
#include "Interface/FFT/ipp_fft_inv_ccs2r.h"
#include "Interface/FFT/ipp_fft_resampl.h"
#include "Interface/ipp_move.h"
#include "Interface/ipp_median.h"
#include "Interface/ipp_mean.h"
#include "Interface/ipp_mul.h"
#include "Interface/ipp_mul_c.h"
#include "Interface/ipp_norm_biased.h"
#include "Interface/ipp_phase_angle.h"
#include "Interface/ipp_phase_offset.h"
#include "Interface/ipp_pow_x.h"
#include "Interface/ipp_rand_uniform.h"
#include "Interface/ipp_rand_uniform_init.h"
#include "Interface/ipp_sample_down.h"
#include "Interface/ipp_sample_up.h"
#include "Interface/ipp_set_value.h"
#include "Interface/ipp_sign.h"
#include "Interface/ipp_signal_parameters.h"
#include "Interface/ipp_sin.h"
#include "Interface/ipp_sqrt.h"
#include "Interface/ipp_sub.h"
#include "Interface/ipp_sub_c.h"
#include "Interface/ipp_sum.h"
#include "Interface/ipp_vector.h"
#include "Interface/Wavelet/ipp_wavelet_fwd.h"
#include "Interface/Wavelet/ipp_wavelet_inv.h"
#include "Interface/Wavelet/ipp_wavelet_init_fwd.h"
#include "Interface/Wavelet/ipp_wavelet_init_inv.h"
#include "Interface/Wavelet/ipp_wavelet_fwd_haar.h"
#include "Interface/Wavelet/ipp_wavelet_inv_haar.h"
#include "Interface/Wavelet/Banks/daubechies.h"
#include "Interface/ipp_zero.h"

//--------------------------- Headers of STDC++ library ----------------------//

#include <cmath>
#include <stdexcept>

//---------------------------- Headers of STDC library -----------------------//

#include <sys/syscall.h>
#include <unistd.h>

#endif // ADDITIONAL_H
