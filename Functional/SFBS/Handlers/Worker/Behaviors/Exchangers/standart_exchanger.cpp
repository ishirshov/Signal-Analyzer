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

#include "standart_exchanger.h"
#include "Modules/empty_mod.h"

StandartExchanger::StandartExchanger(QObject *parent)
    :_module(new EmptyMod)
    ,_current_flag(true)
{
    setParent(parent);
}

StandartExchanger::Weight StandartExchanger::behaviorWeight() const
{
    return WorkerBehavior::Light;
}

void StandartExchanger::setMathModule(MathModule *module)
{
    if(module)
    {
        _module.reset(module);
        _current_flag = true;
    }
}

void StandartExchanger::setAcceptToStore(bool flag)
{
    _current_flag = flag;
    _module->clear();
}

void StandartExchanger::receiveData(const ipp_vector<Ipp16s> &signal)
{
    if(!_current_flag) return;

    _module->operate(signal);

    if(_module->is_compelete())
    {
        _current_flag = false;

        QScopedPointer<ipp_vector<Ipp32f> > signal_data(_module->signal_data());
        emit dataProcessed(*signal_data);
    }
}
