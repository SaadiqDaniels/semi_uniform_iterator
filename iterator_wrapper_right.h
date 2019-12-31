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
	IteratorWrapperRight(CU & iterator) noexcept(true) : IteratorWrapper<T, U>(iterator) {}

	IteratorWrapperRight(const Iterator<T>& rhs) noexcept(true) : IteratorWrapper<T, U>(rhs) {}

	IteratorWrapperRight(const IteratorWrapperRight<T, U>& rhs) noexcept(true) : IteratorWrapper<T, U>(rhs) {}

	virtual ~IteratorWrapperRight() noexcept(true) = default;

	virtual T&operator*()  noexcept(true) {

		return IteratorWrapper<T, U>::_it->second;
	}

	virtual CT&operator*() const noexcept(true) {

		return IteratorWrapper<T, U>::_it->second;
	}

	virtual T*operator->()  noexcept(true) {

		return &(IteratorWrapper<T, U>::_it->second);
	}

	virtual CT*operator->() const noexcept(true) {

		return &(IteratorWrapper<T, U>::_it->second);
	}

	virtual Iterator<T>* Copy() const noexcept(true) {

		return new IteratorWrapperRight(IteratorWrapper<T, U>::_it);
	}
};

#endif //TEMPL_ITERATOR_ITERATOR_WRAPPER_RIGHT_H
