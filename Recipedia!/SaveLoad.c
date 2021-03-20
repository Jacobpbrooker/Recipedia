#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "restaurant.h"
#include "SaveLoad.h"

#define FILENAME "restaurantList.txt"

#define RESTAURANTLINES 6
#define MAXSTRINGLENGTH 100

// load restaurant linked list
//PRESTAURANTNODE loadOrCreate(char* filename)
//{
//	FILE* fp;
//	errno_t fileError = fopen_s(&fp, FILENAME, "r");
//
//	if (fp == NULL)
//	{
//		fprintf(stderr, "File failed to open, exiting\n");
//		exit(EXIT_FAILURE);
//	}
//
//	PRESTAURANTNODE restaurantListPointer = NULL;
//
//	char ch;
//	int lines = 0;
//	while (!feof(fp))
//	{
//		ch = fgetc(fp);
//		if (ch == '\n')
//		{
//			lines++;
//		}
//	}
//	fseek(fp, 0, SEEK_SET);
//
//	for (int i = lines / RESTAURANTLINES; i > 0; i--)
//	{
//		char* restaurantName = malloc(MAXSTRINGLENGTH);			// I should probably explicitly typecast these
//		restaurantName[0] = 0;
//		char* headChef = malloc(MAXSTRINGLENGTH); 
//		headChef[0] = 0;
//		char* sypnopsis = malloc(MAXSTRINGLENGTH);
//		sypnopsis[0] = 0;
//		char* firstSpeciality = malloc(MAXSTRINGLENGTH);
//		firstSpeciality[0] = 0;
//		char* secondSpeciality = malloc(MAXSTRINGLENGTH);
//		secondSpeciality[0] = 0;
//		char* thirdSpeciality = malloc(MAXSTRINGLENGTH);
//		thirdSpeciality[0] = 0;
//		
//		char tempHolding[MAXSTRINGLENGTH] = { '\0' };
//		char buffer[MAXSTRINGLENGTH] = { '\0' };
//
//		fgets(restaurantName, MAXSTRINGLENGTH, fp);
//		fgets(headChef, MAXSTRINGLENGTH, fp);
//		fgets(sypnopsis, MAXSTRINGLENGTH, fp);
//		fgets(firstSpeciality, MAXSTRINGLENGTH, fp);
//		fgets(secondSpeciality, MAXSTRINGLENGTH, fp);
//		fgets(thirdSpeciality, MAXSTRINGLENGTH, fp);
//
//		// this will add the terminator to each of the char strings added
//		for (unsigned int i = 0; i < strlen(restaurantName); i++)
//		{
//			if (restaurantName[i] == '\n')
//			{
//				restaurantName[i] = '\0';
//			}
//		}
//		for (unsigned int i = 0; i < strlen(headChef); i++)
//		{
//			if (headChef[i] == '\n')
//			{
//				headChef[i] = '\0';
//			}
//		}
//		for (unsigned int i = 0; i < strlen(sypnopsis); i++)
//		{
//			if (sypnopsis[i] == '\n')
//			{
//				sypnopsis[i] = '\0';
//			}
//		}
//		for (unsigned int i = 0; i < strlen(firstSpeciality); i++)
//		{
//			if (firstSpeciality[i] == '\n')
//			{
//				firstSpeciality[i] = '\0';
//			}
//		}
//		for (unsigned int i = 0; i < strlen(secondSpeciality); i++)
//		{
//			if (secondSpeciality[i] == '\n')
//			{
//				secondSpeciality[i] = '\0';
//			}
//		}
//		for (unsigned int i = 0; i < strlen(thirdSpeciality); i++)
//		{
//			if (thirdSpeciality[i] == '\n')
//			{
//				thirdSpeciality[i] = '\0';
//			}
//		}
//
//		restaurantListPointer = createRestaurant(restaurantListPointer, restaurantName, headChef, sypnopsis, firstSpeciality, secondSpeciality, thirdSpeciality);
//	}
//
//	fclose(fp);
//
//	return restaurantListPointer;
//}

// save file does not work yet
bool saveFile(PRESTAURANTNODE list)
{
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

	for (int i = 0;i < lines; i++)
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