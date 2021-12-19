/*!
 * @file iterator.h
 * @author Saadiq Daniels
 * @date 23/12/2019
 * @version 2.0
 * @brief
 * 	This file includes all of the smaller files so that there is only one include file,
 * 	also includes helper functions
 */

#ifndef TEMPL_ITERATOR_ITERATOR_H
#define TEMPL_ITERATOR_ITERATOR_H

/*!
 * @brief Takes a type and removes const from that type
 * @tparam T The type to strip const off of
 */
template<typename T>
struct make_mutable : std::true_type
{
	typedef T type;
};

/*!
 * @brief Takes a type and removes const from that type
 * @tparam T The type to strip const off of
 */
template<typename T>
struct make_mutable<const T> : std::false_type
{
	typedef T type;
};

/*!
 * @brief Takes a type and returns the const type for that type
 * @tparam T The type to make const
 */
template<typename T>
struct make_const : std::false_type
{
	typedef const T type;
};

/*!
 * @brief Takes a type and returns the const type for that type
 * @tparam T The type to make const
 */
template<typename T>
struct make_const<const T> : std::true_type
{
	typedef const T type;
};

/*!
 * @brief Takes a type and returns false if it is not a pair
 * @tparam T The type to check
 */
template<typename T>
struct is_pair : std::false_type
{
};

/*!
 * @brief Takes a type and returns true if it is a pair
 * @tparam T The first pair parameter
 * @tparam U The second pair parameter
 */
template<typename T, typename U>
struct is_pair<std::pair<T, U>> : std::true_type
{
	typedef T first;
	typedef U second;
};
template<typename T, typename U>
struct is_pair<std::pair<T, U>&> : std::true_type
{
	typedef T first;
	typedef U second;
};

#include "iterator_base.h"
#include "iterator_wrapper.h"
#include "iterator_wrapper_left.h"
#include "iterator_wrapper_right.h"

/*!
 * @brief Creates an iterator
 * @tparam T The base type (must be specified)
 * @tparam U The derived iterator type (can be deduced) (vector.begin())
 * @param iterator The iterator to store internally
 * @return A new iterator
 */
template<typename T, typename U>
Iterator<T> MakeIterator(const U &iterator) {

	return static_cast<Iterator<T>>(*new IteratorWrapper<T, U>(iterator));
}

/*!
 * @brief Creates an iterator, should be used on pair based containers
 * that look like std::map< base_type , other_type >
 * @tparam T The base type (must be specified)
 * @tparam U The derived iterator type (can be deduced) (map.begin())
 * @param iterator The iterator to store internally
 * @return A new iterator
 */
template<typename T, typename U>
Iterator<T> MakeIteratorLeft(const U &iterator) {

	return static_cast<Iterator<T>>(*new IteratorWrapperLeft<T, U>(iterator));
}

/*!
 * @brief Creates and iterator, should be used on pair based containers
 * that look like std::map< other_type , base_type >
 * @tparam T The base type (must be specified)
 * @tparam U The derived iterator type (can be deduced) (map.begin())
 * @param iterator The iterator to store internally
 * @return A new iterator
 */
template<typename T, typename U>
Iterator<T> MakeIteratorRight(const U &iterator) {

	return static_cast<Iterator<T>>(*new IteratorWrapperRight<T, U>(iterator));
}

#endif //TEMPL_ITERATOR_ITERATOR_H