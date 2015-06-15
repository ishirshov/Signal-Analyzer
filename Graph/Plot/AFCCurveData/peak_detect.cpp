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

#include "peak_detect.h"

Ipp32f* get_peaks(const Ipp32f *pSrc, int n, int k, Ipp32f h, peakFunctionType type)
{
    // This function allows you to identify peaks
    // in a given time-series and select them for
    // further analysis.

    // Compute peak function value for
    // each of the N points in pSrc.
    ipp_ptr<Ipp32f> avg;

    switch (type)
    {
    case S1:
        avg.reset(fS1(pSrc, n, k));
        break;
    case S2:
        avg.reset(fS2(pSrc, n, k));
        break;
    case S3:
        avg.reset(fS3(pSrc, n, k));
        break;
    case S3_mod:
        avg.reset(fS3_mod(pSrc, n, k));
        break;
    default:
        return avg.release();
    }

    // Compute the mean value and standard
    // deviation stddev of all positive values
    // in array avg.
    Ipp32f mean = 0;
    Ipp32f stddev = 0;

    IppStatus status = ippsMeanStdDev_32f(avg.get(), n, &mean, &stddev, ippAlgHintFast);
    if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

    // Remove local peak which are "small"
    // in global context.
    quint32 i = 0;

    ipp_ptr<Ipp32f> peaks(ippsMalloc_32f(n));
    ipp_zero(peaks.get(), n);

    // Order peaks in peaks array in terms of
    // increasing index.
    while(i < n)
    {
        Ipp32f val = avg[i];

        if(val > 0)
            if((val - mean) > (h * stddev))
                peaks[i] = val;

        ++i;
    }

    // Retain only one peak out of any set
    // of peaks within distance k of each other.
    Ipp32f *yj = peaks.get(); // First element.
    Ipp32f *yn = &peaks[n];   // Last element.
    Ipp32f *yi = yj + 1;      // Element iterator.

    // If distance in pair yj and yi equal
    // (yi - yj) <= k then remove lower peak from peaks array.
    while(yi < yn)
    {
        if(*yi != 0)
        {
            if((yi - yj) <= k)
            {
                if(*yj > *yi) *yi = 0.0;
                else
                {
                    *yj = 0.0;
                    yj = yi;
                }
            }
            else yj = yi;
        }

        ++yi;
    }

    return peaks.release();
}

Ipp32f* fS1(const Ipp32f *pSrc, int n, int k)
{
    if(!pSrc) throw std::runtime_error("Cannot handle nullpointer.");
    if(n < k) throw std::runtime_error("Windows value must be greather length of array.");

    ipp_ptr<Ipp32f> avg(ippsMalloc_32f(n));
    ipp_zero(avg.get(), n);

    ipp_ptr<Ipp32f> left_vals(ippsMalloc_32f(k));
    ipp_ptr<Ipp32f> rigth_vals(ippsMalloc_32f(k));

    n = n - k;
    for(quint32 i = k; i < n; ++i)
    {
        Ipp32f x = pSrc[i];

        for(quint32 m = 0; m < k; ++m)
        {
            left_vals[m] = x - pSrc[i - m];
            rigth_vals[m] = x - pSrc[i + m];
        }

        Ipp32f left_max = 0.0;
        Ipp32f right_max = 0.0;

        IppStatus status = ippsMax_32f(left_vals.get(), k, &left_max);
        if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

        status = ippsMax_32f(rigth_vals.get(), k, &right_max);
        if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

        avg[i] = (left_max + right_max)/2;
    }

    return avg.release();
}

Ipp32f *fS2(const Ipp32f *pSrc, int n, int k)
{
    if(!pSrc) throw std::runtime_error("Cannot handle nullpointer.");
    if(n < k) throw std::runtime_error("Windows value must be greather length of array.");

    ipp_ptr<Ipp32f> avg(ippsMalloc_32f(n));
    ipp_zero(avg.get(), n);

    n -= k;
    for(quint32 i = k; i < n; ++i)
    {
        Ipp32f x = pSrc[i];

        Ipp32f left_val = 0.0;
        Ipp32f right_val = 0.0;

        for(quint32 m = 0; m < k; ++m)
        {
            left_val += x - pSrc[i - m];
            right_val += x - pSrc[i + m];
        }

        left_val /= k;
        right_val /= k;

        avg[i] = (left_val + right_val)/2;
    }

    return avg.release();
}

Ipp32f* fS3(const Ipp32f *pSrc, int n, int k)
{
    if(!pSrc) throw std::runtime_error("Cannot handle nullpointer.");
    if(n < k) throw std::runtime_error("Windows value must be greather length of array.");

    ipp_ptr<Ipp32f> avg(ippsMalloc_32f(n));
    ipp_zero(avg.get(), n);

    n = n - k;
    for(quint32 i = k; i < n; ++i)
    {
        Ipp32f left_val = 0.0;
        Ipp32f right_val = 0.0;

        for(quint32 m = 0; m < k; ++m)
        {
            left_val += pSrc[i - m];
            right_val += pSrc[i + m];
        }

        Ipp32f x = pSrc[i];

        left_val = x - (left_val/k);
        right_val = x - (right_val/k);
        avg[i] = (left_val + right_val)/2;
    }

    return avg.release();
}

Ipp32f *fS3_mod(const Ipp32f *pSrc, int n, int k)
{
    if(!pSrc) throw std::runtime_error("Cannot handle nullpointer.");
    if(n < k) throw std::runtime_error("Windows value must be greather length of array.");

    ipp_ptr<Ipp32f> avg(ippsMalloc_32f(n));
    ipp_zero(avg.get(), n);

    n = n - k;
    quint32 m = k * 2;

    for(quint32 i = k; i < n; ++i)
    {
        Ipp32f sum = 0.0;

        IppStatus status = ippsSum_32f(pSrc + i, m, &sum, ippAlgHintFast);
        if(status != ippStsNoErr) throw std::runtime_error(ippGetStatusString(status));

        avg[i] = sum / m;
        avg[i] = pSrc[i] - avg[i];
        avg[i] = avg[i] / 2;
    }

    return avg.release();
}
