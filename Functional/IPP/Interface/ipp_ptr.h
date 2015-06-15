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

#ifndef IPP_PTR_H
#define IPP_PTR_H

#include <stdexcept>
#include "ipp_allocator.h"
#include "ipp_zero.h"

/*!
 * \brief Класс ipp_ptr реализует идиому интелектуального
 *        указатель, который управляет "голым" указателем
 *        и устраняет проблемы утечек памяти.
 */
template<class T>
class ipp_ptr
{
    T *_data; //!< Хранимый указатель

    /*!
     * \brief Копирующий конструктор класса ipp_ptr.
     * \param[in] b Ссылка на копируемый объект.
     */
    ipp_ptr(const ipp_ptr &b);

    /*!
     * \brief Оператор копирующего присваивания.
     * \param[in] b Ссылка на копируемый объект.
     * \return Ссылка на новый объект.
     */
    ipp_ptr& operator=(const ipp_ptr &b);

public:
    typedef T           value_type;         //!< Ссылка на тип данных.
    typedef T&          reference_type;     //!< Ссылка на тип данных со ссылкой.
    typedef T*          pointer_type;       //!< Ссылка на тип указателя.
    typedef const T*    const_pointer;      //!< Ссылка на константный тип указателя.

    /*!
     * \brief Конструктор класса ipp_ptr,
     *        принимающий в качестве аргумента
     *        хранимый указатель.
     * \param[in] p Хранимый указатель.
     */
    explicit ipp_ptr(pointer_type p = 0);

    /*!
     * \brief Конструктор класса ipp_ptr,
     *        принимающий в качестве аргумента
     *        размер для выделения памяти под
     *        хранимый указатель.
     * \param[in] size Размер памяти.
     */
    explicit ipp_ptr(Ipp32u size);

    /*!
     * \brief Функция позволяет освободить
     *        хранимый указатель из под
     *        управления данным классом.
     * \return Хранимый указатель.
     */
    pointer_type release();

    /*!
     * \brief Функция позволяет освободить
     *        ресурс занимаемый хранимым
     *        указателем и взять под управление
     *        новый указатель p.
     * \param[in] p Ноый указатель.
     */
    void reset(pointer_type p = 0);

    /*!
     * \brief Функция позволяет выполнить
     *        обмен хранимыми указателями
     *        между смежными классами.
     * \param[in] p Новый указатель.
     */
    void swap(ipp_ptr<T> &p);

    /*!
     * \brief Функция позволяет получить
     *        адрес хранимого указателя.
     * \return Адрес указателя.
     */
    pointer_type get() const;

    /*!
     * \brief Оператор позволяет выполнить
     *        сравнение адресов хранимых
     *        указателя.
     * \return Результат сравнения.
     */
    operator bool() const;

    /*!
     * \brief Перегруженный оператор разыменования.
     * \return Данные хранящиеся в первом элементе массива.
     */
    reference_type operator*() const;

    /*!
     * \brief Перегруженный оператор доступа к данным.
     * \return Хранимый указатель.
     */
    pointer_type operator->() const;

    /*!
     * \brief Перегруженный оператор индексированного
     *        доступа к данным массива.
     * \param[in] n Индекс.
     * \return Данный хранящиейся в N элементе массива.
     */
    reference_type operator[](int n) const;

    /*!
     * \brief Деструктор класса ipp_ptr.
     */
    virtual ~ipp_ptr();
};

template<class T>
ipp_ptr<T>::ipp_ptr(typename ipp_ptr<T>::pointer_type _p)
    :_data(_p)
{
}

template<class T>
ipp_ptr<T>::ipp_ptr(Ipp32u size)
    :_data(ipp_malloc<T>(size))
{
}

template<class T>
typename ipp_ptr<T>::pointer_type ipp_ptr<T>::release()
{
    pointer_type p = get();
    _data = 0;

    return p;
}

template<class T>
void ipp_ptr<T>::reset(pointer_type _p)
{
    ipp_free(_data);

    _data = _p;
}

template<class T>
void ipp_ptr<T>::swap(ipp_ptr<T>& p)
{
    pointer_type _pdata = p._data;
    p._data = _data;
    _data = _pdata;
}

template<class T>
typename ipp_ptr<T>::pointer_type ipp_ptr<T>::get() const
{
    return _data;
}

template<class T>
ipp_ptr<T>::operator bool() const
{
    return bool(_data);
}

template<class T>
typename ipp_ptr<T>::reference_type ipp_ptr<T>::operator*() const
{
    if(!_data)
        throw std::runtime_error("Null pointer cannot be dereferenced.");

    return *_data;
}

template<class T>
typename ipp_ptr<T>::pointer_type ipp_ptr<T>::operator->() const
{
    if(!_data)
        throw std::runtime_error("It is impossible to provide access to a null pointer.");

    return _data;
}

template<class T>
typename ipp_ptr<T>::reference_type ipp_ptr<T>::operator[](int n) const
{
    if(!_data)
        throw std::runtime_error("A null pointer contain no data.");

    return _data[n];
}

template<class T>
ipp_ptr<T>::~ipp_ptr()
{
    ipp_free(_data);
}

#endif // IPP_PTR_H
