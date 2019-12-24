/*!
 * @file const_iterator_base.h
 * @author Saadiq Daniels
 * @date 23/12/2019
 * @version 1.0
 * @brief
 * 	The iterator base class, const qualified. Provides an
 * 	interface to the more templatized derived class
 */

#ifndef TEMPL_ITERATOR_CONST_ITERATOR_BASE_H
#define TEMPL_ITERATOR_CONST_ITERATOR_BASE_H

/*!
 * @brief Forward declaration of the iterator base class
 * @tparam T The base derived type
 */
template <typename T>
class Iterator;

/*!
 * @brief A const qualified base iterator class
 * @tparam T The base derived type
 */
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
	 * because of const-ness
	 * virtual Iterator &operator++() = 0;
	 * virtual Iterator &operator=(const Iterator<T> &rhs) = 0;
	 */

	/*!
	 * @brief Equality operator
	 * @param rhs The iterator to compare with
	 * @return True if the iterators are pointing at the same object
	 */
	virtual bool operator==(const Iterator<T> &rhs) const = 0;

	/*!
	 * @brief Equality operator
	 * @param rhs The iterator to compare with, const qualified
	 * @return True if the iterators are pointing at the same object
	 */
	virtual bool operator==(const Iterator<const T> &rhs) const = 0;

	/*!
	 * @brief Inequality operator
	 * @param rhs The iterator to compare with
	 * @return False if the iterators are pointing at the same object
	 */
	virtual bool operator!=(const Iterator<T> &rhs) const = 0;

	/*!
	 * @brief Inequality operator
	 * @param rhs The iterator to compare with, const qualified
	 * @return False if the iterators are pointing at the same object
	 */
	virtual bool operator!=(const Iterator<const T> &rhs) const = 0;

	/*!
	 * @brief Copies this iterator
	 * @return A new, identical iterator
	 */
	virtual Iterator<const T> *Copy() const = 0;
};

#endif //TEMPL_ITERATOR_CONST_ITERATOR_BASE_H
