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

#ifndef WAVELET_TRANSFORMATION_H
#define WAVELET_TRANSFORMATION_H

#include <QObject>
#include "math_decorators.h"
#include "wavelet_modules.h"

class WaveletTransformation : public QObject, public MathDecorators
{
    Q_OBJECT

public:
    explicit WaveletTransformation(MathModule *mmodule, WaveletModule *wmodule);

    ipp_vector<Ipp32f>* signal_data();

public slots:
    void setFilterBank(waveletFilterBanks);
    void setTransformationLevel(Ipp32s);

private:
    QScopedPointer<WaveletModule> _wavelet_module;  // Addtition wavelet compute module (usualy filter for highpass data)
    qint32 _N_lvl;                                  // Decomposition level
    bool _is_haar_transform;                        // Flag for Haar wavelet transform

    // Data structures with wavelet settings:
    ipp_ptr<IppsWTFwdState_32f> _fwd_state;         // For forward wavelet transformation
    ipp_ptr<IppsWTInvState_32f> _inv_state;         // For inverse wavelet transformation

    // Intermediate buffers for detail and approx data:
    ipp_vector<Ipp32f> _coarse_detail;

};

#endif // WAVELET_TRANSFORMATION_H
