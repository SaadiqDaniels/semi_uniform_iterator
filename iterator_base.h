/*!
 * @file iterator_base.h
 * @author Saadiq Daniels
 * @date 23/12/2019
 * @version 2.0
 * @brief
 * 	The iterator base class. Provides an interface to
 * 	the derived (IteratorWrapper) class which holds
 * 	an actual iterator of your container of choice.
 */

//#define COUT_CONSTRUCTOR_ERROR_PRINTING
#ifdef COUT_CONSTRUCTOR_ERROR_PRINTING
#include <iostream>
#endif

#ifndef TEMPL_ITERATOR_ITERATOR_BASE_H
#define TEMPL_ITERATOR_ITERATOR_BASE_H

// Forward declaration of the IteratorWrapper class
template<typename T, typename U>
class IteratorWrapper;

/*!
 * @brief The base iterator class
 * @tparam T The base class of the object type stored in your container
 */
template<typename T>
class Iterator : std::forward_iterator_tag {
public:

    // User friendly names for data types
    using value_type = T;
    using difference_type = long;
    using pointer = T *;
    using reference = T &;

    // If T is const, this removes the const for copying
    using mutable_value_type = typename make_mutable<value_type>::type;
    // If T is not const, this makes a const value_type
    using const_value_type = typename make_const<value_type>::type;
    // Makes the data of related value_type iterators (regardless of const-ness
    // of the value_type) able to see all of their data values
    friend Iterator<mutable_value_type>;
    friend Iterator<const_value_type>;

protected:

    // A reference counter for how many things point to this object
    int _refCount;

private:

    // The template iterator stored inside
    Iterator<T> *_data;

    /*!
     * @brief Lazy copies the data if needed
     */
    void CopyIf() noexcept(true) {

        // If the data exists and has more than one iterator pointing at it,
        // make a duplicate and point at that duplicate
        if (_data && _data->_refCount > 1) {
            // This iterator is no longer pointing at that data
            --_data->_refCount;
            // Copy the data
            _data = Copy();
            // Set the reference count for the copied data to 1 (this iterator
            // is pointing at it)
            _data->_refCount = 1;
        }
    }

    /*!
     * @brief Deletes the object if this is the only iterator pointing at it
     */
    void DeleteIf() noexcept(true) {

        // TODO: Debug break if _data->_refCount is less than 0
        // If this is the last instance delete the data
        if (_data && _data->_refCount == 1) {
            _data->_refCount = 0;
            delete _data;
            _data = nullptr;
            return;
        }
        // If the last statement is false, then there are other references to
        // this data and keep it
        if (_data) {
            --_data->_refCount;
        }
    }

public:

    /* Examples:
     * --- Setup:
     *
     * Iterator<foo> a;
     *
     *  --- Cases:
     *
     * Iterator<foo> new_iterator(a);
     * // This should be allowed
     *
     *
     * Iterator<const foo> new_iterator(a);
     * // This should be allowed
     */
    /*!
     * @brief Copy constructor
     * @param rhs The mutable iterator to copy
     */
    Iterator(const Iterator<mutable_value_type> &rhs) noexcept(true): _refCount(0), _data(nullptr) {

        // If the value_type of this iterator is NOT const...
        if constexpr (make_mutable<T>::value) {
            // assign as normal
            _data = rhs._data;
        } else {
            // cast to INCLUDE const
            _data = reinterpret_cast<Iterator<const_value_type> *>(rhs._data);
        }
        // Remember, the _data sub-iterator is not const at all, allowing us to
        // increment the reference counter
        ++_data->_refCount;
    }

    /* Examples:
     * --- Setup:
     *
     * Iterator<const foo> a;
     *
     * --- Cases:
     *
     * Iterator<foo> new_iterator(a);
     * // Should not be allowed, would break const correctness
     *
     * Iterator<const foo> new_iterator(a);
     * // This should be allowed since const correctness is maintained
     */
    /*!
     * @brief Copy constructor, const
     * @param rhs The const iterator to copy from
     */
    explicit Iterator(const Iterator<const_value_type> &rhs) noexcept(true): _refCount(0), _data(nullptr) {

        // If the value_type of this iterator is NOT const...
        if constexpr (make_mutable<T>::value) {
            // Throw an exception
            // If you have reached this exception view the example
            // comment above
            static_assert("Trying to assign a const value_type to a "
                                "non-const value_type, see comment above for "
                                "reason why this assert has triggered");
#ifdef COUT_CONSTRUCTOR_ERROR_PRINTING
            std::cout << "Error" << std::endl;
#endif
        } else {
            // assign as normal
            _data = rhs._data;
        }
        // Remember, the _data sub-iterator is not const at all, allowing us to
        // increment the reference counter
        ++_data->_refCount;
    }

