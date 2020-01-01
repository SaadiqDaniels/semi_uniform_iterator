/*!
 * @file iterator_wrapper_right.h
 * @author Saadiq Daniels
 * @date 31/12/2019
 * @version 0.5
 * @brief
 * 	The further specialization for pair iterators with a right base
 */

#ifndef TEMPL_ITERATOR_ITERATOR_WRAPPER_RIGHT_H
#define TEMPL_ITERATOR_ITERATOR_WRAPPER_RIGHT_H

#include "iterator_wrapper.h"

template<typename T, typename U>
class IteratorWrapperRight : public IteratorWrapper<T, U>
{
	typedef typename MakeMutable<T>::type MT;
	typedef typename MakeConst<T>::type   CT;
	typedef typename MakeMutable<U>::type MU;
	typedef typename MakeConst<U>::type   CU;

public:
	/*!
	 * @brief Conversion constructor, takes an iterator
	 * @param iterator The iterator to store internally
	 */
	explicit IteratorWrapperRight(CU & iterator) noexcept(true) : IteratorWrapper<T, U>(iterator) {}

	/*!
	 * @brief Conversion constructor, takes another iterator
	 * @param rhs The iterator to copy
	 */
	explicit IteratorWrapperRight(const Iterator<T>& rhs) noexcept(true) : IteratorWrapper<T, U>(rhs) {}

	/*!
	 * @brief Copy constructor
	 * @param rhs The IteratorWrapperLeft to copy
	 */
	IteratorWrapperRight(const IteratorWrapperRight<T, U>& rhs) noexcept(true) : IteratorWrapper<T, U>(rhs) {}

	/*!
	 * @brief Default destructor
	 */
	virtual ~IteratorWrapperRight() noexcept(true) = default;

	/*!
	 * @brief Dereference operator
	 * @return A reference to the base class
	 */
	virtual T&operator*()  noexcept(true) {

		return IteratorWrapper<T, U>::_it->second;
	}

	/*!
	 * @brief Dereference operator, const
	 * @return A const reference to the base class
	 */
	virtual CT&operator*() const noexcept(true) {

		return IteratorWrapper<T, U>::_it->second;
	}

	/*!
	 * @brief Arrow operator
	 * @return A pointer to the base class
	 */
	virtual T*operator->()  noexcept(true) {

		return &(IteratorWrapper<T, U>::_it->second);
	}

	/*!
	 * @brief Arrow operator, const
	 * @return A const pointer to the base class
	 */
	virtual CT*operator->() const noexcept(true) {

		return &(IteratorWrapper<T, U>::_it->second);
	}

	/*!
	 * @brief Copies this iterator
	 * @return A new, identical iterator
	 */
	virtual Iterator<T>* Copy() const noexcept(true) {

		return new IteratorWrapperRight(IteratorWrapper<T, U>::_it);
	}
};

#endif //TEMPL_ITERATOR_ITERATOR_WRAPPER_RIGHT_H
