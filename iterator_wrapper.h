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

/*!
 * @brief A forward declaration of the Iterator class
 * @tparam T The base class type
 */
template<typename T>
class Iterator;

/*!
 * @brief The declaration of the iterator wrapper class
 * @tparam T The base class type
 * @tparam U The derived iterator type
 */
template<typename T, typename U>
class IteratorWrapper : public Iterator<T>
{
	// The iterator wrapper const class is a friend of this class
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
	explicit IteratorWrapper(const U &iterator) noexcept(true) : Iterator<T>(this), _data(iterator) {
	}

	/*!
	 * @brief Conversion constructor, using the iterator base class
	 * @param rhs The iterator to copy
	 */
	explicit IteratorWrapper(const Iterator<T> &rhs) noexcept(true) : Iterator<T>(this), _data(
		reinterpret_cast<IteratorWrapper<T, U> *>(&rhs)->_data) {
	}

	/*!
	 * @brief Copy constructor
	 * @param rhs The IteratorWrapper to copy
	 */
	explicit IteratorWrapper(const IteratorWrapper<T, U> &rhs) noexcept(true) : Iterator<T>(this), _data(rhs._data) {
	}

	/*!
	 * @brief Copy constructor, const correct
	 * @param rhs The const IteratorWrapper to copy
	 */
	// IteratorWrapper(const IteratorWrapper<const T, U> &rhs) noexcept(true) : Iterator<T>(this), _data(rhs._data) {
	// }

	/*!
	 * @brief Virtual destructor
	 */
	virtual ~IteratorWrapper() noexcept(true) = default;

	/*!
	 * @brief Dereference operator
	 * @return A reference to the base class stored inside
	 */
	virtual T &operator*() noexcept(true) {

		return *_data;
	}

	/*!
	 * @brief Dereference operator
	 * @return A reference to the base class stored inside
	 */
	virtual const T &operator*() const noexcept(true) {

		return *_data;
	}

	/*!
	 * @brief Arrow operator
	 * @return A pointer to the base class stored inside
	 */
	virtual T *operator->() noexcept(true) {

		return &*_data;
	}

	/*!
	 * @brief Arrow operator
	 * @return A pointer to the base class stored inside
	 */
	virtual const T *operator->() const noexcept(true) {

		return &*_data;
	}

	/*!
	 * @brief Increment operator, moves the pointer forward
	 * @return A reference to the left hand object
	 */
	virtual Iterator<T> &operator++() noexcept(true) {

		++_data;
		return *this;
	}

	/*!
	 * @brief Assignment operator
	 * @param rhs The Iterator to copy
	 * @return A reference to the left hand object
	 */
	virtual Iterator<T> &operator=(const Iterator<T> &rhs) noexcept(true) {

		_data = reinterpret_cast<const IteratorWrapper<T, U> *>(&rhs)->_data;
		return *this;
	}

	/*!
	 * @brief Assignment operator, const qualified
	 * @param rhs The Iterator to copy
	 * @return A reference to the left hand object
	 */
	// TODO: Find out why MSVC does not like this line (works on gcc 6.1+)
	// virtual Iterator<T> &operator=(const Iterator<const T> &rhs) noexcept(true) {
	//
	// 	_data = reinterpret_cast<const IteratorWrapper<const T, U> *>(&rhs)->_data;
	// 	return *this;
	// }

	/*!
	 * @brief Equality operator
	 * @param rhs The iterator to compare with
	 * @return True if the iterators are pointing at the same object
	 */
	virtual bool operator==(const Iterator<T> &rhs) const noexcept(true) {

		return _data == (reinterpret_cast<const IteratorWrapper<T, U> *>(&rhs))->_data;
	}

	/*!
	 * @brief Equality operator, const qualified
	 * @param rhs The iterator to compare with
	 * @return True if the iterators are pointing at the same object
	 */
	// virtual bool operator==(const Iterator<const T> &rhs) const noexcept(true) {
	//
	// 	return _data == (reinterpret_cast<const IteratorWrapper<T, U> *>(&rhs))->_data;
	// }

	/*!
	 * @brief Inequality operator
	 * @param rhs The iterator to compare with
	 * @return False if the iterators are pointing at the same object
	 */
	virtual bool operator!=(const Iterator<T> &rhs) const noexcept(true) {

		return !((*this) == rhs);
	}

	/*!
	 * @brief Inequality operator, const qualified
	 * @param rhs The iterator to compare with
	 * @return False if the iterators are pointing at the same object
	 */
	// virtual bool operator!=(const Iterator<const T> &rhs) const noexcept(true) {
	//
	// 	return !((*this) == rhs);
	// }

	/*!
	 * @brief Copies this iterator
	 * @return A new, identical iterator
	 */
	virtual Iterator<T> *Copy() const noexcept(true) {

		return new IteratorWrapper<T, U>(_data);
	}
};

#endif //TEMPL_ITERATOR_ITERATOR_WRAPPER_H
