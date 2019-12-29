/*!
 * @file iterator_base.h
 * @author Saadiq Daniels
 * @date 23/12/2019
 * @version 1.0
 * @brief
 * 	The iterator base class, not const qualified. Provides an
 * 	interface to the more templatized derived class
 */

#ifndef TEMPL_ITERATOR_ITERATOR_BASE_H
#define TEMPL_ITERATOR_ITERATOR_BASE_H

#include <algorithm>

template<typename T, typename U>
class IteratorWrapper;

/*!
 * @brief The base iterator class
 * @tparam T The base iterator type
 */
template<typename T>
class Iterator
{
	Iterator<T> *_data;
	int         *_RC;

	/*!
	 * @brief Copies the reference if it is needed
	 */
	void CopyIf() noexcept(true) {

		if (*_RC > 1)
		{
			--*_RC;
			_data = Copy();
			_RC   = new int(1);
		}
	}

	/*!
	 * @brief Deletes the object if needed
	 */
	void DeleteIf() noexcept(true) {

		if (!--*_RC)
		{
			// If this is the last instance delete the data
			delete _data;
			delete _RC;
		}
	}

public:
	/*!
	 * @brief Copy constructor
	 * @param rhs The Iterator to copy from
	 */
	Iterator(const Iterator<T> &rhs) noexcept(true) : _data(rhs._data), _RC(&++*rhs._RC) {
	}

	/*!
	 * @brief Move constructor (previous object has null values afterward)
	 * @param rhs The iterator to swap with
	 */
	Iterator(Iterator<T> &&rhs) noexcept(true) : _data(rhs._data), _RC(rhs._RC) {

		rhs._data = nullptr;
		rhs._RC   = nullptr;
	}

	/*!
	 * @brief Conversion constructor, takes an iterator wrapper class
	 * @tparam U The derived template type
	 * @param rhs The iterator to copy
	 */
	template<typename U>
	Iterator(IteratorWrapper<T, U> *rhs) noexcept(true) : _data(rhs), _RC(new int(0)) {
	}

	/*!
	 * @brief Virtual destructor
	 */
	virtual ~Iterator() noexcept(true) {

		DeleteIf();
	}

	/*!
	 * @brief Dereference operator
	 * @return A reference to the base class stored inside
	 */
	virtual T &operator*() noexcept(true) {

		CopyIf();
		return **_data;
	}

	/*!
	 * @brief Dereference operator
	 * @return A reference to the base class stored inside
	 */
	virtual const T &operator*() const noexcept(true) {

		return **_data;
	}

	/*!
	 * @brief Arrow operator
	 * @return A pointer to the base class stored inside
	 */
	virtual T *operator->() noexcept(true) {

		CopyIf();
		return &**_data;
	}

	/*!
	 * @brief Arrow operator
	 * @return A pointer to the base class stored inside
	 */
	virtual const T *operator->() const noexcept(true) {

		return &**_data;
	}

	/*!
	 * @brief Increment operator, moves the pointer forward
	 * @return A reference to the left hand object
	 */
	virtual Iterator &operator++() noexcept(true) {

		CopyIf();
		++*_data;
		return *this;
	}

	/*!
	 * @brief Post increment operator
	 * @return A copy of this iterator before the increment
	 */
	Iterator<T> operator++(int) noexcept(true) {

		const Iterator<T> RV(*this);
		CopyIf();
		++*_data;
		return RV;
	}

	/*!
	 * @brief Assignment operator
	 * @param rhs The Iterator to copy
	 * @return A reference to the left hand object
	 */
	virtual Iterator &operator=(const Iterator<T> &rhs) noexcept(true) {

		DeleteIf();
		_data = rhs._data;
		_RC   = rhs._RC;
	}

	/*!
	 * @brief Move assignment operator
	 * @param rhs The Iterator to swap
	 * @return A reference to the left hand object
	 */
	virtual Iterator &operator=(Iterator<T> &&rhs) noexcept(true) {

		std::swap(_data, rhs._data);
		std::swap(_RC, rhs._RC);
		return *this;
	}

	/*!
	 * @brief Equality operator
	 * @param rhs The iterator to compare with
	 * @return True if the iterators are pointing at the same object
	 */
	virtual bool operator==(const Iterator<T> &rhs) const noexcept(true) {

		return *_data == *rhs._data;
	}

	/*!
	 * @brief Inequality operator
	 * @param rhs The iterator to compare with
	 * @return False if the iterators are pointing at the same object
	 */
	virtual bool operator!=(const Iterator<T> &rhs) const noexcept(true) {

		return !(*_data == *rhs._data);
	}

	/*!
	 * @brief Copies this iterator
	 * @return A new, identical iterator
	 */
	virtual Iterator<T> *Copy() const noexcept(true) {

		return _data->Copy();
	}
};

#endif //TEMPL_ITERATOR_ITERATOR_BASE_H
