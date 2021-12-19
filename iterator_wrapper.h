/*!
 * @file iterator_wrapper.h
 * @author Saadiq Daniels
 * @date 23/12/2019
 * @version 2.1
 * @brief
 * 	The declaration of the iterator wrapper class, which extends from
 * 	the base iterator class
 */
#include <utility>
#include "iterator_base.h"

#ifndef TEMPL_ITERATOR_ITERATOR_WRAPPER_H
#define TEMPL_ITERATOR_ITERATOR_WRAPPER_H

/*!
 * @brief The declaration of the iterator wrapper class
 * @tparam T The base class type
 * @tparam U The derived iterator type
 */
template<typename T, typename U>
class IteratorWrapper : public Iterator<T> {
public:
    // User friendly names for data types
    using value_type = T;
    using derived_type = U;
    using difference_type = long;
    using pointer = T *;
    using reference = T &;
    // If T is const, this removes the const for copying
    using mutable_value_type = typename make_mutable<value_type>::type;
    // If T is not const, this makes a const value_type
    using const_value_type = typename make_const<value_type>::type;
    // Makes the data of related value_type iterators (regardless of const-ness
    // of the value_type) able to see all of their data values
    using mutable_derived_type = typename make_mutable<derived_type>::type;
    using const_derived_type = typename make_const<derived_type>::type;
    //Figuring out if *operator returns a pair or not
    using return_value = typename std::result_of<decltype(&derived_type::operator*)(derived_type)>::type;

    friend class IteratorWrapper<mutable_value_type, mutable_derived_type>;

    friend class IteratorWrapper<const_value_type, mutable_derived_type>;

    friend class IteratorWrapper<mutable_value_type, const_derived_type>;

    friend class IteratorWrapper<const_value_type, const_derived_type>;

protected:
    // The derived iterator to store internally
    mutable_derived_type _it;

public:


    /*!
     * @brief Conversion constructor, taking a derived iterator
     * @param iterator The derived iterator to store
     */
    explicit IteratorWrapper(const_derived_type &iterator) noexcept(true): Iterator<T>(this), _it(iterator) {

        --Iterator<T>::_refCount;
        // Since most IteratorWrappers are meant to be created on the heap, this disables self reference
        // because technically, the Iterator inside the IteratorWrapper points at itself
        // This allows the second to last Iterator to clean up memory
        // However, if the IteratorWrapper is created on the stack, call DisableMemoryManagement on the
        // IteratorWrapper
    }

    /*!
     * @brief Allows IteratorWrappers created on the stack to clean up themselves
     */
    void DisableMemoryManagement() noexcept(true) {

        Iterator<T>::_refCount += 2;
    }

    /*!
     * @brief Conversion constructor, using the iterator base class
     * @param rhs The iterator to copy
     */
    explicit IteratorWrapper(const Iterator<T> &rhs) noexcept(true): Iterator<T>(this),
                                                                     _it(reinterpret_cast<IteratorWrapper<T, U> *>(&rhs)->_it) {
    }

    /*!
     * @brief Copy constructor
     * @param rhs The IteratorWrapper to copy
     */
    explicit IteratorWrapper(const IteratorWrapper<T, U> &rhs) noexcept(true): Iterator<T>(this), _it(rhs._it) {
    }

    /*!
     * @brief Virtual destructor
     */
    virtual ~IteratorWrapper() noexcept(true) = default;

    /*!
     * @brief Assignment operator
     * @param rhs The Iterator to copy
     * @return A reference to the left hand object
     */
    virtual Iterator<T> &operator=(const Iterator<T> &rhs) noexcept(true) {

        _it = reinterpret_cast<const IteratorWrapper<T, U> *>(&rhs)->_it;
        return static_cast<Iterator<T> &>(*this);
    }

    /*!
     * @brief Equality operator
     * @param rhs The iterator to compare with
     * @return True if the iterators are pointing at the same object
     */
    virtual bool operator==(const Iterator<T> &rhs) const noexcept(true) {

        return _it == (reinterpret_cast<const IteratorWrapper<T, U> *>(&rhs))->_it;
    }

    /*!
     * @brief Inequality operator
     * @param rhs The iterator to compare with
     * @return False if the iterators are pointing at the same object
     */
    virtual bool operator!=(const Iterator<T> &rhs) const noexcept(true) {

        return _it != reinterpret_cast<const IteratorWrapper<value_type, derived_type> &>(rhs)._it;
    }

    /*!
     * @brief Subtraction operator, finds the difference between two iterators
     * @param rhs The end iterator to find the difference between
     * @return A difference_type(long) representing the distance between them
     */
    virtual difference_type operator-(const Iterator<T> &rhs) const noexcept(true) {

        return std::distance(_it, reinterpret_cast<const IteratorWrapper<value_type, derived_type> &>(rhs)._it);
    }

    /*!
     * @brief Dereference operator
     * @return A reference to the base class stored inside
     */
    virtual reference operator*() const noexcept(true) {

        if constexpr(!is_pair<return_value>::value) {
            return *_it;
        } else {
            // This code will not be called
            // it will be overloaded by iterator_wrapper_left and iterator_wrapper_right
            return reinterpret_cast<reference>(*_it);
        }
    }

    /*!
     * @brief Arrow operator
     * @return A pointer to the base class stored inside
     */
    virtual pointer operator->() const noexcept(true) {

        if constexpr(!is_pair<return_value>::value) {
            return &*_it;
        } else {
            // This code will not be called
            // it will be overloaded by iterator_wrapper_left and iterator_wrapper_right
            return reinterpret_cast<pointer>(&*_it);
        }
    }

    /*!
     * @brief Increment operator, moves the pointer forward
     * @return A reference to the left hand object
     */
    virtual Iterator<T> &operator++() noexcept(true) {

        ++_it;
        return static_cast<Iterator<T> &>(*this);
    }

    /*!
     * @brief Copies this iterator
     * @return A new, identical iterator
     */
    virtual Iterator<T> *Copy() const noexcept(true) {

        return new IteratorWrapper<T, U>(_it);
    }
};

#endif //TEMPL_ITERATOR_ITERATOR_WRAPPER_H
