/*!
 * @file const_iterator_wrapper.h
 * @author Saadiq Daniels
 * @date 23/12/2019
 * @version 1.5
 * @brief
 * 	The declaration of the const iterator wrapper class, which extends from
 * 	the base iterator class
 */
#ifndef TEMPL_ITERATOR_CONST_ITERATOR_WRAPPER_H
#define TEMPL_ITERATOR_CONST_ITERATOR_WRAPPER_H

/*!
 * @brief A forward declaration of the Iterator class
 * @tparam T The base class type
 */
template <typename T>
class Iterator;

/*!
 * @brief Forward declaration of the IteratorWrapper class
 * @tparam T The base type
 * @tparam U The derived iterator type
 */
template <typename T, typename U>
class IteratorWrapper;

/*!
 * @brief Definition of the const iterator class, which extends from the
 * const base iterator
 * @tparam T The base class type
 * @tparam U The derived iterator type
 */
template<typename T, typename U>
class IteratorWrapper<const T, U> : public Iterator<const T>
{
	// The iterator wrapper (non-const) class is a friend of this class
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

	/*!
	 * @brief Equality operator, const qualified
	 * @param rhs The iterator to compare with
	 * @return True if the iterators are pointing at the same object
	 */
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

	/*!
	 * @brief Inequality operator, const qualified
	 * @param rhs The iterator to compare with
	 * @return False if the iterators are pointing at the same object
	 */
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

#endif //TEMPL_ITERATOR_CONST_ITERATOR_WRAPPER_H
