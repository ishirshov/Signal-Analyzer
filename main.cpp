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

#include "Graph/mainwindow.h"
#include "Graph/application.h"

Q_DECLARE_METATYPE(libsfbs_event_data_t)

Q_DECLARE_METATYPE(Ipp8s)
Q_DECLARE_METATYPE(Ipp16s)
Q_DECLARE_METATYPE(Ipp32s)
Q_DECLARE_METATYPE(Ipp64s)
Q_DECLARE_METATYPE(Ipp8u)
Q_DECLARE_METATYPE(Ipp16u)
Q_DECLARE_METATYPE(Ipp32u)
Q_DECLARE_METATYPE(Ipp64u)
Q_DECLARE_METATYPE(Ipp8sc)
Q_DECLARE_METATYPE(Ipp16sc)
Q_DECLARE_METATYPE(Ipp32sc)
Q_DECLARE_METATYPE(Ipp64sc)
Q_DECLARE_METATYPE(Ipp16uc)
Q_DECLARE_METATYPE(Ipp32fc)
Q_DECLARE_METATYPE(Ipp64fc)

Q_DECLARE_METATYPE(ipp_vector<Ipp16s>)
Q_DECLARE_METATYPE(ipp_vector<Ipp32s>)
Q_DECLARE_METATYPE(ipp_vector<Ipp64s>)
Q_DECLARE_METATYPE(ipp_vector<Ipp8u>)
Q_DECLARE_METATYPE(ipp_vector<Ipp32f>)
Q_DECLARE_METATYPE(ipp_vector<Ipp64f>)
Q_DECLARE_METATYPE(ipp_vector<Ipp16sc>)
Q_DECLARE_METATYPE(ipp_vector<Ipp32sc>)
Q_DECLARE_METATYPE(ipp_vector<Ipp64sc>)
Q_DECLARE_METATYPE(ipp_vector<Ipp32fc>)
Q_DECLARE_METATYPE(ipp_vector<Ipp64fc>)

void register_ipp_real_metatypes()
{
    qRegisterMetaType<Ipp8s>("Ipp8s");
    qRegisterMetaType<Ipp16s>("Ipp16s");
    qRegisterMetaType<Ipp32s>("Ipp32s");
    qRegisterMetaType<Ipp64s>("Ipp64s");

    qRegisterMetaType<Ipp8u>("Ipp8u");
    qRegisterMetaType<Ipp16u>("Ipp16u");
    qRegisterMetaType<Ipp32u>("Ipp32u");
    qRegisterMetaType<Ipp64u>("Ipp64u");

    qRegisterMetaType<Ipp32f>("Ipp32f");
    qRegisterMetaType<Ipp64f>("Ipp64f");
}

void register_ipp_complex_metatypes()
{
    qRegisterMetaType<Ipp8sc>("Ipp8sc");
    qRegisterMetaType<Ipp16sc>("Ipp16sc");
    qRegisterMetaType<Ipp32sc>("Ipp32sc");
    qRegisterMetaType<Ipp64sc>("Ipp64sc");

    qRegisterMetaType<Ipp16uc>("Ipp16uc");

    qRegisterMetaType<Ipp32fc>("Ipp32fc");
    qRegisterMetaType<Ipp64fc>("Ipp64fc");
}

void register_ipp_real_vector_metatypes()
{
    qRegisterMetaType<ipp_vector<Ipp16s> >("ipp_vector<Ipp16s>");
    qRegisterMetaType<ipp_vector<Ipp32s> >("ipp_vector<Ipp32s>");
    qRegisterMetaType<ipp_vector<Ipp64s> >("ipp_vector<Ipp64s>");

    qRegisterMetaType<ipp_vector<Ipp8u> >("ipp_vector<Ipp8u>");

    qRegisterMetaType<ipp_vector<Ipp32f> >("ipp_vector<Ipp32f>");
    qRegisterMetaType<ipp_vector<Ipp64f> >("ipp_vector<Ipp64f>");
}

void register_ipp_complex_vector_metatypes()
{
    qRegisterMetaType<ipp_vector<Ipp16sc> >("ipp_vector<Ipp16sc>");
    qRegisterMetaType<ipp_vector<Ipp32sc> >("ipp_vector<Ipp32sc>");
    qRegisterMetaType<ipp_vector<Ipp64sc> >("ipp_vector<Ipp64sc>");

    qRegisterMetaType<ipp_vector<Ipp32fc> >("ipp_vector<Ipp32fc>");
    qRegisterMetaType<ipp_vector<Ipp64fc> >("ipp_vector<Ipp64fc>");
}

void register_ipp_metatypes()
{
    register_ipp_real_metatypes();
    register_ipp_complex_metatypes();
    register_ipp_real_vector_metatypes();
    register_ipp_complex_vector_metatypes();
}

void register_metatypes()
{
    register_ipp_metatypes();
    qRegisterMetaType<libsfbs_event_data_t>("libsfbs_event_data_t");
}

int main(int argc, char *argv[])
try{
    Application app(argc, argv);

    register_metatypes();

    MainWindow window;
    window.show();

    return app.exec();
}
catch(std::exception &e){
    std::cerr << e.what() << '\n';
    return 1;
}
catch(...){
    std::cerr << "Unhandled exception.\n";
    return 2;
}
