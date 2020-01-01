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
	typedef typename MakeMutable<T>::type MT;
	typedef typename MakeConst<T>::type   CT;
	typedef typename MakeMutable<U>::type MU;
	typedef typename MakeConst<U>::type   CU;

public:
	/*!
	 * @brief Conversion constructor, takes an iterator
	 * @param iterator The iterator to store internally
	 */
	explicit IteratorWrapperLeft(CU & iterator) noexcept(true) : IteratorWrapper<T, U>(iterator) {}

	/*!
	 * @brief Conversion constructor, takes another iterator
	 * @param rhs The iterator to copy
	 */
	explicit IteratorWrapperLeft(const Iterator<T>& rhs) noexcept(true) : IteratorWrapper<T, U>(rhs) {}

	/*!
	 * @brief Copy constructor
	 * @param rhs The IteratorWrapperLeft to copy
	 */
	IteratorWrapperLeft(const IteratorWrapperLeft<T, U>& rhs) noexcept(true) : IteratorWrapper<T, U>(rhs) {}

	/*!
	 * @brief Default destructor
	 */
	virtual ~IteratorWrapperLeft() noexcept(true) = default;

	/*!
	 * @brief Dereference operator
	 * @return A reference to the base class
	 */
	virtual T&operator*()  noexcept(true) {

		return IteratorWrapper<T, U>::_it->first;
	}

	/*!
	 * @brief Dereference operator, const
	 * @return A const reference to the base class
	 */
	virtual CT&operator*() const noexcept(true) {

		return IteratorWrapper<T, U>::_it->first;
	}

	/*!
	 * @brief Arrow operator
	 * @return A pointer to the base class
	 */
	virtual T*operator->()  noexcept(true) {

		return &(IteratorWrapper<T, U>::_it->first);
	}

	/*!
	 * @brief Arrow operator, const
	 * @return A const pointer to the base class
	 */
	virtual CT*operator->() const noexcept(true) {

		return &(IteratorWrapper<T, U>::_it->first);
	}

	/*!
	 * @brief Copies this iterator
	 * @return A new, identical iterator
	 */
	virtual Iterator<T>* Copy() const noexcept(true) {

		return new IteratorWrapperLeft(IteratorWrapper<T, U>::_it);
	}
};

#endif //TEMPL_ITERATOR_ITERATOR_WRAPPER_LEFT_H
