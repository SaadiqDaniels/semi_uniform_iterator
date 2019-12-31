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
	IteratorWrapperLeft(CU & iterator) noexcept(true) : IteratorWrapper<T, U>(iterator) {}

	IteratorWrapperLeft(const Iterator<T>& rhs) noexcept(true) : IteratorWrapper<T, U>(rhs) {}

	IteratorWrapperLeft(const IteratorWrapperLeft<T, U>& rhs) noexcept(true) : IteratorWrapper<T, U>(rhs) {}

	virtual ~IteratorWrapperLeft() noexcept(true) = default;

	virtual T&operator*()  noexcept(true) {

		return IteratorWrapper<T, U>::_it->first;
	}

	virtual CT&operator*() const noexcept(true) {

		return IteratorWrapper<T, U>::_it->first;
	}

	virtual T*operator->()  noexcept(true) {

		return &(IteratorWrapper<T, U>::_it->first);
	}

	virtual CT*operator->() const noexcept(true) {

		return &(IteratorWrapper<T, U>::_it->first);
	}

	virtual Iterator<T>* Copy() const noexcept(true) {

		return new IteratorWrapperLeft(IteratorWrapper<T, U>::_it);
	}
};

#endif //TEMPL_ITERATOR_ITERATOR_WRAPPER_LEFT_H
