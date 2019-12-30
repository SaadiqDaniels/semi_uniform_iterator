/*!
 * @file helpers.h
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 0.8
 */

#ifndef TEMPL_ITERATOR_HELPERS_H
#define TEMPL_ITERATOR_HELPERS_H

#include <iostream>

#include "iterator.h"

template<typename T>
void print(Iterator<T> begin, const Iterator<T> &end) {

	while (begin != end)
	{
		// Print out the number
		// Move to the next
		std::cout << *(begin++) << " ";
	}
	// End the line
	std::cout << std::endl;
}

template<typename T>
void print(Iterator<const T> begin, const Iterator<const T> &end) {

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
