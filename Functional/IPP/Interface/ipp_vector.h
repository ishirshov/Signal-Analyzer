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

#ifndef IPP_VECTOR_H
#define IPP_VECTOR_H

#include "ipp_copy.h"
#include "ipp_convert.h"
#include "ipp_allocator.h"
#include "ipp_set_value.h"
#include "ipp_ptr.h"

/*!
 * \brief Контейнер для хранения типов данных
 *        библиотеки Intel PP. Аналогичный вектор
 *        из библиотеки STL.
 */
template<class T>
class ipp_vector 
{
    static const Ipp32u fixed_min = 2;      //!< Минимальный размер свободного места вектора.

    Ipp32u space;                           //!< Размер массива _data.
    Ipp32u sz;                              //!< Размер занятого места.
    T *_data;                               //!< Указатель на массив с данными.
	
public:
    typedef T*            pointer;          //!< Ссылка на тип указателя.
    typedef const T*      const_pointer;    //!< Ссылка на константного тип указателя.
    typedef pointer		  iterator;         //!< Ссылка на тип итератора.
    typedef const_pointer const_iterator;   //!< Ссылка на константный тип итератора.
    typedef T             value_type;       //!< Ссылка на тип данных вектора.
    typedef Ipp32s        size_type;        //!< Ссылка на тип размера.
	
    /*!
     * \brief Конструктор класса ipp_vector,
     *        принимающий в качестве аргумента
     *        размер вектора.
     * \param[in] size Размер занятого места.
     */
	explicit ipp_vector(size_type size = 0);

    /*!
     * \brief Конструктор класса ipp_vector,
     *        принимающий в качестве аргументов
     *        размер вектора и значение для инициализации.
     * \param[in] size Размер занятого места.
     * \param[in] val  Значение по умолчанию для инициализации.
     */
	explicit ipp_vector(size_type size, T val);

    /*!
     * \brief Конструктор класса ipp_vector,
     *        принимающий в качестве аргументов
     *        указатель на массив данных длинной size.
     * \detailed Данный конструктор произведёт копирование
     *           массива длинной size. После чего вектор
     *           будет содержать данные из массива _data.
     * \param[in] _data Исходный указатель типа T.
     * \param[in] size Размер исходного указателя.
     */
    explicit ipp_vector(const pointer data, size_type size);

    /*!
     * \brief Конструктор класса ipp_vector,
     *        принимающий в качестве аргументов
     *        указатель на массив данных длинной size.
     * \detailed Данный конструктор произведёт преобразование
     *           массива длинной size из типа U в тип T. После
     *           чего вектор будет содержать данные из массива
     *           _data.
     * \param[in] _data Исходный указатель типа U.
     * \param[in] size Размер исходного указателя.
     */
	template<class U> ipp_vector(const U *_data, size_type size);	

    /*!
     * \brief Копирующий конструктор класса ipp_vector.
     * \param[in] b Ссылка на копируемый объект.
     */
    ipp_vector(const ipp_vector &b);

    /*!
     * \brief Оператор копирующего присваивания.
     * \param[in] b Ссылка на копируемый объект.
     * \return Ссылка на новый объект.
     */
    ipp_vector& operator=(const ipp_vector &b);

    /*!
     * \brief Копирующий конструктор класса ipp_vector.
     * \param[in] b Ссылка на копируемый объект типа U.
     */
    template<class U> ipp_vector(const ipp_vector<U> &b);

    /*!
     * \brief Оператор копирующего присваивания.
     * \param[in] b Ссылка на копируемый объект типа U.
     * \return Ссылка на новый объект типа T.
     */
    template<class U> ipp_vector& operator=(const ipp_vector<U> &b);
	
    /*!
     * \brief Функция позволяет получить последний
     *        элемент вектора.
     * \return Константное значение последнего элемента вектора.
     */
    const value_type& back() const { return _data[sz-1]; }

    /*!
     * \brief Функция позволяет получить последний
     *        элемент вектора.
     * \return Значение последнего элемента вектора.
     */
    value_type& back() { return _data[sz-1]; }

    /*!
     * \brief Функция позволяет получить первый
     *        элемент вектора.
     * \return Константное значение первого элемента вектора.
     */
    const value_type& front() const { return *_data; }

    /*!
     * \brief Функция позволяет получить первый
     *        элемент вектора.
     * \return Значение первого элемента вектора.
     */
    value_type& front() { return *_data; }

