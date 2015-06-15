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

#ifndef SFBS_GET_INFO_H
#define SFBS_GET_INFO_H

#include "Functional/SFBS/Channels/Interfaces/ipc_state.h"

class sfbsGetInfo : public IPCState
{
    IsomorphPanel *_panel;
    bool _is_exec;

public:
    sfbsGetInfo(IsomorphPanel *panel);

    void sendMessage();
    void messageReceive(void *msg);

};

#endif // SFBS_GET_INFO_H
