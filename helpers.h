/*!
 * @file helpers.h
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 0.8
 */

#ifndef TEMPL_ITERATOR_HELPERS_H
#define TEMPL_ITERATOR_HELPERS_H

#include <iostream>

#include "iterator.h"    // Iterator stuff
#include "inheritance.h" // Inheritance classes

// An iterator
typedef std::unique_ptr<iterate::Semi_Uniform_It<inherit::base>*> it_rtr;
// A constant iterator
typedef std::unique_ptr<const iterate::Semi_Uniform_It<inherit::base>*> cit_rtr;

namespace helper
{
    void print(it_rtr& begin, cit_rtr& end)
    {
        while (begin != end)
        {
            // Print out the number
            std::cout << ***begin << " ";
            // Move to the next
            ++(**begin);
        }
        // End the line
        std::cout << std::endl;
    }
}

#endif //TEMPL_ITERATOR_HELPERS_H
