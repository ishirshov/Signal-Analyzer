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

#ifndef VARS_H
#define VARS_H

#include <QObject>
#include <QMap>

#include <qwt_interval.h>

#include <ippdefs.h>

/*!
 * \brief Типы вейвлет коэффициентов ("банк")
 *        для вейвлет преобразования.
 */
enum waveletFilterBanks
{
    db2,    /*!< Коэффициенты Добеши D2 (см. http://wavelets.pybytes.com/wavelet/db2/). */
    db4,    /*!< Коэффициенты Добеши D4. */
    db6,    /*!< Коэффициенты Добеши D6. */
    db8,    /*!< Коэффициенты Добеши D8. */
    db10,   /*!< Коэффициенты Добеши D10. */
    db12,   /*!< Коэффициенты Добеши D12. */
    db14,   /*!< Коэффициенты Добеши D14. */
    db16,   /*!< Коэффициенты Добеши D16. */
    db18,   /*!< Коэффициенты Добеши D18. */
    db20,   /*!< Коэффициенты Добеши D20. */
    haar    /*!< Коэффициенты Хаара (см. http://wavelets.pybytes.com/wavelet/haar/). */
};

const Ipp32f c_B = 19.93156857;                             //!< Константа для преобразования уровней в децибеллы.
const Ipp32f c_Lvl = 1/c_B;                                 //!< Константа для преобразования децибеллов в уровни.
const Ipp32f c_V_FPGA_12bit = 4096;                         //!< Константа для преобразования уровней в вольты в 12 разрядном режиме для FPGA.
const Ipp32f c_V_FPGA_16bit = 32768;                        //!< Константа для преобразования уровней в вольты в 16 разрядном режиме для FPGA.
const Ipp32f c_V_FPGA_32bit = 2147483647;                   //!< Константа для преобразования уровней в вольты в 32 разрядном режиме для FPGA.
const Ipp32f c_V_DSP_12bit = 4096;                          //!< Константа для преобразования уровней в вольты в 12 разрядном режиме для DSP.
const Ipp32f c_V_GPP_12bit = 4096;                          //!< Константа для преобразования уровней в вольты в 12 разрядном режиме для GPP.
const Ipp32f c_Kalman_gain = 0.070;                         //!< Базовая константа усиления Калмана.
const Ipp32s c_Median_K = 31;                               //!< Базовая константа для коэфф. медианного фильтра.
const Ipp32s c_Transform_level = 1;                         //!< Базовая константа для уровня вейвлет преобразования.
const Ipp32s c_Default_Fs = 5000000;                        //!< Константа частоты дискретизации (по умолчанию).
const Ipp32s c_Default_Fn = 1000000;                        //!< Константа частоты сигнала (по умолчанию).
const Ipp32s c_Default_Amp = 2048;                          //!< Константа амплитуды сигнала (по умолчанию).
const Ipp32s c_Default_Noise = 0;                           //!< Константа амплитуды шума (по умолчанию).
const Ipp32s c_Default_Buffer_sz = 32768;                   //!< Константа размера буфера потока (по умолчанию).
const QwtInterval c_Fs_range = QwtInterval(1, 251000000);   //!< Константый интервал допустимого диапазона частоты дискретизации.
const QwtInterval c_Fn_range = QwtInterval(1, 126000000);   //!< Константый интервал допустимого диапазона частоты сигнала.
const QwtInterval c_Amp_range = QwtInterval(1, 4096);       //!< Константый интервал допустимого диапазона амплитуды сигнала.
const QwtInterval c_Noise_range = QwtInterval(0, 4096);     //!< Константый интервал допустимого диапазона амплитуды шума.
const waveletFilterBanks c_WaveletFilterBank = db2;         //!< Банк коэффициентов для вейвлет преобразования (по умолчанию).

/*!
 * \brief Класс GlobalVariables является производным от
 *        класса QObject.
 * \detailed Данный класс является реализацией паттерна
 *           "Signleton" и представляет глобальные переменные
 *           в наиболее защищенном виде для модификации.
 */
class GlobalVariables : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Функция позволяет получить
     *        доступ к глобальным переменным.
     * \return Ссылку на статический объект.
     */
    inline static GlobalVariables& getInstance()
    {
        static GlobalVariables values;
        return values;
    }

    /*!
     * \brief Функция позволяет получить коэффициент
     *        усиления Калмана.
     * \return Текущий коэффициент усиления Калмана.
     */
    float getKalmanGain() const { return _kalmanGain; }

    /*!
     * \brief Функция позволяет получить коэффициент
     *        преобразования уровней в вольты.
     * \return Текущий коэффициент преобразования
     *         уровней в вольты.
     */
    float getVoltsLevel() const { return _Vlts; }

    /*!
     * \brief Функция позволяет получить значение
     *        уровня вейвлет преобразования.
     * \return Теукщее значение уровня вейвлет преобразования.
     */
    int getTransformLevel() const { return _transformLvl; }

    /*!
     * \brief Функция позволяет получить коэффициент
     *        медианного фильтра.
     * \return Текущий коэффициент медианного фильтра.
     */
    int getMedianK() const { return _medianK; }

    /*!
     * \brief Функция позволяет получить значение
     *        частоты дискретизации.
     * \return Текущее значение частоты дискретизации.
     */
    ulong getSamplingFrequency() const { return _samplingFrequency; }

    /*!
     * \brief Функция позволяет получить размер
     *        буфера входного потока.
     * \return Текущий размер буфера входного потока.
     */
    int getBufferSize() const { return _bufferSize; }

    /*!
     * \brief Функция позволяет получить тип банка
     *        коэффициентов для вейвлет преобразования.
     * \return Текущий тип банка коэффициентов.
     */
    waveletFilterBanks getFilterBank() { return _filterBank; }

    /*!
     * \brief Функция позволяет получить список
     *        доступных коэффициентов вейвлет
     *        преобразования.
     * \return Текущий список доступных коэффициентов.
     */
    QList<QString> getWaveletFilterBanks() const;

