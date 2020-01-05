/*!
 * @file iterator_wrapper.h
 * @author Saadiq Daniels
 * @date 23/12/2019
 * @version 1.5
 * @brief
 * 	The declaration of the iterator wrapper class, which extends from
 * 	the base iterator class
 */

#ifndef TEMPL_ITERATOR_ITERATOR_WRAPPER_H
#define TEMPL_ITERATOR_ITERATOR_WRAPPER_H

#include "iterator_base.h"

/*!
 * @brief The declaration of the iterator wrapper class
 * @tparam T The base class type
 * @tparam U The derived iterator type
 */
template<typename T, typename U>
class IteratorWrapper : public Iterator<T>
{
	typedef typename make_mutable<T>::type                            MT;
	typedef typename make_const<T>::type                              CT;
	typedef typename make_mutable<U>::type                            MU;
	typedef typename make_const<U>::type                              CU;

	//Figuring out if *operator returns a pair or not
	typedef typename std::result_of<decltype(&U::operator*)(U)>::type RV;

protected:
	/*!
	 * @brief The derived iterator to store internally
	 */
	MU _it;

public:
	/*!
	 * @brief Conversion constructor, taking a derived iterator
	 * @param iterator The derived iterator to store
	 */
	explicit IteratorWrapper(CU &iterator) noexcept(true) : Iterator<T>(this), _it(iterator) {
		//std::cout << typeid(RV).name() << std::endl;
		//std::cout << is_pair<RV>::value << std::endl;
	}

	/*!
	 * @brief Conversion constructor, using the iterator base class
	 * @param rhs The iterator to copy
	 */
	explicit IteratorWrapper(const Iterator<T> &rhs) noexcept(true) : Iterator<T>(this),
	                                                                  _it(reinterpret_cast<IteratorWrapper<T, U> *>(&rhs)->_it) {
	}

	/*!
	 * @brief Copy constructor
	 * @param rhs The IteratorWrapper to copy
	 */
	explicit IteratorWrapper(const IteratorWrapper<T, U> &rhs) noexcept(true) : Iterator<T>(this), _it(rhs._it) {
	}

	/*!
	 * @brief Virtual destructor
	 */
	virtual ~IteratorWrapper() noexcept(true) = default;

	/*!
	 * @brief Dereference operator
	 * @return A reference to the base class stored inside
	 */
	T &operator*() const noexcept(true) {

		if constexpr (!is_pair<RV>::value)
		{
			return *_it;
		}
	}

	/*!
	 * @brief Arrow operator
	 * @return A pointer to the base class stored inside
	 */
	T *operator->() const noexcept(true) {

		if constexpr (!is_pair<RV>::value)
		{
			return &*_it;
		}
	}

	/*!
	 * @brief Increment operator, moves the pointer forward
	 * @return A reference to the left hand object
	 */
	virtual Iterator<T> &operator++() noexcept(true) {

		++_it;
		return *this;
	}

	/*!
	 * @brief Assignment operator
	 * @param rhs The Iterator to copy
	 * @return A reference to the left hand object
	 */
	virtual Iterator<T> &operator=(const Iterator<T> &rhs) noexcept(true) {

		_it = reinterpret_cast<const IteratorWrapper<T, U> *>(&rhs)->_it;
		return *this;
	}

	/*!
	 * @brief Equality operator
	 * @param rhs The iterator to compare with
	 * @return True if the iterators are pointing at the same object
	 */
	virtual bool operator==(const Iterator<T> &rhs) const noexcept(true) {

		return _it == (reinterpret_cast<const IteratorWrapper<T, U> *>(&rhs))->_it;
	}

	/*!
	 * @brief Inequality operator
	 * @param rhs The iterator to compare with
	 * @return False if the iterators are pointing at the same object
	 */
	virtual bool operator!=(const Iterator<T> &rhs) const noexcept(true) {

		return !((*this) == rhs);
	}

	/*!
	 * @brief Copies this iterator
	 * @return A new, identical iterator
	 */
	virtual Iterator<T> *Copy() const noexcept(true) {

		return new IteratorWrapper<T, U>(_it);
	}
};

#endif //TEMPL_ITERATOR_ITERATOR_WRAPPER_H
