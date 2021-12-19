/*!
 * @file s_map_driver.cpp
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 2.0
 */

#include <iostream>
#include <map>
#include <unordered_map>

#include "iterator.h"
#include "base.h"

/*!
 * Tests simple uses of iterators on map containers :
 * print data from beginning to end
 * @return 0
 */
int main() {

    // Creating data //

    // Base class is on the left
    std::map<derived1, int> derived1_map;
    // Base class is on the right
    std::unordered_map<int, derived2> derived2_hash;

    for (int i = 0; i < 10; ++i) {
        derived1_map[derived1(static_cast<float>(i))] = i;

        derived2_hash.insert(
                std::make_pair<int, derived2>(
                        reinterpret_cast<int &&>(i),
                        derived2(static_cast<float>(i))
                ));
    }

    // Printing derived1_map //
    Iterator<const base> derived1_map_begin = MakeIteratorLeft<const base>(derived1_map.begin());
    Iterator<const base> derived1_map_end = MakeIteratorLeft<const base>(derived1_map.end());

    std::cout << "Derived1_Map:" << std::endl;
    for(; derived1_map_begin != derived1_map_end; ++derived1_map_begin)
    {
        std::cout << "(" << (*derived1_map_begin).getInt() << ", " << (*derived1_map_begin).getfloat() << ")\t";
    }
    std::cout << std::endl;

    Iterator<base> derived2_hash_begin = MakeIteratorRight<base>(derived2_hash.begin());
    Iterator<base> derived2_hash_end = MakeIteratorRight<base>(derived2_hash.end());

    std::cout << "Derived3_Hash:" << std::endl;
    for(; derived2_hash_begin != derived2_hash_end; derived2_hash_begin++)
    {
        std::cout << "(" << derived2_hash_begin->getInt() << ", " << derived2_hash_begin->getfloat() << ")\t";
    }
    std::cout << std::endl;

    return 0;
}