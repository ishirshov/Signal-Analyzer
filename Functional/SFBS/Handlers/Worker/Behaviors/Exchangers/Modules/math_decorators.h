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

#ifndef MATH_DECORATORS_H
#define MATH_DECORATORS_H

#include "math_module.h"

class MathDecorators : public MathModule
{
protected:
    MathModule *_module;

public:
    explicit MathDecorators(MathModule *module)
        :_module(module)
    {
        if(!_module)
            throw std::runtime_error("Mathematic module cannot be a nullpointer.");
        if(_module == this)
            throw std::runtime_error("Decorator cannot pointed to self-to-self.");
    }

    void operate(const ipp_vector<Ipp16s> &data) { _module->operate(data); }
    void clear() { _module->clear(); }

    virtual ipp_vector<Ipp32f>* signal_data() = 0;
    bool is_compelete() const { return _module->is_compelete(); }

    virtual ~MathDecorators() { delete _module; }

};

#endif // MATH_DECORATORS_H
