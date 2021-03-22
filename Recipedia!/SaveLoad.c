#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "restaurant.h"
#include "SaveLoad.h"

#define FILENAME "restaurantList.txt"

#define RESTAURANTLINES 6
#define MAXSTRINGLENGTH 100

// load restaurants to list
PRESTAURANTNODE loadRestaurants(char* filename)
{
	FILE* fp;
	errno_t fileError = fopen_s(&fp, filename, "r");

	if (fp == NULL)
	{
		fprintf(stderr, "File failed to open, exiting\n");
		exit(EXIT_FAILURE);
	}

	PRESTAURANTNODE restaurantListPointer = NULL;

	char restaurantFiles[10][50] = { '\0' };

	char ch;
	int lines = 0;
	while (!feof(fp))
	{
		ch = fgetc(fp);
		if (ch == '\n')
		{
			lines++;
		}
	}
	fseek(fp, 0, SEEK_SET);

	for (int i = 0; i < lines; i++)
	{


		fgets(restaurantFiles[i], MAXSTRINGLENGTH, fp);

		// this will add the terminator to each of the char strings added
		for (unsigned int j = 0; j < strlen(restaurantFiles[i]); j++)
		{
			if (restaurantFiles[i][j] == '\n')
			{
				restaurantFiles[i][j] = '\0';
			}
		}
		// do i need to return maybe new restaurant
		restaurantListPointer = createRestaurant(restaurantListPointer, returnRestaurant(restaurantFiles[i]));
	}

	fclose(fp);

	return restaurantListPointer;
}

// save file does not work yet
bool saveFile(PRESTAURANTNODE list)
{
	// i need to follow every step of the load process but just not write until I have all the file names
	// read master file
	// follow file path to sub master document
	// open restaurant doc
	//		write restaurant to file
	// open ingredients doc
	//		write ingredients to file
	//		*loop* free instruction node
	//		free ingredients queue
	// open instruction doc
	//		write instruction to file
	//		*loop* free instruction node
	//		free instruction queue

	FILE* fp;
	errno_t fileError = fopen_s(&fp, FILENAME, "w");

	if (fp == NULL)
	{
		fprintf(stderr, "File failed to write, exiting\n");
		exit(EXIT_FAILURE);

	}

	PRESTAURANTNODE tempList = (PRESTAURANTNODE)malloc(sizeof(PRESTAURANTNODE));
	if (!tempList)
	{
		fprintf(stderr, "Failed to allocate memory for RestaurantList, exiting\n");
		exit(EXIT_FAILURE);
	}

	tempList = list;

	do
	{
		fprintf(fp, "%s\n", tempList->restaurant.restaurantName);
		fprintf(fp, "%s\n", tempList->restaurant.headChef);
		fprintf(fp, "%s\n", tempList->restaurant.restaurantSypnopsis);
		for (int i = 0; i < MENUSIZE; i++)
		{
			fprintf(fp, "%s\n", tempList->restaurant.specialityMenu[i]);
		}

		tempList = fetchNextNode(tempList);

		//this is where I will write the save data back
	} while (tempList != NULL);

	fclose(fp);

	return EXIT_SUCCESS;
}

