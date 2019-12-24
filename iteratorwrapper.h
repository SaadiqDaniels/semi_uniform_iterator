/*!
 * @file iteratorwrapper.h
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 1.3
 */

#include "handle.h"

#ifndef TEMPL_ITERATOR_ITERATORWRAPPER_H
#define TEMPL_ITERATOR_ITERATORWRAPPER_H

template<typename T, typename U>
class IteratorWrapper : public Iterator<T>
{
	friend class IteratorWrapper<const T, U>;
	/*!
	 * @brief The derived iterator to store internally
	 */
	U _data;

public:
	/*!
	 * @brief Conversion constructor, taking a derived iterator
	 * @param iterator The derived iterator to store
	 */
	explicit IteratorWrapper(const U &iterator) : _data(iterator) {
	}

	/*!
	 * @brief Conversion constructor, using the iterator base class
	 * @param rhs The iterator to copy
	 */
	explicit IteratorWrapper(const Iterator<T> &rhs) : _data(reinterpret_cast<IteratorWrapper<T, U> *>(&rhs)->_data) {
	}

	/*!
	 * @brief Copy constructor
	 * @param rhs The IteratorWrapper to copy
	 */
	IteratorWrapper(const IteratorWrapper<T, U> &rhs) : _data(rhs._data) {
	}

	/*!
	 * @brief Virtual destructor
	 */
	virtual ~IteratorWrapper() = default;

	/*!
	 * @brief Dereference operator
	 * @return A reference to the base class stored inside
	 */
	virtual T &operator*() {

		return *_data;
	}

	/*!
	 * @brief Dereference operator
	 * @return A reference to the base class stored inside
	 */
	virtual const T &operator*() const {

		return *_data;
	}

	/*!
	 * @brief Arrow operator
	 * @return A pointer to the base class stored inside
	 */
	virtual T *operator->() {

		return &*_data;
	}

	/*!
	 * @brief Arrow operator
	 * @return A pointer to the base class stored inside
	 */
	virtual const T *operator->() const {

		return &*_data;
	}

	/*!
	 * @brief Increment operator, moves the pointer forward
	 * @return A reference to the left hand object
	 */
	virtual Iterator<T> &operator++() {

		++_data;
		return *this;
	}

	/*!
	 * @brief Assignment operator
	 * @param rhs The Iterator to copy
	 * @return A reference to the left hand object
	 */
	virtual Iterator<T> &operator=(const Iterator<T> &rhs) {

		_data = reinterpret_cast<const IteratorWrapper<T, U> *>(&rhs)->_data;
		return *this;
	}
	virtual Iterator<T> &operator=(const Iterator<const T> &rhs) {

		_data = reinterpret_cast<const IteratorWrapper<const T, U> *>(&rhs)->_data;
		return *this;
	}

	/*!
	 * @brief Equality operator
	 * @param rhs The iterator to compare with
	 * @return True if the iterators are pointing at the same object
	 */
	virtual bool operator==(const Iterator<T> &rhs) const {

		return _data == (reinterpret_cast<const IteratorWrapper<T, U> *>(&rhs))->_data;
	}
	virtual bool operator==(const Iterator<const T> &rhs) const {

		return _data == (reinterpret_cast<const IteratorWrapper<T, U> *>(&rhs))->_data;
	}

	/*!
	 * @brief Inequality operator
	 * @param rhs The iterator to compare with
	 * @return False if the iterators are pointing at the same object
	 */
	virtual bool operator!=(const Iterator<T> &rhs) const {

		return !((*this) == rhs);
	}
	virtual bool operator!=(const Iterator<const T> &rhs) const {

		return !((*this) == rhs);
	}

	/*!
	 * @brief Copies this iterator
	 * @return A new, identical iterator
	 */
	virtual Iterator<T> *Copy() const {

		return new IteratorWrapper<T, U>(_data);
	}
};

template<typename T, typename U>
class IteratorWrapper<const T, U> : public Iterator<const T>
{
	friend class IteratorWrapper<T, U>;
	/*!
	 * @brief The derived iterator to store internally
	 */
	U _data;

public:
	/*!
	 * @brief Conversion constructor, taking a derived iterator
	 * @param iterator The derived iterator to store
	 */
	explicit IteratorWrapper(const U &iterator) : _data(iterator) {
	}

	/*!
	 * @brief Conversion constructor, using the iterator base class
	 * @param rhs The iterator to copy
	 */
	explicit IteratorWrapper(const Iterator<T> &rhs) : _data(reinterpret_cast<IteratorWrapper<T, U> *>(&rhs)->_data) {
	}

	/*!
	 * @brief Copy constructor
	 * @param rhs The IteratorWrapper to copy
	 */
	IteratorWrapper(const IteratorWrapper<T, U> &rhs) : _data(rhs._data) {
	}

	/*!
	 * @brief Virtual destructor
	 */
	virtual ~IteratorWrapper() = default;

	/*!
	 * @brief Dereference operator
	 * @return A reference to the base class stored inside
	 */
	virtual const T &operator*() const {

		return *_data;
	}

	/*!
	 * @brief Arrow operator
	 * @return A pointer to the base class stored inside
	 */
	virtual const T *operator->() const {

		return &*_data;
	}

	/*!
	 * @brief Equality operator
	 * @param rhs The iterator to compare with
	 * @return True if the iterators are pointing at the same object
	 */
	virtual bool operator==(const Iterator<T> &rhs) const {

		return _data == (reinterpret_cast<const IteratorWrapper<T, U> *>(&rhs))->_data;
	}
	virtual bool operator==(const Iterator<const T> &rhs) const {

		return _data == (reinterpret_cast<const IteratorWrapper<T, U> *>(&rhs))->_data;
	}

	/*!
	 * @brief Inequality operator
	 * @param rhs The iterator to compare with
	 * @return False if the iterators are pointing at the same object
	 */
	virtual bool operator!=(const Iterator<T> &rhs) const {

		return !((*this) == rhs);
	}
	virtual bool operator!=(const Iterator<const T> &rhs) const {

		return !((*this) == rhs);
	}

	/*!
	 * @brief Copies this iterator
	 * @return A new, identical iterator
	 */
	virtual Iterator<const T> *Copy() const {

		return new IteratorWrapper<const T, const U>(_data);
	}
};

/*!
 * @brief Creates an iterator and associated handle
 * @tparam T The base type (must be specified)
 * @tparam U The derived iterator type (can be deduced) (vector.begin())
 * @param iterator The derived iterator to store
 * @return A new handle to the derived iterator
 */
template<typename T, typename U>
Handle<T> MakeIterator(const U &iterator) {

	return Handle<T>(new IteratorWrapper<T, U>(iterator));
}

#endif //TEMPL_ITERATOR_ITERATORWRAPPER_H