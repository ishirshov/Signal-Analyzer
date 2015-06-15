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

#ifndef HANDLERS_H
#define HANDLERS_H

// -------------------- Class of handler behaviors -------------------- //

#include "Handlers/ramp_checker.h"
#include "Handlers/empty_handler.h"
#include "Handlers/afc/wide_range_afc.h"
#include "Handlers/afc/short_range_afc.h"

// ----------------------- Modules of AFC class ----------------------- //

#include "Handlers/afc/afcDecorator/mkl_fft_fwd.h"
#include "Handlers/afc/afcDecorator/ipp_fft_fwd.h"
#include "Handlers/afc/afcDecorator/param_extract.h"
#include "Handlers/afc/afcDecorator/window_function.h"
#include "Handlers/afc/afcDecorator/amplitude_extract.h"

#endif // HANDLERS_H
