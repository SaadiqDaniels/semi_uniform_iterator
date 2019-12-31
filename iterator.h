/*!
 * @file iterator.h
 * @author Saadiq Daniels
 * @date 23/12/2019
 * @version 1.0
 * @brief
 * 	This file includes all of the smaller files so that ther is only one include file,
 * 	also includes a helper function
 */

#ifndef TEMPL_ITERATOR_ITERATOR_H
#define TEMPL_ITERATOR_ITERATOR_H

template<typename T>
struct MakeMutable
{
	typedef T type;
};

template<typename T>
struct MakeMutable<const T>
{
	typedef T type;
};

template<typename T>
struct MakeConst
{
	typedef const T type;
};

template<typename T>
struct MakeConst<const T>
{
	typedef const T type;
};

#include "iterator_base.h"
#include "iterator_wrapper.h"
#include "iterator_wrapper_left.h"
#include "iterator_wrapper_right.h"

/*!
 * @brief Creates an iterator and associated handle
 * @tparam T The base type (must be specified)
 * @tparam U The derived iterator type (can be deduced) (vector.begin())
 * @param iterator The derived iterator to store
 * @return A new iterator
 */
template<typename T, typename U>
Iterator<T> MakeIterator(const U &iterator) {

	return *new IteratorWrapper<T, U>(iterator);
}

template<typename T, typename U>
Iterator<T> MakeIteratorLeft(const U &iterator) {

	return *new IteratorWrapperLeft<T, U>(iterator);
}

template<typename T, typename U>
Iterator<T> MakeIteratorRight(const U &iterator) {

	return *new IteratorWrapperRight<T, U>(iterator);
}

#endif //TEMPL_ITERATOR_ITERATOR_H