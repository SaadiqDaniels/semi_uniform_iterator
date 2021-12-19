/*!
 * @file algorithm_driver.cpp
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 2.0
 */

#include <iostream>
#include <deque>
#include <algorithm>
#include <random>

#include "iterator.h"
#include "base.h"

/*!
 * Tests the uses of the iterator classes with
 * standard template library algorithms
 * @return 0
 */
int main() {

	std::deque<derived1> vector;
	for (int             i = 0; i < 100; ++i)
	{
		// Push to the front of the vector
		vector.emplace_front(i);
	}
    // Scramble the vector
    // This needs random access iterators, which are not accessible through Iterator<T> classes
    std::shuffle(vector.begin(), vector.end(), std::mt19937(std::random_device()()));

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

	// Print again, starting from the smallest element
	std::for_each(min, list_back, [](const base &rhs) {
		std::cout << dynamic_cast<const derived1&>(rhs);
	});
	std::cout << std::endl;

	return 0;
}