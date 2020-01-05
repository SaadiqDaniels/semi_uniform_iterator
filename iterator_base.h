/*!
 * @file iterator_base.h
 * @author Saadiq Daniels
 * @date 23/12/2019
 * @version 1.2
 * @brief
 * 	The iterator base class. Provides an interface
 * 	to the more templatized derived class.
 */

#ifndef TEMPL_ITERATOR_ITERATOR_BASE_H
#define TEMPL_ITERATOR_ITERATOR_BASE_H

// Forward declaration of the IteratorWrapper class
template<typename T, typename U>
class IteratorWrapper;

/*!
 * @brief The base iterator class
 * @tparam T The base class to iterate over
 */
template<typename T>
class Iterator : std::forward_iterator_tag
{
	typedef typename make_mutable<T>::type MT;
	typedef typename make_const<T>::type   CT;
	friend Iterator<MT>;
	friend Iterator<CT>;

	// The template iterator stored inside
	Iterator<T> *_data;
	// The reference counter
	int         *_RC;

	/*!
	 * @brief Copies the reference if it is needed
	 */
	void CopyIf() noexcept(true) {

		if (*_RC > 1)
		{
			--*_RC;
			_data = Copy();
			_RC   = _data->_RC;
			++*_RC;
		}
	}

	/*!
	 * @brief Deletes the object if needed
	 */
	void DeleteIf() noexcept(true) {

		if (_RC)
		{
			if (!--*_RC)
			{
				// If this is the last instance delete the data
				delete _data;
				delete _RC;
			}
		}
	}

public:
	using value_type = T;
	using difference_type = long;
	using pointer = T *;
	using reference = T &;

	/*!
	 * @brief Copy constructor
	 * @param rhs The Iterator to copy from
	 */
	Iterator(const Iterator<MT> &rhs) noexcept(true) : _data(nullptr), _RC(&++*rhs._RC) {

		if constexpr (make_mutable<T>::value)
		{
			_data = reinterpret_cast<Iterator<MT> *>(rhs._data);
		}
		else
		{
			_data = reinterpret_cast<Iterator<CT> *>(rhs._data);
		}

	}

	/*!
	 * @brief Copy constructor, const
	 * @param rhs The const iterator to copy from
	 */
	Iterator(const Iterator<CT> &rhs) noexcept(true) : _data(nullptr), _RC(&++*(rhs._RC)) {

		if constexpr (make_mutable<T>::value)
		{
			_data = reinterpret_cast<Iterator<MT> *>(rhs._data);
		}
		else
		{
			_data = reinterpret_cast<Iterator<CT> *>(rhs._data);
		}
	}

	/*!
	 * @brief Move constructor (previous object has null values afterward)
	 * @param rhs The iterator to swap with
	 */
	Iterator(Iterator<MT> &&rhs) noexcept(true) : _data(rhs._data), _RC(rhs._RC) {

		rhs._data = nullptr;
		rhs._RC   = nullptr;
	}

	/*!
	 * @brief Conversion constructor, takes an iterator wrapper class pointer
	 * @tparam U The derived template type
	 * @param rhs The iterator to copy
	 */
	template<typename U>
	Iterator(IteratorWrapper<MT, U> *rhs) noexcept(true) : _data(rhs), _RC(new int(0)) {
	}

	/*!
	 * @brief Conversion constructor, takes a const iterator wrapper class pointer
	 * @tparam U The derived template type
	 * @param rhs The iterator to copy
	 */
	template<typename U>
	Iterator(IteratorWrapper<CT, U> *rhs) noexcept(true) : _data(rhs), _RC(new int(0)) {
	}

	/*!
	 * @brief Virtual destructor
	 */
	virtual ~Iterator() noexcept(true) {

		DeleteIf();
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
		++*_RC;
		return *this;
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
	 * @brief Subtraction operator, finds the difference between two iterators
	 * @param rhs The end iterator to find the difference between
	 * @return A difference_type(long) representing the distance between them
	 */
	virtual difference_type operator-(const Iterator<T> &rhs) const noexcept(true) {

		return (*_data) - (*rhs._data);
	}

	/*!
	 * @brief Dereference operator
	 * @return A reference to the base class stored inside
	 */
	virtual reference operator*() const noexcept(true) {

		return **_data;
	}

	/*!
	 * @brief Arrow operator
	 * @return A pointer to the base class stored inside
	 */
	virtual pointer operator->() const noexcept(true) {

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
	const Iterator<T> operator++(int) noexcept(true) {

		const Iterator<T> RV(*this);
		CopyIf();
		++*_data;
		return RV;
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