public slots:
    /*!
     * \brief Функция позволяет установить
     *        коэффициент усиления Калмана.
     * \param[in] val Новый коэффициент усиления Калмана.
     */
    void setKalmanGain(double val);

    /*!
     * \brief Функция позволяет установить
     *        коэффициент преобразования уровней в вольты.
     * \param[in] val Новый коэффициент преобразования.
     */
    void setVoltsLevel(float val);

    /*!
     * \brief Функция позволяет установить уровень
     *        вейвлет преобразования.
     * \param[in] val Новый уровень вейвлет преобразования.
     */
    void setTransformLevel(int val);

    /*!
     * \brief Функция позволяет установить коэффициент
     *        медианного фильтра.
     * \param[in] val Новый коэффициент медианного фильтра.
     */
    void setMedianK(int val);

    /*!
     * \brief Функция позволяет установить
     *        значение частоты дискретизации.
     * \param[in] val Новое значение частоты дискретизации.
     */
    void setSamplingFrequency(ulong val);

    /*!
     * \brief Функция позволяет установить размер
     *        буфера входного потока.
     * \param[in] val Новое значение размера буфера.
     */
    void setBufferSize(int val);

    /*!
     * \brief Функция позволяет установить тип банка
     *        коэффициентов для вейвлет преобразования.
     * \param[in] val Новый тип банка коэффициентов.
     */
    void setFilterBank(const QString& val);

    /*!
     * \brief Функция позволяет установить значение
     *        флага блокировки изменения частоты
     *        дискретизации.
     * \param[in] val Флаг блокировки.
     */
    void setBlockSamplingFrequency(bool val);

signals:
    /*!
     * \brief Сигнал инициируется в после изменения
     *        коэффициент усиления Калмана.
     * \param[in] val Текущий коэффициент усиления Калмана.
     */
    void kalmanGainChanged(Ipp32f val);

    /*!
     * \brief Сигнал инициируется в после изменения
     *        коэффициент преобразования уровней в вольты.
     * \param[in] val Текущий коэффициент преобразования.
     */
    void voltsLevelChanged(Ipp32f val);

    /*!
     * \brief Сигнал инициируется в после изменения
     *        уровень вейвлет преобразования.
     * \param[in] val Текущий уровень вейвлет преобразования.
     */
    void transformLevelChanged(Ipp32s val);

    /*!
     * \brief Сигнал инициируется в после изменения
     *        коэффициент медианного фильтра.
     * \param[in] val Текущий коэффициент медианного фильтра.
     */
    void medianKChanged(Ipp32s val);

    /*!
     * \brief Сигнал инициируется в после изменения
     *        значение частоты дискретизации.
     * \param[in] val Новое значение частоты дискретизации.
     */
    void samplingFrequencyChanged(ulong val);

    /*!
     * \brief Сигнал инициируется в после изменения
     *        размер буфера входного потока.
     * \param[in] val Новое значение размера буфера.
     */
    void bufferSizeChanged(Ipp32s val);

    /*!
     * \brief Сигнал инициируется в после изменения
     *        типа банка коэффициентов для вейвлет преобразования.
     * \param[in] val Текущий тип банка коэффициентов.
     */
    void waveletFilterBankChanged(waveletFilterBanks val);

    /*!
     * \brief Сигнал инициируется в после изменения
     *        флага блокировки изменения частоты
     *        дискретизации.
     * \param[in] val Флаг блокировки.
     */
    void blockSamplingFrequencyChanged(bool val);

    /*!
     * \brief Сигнал инициируется в после включения
     *        панели подсчета ошибок в сигнале.
     * \param[in] val Флаг включения.
     */
    void rampSignalStyleDetected(bool val);

private:
    /*!
     * \brief Конструкто по умолчанию класса GlobalVariables.
     */
    GlobalVariables();

    /*!
     * \brief Копирующий конструктор класса GlobalVariables.
     * \param[in] b Ссылка на копируемый объект.
     */
    GlobalVariables(const GlobalVariables &b);

    /*!
     * \brief Оператор копирующего присваивания.
     * \param[in] b Ссылка на копируемый объект.
     * \return Ссылка на новый объект.
     */
    GlobalVariables& operator=(const GlobalVariables &b);

    /*!
     * \brief Деструктор класса GlobalVariables.
     */
    ~GlobalVariables() {}

    waveletFilterBanks _filterBank;                         //!< Тип банка коэффициентов вейвлет преобразования.
    Ipp32s _medianK;                                        //!< Коэффициент медианного фильтра.
    Ipp32s _transformLvl;                                   //!< Уровень преобразования вейвлет.
    Ipp32f _Vlts;                                           //!< Значение преобразования уровней в вольты.
    Ipp32f _kalmanGain;                                     //!< Коэффициент усиления фильтра Калмана.
    Ipp32s _samplingFrequency;                              //!< Частота дискретизации.
    Ipp32s _bufferSize;                                     //!< Размер буфера входного потока.
    bool _blockSamplingFrequency;                           //!< Флаг блокировки изменения частоты дискретизации.
    QMap<QString, waveletFilterBanks> _convertStringToEnum; //!< Список типов банка коэффициентов вейвлет преобразования.

};

#endif // VARS_H
