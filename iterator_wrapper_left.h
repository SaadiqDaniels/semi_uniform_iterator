/*!
 * @file iterator_wrapper_left.h
 * @author Saadiq Daniels
 * @date 31/12/2019
 * @version 0.5
 * @brief
 * 	The further specialization for pair iterators with a left base
 */

#ifndef TEMPL_ITERATOR_ITERATOR_WRAPPER_LEFT_H
#define TEMPL_ITERATOR_ITERATOR_WRAPPER_LEFT_H

#include "iterator_wrapper.h"

template<typename T, typename U>
class IteratorWrapperLeft : public IteratorWrapper<T, U>
{
	typedef typename make_mutable<T>::type                            MT;
	typedef typename make_const<T>::type                              CT;
	typedef typename make_mutable<U>::type                            MU;
	typedef typename make_const<U>::type                              CU;

public:
	/*!
	 * @brief Conversion constructor, takes an iterator
	 * @param iterator The iterator to store internally
	 */
	explicit IteratorWrapperLeft(CU &iterator) noexcept(true) : IteratorWrapper<T, U>(iterator) {
	}

	/*!
	 * @brief Conversion constructor, takes another iterator
	 * @param rhs The iterator to copy
	 */
	explicit IteratorWrapperLeft(const Iterator<T> &rhs) noexcept(true) : IteratorWrapper<T, U>(rhs) {
	}

	/*!
	 * @brief Copy constructor
	 * @param rhs The IteratorWrapperLeft to copy
	 */
	IteratorWrapperLeft(const IteratorWrapperLeft<T, U> &rhs) noexcept(true) : IteratorWrapper<T, U>(rhs) {
	}

	/*!
	 * @brief Default destructor
	 */
	virtual ~IteratorWrapperLeft() noexcept(true) = default;

	// Finding the return value of the dereference operator on the iterator
	typedef typename std::result_of<decltype(&U::operator*)(U)>::type RV;
	typedef typename pair_values<RV>::first                           first;
	typedef typename pair_values<RV>::second                          second;

	/*!
	 * @brief Dereference operator, const
	 * @return A const reference to the base class
	 */
	template<typename std::enable_if<std::is_const<T>::value, T>::type * = nullptr>
	T &operator*() const noexcept(true) {

		return (*IteratorWrapper<T, U>::_it).first;
	}

	template<typename std::enable_if<!std::is_const<T>::value, T>::type * = nullptr>
	T &operator*() const noexcept(true) {

		return const_cast<first &>((*IteratorWrapper<T, U>::_it).first);
	}

	/*!
	 * @brief Arrow operator, const
	 * @return A const pointer to the base class
	 */
	template<typename std::enable_if<std::is_const<T>::value, T>::type * = nullptr>
	T *operator->() const noexcept(true) {

		return &((*IteratorWrapper<T, U>::_it).first);
	}

	template<typename std::enable_if<!std::is_const<T>::value, T>::type * = nullptr>
	T *operator->() const noexcept(true) {

		return const_cast<first *>(&((*IteratorWrapper<T, U>::_it).first));
	}

	/*!
	 * @brief Copies this iterator
	 * @return A new, identical iterator
	 */
	virtual Iterator<T> *Copy() const noexcept(true) {

		return new IteratorWrapperLeft(IteratorWrapper<T, U>::_it);
	}
};

#endif //TEMPL_ITERATOR_ITERATOR_WRAPPER_LEFT_H
