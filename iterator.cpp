/*!
 * @file iterator.cpp
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 0.8
 */


#ifndef TEMPL_ITERATOR_ITERATOR_CPP
#define TEMPL_ITERATOR_ITERATOR_CPP

#include "iterator.h"

namespace iterate
{
    /*!
     * A single-argument constructor for the template iterator
     * @tparam T The base type
     * @tparam U The derived iterator type
     * @param x The derived iterator to store internally
     */
    template<typename T, typename U>
    Templ_Iterator<T, U>::Templ_Iterator(U &x)
            : it(x)
    {
    }

    /*!
     * A copy constructor for the template iterator
     * @tparam T the base type
     * @tparam U the derived iterator type
     * @param rhs The template iterator to copy
     */
    template<typename T, typename U>
    Templ_Iterator<T, U>::Templ_Iterator(Templ_Iterator<T, U> const &rhs)
            : it(rhs.it)
    {
    }

    /*!
     * Dereferences the iterator to return a reference to the base type
     * @tparam T The base type
     * @tparam U The derived iteraator type
     * @return A reference to the base class
     */
    template<typename T, typename U>
    T &Templ_Iterator<T, U>::operator*()
    {
        return *it;
    }

    /*!
     * Dereferences the iterator to return a const reference to the base type
     * @tparam T The base type
     * @tparam U The derived iterator type
     * @return A const reference to the base class
     */
    template<typename T, typename U>
    const T &Templ_Iterator<T, U>::operator*() const
    {
        return *it;
    }

    /*!
     * Arrow operator
     * @tparam T The base type
     * @tparam U The derived iterator type
     * @return The address of the base type object
     */
    template<typename T, typename U>
    T *Templ_Iterator<T, U>::operator->()
    {
        return &*it;
    }

    /*!
     * Constant arrow operator
     * @tparam T The base type
     * @tparam U The derived iterator type
     * @return The address of the base type object (const)
     */
    template<typename T, typename U>
    T const *Templ_Iterator<T, U>::operator->() const
    {
        return &*it;
    }

    /*!
     * Moves the iterator forward, pre-increment
     * @tparam T The base type
     * @tparam U The derived iterator type
     * @return The object that this operator is being called on
     */
    template<typename T, typename U>
    Semi_Uniform_It<T> &Templ_Iterator<T, U>::operator++()
    {
        ++it;
        return *this;
    }

    /*!
     * Moves the iterator forward, post-increment
     * @tparam T The base type
     * @tparam U The derived type
     * @return A copy of the object that this operator is being called on, before the operation happened
     */
    template<typename T, typename U>
    std::unique_ptr<Semi_Uniform_It<T> *> Templ_Iterator<T, U>::operator++(int)
    {
        auto rv = std::make_unique<Semi_Uniform_It<T> *>(reinterpret_cast<Semi_Uniform_It<T> *>(copy()));
        it++;
        return rv;
    }

    /*!
     * Assignment operator
     * @tparam T The base type
     * @tparam U The derived type
     * @param rhs The right hand operator
     * @return The left hand operator of the assignment
     */
    template<typename T, typename U>
    Semi_Uniform_It<T> &Templ_Iterator<T, U>::operator=(Semi_Uniform_It<T> const &rhs) noexcept(true)
    {
        return (*this = static_cast<const Templ_Iterator<T, U> &>(rhs));
    }

    /*!
     * Equality operator
     * @tparam T The base type
     * @tparam U The derived type
     * @param rhs The right hand operator
     * @return boolean, true if both are equal, false if not
     */
    template<typename T, typename U>
    bool Templ_Iterator<T, U>::operator==(const Semi_Uniform_It<T> &rhs)
    {
        return it == static_cast<const Templ_Iterator<T, U> &>(rhs).it;
    }

    /*!
     * Inequality operator
     * @tparam T The base type
     * @tparam U The derived type
     * @param rhs The right hand operator
     * @return boolean, true if both are not the same, false if not
     */
    template<typename T, typename U>
    bool Templ_Iterator<T, U>::operator!=(const Semi_Uniform_It<T> &rhs)
    {
        return it != static_cast<const Templ_Iterator<T, U> &>(rhs).it;
    }

    /*!
     * Copies this object into a new object
     * @tparam T The base class
     * @tparam U The derived iterator
     * @return A pointer to the copy object
     */
    template<typename T, typename U>
    Semi_Uniform_It<T> *Templ_Iterator<T, U>::copy() const
    {
        return new Templ_Iterator(*this);
    }

    /*!
     * Assignment operator, using the exact template
     * @tparam T The base type
     * @tparam U The derived iterator type
     * @param rhs The right hand operator
     * @return The left hand operator of the assignment
     */
    template<typename T, typename U>
    Semi_Uniform_It<T> &Templ_Iterator<T, U>::operator=(Templ_Iterator<T, U> const &rhs)
    {
        it = rhs.it;
        return *this;
    }

    /*!
     * The public interface for creating an iterator for the first time
     * @tparam T The base class
     * @tparam U The deriverd class iterator
     * @param it An iterator to the derived class container
     * @return A unique pointer to the semi-uniform iterator
     */
    template<typename T, typename U>
    std::unique_ptr<Semi_Uniform_It<T> *> MakeIterator(U it)
    {
        return std::make_unique<Semi_Uniform_It<T> *>(
                reinterpret_cast<Semi_Uniform_It<T> *>(new Templ_Iterator<T, U>(it)));
    }

    /*!
    * The public interface for creating a constant iterator
    * @tparam T The base type
    * @tparam U The derived type iterator
    * @param it The iterator
    * @return A unique pointer to the constant iterator
    */
    template<typename T, typename U>
    std::unique_ptr<const Semi_Uniform_It<T> *> MakeCIterator(U it)
    {
        return std::make_unique<const Semi_Uniform_It<T> *>(
                reinterpret_cast<Semi_Uniform_It<T> *>(new Templ_Iterator<T, U>(it)));
    }
}

#endif //TEMPL_ITERATOR_ITERATOR_CPP