    /* Examples:
     * --- Setup:
     *
     * In these examples make_iterator() returns Iterator<foo>
     *
     *  --- Cases:
     *
     * Iterator<foo> new_iterator(make_iterator());
     * // This should be allowed
     *
     * Iterator<const foo> new_iterator(make_iterator());
     * // This should be allowed
     */
    /*!
     * @brief Move constructor (previous object has null values afterward)
     * @param rhs The iterator to swap with
     */
    explicit Iterator(Iterator<mutable_value_type> &&rhs) noexcept(true): _refCount(0), _data(nullptr) {

        _refCount = rhs._refCount;
        // If the value_type of this iterator is NOT const...
        if constexpr (make_mutable<value_type>::value) {
            _data = rhs._data;
        } else {
            _data = reinterpret_cast<Iterator<value_type> *>(rhs._data);
        }
        rhs._data = nullptr;
        rhs._refCount = 0;
    }

    /* Examples:
     * --- Setup:
     *
     * In these examples make_iterator() returns Iterator<const foo>
     *
     *  --- Cases:
     *
     * Iterator<foo> new_iterator(make_iterator());
     * // This should not be allowed, breaks const correctness
     *
     * Iterator<const foo> new_iterator(make_iterator());
     * // This should be allowed
     */
    /*!
     * @brief Move constructor (previous object has null values afterward)
     * @param rhs The iterator to swap with
     */
    explicit Iterator(Iterator<const_value_type> &&rhs) noexcept(true): _refCount(rhs._refCount), _data(rhs._data) {

        // If the value_type of this iterator is NOT const...
        if constexpr (make_mutable<T>::value) {
            // Throw an exception
            // If you have reached this exception view the example
            // comment above
            static_assert("Trying to assign a const value_type to a "
                                "non-const value_type, see comment above for "
                                "reasons why this assert has triggered");
#ifdef COUT_CONSTRUCTOR_ERROR_PRINTING
            std::cout << "Error" << std::endl;
#endif
        }
        rhs._data = nullptr;
        rhs._refCount = 0;
    }

    /* Examples:
     * --- Setup:
     *
     * IteratorWrapper<foo, bar>             a;
     *
     * --- Cases:
     *
     * Iterator<foo> new_iterator(&a);
     * // This should work
     *
     * Iterator<const foo> new_iterator(&a);
     * // This should work
     *
     * IteratorWrapper<foo, const bar> b;
     * // This should not work, since you would be allowed to access a const bar from a non-const foo
     *
     */
    /*!
     * @brief Conversion constructor, takes an iterator wrapper class pointer
     * @tparam U The derived template type
     * @param rhs The iterator to copy
     */
    template<typename U>
    explicit Iterator(IteratorWrapper<mutable_value_type, U> *rhs) noexcept(true): _refCount(0), _data(nullptr) {

        // If the value_type of this iterator is NOT const...
        if constexpr (make_mutable<T>::value) {
            // If the second value type is NOT const...
            if constexpr (make_mutable<U>::value) {
                // Assign as normal
                _data = static_cast<Iterator<mutable_value_type> *>(rhs);
            } else {
                // Throw an exception
                // This would allow you to interact with a
                // non-const U type without a const T type
                static_assert("Trying to assign a const derived value type (U)"
                              "to a non-const value_type, see comment above "
                              "for reasons why this assert has triggered");
#ifdef COUT_CONSTRUCTOR_ERROR_PRINTING
                std::cout << "Error" << std::endl;
#endif
            }
        } else {
            // Assign as normal
            _data = reinterpret_cast<Iterator<const_value_type> *>(rhs);
        }
        // Remember, the _data sub-iterator is not const at all, allowing us to
        // increment the reference counter
        ++_data->_refCount;
    }

