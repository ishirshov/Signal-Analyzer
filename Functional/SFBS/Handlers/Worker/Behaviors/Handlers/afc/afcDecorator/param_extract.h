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

#ifndef PARAM_EXTRACT_H
#define PARAM_EXTRACT_H

#include "compute_decorator.h"

class paramExtract : public ComputeDecorator
{
    Q_OBJECT

public:
    explicit paramExtract(ComputeModule *_module);

public slots:
    void setSamplingFrequency(ulong);

    void handleData(ipp_vector<Ipp32f> &);

signals:
    // Unused signal
    void dataProcessed(const ipp_vector<Ipp32f>&);

    // Worked signals
    void updateFrequencyLCD(qreal);
    void updateAmplitudeLCD(qreal);

private:
    Ipp64f param[3];
    ulong sampl_freq;
    
};

#endif // PARAM_EXTRACT_H
