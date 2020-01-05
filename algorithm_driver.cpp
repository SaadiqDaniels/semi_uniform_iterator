/*!
 * @file algorithm_driver.cpp
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 1.0
 */

#include <iostream>      // std::cout

#include <list>          // std::list
#include <deque>         // std::deque

#include <algorithm>     // std::sort, std::find

#include "iterator.h"    // Iterator stuff
#include "base.h"        // Inheritance classes
#include "helpers.h"     // Print function

/*!
 * Tests the uses of the iterator classes with
 * standard template library algorithms
 * @return 0
 */
int main() {

	std::deque<derived1> vector;
	for (int             i = 0; i < 2; ++i)
	{
		// Push to the front of the vector
		vector.push_front(i);
	}

	// Make iterators for the front and back
	Iterator<base> list_front = MakeIterator<base>(vector.begin());
	Iterator<base> list_back  = MakeIterator<base>(vector.end());

	// Print the list using the iterators
	std::for_each(list_front, list_back, [](const base &rhs) {
		std::cout << rhs;
	});
	std::cout << std::endl;

	// Find the smallest element
	auto min = std::min_element(list_front, list_back);
	std::cout << *min << std::endl;

	// Print again
	std::for_each(list_front, list_back, [](const base &rhs) {
		std::cout << rhs;
	});
	std::cout << std::endl;

	return 0;
}