    /*!
     * \brief Перегруженный оператор индексированного доступа.
     * \param[in] n Индекс элемента.
     * \return Константное значение n-ого элемента вектора.
     */
	const value_type& operator[](size_type n) const { return _data[n]; }

    /*!
     * \brief Перегруженный оператор индексированного доступа.
     * \param[in] n Индекс элемента.
     * \return Значение n-ого элемента вектора.
     */
	value_type& operator[](size_type n) { return _data[n]; }
	
    /*!
     * \brief Функция позволяет получить итератор
     *        указывающий на начало вектора.
     * \return Итератор вектора.
     */
	iterator begin() { return _data; }

    /*!
     * \brief Функция позволяет получить итератор
     *        указывающий на начало вектора.
     * \return Константный итератор вектора.
     */
	const_iterator cbegin() const { return _data; }

    /*!
     * \brief Функция позволяет получить итератор
     *        указывающий на конец вектора.
     * \return Итератор вектора.
     */
	iterator end() { return _data + sz; }

    /*!
     * \brief Функция позволяет получить итератор
     *        указывающий на конец вектора.
     * \return Константный итератор вектора.
     */
	const_iterator cend() const { return _data + sz; }

    /*!
     * \brief Функция позволяет получить указатель
     *        на массив хранящий значения вектора.
     * \return Константный указатель на внутренний массив.
     */
    const_pointer data() const { return _data; }

    /*!
     * \brief Функция позволяет получить указатель
     *        на массив хранящий значения вектора.
     * \return Указатель на внутренний массив.
     */
    pointer data() { return _data; }

    /*!
     * \brief Функция позволяет получить информацию
     *        о свободном месте в векторе.
     * \return Количество свободного места.
     */
    size_type available_space() const { return space - sz; }

    /*!
     * \brief Функция позволяет получить информацию
     *        о занятом месте в векторе.
     * \return Количество занятого места.
     */
	size_type size() const { return sz; }

    /*!
     * \brief Функция позволяет получить информацию
     *        о размере внутреннего массива.
     * \return Размер внутреннего массива.
     */
	size_type capacity() const { return space; }

    /*!
     * \brief Функция позволяет получить информацию
     *        о полноте вектора.
     * \return Полон или нет.
     */
	bool empty() const { return cbegin() == cend(); }

    /*!
     * \brief Функция копирует все данные вектора
     *        в новый массив с размером size().
     * \return Указатель на массив.
     */
    pointer to_pointer() const;

    /*!
     * \brief Функция копирует все данные вектора
     *        в новый массив с размером size().
     * \return Указатель на массив типа U.
     */
    template<class U> U* to_pointer() const;
	
    /*!
     * \brief Функция позволяет добавить значение
     *        в конец вектора.
     * \param[in] val Новое значение.
     */
    void push_back(value_type val);

    /*!
     * \brief Функция позволяет добавить массив
     *        размером size в конец вектора.
     * \param[in] data Указатель на массив.
     * \param[in] size Размера массива.
     */
    void push_back(const_pointer data, size_type size);

    /*!
     * \brief Функция позволяет добавить массив
     *        типа U размером size в конец вектора.
     * \param[in] _data Указатель на массив типа U.
     * \param[in] size Размера массива.
     */
    template<class U> void push_back(const U *_data, size_type size);

    /*!
     * \brief Функция позволяет добавить вектор
     *        размером size в конец вектора.
     * \param[in] vector Ссылка на копируемый вектор.
     * \param[in] size Размера копируемых элементов вектора.
     */
    void push_back(const ipp_vector<value_type> &vector, size_type size);

    /*!
     * \brief Функция позволяет добавить вектор
     *        типа U размером size в конец вектора.
     * \param[in] vector Ссылка на копируемый вектор.
     * \param[in] size Размера копируемых элементов вектора.
     */
    template<class U> void push_back(const ipp_vector<U> &vector, size_type size);

    /*!
     * \brief Функция позволяет зарезервировать
     *        дополнительное место для данных
     *        вектора.
     * \param[in] capacity Количество резервируемого места.
     */
	void reserve(size_type capacity);

    /*!
     * \brief Функция позволяет изменить размер
     *        вектора.
     * \param size Новый размер вектора.
     * \param val Значение инициализации
     *            (данное значение используется,
     *             если размер вектора больше текущего).
     */
	void resize(size_type size, value_type val = T());

