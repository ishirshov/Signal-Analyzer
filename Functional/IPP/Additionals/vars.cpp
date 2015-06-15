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

#include "vars.h"

GlobalVariables::GlobalVariables()
    :_filterBank(db2)
    ,_medianK(c_Median_K)
    ,_transformLvl(1)
    ,_Vlts(c_V_DSP_12bit)
    ,_kalmanGain(c_Kalman_gain)
    ,_samplingFrequency(c_Fs_range.minValue())
    ,_bufferSize(c_Default_Buffer_sz)
    ,_blockSamplingFrequency(false)
{
    _convertStringToEnum["DB2"] = db2;
    _convertStringToEnum["DB4"] = db4;
    _convertStringToEnum["DB6"] = db6;
    _convertStringToEnum["DB8"] = db8;
    _convertStringToEnum["DB10"] = db10;
    _convertStringToEnum["DB12"] = db12;
    _convertStringToEnum["DB14"] = db14;
    _convertStringToEnum["DB16"] = db16;
    _convertStringToEnum["DB18"] = db18;
    _convertStringToEnum["DB20"] = db20;
    _convertStringToEnum["Haar"] = haar;
}

QList<QString> GlobalVariables::getWaveletFilterBanks() const
{
    QList<QString> keys = _convertStringToEnum.keys();
    qSort(keys.begin(), keys.end(), qLess<QString>()); // FIXME: Fix sort algorithm

    return keys;
}

void GlobalVariables::setKalmanGain(double val)
{
    _kalmanGain = val;
    emit kalmanGainChanged(_kalmanGain);
}

void GlobalVariables::setVoltsLevel(float val)
{
    if((val == c_V_DSP_12bit) ||
       (val == c_V_FPGA_12bit) ||
       (val == c_V_FPGA_16bit) ||
       (val == c_V_FPGA_32bit) ||
       (val == c_V_GPP_12bit))
    {
        _Vlts = val;
        emit voltsLevelChanged(_Vlts);
    }
}

void GlobalVariables::setTransformLevel(int val)
{
    if(val < 1) return;

    _transformLvl = val;
    emit transformLevelChanged(_transformLvl);
}

void GlobalVariables::setMedianK(int val)
{
    if(val%2 == 0) return;

    _medianK = val;
    emit medianKChanged(_medianK);
}

void GlobalVariables::setSamplingFrequency(ulong val)
{
    if(_blockSamplingFrequency || !c_Fs_range.contains(val)) return;

    _samplingFrequency = val;
    emit samplingFrequencyChanged(val);
}

void GlobalVariables::setBufferSize(int val)
{
    if(val < c_Default_Buffer_sz) return;

    _bufferSize = val;
    emit bufferSizeChanged(val);
}

void GlobalVariables::setFilterBank(const QString &type)
{
    if(!_convertStringToEnum.contains(type)) return;

    _filterBank = _convertStringToEnum[type];
    emit waveletFilterBankChanged(_filterBank);
}

void GlobalVariables::setBlockSamplingFrequency(bool val)
{
    _blockSamplingFrequency = val;
    emit blockSamplingFrequencyChanged(val);
}
