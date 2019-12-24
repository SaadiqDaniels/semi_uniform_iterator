/*!
 * @file const_iterator_handle.h
 * @author Saadiq Daniels
 * @date 23/12/2019
 * @version 1.0
 * @brief
 * 	Defines the const handle class, the class wrapping around the
 * 	base and derived iterator
 */

#ifndef TEMPL_ITERATOR_CONST_ITERATOR_HANDLE_H
#define TEMPL_ITERATOR_CONST_ITERATOR_HANDLE_H

/*!
 * @brief Forward declaration of the Iterator class
 * @tparam T The base iterator type
 */
template <typename T>
class Iterator;

/*!
 * @brief Forward declaration of the IteratorWrapper class
 * @tparam T The base type
 * @tparam U The derived iterator type
 */
template<typename T, typename U>
class IteratorWrapper;

/*!
 * @brief Forward declaration of the handle class
 * @tparam T The base class type
 */
template <typename T>
class Handle;

/*!
 * @brief A template specialization of the handle class on
 * const correctness
 * @tparam T The base class type
 */
template<typename T>
class Handle<const T>
{
	// The base handle class is a friend of this class
	friend class Handle<T>;

	/*!
	 * @brief The data being stored in the handle,
	 * the pointer to the iterator
	 */
	Iterator<const T> *_data;

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
			--*RC;
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
	 * @brief Conversion constructor, takes a const Iterator pointer
	 * and stores it
	 * @param rhs The pointer to an iterator to store
	 */
	explicit Handle(Iterator<const T> *rhs) : _data(rhs), RC(new int(1)) {
	}

	/*!
	 * @brief Conversion constructor, takes any const derived iterator
	 * pointer with the same base type
	 * @tparam U The derived iterator type
	 * @param rhs The pointer to the derived iterator to store
	 */
	template<typename U>
	Handle(IteratorWrapper<const T, U> *rhs) : _data(rhs), RC(new int(1)) {
	}

	/*!
	 * @brief Copy constructor
	 * @param rhs The handle to copy from, const
	 */
	Handle(const Handle<const T> &rhs) : _data(rhs._data), RC(rhs.RC) {
		// Increment the reference counter
		++*RC;
	}

	/*!
	 * @brief Move constructor, swaps the data in both handles
	 * @param rhs The handle to swap data with
	 */
	Handle(Handle<const T> &&rhs) {
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
	const T *operator->() const {

		return (&**_data);
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
};

#endif //TEMPL_ITERATOR_CONST_ITERATOR_HANDLE_H