    /* Examples:
     * --- Setup:
     *
     * IteratorWrapper<const foo, bar>       a;
     * IteratorWrapper<const foo, const bar> b;
     *
     * --- Cases:
     *
     * Iterator<foo> new_iterator(a);
     * // This should fail, this code would not be const correct
     *
     * Iterator<foo> new_iterator(b);
     * // This should fail, this code would not be const correct
     *
     * Iterator<const foo> new_iterator(b);
     * // This should work
     *
     * Iterator<const foo> new_iterator(b);
     * // This should work
     */
    /*!
     * @brief Conversion constructor, takes a const iterator wrapper class pointer
     * @tparam U The derived template type
     * @param rhs The iterator to copy
     */
    template<typename U>
    explicit Iterator(IteratorWrapper<const_value_type, U> *rhs) noexcept(true): _refCount(0), _data(nullptr) {
        // If the value_type of this iterator is NOT const...
        if constexpr (make_mutable<T>::value) {
            // Throw an exception
            // This would allow you to interact with a
            // non-const U type without a const T type
            static_assert("Trying to assign a const derived value type (U)"
                          "to a non-const value_type, see comment above "
                          "for reasons why this assert has triggered");
#ifdef COUT_CONSTRUCTOR_ERROR_PRINTING
            std::cout << "Error" << std::endl;
#endif
        } else {
            // Assign as normal
            _data = static_cast<Iterator<const_value_type> *>(rhs);
        }
        // Remember, the _data sub-iterator is not const at all, allowing us to
        // increment the reference counter
        ++_data->_refCount;
    }

    /*!
     * @brief Clean up memory if needed
     */
    virtual ~Iterator() noexcept(true) {

        DeleteIf();
    }

    /*!
     * @brief Copy another iterator's data to this one
     * @param rhs The iterator to copy
     * @return A reference to this iterator
     */
    virtual Iterator &operator=(const Iterator<T> &rhs) noexcept(true) {

        // Self assignment early return
        if (&rhs == this) {
            return *this;
        }

        // Decouple from the current reference if there is one
        DeleteIf();
        // Copy the data and iterate the reference counter
        _data = rhs._data;
        ++_data->_refCount;
        return *this;
    }

    /*!
     * @brief Swap another iterator's data with this one
     * @param rhs The iterator to swap
     * @return A reference to this iterator
     */
    virtual Iterator &operator=(Iterator<T> &&rhs) noexcept(true) {

        std::swap(_data, rhs._data);
        return *this;
    }

    /*!
     * @brief Equality operator
     * @details
     *      This does not simply check if this and another iterator are
     *      pointing to the same memory. This calls the equality operator
     *      of the IteratorWrapper, which then calls the equality operator
     *      of the original container's iterator.
     * @param rhs The iterator to compare with
     * @return True if the hidden container's iterators are the same
     */
    virtual bool operator==(const Iterator<T> &rhs) const noexcept(true) {

        return *_data == *rhs._data;
    }

    /*!
     * @brief Inequality operator
     * @details
     *      This does not simply check if this and another iterator are
     *      pointing to the same memory. This calls the inequality operator
     *      of the IteratorWrapper, which then calls the inequality operator
     *      of the original container's iterator.
     * @param rhs The iterator to compare with
     * @return False if the hidden container's iterators are the same
     */
    virtual bool operator!=(const Iterator<T> &rhs) const noexcept(true) {

        return *_data != *rhs._data;
    }

    /*!
     * @brief Subtraction operator, finds the difference between two iterators
     * @param rhs The end iterator for the length comparison
     * @return A difference_type representing the distance two iterators
     */
    virtual difference_type operator-(const Iterator<T> &rhs)
    const noexcept(true) {

        return (*_data) - (*rhs._data);
    }

    /*!
     * @brief Dereference operator
     * @return A reference to the base class object pointed at by this iterator
     */
    virtual reference operator*() const noexcept(true) {

        /*!
         * *_data   = bring _data from a pointer to an Iterator to an Iterator
         * **_data  = deference operator on the IteratorWrapper
         */
        return **_data;
    }

    /*!
     * @brief Arrow operator
     * @return A pointer to the base class object pointed at by this iterator
     */
    virtual pointer operator->() const noexcept(true) {

        /*!
         * *_data   = bring _data from a pointer to an Iterator to an Iterator
         * **_data  = deference operator on the IteratorWrapper
         * &**_data = the address of the base class object returned by
         * IteratorWrapper
         */
        return &**_data;
    }

    /*!
     * @brief Increment operator, moves the pointer forward
     * @return A reference to this iterator
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