    /*!
     * \brief Выравнить размер внутренней памяти
     *        по границе размера size().
     */
	void shrink_to_fit();

    /*!
     * \brief Функция позволяет очистить данные
     *        из вектора.
     */
    void clear() { sz = 0; }

    /*!
     * \brief Функция выполняет обмен указателями
     *        внутренних массивов.
     * \param[in] b Вектор обмена.
     */
    void swap(ipp_vector &b);

    /*!
     * \brief Функция выполняет обмен указателями
     *        внутренних массивов.
     * \param[in] b Вектор обмена типа U.
     */
    template<class U> void swap(ipp_vector<U> &b);

    /*!
     * \brief Деструктор класса ipp_vector.
     */
	virtual ~ipp_vector();

private:
    /*!
     * \brief Функция инициализации внутреннего
     *        массива данных.
     * \param[in] size Размер внутреннего массива.
     * \param[in] value Значение для инициализации.
     */
    void init_construct(size_type size, value_type value = T());

    /*!
     * \brief Функция копирует данные из указателя
     *        _data размером size в текущий массив
     *        данных.
     * \param _data Копируемый массив.
     * \param size Размер копируемого массива.
     */
    void copy_construct(const T *_data, size_type size);

    /*!
     * \brief Функция копирует данные из указателя
     *        _data размером size в текущий массив
     *        данных.
     * \param _data Копируемый массив типа U.
     * \param size Размер копируемого массива.
     */
    template<class U> void conv_construct(const U *_data, size_type size);

};

template<class T>
ipp_vector<T>::ipp_vector(typename ipp_vector<T>::size_type size)
{
    init_construct(size);
}

template<class T>
ipp_vector<T>::ipp_vector(typename ipp_vector<T>::size_type size, T val)
{
    init_construct(size, val);
}

template<class T>
ipp_vector<T>::ipp_vector(const typename ipp_vector<T>::pointer data,
								typename ipp_vector<T>::size_type size)
{	
    copy_construct(data, size);
}

template<class T>
template<class U>
ipp_vector<T>::ipp_vector(const U *data, typename ipp_vector<T>::size_type size)
{
    conv_construct(data, size);
}

template<class T>
ipp_vector<T>::ipp_vector(const ipp_vector<T> &v)
{
    copy_construct(v._data, v.sz);
}

template<class T>
ipp_vector<T>& ipp_vector<T>::operator=(const ipp_vector<T> &v)
{    
    size_type new_sz = v.sz;

    if(new_sz > 0) {
        reserve(new_sz);
        ipp_copy(v._data, _data, new_sz);
    }

    sz = new_sz;
	return *this;
}

template<class T>
template<class U>
ipp_vector<T>::ipp_vector(const ipp_vector<U> &v)
{
    conv_construct(v.data(), v.size());
}

template<class T>
template<class U>
ipp_vector<T>& ipp_vector<T>::operator=(const ipp_vector<U> &v)
{
    size_type new_sz = v.size();

    if(new_sz > 0) {
        reserve(new_sz);
        ipp_convert(v.data(), _data, new_sz);
    }

    sz = new_sz;
	return *this;
}

template<class T>
void ipp_vector<T>::push_back(typename ipp_vector<T>::value_type val)
{
	if(sz == space)	
		reserve(sz * 2);

	_data[sz] = val;
	++sz;
}

template<class T>
void ipp_vector<T>::push_back(typename ipp_vector<T>::const_pointer data,
                              typename ipp_vector<T>::size_type size)
{
    if(!data || (size < 1)) return;

    if((size + sz) > space) reserve(size + sz);

    ipp_copy(data, _data + sz, size);

    sz += size;
}

template<class T>
template<class U>
void ipp_vector<T>::push_back(const U *data, typename ipp_vector<T>::size_type size)
{
    if(!data || (size < 1)) return;

    if((size + sz) > space) reserve(size + sz);

    ipp_convert(data, _data + sz, size);

    sz += size;
}

template<class T>
void ipp_vector<T>::push_back(const ipp_vector<T> &vector, size_type size)
{
    if(vector.empty() || (vector.size() < size)) return;

    if((size + sz) > space) reserve(size + sz);

    ipp_copy(vector.data(), _data + sz, size);

    sz += size;
}

