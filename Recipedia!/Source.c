#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "admin.h"
#include "queue.h"
#include "restaurant.h"
#include "SaveLoad.h"
#include "search.h"
#pragma warning(disable:4996)
#define RECIPEDIALOADFILE "restaurants/toptenrestaurants.txt"

int main(int argc, char* argv[])
{
	PRESTAURANTNODE	restaurantList = testLoad(RECIPEDIALOADFILE);

	char str[20];

	scanf("%s", str);
	PRESTAURANTNODE a = searchRecipe(restaurantList, str);
	printf("%s", a->restaurant.specialityMenu[2]);
	
	/*
	bool adminAccess = adminMode(argv[1], strlen(argv[1]));

	if (adminAccess)
	{
		// allow them to delete or add
		exit(EXIT_SUCCESS);
	}
	else
	{

	}*/

	//loadOrCreate(RECIPEDIALOADFILE);
	//PRESTAURANTNODE	restaurantList = loadOrCreate(RECIPEDIALOADFILE);

	//saveFile(restaurantList);

	exit(EXIT_SUCCESS);
}
