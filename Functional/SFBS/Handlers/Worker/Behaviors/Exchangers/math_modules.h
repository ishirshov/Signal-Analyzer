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

#ifndef MATH_MODULES_H
#define MATH_MODULES_H

// Modules

#include "Modules/empty_mod.h"
#include "Modules/resampling_up.h"
#include "Modules/resampling_down.h"
#include "Modules/approx_delta_t.h"
#include "Modules/approx_high_frequency.h"
#include "Modules/approx_low_frequency.h"

// Decorator of modules

#include "Modules/autocorr_norm.h"
#include "Modules/interp_sig.h"
#include "Modules/levels_to_vlts.h"
#include "Modules/median_filter.h"
#include "Modules/phase_offset.h"
#include "Modules/simple_kalman_filter.h"
#include "Modules/soft_thresholding.h"
#include "Modules/hyperbolic_thresholding.h"
#include "Modules/wavelet_transformation.h"

#endif // MATH_MODULES_H
