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
PRESTAURANTNODE searchRestaurant(PRESTAURANTNODE r, char* input)
{
	PRESTAURANTNODE copy = r;

	int count = 0;
	while (copy->nextNode != NULL)
	{
		count++;
		copy = copy->nextNode;
	}

	//reset copy to the head
	copy = r;

	//check if input matches the name of a restaurant
	for (int i = 0; i <= count; i++)
	{
		if (strcmp(input, copy->restaurant.restaurantName) == 0)
			return copy;

		copy = copy->nextNode;
	}

	//return an empty restaurant if nothing is found
	PRESTAURANTNODE empty = NULL;
	return empty;
}

PRESTAURANTNODE searchRecipe(PRESTAURANTNODE r, char* input)
{
	PRESTAURANTNODE copy = r;

	int count = 0;
	while (copy->nextNode != NULL)
	{
		count++;
		copy = copy->nextNode;
	}

	//reset copy to the head
	copy = r;

	//check if input matches the name of a recipe
	for (int i = 0; i <= count; i++) //for each restaurant
	{
		for (int j = 0; j < 3; j++) //for each recipe
		{
			if (strcmp(input, copy->restaurant.specialityMenu[j]) == 0)
				return copy;
		} 
		copy = copy->nextNode;
	}

	PRESTAURANTNODE empty = NULL;
	return empty;
}
