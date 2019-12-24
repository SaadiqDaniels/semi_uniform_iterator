/*!
 * @file base.h
 * @author Saadiq Daniels
 * @date 21/12/2019
 * @version 1.0
 */

#ifndef TEMPL_ITERATOR_ITERATOR_H
#define TEMPL_ITERATOR_ITERATOR_H

/*!
 * @brief The base iterator class
 * @tparam T The base iterator type
 */
template<typename T>
class Iterator
{
public:
	/*!
	 * @brief Virtual destructor
	 */
	virtual ~Iterator() = default;

	/*!
	 * @brief Dereference operator
	 * @return A reference to the base class stored inside
	 */
	virtual T &operator*() = 0;

	/*!
	 * @brief Dereference operator
	 * @return A reference to the base class stored inside
	 */
	virtual const T &operator*() const = 0;

	/*!
	 * @brief Arrow operator
	 * @return A pointer to the base class stored inside
	 */
	virtual T *operator->() = 0;

	/*!
	 * @brief Arrow operator
	 * @return A pointer to the base class stored inside
	 */
	virtual const T *operator->() const = 0;

	/*!
	 * @brief Increment operator, moves the pointer forward
	 * @return A reference to the left hand object
	 */
	virtual Iterator &operator++() = 0;

	/*!
	 * @brief Assignment operator
	 * @param rhs The Iterator to copy
	 * @return A reference to the left hand object
	 */
	virtual Iterator &operator=(const Iterator<T> &rhs) = 0;

	/*!
	 * @brief Equality operator
	 * @param rhs The iterator to compare with
	 * @return True if the iterators are pointing at the same object
	 */
	virtual bool operator==(const Iterator<T> &rhs) const = 0;
	virtual bool operator==(const Iterator<const T> &rhs) const = 0;

	/*!
	 * @brief Inequality operator
	 * @param rhs The iterator to compare with
	 * @return False if the iterators are pointing at the same object
	 */
	virtual bool operator!=(const Iterator<T> &rhs) const = 0;
	virtual bool operator!=(const Iterator<const T> &rhs) const = 0;

	/*!
	 * @brief Copies this iterator
	 * @return A new, identical iterator
	 */
	virtual Iterator *Copy() const = 0;
};


template <typename T>
class Iterator<const T>
{
public:
	/*!
	 * @brief Virtual destructor
	 */
	virtual ~Iterator() = default;

	/*!
	 * @brief Dereference operator
	 * @return A reference to the base class stored inside
	 */
	virtual const T &operator*() const = 0;

	/*!
	 * @brief Arrow operator
	 * @return A pointer to the base class stored inside
	 */
	virtual const T *operator->() const = 0;

	/*!
	 * @brief No assignment operator or increment operator
	 * because const-ness
	 * virtual Iterator &operator++() = 0;
	 * virtual Iterator &operator=(const Iterator<T> &rhs) = 0;
	 */

	/*!
	 * @brief Equality operator
	 * @param rhs The iterator to compare with
	 * @return True if the iterators are pointing at the same object
	 */
	virtual bool operator==(const Iterator<T> &rhs) const = 0;
	virtual bool operator==(const Iterator<const T> &rhs) const = 0;

	/*!
	 * @brief Inequality operator
	 * @param rhs The iterator to compare with
	 * @return False if the iterators are pointing at the same object
	 */
	virtual bool operator!=(const Iterator<T> &rhs) const = 0;
	virtual bool operator!=(const Iterator<const T> &rhs) const = 0;

	/*!
	 * @brief Copies this iterator
	 * @return A new, identical iterator
	 */
	virtual Iterator<const T> *Copy() const = 0;
};

#endif //TEMPL_ITERATOR_ITERATOR_H