template<class T>
template<class U>
void ipp_vector<T>:: push_back(const ipp_vector<U> &vector, size_type size)
{
    if(vector.empty() || (vector.size() < size)) return;

    if((size + sz) > space) reserve(size + sz);

    ipp_convert(vector.data(), _data + sz, size);

    sz += size;
}

template<class T>
void ipp_vector<T>::reserve(typename ipp_vector<T>::size_type capacity)
{
	if(capacity <= space) return;
		
	ipp_ptr<T> new_data(ipp_malloc<T>(capacity));
		
    if(sz > 0)
        ipp_copy(_data, new_data.get(), sz);
    ipp_free(_data);
	
	_data = new_data.release();	
	space = capacity;
}

template<class T>
void ipp_vector<T>::resize(typename ipp_vector<T>::size_type size, 
						   typename ipp_vector<T>::value_type value)
{
    if(size == sz || size < 0) return;

    if(size < sz) {
        sz = size;

        shrink_to_fit();
    }
	else if(size > sz) 
	{
        reserve(size);

        ipp_set(value, _data + sz, size - sz);
		sz = size;
	}
}

template<class T>
void ipp_vector<T>::shrink_to_fit()
{
	if((space == sz) || (space == fixed_min)) return;
	
	if(space > sz)
	{
        int shrink_size = (sz < fixed_min) ? (fixed_min) : (sz);
		ipp_ptr<T> shrink_data(ipp_malloc<T>(shrink_size));

        ipp_copy(_data, shrink_data.get(), shrink_size);
        ipp_free(_data);
	
		_data = shrink_data.release();
		space = shrink_size;
	}
}

template<class T>
template<class U>
void ipp_vector<T>::swap(ipp_vector<U>& v)
{
	// Save swap data.
	ipp_ptr<T> old_data(_data);
	const size_type old_size = sz;

	// Reset old data and construct new.
    conv_construct(v.data(), v.size());

	// Then move values into old data to vector v.
    v.clear();
    v.copy_back(old_data.get(), v.size());
}

template<class T>
void ipp_vector<T>::swap(ipp_vector<T>& v)
{
	// Save swap data.
    ipp_ptr<T> old_data(v._data);
    const size_type old_size = v.sz;
    const size_type old_space = v.space;

	// Move this vector data to vector v.
	v._data = _data;
	v.sz = sz;
	v.space = space;

	// And move saved data from vector v.
    _data = old_data.release();
    sz = old_size;
    space = old_space;
}

template<class T>
typename ipp_vector<T>::pointer ipp_vector<T>::to_pointer() const
{
    ipp_ptr<T> p;

    if(sz > 0) {
        p.reset(ipp_malloc<T>(sz));
        ipp_copy(_data, p.get(), sz);
    }

	return p.release();
}

template<class T>
template<class U>
U* ipp_vector<T>::to_pointer() const
{
    ipp_ptr<U> p;

    if(sz > 0) {
        p.reset(ipp_malloc<U>(sz));
        ipp_convert(_data, p.get(), sz);
    }
	
	return p.release();
}

template<class T>
ipp_vector<T>::~ipp_vector()
{
    ipp_free(_data);
}

template<class T>
void ipp_vector<T>::init_construct(typename ipp_vector<T>::size_type size,
                                   typename ipp_vector<T>::value_type value)
{
    space = (size > 0) ? (size) : (fixed_min);
	_data = ipp_malloc<T>(space);	

    if(size > 0) {
        sz = size;
        ipp_set(value, _data, sz);
    }
    else sz = 0;
}

template<class T>
void ipp_vector<T>::copy_construct(const T *_src, size_type size)
{
    if(!_src)
        throw std::runtime_error("Can not initialize vector from null pointer.");

    space = (size > 0) ? (size) : (fixed_min);
    _data = ipp_malloc<T>(space);

    if(size > 0) {
        sz = size;
        ipp_copy(_src, _data, sz);
    }
    else sz = 0;
}

template<class T>
template<class U>
void ipp_vector<T>::conv_construct(const U *_src, typename ipp_vector<T>::size_type size)
{
    if(!_src)
        throw std::runtime_error("Can not initialize vector from null pointer.");

    space = (size > 0) ? (size) : (fixed_min);
    _data = ipp_malloc<T>(space);

    if(size > 0) {
        sz = size;
        ipp_convert(_src, _data, sz);
    }
    else sz = 0;
}

#endif // IPP_VECTOR_H
