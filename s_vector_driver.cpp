/*!
 * @file s_vector_driver.cpp
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 0.5
 */

#include <iostream>      // std::cout
#include <cassert>       // assert

#include <vector>        // std::vector
#include <list>          // std::list

#include "iterator.h"    // Iterator stuff
#include "inheritance.h" // Inheritance classes

#include "helpers.h"     // print

/*!
 * Tests simple uses of vector containers:
 * list values
 * set values
 * @return 0
 */
int main()
{
    // Three different data structures
    std::list<inherit::derived1> list_d1;
    std::vector<inherit::derived1> vector_d1;
    std::list<inherit::derived3> list_d3;

    // Push data back into all of the containers
    for(int i = 0; i < 10; ++i)
    {
        // Push to the front of the list
        list_d1.push_front(i);
        // Push to the back of the vector
        vector_d1.push_back(i);

        // Alternate between pushing to the front and back of the list
        if(i % 2)
            list_d3.push_front(inherit::derived3());
        else
            list_d3.emplace_back(inherit::derived3());
    }

    assert(list_d1.size() == vector_d1.size() && vector_d1.size() == list_d3.size());

    it_rtr list_d1_it_rtr = iterate::MakeIterator<inherit::base>(list_d1.begin());
    cit_rtr list_d1_cit_rtr = iterate::MakeCIterator<inherit::base>(list_d1.end());

    // Print the d1 list using the iterators
    helper::print(list_d1_it_rtr, list_d1_cit_rtr);

    return 0;
}