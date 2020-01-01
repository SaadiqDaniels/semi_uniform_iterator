/*!
 * @file c_map_driver.cpp
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 0.5
 */

#include <iostream>      // std::cout

#include <map>           // std::map
#include <unordered_map> // std::unordered_map

#include "iterator.h"    // Iterator stuff
#include "base.h"        // Inheritance classes
#include "helpers.h"     // Print function

/*!
 * Tests complex uses of map containers :
 * swapping data
 * printing data
 * reverse iterating
 * @return
 */
int main()
{
	// Base class is on the left
	std::map<derived1, int> map_d1;
	// Base class is on the right
	std::unordered_map<int, derived2> unmap_d2;

	for(int i = 0; i < 10; ++i)
	{
		map_d1[derived1(i)] = i;

		unmap_d2.insert(std::make_pair<int, derived2>(reinterpret_cast<int &&>(i), derived2(i)));
	}

	auto map_d1_front = MakeIteratorLeft<const base>(map_d1.begin());
	auto map_d1_back = MakeIteratorLeft<const base>(map_d1.end());

	auto unmap_d2_front = MakeIteratorRight<const base>(unmap_d2.begin());
	auto unmap_d2_back = MakeIteratorRight<const base>(unmap_d2.end());

	print(map_d1_front, map_d1_back);

	print(unmap_d2_front, unmap_d2_back);

	return 0;
}