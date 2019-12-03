/*!
 * @file iterator.h
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 0.8
 */

#include <memory>

#ifndef TEMPL_ITERATOR_ITERATOR_H
#define TEMPL_ITERATOR_ITERATOR_H

namespace iterate
{
    /*!
     * The base class iterator pure virtual type
     * @tparam T The base class type
     */
    template<typename T>
    class Semi_Uniform_It
    {
    public:
        /*!
         * The default destructor for the base class iterator
         */
        virtual ~Semi_Uniform_It() noexcept(true) = default;

        /*!
         * Dereferences the iterator to return a reference to the base type
         * @return A reference to the base class
         */
        virtual T &operator*() = 0;

        /*!
         * Dereferences the iterator to return a const reference to the base type
         * @return A const reference to the base class
         */
        virtual T const &operator*() const = 0;

        /*!
         * Arrow operator
         * @return The address of the base type object
         */
        virtual T *operator->() = 0;

        /*!
         * Constant arrow operator
         * @return The address of the base type object (const)
         */
        virtual T const *operator->() const = 0;

        /*!
         * Moves the iterator forward, pre-increment
         * @return The object that this operator is being called on
         */
        virtual Semi_Uniform_It<T> &operator++() = 0;

        /*!
         * Moves the iterator forward, post-increment
         * @return A copy of the object that this operator is being called on, before the operation happened
         */
        virtual std::unique_ptr<Semi_Uniform_It<T> *> operator++(int) = 0;

        /*!
         * Assignment operator
         * @return The left hand operator of the assignment
         */
        virtual Semi_Uniform_It<T> &operator=(Semi_Uniform_It<T> const &) noexcept(true) = default;

        /*!
         * Equality operator
         * @return boolean, true if both are equal, false if not
         */
        virtual bool operator==(Semi_Uniform_It<T> const &) = 0;

        /*!
         * Inequality operator
         * @return boolean, true if both are not the same, false if not
         */
        virtual bool operator!=(Semi_Uniform_It<T> const &) = 0;

        /*!
         * Copies this object into a new object
         * @return A pointer to the copy object
         */
        virtual Semi_Uniform_It<T> *copy() const = 0;
    };

    /*!
     * The template iterator class, this actually holds the iterator
     * @tparam T The base type
     * @tparam U The type of the internally stored iterator
     */
    template<typename T, typename U>
    class Templ_Iterator
            : public Semi_Uniform_It<T>
    {
        /*!
         * The internally stored iterator
         */
        U it;
    public:
        /*!
         * There is no default constructor because the
         * internal iterator would be uninitialized garbage
         */
        Templ_Iterator() = delete;

        /*!
         * A default destructor since there is no allocated memory
         */
        ~Templ_Iterator() noexcept(true) = default;

        /*!
         * A single-argument constructor for the template iterator
         */
        explicit Templ_Iterator(U &);

        /*!
         * A copy constructor for the template iterator
         */
        Templ_Iterator(Templ_Iterator<T, U> const &);

        /*!
         * Dereferences the iterator to return a reference to the base type
         * @return A reference to the base class
         */
        T &operator*();

        /*!
         * Dereferences the iterator to return a const reference to the base type
         * @return A const reference to the base class
         */
        const T &operator*() const;

        /*!
         * Arrow operator
         * @return The address of the base type object
         */
        T *operator->();

        /*!
         * Constant arrow operator
         * @return The address of the base type object (const)
         */
        T const *operator->() const;

        /*!
         * Moves the iterator forward, pre-increment
         * @return The object that this operator is being called on
         */
        Semi_Uniform_It<T> &operator++();

        /*!
         * Moves the iterator forward, post-increment
         * @return A copy of the object that this operator is being called on, before the operation happened
         */
        std::unique_ptr<Semi_Uniform_It<T> *> operator++(int);

        /*!
         * Assignment operator
         * @return The left hand operator of the assignment
         */
        Semi_Uniform_It<T> &operator=(Semi_Uniform_It<T> const &) noexcept(true);

        /*!
         * Assignment operator, using the exact template
         * @return The left hand operator of the assignment
         */
        Semi_Uniform_It<T> &operator=(Templ_Iterator<T, U> const &);

        /*!
         * Equality operator
         * @return boolean, true if both are equal, false if not
         */
        bool operator==(Semi_Uniform_It<T> const &);

        /*!
         * Inequality operator
         * @return boolean, true if both are not the same, false if not
         */
        bool operator!=(Semi_Uniform_It<T> const &);

        /*!
         * Copies this object into a new object
         * @return A pointer to the copy object
         */
        Semi_Uniform_It<T> *copy() const;
    };

    /*!
     * The public interface for creating an iterator for the first time
     * @tparam T The base class
     * @tparam U The deriverd class iterator
     * @param it An iterator to the derived class container
     * @return A unique pointer to the semi-uniform iterator
     */
    template<typename T, typename U>
    std::unique_ptr<Semi_Uniform_It<T> *> MakeIterator(U it);

    /*!
     * The public interface for creating a constant iterator
     * @tparam T The base type
     * @tparam U The derived type iterator
     * @param it The iterator
     * @return A unique pointer to the constant iterator
     */
    template<typename T, typename U>
    std::unique_ptr<const Semi_Uniform_It<T> *> MakeCIterator(U it);
}
#include "iterator.cpp"

#endif //TEMPL_ITERATOR_ITERATOR_H