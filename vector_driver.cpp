/*!
 * @file s_vector_driver.cpp
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 2.0
 */

#include <vector>
#include <list>
#include <deque>

#include "iterator.h"
#include "base.h"

/*!
 * Tests simple uses of vector containers
 * @return 0
 */
int main() {

    // Creating data //

    // Three different data structures
    std::list<derived1> derived1_list;
    std::vector<derived1> derived1_vector;
    std::deque<derived3> derived3_deque;
    // Push data back into all the containers
    for (int i = 0; i < 100; ++i) {
        // Push to the front of the list
        derived1_list.emplace_front(static_cast<float>(i));
        // Push to the back of the vector
        derived1_vector.emplace_back(static_cast<float>(i));
        // Alternate between pushing to the front and back of the list
        if (i % 2) {
            derived3_deque.emplace_front(static_cast<float>(i));
        } else {
            derived3_deque.emplace_back(static_cast<float>(i));
        }
    }

    // Printing derived1_list //
    Iterator<base> derived1_list_begin = MakeIterator<base>(derived1_list.begin());
    Iterator<base> derived1_list_end = MakeIterator<base>(derived1_list.end());

    std::cout << "Derived1_List:" << std::endl;
    for(; derived1_list_begin != derived1_list_end; derived1_list_begin++)
    {
        std::cout << "(" << (*derived1_list_begin).getInt() << ", " << (*derived1_list_begin).getfloat() << ")\t";
    }
    std::cout << std::endl;

    // Printing derived1_vector //
    Iterator<const base> derived1_vector_begin = MakeIterator<const base>(derived1_vector.cbegin());
    Iterator<const base> derived1_vector_end = MakeIterator<const base>(derived1_vector.cend());

    std::cout << "Derived1_Vector:" << std::endl;
    for(; derived1_vector_begin != derived1_vector_end; ++derived1_vector_begin)
    {
        std::cout << "(" << (*derived1_vector_begin).getInt() << ", " << (*derived1_vector_begin).getfloat() << ")\t";
    }
    std::cout << std::endl;

    // Printing derived3_deque //
    Iterator<base> derived3_deque_begin = MakeIterator<base>(derived3_deque.begin());
    Iterator<base> derived3_deque_end = MakeIterator<base>(derived3_deque.end());

    std::cout << "Derived3_Deque:" << std::endl;
    for(; derived3_deque_begin != derived3_deque_end; ++derived3_deque_begin)
    {
        std::cout << "(" << derived3_deque_begin->getInt() << ", " << derived3_deque_begin->getfloat() << ")\t";
    }
    std::cout << std::endl;

    return 0;
}