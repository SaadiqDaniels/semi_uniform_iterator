/*!
 * @file constructor_driver.cpp
 * @author Saadiq Daniels
 * @date 18/12/2021
 * @version 2.0
 */

#include <vector>

#include "iterator.h"
#include "base.h"

/*!
 * Tests to make sure that all of the constructor cases work as intended
 */
int main() {

    // Creating data //

    std::vector<derived1> derived1_vector;
    derived1_vector.reserve(100);
    // Push data back into all the containers
    for (int i = 0; i < 100; ++i) {
        // Push to the back of the vector
        derived1_vector.emplace_back(static_cast<float>(i));

    }

    // Testing constructors //
    {
        // Testing -> Iterator(const Iterator<mutable_value_type> &rhs) noexcept(true)
        Iterator<base> a = MakeIterator<base>(derived1_vector.begin());
        {
            Iterator<base> new_iterator(a);
        }
        {
            Iterator<const base> new_iterator(a);
        }
    }
    {
        // Testing -> Iterator(const Iterator<const_value_type> &rhs) noexcept(true)
        Iterator<const base> a = MakeIterator<const base>(derived1_vector.begin());
        {
            // Uncomment this line to make sure that it does not work
            //Iterator<base> new_iterator(a);
        }
        {
            Iterator<const base> new_iterator(a);
        }
    }
    {
        // Testing -> Iterator(Iterator<mutable_value_type> &&rhs) noexcept(true)
        {
            Iterator<base> new_iterator(MakeIterator<base>(derived1_vector.begin()));
        }
        {
            Iterator<const base> new_iterator(MakeIterator<base>(derived1_vector.begin()));
        }
    }
    {
        // Testing -> Iterator(Iterator<const_value_type> &&rhs) noexcept(true)
        {
            // Uncomment this line to make sure that it does not work
            //Iterator<base> new_iterator(MakeIterator<const base>(derived1_vector.begin()));
        }
        {
            Iterator<const base> new_iterator(MakeIterator<const base>(derived1_vector.begin()));
        }
    }
    {
        // Testing -> template<typename U> explicit Iterator(IteratorWrapper<mutable_value_type, U> *rhs) noexcept(true)
        IteratorWrapper<base, std::vector<derived1>::iterator>
                a(derived1_vector.begin());
        a.DisableMemoryManagement();
        {
            Iterator<base> new_iterator(&a);
        }
        {
            Iterator<const base> new_iterator(&a);
        }
        // Uncomment this line to make sure that it does not work
        //IteratorWrapper<base, std::vector<derived1>::const_iterator> b(derived1_vector.cbegin());
    }
    {
        // Testing -> template<typename U> Iterator(IteratorWrapper<const_value_type, U> *rhs) noexcept(true)
        IteratorWrapper<const base, std::vector<derived1>::iterator>
                a(derived1_vector.begin());
        IteratorWrapper<const base, std::vector<derived1>::const_iterator>
                b(derived1_vector.cbegin());
        a.DisableMemoryManagement();
        b.DisableMemoryManagement();
        {
            // Uncomment this line to make sure that it does not work
            //Iterator<base> new_iterator(&a);
        }
        {
            // Uncomment this line to make sure that it does not work
            //Iterator<base> new_iterator(&b);
        }
        {
            Iterator<const base> new_iterator(&a);
        }
        {
            Iterator<const base> new_iterator(&b);
        }
    }

    return 0;
}