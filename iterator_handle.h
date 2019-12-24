/*!
 * @file iterator_handle.h
 * @author Saadiq Daniels
 * @date 23/12/2019
 * @version 1.0
 * @brief
 * 	Defines the handle class, the class wrapping around the
 * 	base and derived iterator, not const qualified
 */

#ifndef TEMPL_ITERATOR_ITERATOR_HANDLE_H
#define TEMPL_ITERATOR_ITERATOR_HANDLE_H

/*!
 * @brief Forward declaration of the Iterator class
 * @tparam T The base iterator type
 */
template <typename T>
class Iterator;

/*!
 * @brief Forward declaration of the IteratorWrapper class
 * @tparam T The base iterator type
 * @tparam U The derived iterator type
 */
template <typename T, typename U>
class IteratorWrapper;

/*!
 * @brief A class to wrap around the dynamically allocated
 * derived type iterators
 * @tparam T The base class type
 */
template<typename T>
class Handle
{
	// Friend of the const version of this template class
	friend class Handle<const T>;

	/*!
	 * @brief The data being stored in the handle,
	 * the pointer to the iterator
	 */
	Iterator<T> *_data;

	/*!
	 * @brief A reference counter for the handles
	 */
	int *RC;

	/*!
	 * @brief Copies the reference if it is needed
	 */
	void CopyIf() {

		if (*RC > 1)
		{
			_data = _data->Copy();
			RC    = new int(1);
		}
	}

	/*!
	 * @brief Deletes the object if needed
	 */
	void DeleteIf() {

		if (!--*RC)
		{
			// If this is the last instance delete the data
			delete _data;
			delete RC;
		}
	}

public:
	/*!
	 * @brief Default constructor, should never be used
	 */
	Handle() = delete;

	/*!
	 * @brief Conversion constructor, takes an Iterator pointer
	 * and stores it
	 * @param rhs The pointer to an iterator to store
	 */
	explicit Handle(Iterator<T> *rhs) : _data(rhs), RC(new int(1)) {
	}

	/*!
	 * @brief Conversion constructor, takes any derived iterator
	 * pointer with the same base type
	 * @tparam U The derived iterator type
	 * @param rhs The pointer to the derived iterator to store
	 */
	template<typename U>
	Handle(IteratorWrapper<T, U> *rhs) : _data(rhs), RC(new int(1)) {
	}

	/*!
	 * @brief Copy constructor
	 * @param rhs The handle to copy from
	 */
	Handle(const Handle<T> &rhs) : _data(rhs._data), RC(rhs.RC) {
		// Increment the reference counter
		++*RC;
	}

	/*!
	 * @brief Move constructor, swaps the data in both handles
	 * @param rhs The handle to swap data with
	 */
	Handle(Handle<T> &&rhs) {
		// Swap the data and reference counter, both pointers
		std::swap(_data, rhs._data);
		std::swap(RC, rhs.RC);
	}

	/*!
	 * @brief Handle destructor, may delete the data if
	 * that instance is the last
	 */
	~Handle() {

		DeleteIf();
	}

	/*!
	 * @brief Assignment operator
	 * @param rhs The handle to copy
	 * @return A reference to this handle
	 */
	Handle &operator=(const Handle<T> &rhs) {

		if (_data != rhs._data)
		{
			DeleteIf();

			_data = rhs._data;
			RC    = rhs.RC;

			++*RC;
		}
	}

	/*!
	 * @brief Gives access to the base iterator
	 * @return The base iterator, by reference
	 */
	T &operator*() {

		CopyIf();
		return **_data;
	}

	/*!
	 * @brief Gives access to the base iterator
	 * @return The base iterator, by reference
	 */
	const T &operator*() const {

		return **_data;
	}

	/*!
	 * @brief Gives access to the base iterator
	 * @return The base iterator, by pointer
	 */
	T *operator->() {

		CopyIf();
		return (*_data)->;
	}

	/*!
	 * @brief Gives access to the base iterator
	 * @return The base iterator, by pointer
	 */
	const T *operator->() const {

		return (*_data)->;
	}

	/*!
	 * @brief Equality operator
	 * @param rhs The handle to compare with
	 * @return True if their iterators are pointing to the same
	 * location in memory
	 */
	bool operator==(const Handle<T> &rhs) const {

		return *_data == *rhs._data;
	}

	/*!
	 * @brief Equality operator
	 * @param rhs The handle to compare with, const qualified
	 * @return True if their iterators are pointing to the same
	 * location in memory
	 */
	bool operator==(const Handle<const T> &rhs) const {

		return *_data == *rhs._data;
	}

	/*!
	 * @brief Inequality operator
	 * @param rhs The handle to compare with
	 * @return True if their iterators not are pointing to the same
	 * location in memory
	 */
	bool operator!=(const Handle<T> &rhs) const {

		return *_data != *rhs._data;
	}

	/*!
	 * @brief Inequality operator
	 * @param rhs The handle to compare with, const qualified
	 * @return True if their iterators not are pointing to the same
	 * location in memory
	 */
	bool operator!=(const Handle<const T> &rhs) const {

		return *_data != *rhs._data;
	}

	/*!
	 * @brief Increment operator, increments the iterator
	 * stored inside of this class
	 * @return This handle
	 */
	Handle&operator++()
	{
		++(*_data);
		return *this;
	}
};

#endif //TEMPL_ITERATOR_ITERATOR_HANDLE_H
