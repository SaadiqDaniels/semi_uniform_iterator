/*!
 * @file helpers.h
 * @author Saadiq Daniels
 * @date 2/12/2019
 * @version 0.8
 */

#ifndef TEMPL_ITERATOR_HELPERS_H
#define TEMPL_ITERATOR_HELPERS_H

#include <iostream>

#include "iteratorwrapper.h"

void print(Handle<base> begin, const Handle<base>& end) {

	while (*begin != *end)
	{
		// Print out the number
		std::cout << **begin << " ";
		// Move to the next
		++(*begin);
	}
	// End the line
	std::cout << std::endl;
}

#endif //TEMPL_ITERATOR_HELPERS_H
