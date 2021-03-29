#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "admin.h"
#include "queue.h"
#include "restaurant.h"
#include "SaveLoad.h"


#define MAXUSERNAME 50

int main(int argc, char* argv[])
{
	PRESTAURANTNODE	restaurantList = loadRestaurants(RECIPEDIADIRECTORY);

	//freeRestaurantList(restaurantList);
	if (!saveFile(restaurantList, RECIPEDIADIRECTORY))
		exit(EXIT_FAILURE);

	//exit(EXIT_SUCCESS);

	bool adminAccess = returnAdminConfirmation(argv[1], strlen(argv[1]));

	if (adminAccess)
	{
		// allow them to delete or add
		adminMode(restaurantList);
		exit(EXIT_SUCCESS);
	}
	else
	{
		char userName[MAXUSERNAME];
		strcpy_s(userName, MAXUSERNAME, argv[1]);
	}

	//PRESTAURANTNODE	restaurantList = loadOrCreate(RECIPEDIALOADFILE);

	//saveFile(restaurantList);

	exit(EXIT_SUCCESS);
}
