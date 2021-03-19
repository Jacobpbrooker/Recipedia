#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "admin.h"
#include "queue.h"
#include "restaurant.h"
#include "SaveLoad.h"

#define RECIPEDIALOADFILE "restaurants/toptenrestaurants.txt"

int main(int argc, char* argv[])
{
	PRESTAURANTNODE	restaurantList = testLoad(RECIPEDIALOADFILE);

	bool adminAccess = adminMode(argv[1], strlen(argv[1]));

	if (adminAccess)
	{
		// allow them to delete or add
		exit(EXIT_SUCCESS);
	}
	else
	{

	}

	//PRESTAURANTNODE	restaurantList = loadOrCreate(RECIPEDIALOADFILE);

	//saveFile(restaurantList);

	exit(EXIT_SUCCESS);
}
