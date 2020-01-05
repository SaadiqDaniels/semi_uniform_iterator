/*!
 * @file helpers.h
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 1.0
 */

#ifndef TEMPL_ITERATOR_HELPERS_H
#define TEMPL_ITERATOR_HELPERS_H

#include <iostream>

#include "iterator.h"

template<typename T, typename U>
void print(Iterator<T> begin, const Iterator<U> &end) {

	while (begin != end)
	{
		// Print out the number
		// Move to the next
		std::cout << *(begin++) << " ";
	}
	// End the line
	std::cout << std::endl;
}

#endif //TEMPL_ITERATOR_HELPERS_H
