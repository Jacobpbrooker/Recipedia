#include "search.h"
#include <stdio.h>

PRESTAURANTNODE searchNum(PRESTAURANTNODE r, int input)
{
	PRESTAURANTNODE copy = r;

	//given a number, traverse the list that many times and return the restaurant there

	for (int i = 0; i < input-1; i++)
	{
		copy = copy->nextNode;
	}

	return copy;
}