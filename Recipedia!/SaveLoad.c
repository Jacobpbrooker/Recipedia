#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "restaurant.h"
#include "SaveLoad.h"

#define FILENAME "restaurantList.txt"

#define RESTAURANTLINES 6
#define MAXSTRINGLENGTH 100
#define NUMBEROFRESTAURANTS 10
#define RESTAURANTNAME 50

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

	char restaurantFiles[NUMBEROFRESTAURANTS][RESTAURANTNAME] = { '\0' };

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

// save file
bool saveFile(PRESTAURANTNODE list, char* filename)
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

	// open and read master file (don't need to write to this file only read)
	FILE* fp;
	errno_t fileError = fopen_s(&fp, filename, "r");

	if (fp == NULL)
	{
		fprintf(stderr, "File failed to open, exiting\n");
		exit(EXIT_FAILURE);
	}

	char restaurantFiles[NUMBEROFRESTAURANTS][RESTAURANTNAME] = { '\0' };		// set the multidimensional array for restaurants and their directory locations

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

		// I could call three different functions
		saveRestaurantInfo(list, getRestaurantFileName(restaurantFiles[i]));
		saveIngredients(list, getIngredientsFileName(restaurantFiles[i]));
		saveInstructions(list, getInstructionsFileName(restaurantFiles[i]));
		// or call one function three times
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

void saveRestaurant(PRESTAURANTNODE list, char* filename, DIRECTORYTYPE dir)
{
	if (dir == restaurantDir)
	{
		FILE* fp;
		errno_t fileError = fopen_s(&fp, filename, "w");		// this needs to be write maybe

		if (fp == NULL)
		{
			fprintf(stderr, "File failed to open, exiting\n");
			exit(EXIT_FAILURE);
		}
		
		PRESTAURANTNODE tempList = (PRESTAURANTNODE)malloc(sizeof(PRESTAURANTNODE));

		if (!tempList)
		{
			fprintf(stderr, "Failed to allocate memory for RestaurantList, exiting\n");
			exit(EXIT_FAILURE);
		}

		tempList = list;

		//tempList = searchForNode(name)

		fprintf(fp, "%s\n", tempList->restaurant.restaurantName);
		fprintf(fp, "%s\n", tempList->restaurant.headChef);
		fprintf(fp, "%s\n", tempList->restaurant.restaurantSypnopsis);
		fprintf(fp, "%s\n", tempList->restaurant.specialityMenu[0]);
		fprintf(fp, "%s\n", tempList->restaurant.specialityMenu[1]);
		fprintf(fp, "%s\n", tempList->restaurant.specialityMenu[2]);
	}
	else if (dir == ingredientsDir)
	{

	}
	else if (dir == instructionsDir)
	{

	}


	free(filename);
}

char* getRestaurantFileName(char* filename)
{
	FILE* fp;
	errno_t fileError = fopen_s(&fp, filename, "r");

	char* restaurantInfo = (char*)malloc(MAXSTRINGLENGTH);
	char* ingredientInfo = (char*)malloc(MAXSTRINGLENGTH);
	char* instructionInfo = (char*)malloc(MAXSTRINGLENGTH);

	if (fp == NULL)
	{
		fprintf(stderr, "File failed to open, exiting\n");
		exit(EXIT_FAILURE);
	}

	// so i need to return the first directory in notepad
	fgets(restaurantInfo, MAXSTRINGLENGTH, fp);
	fgets(ingredientInfo, MAXSTRINGLENGTH, fp);
	fgets(instructionInfo, MAXSTRINGLENGTH, fp);

	// this will add the terminator to each of the char strings added
	for (unsigned int i = 0; i < strlen(restaurantInfo); i++)
		if (restaurantInfo[i] == '\n')
			restaurantInfo[i] = '\0';

	free(ingredientInfo);
	free(instructionInfo);

	return restaurantInfo;
}

char* getIngredientsFileName(char* filename)
{
	FILE* fp;
	errno_t fileError = fopen_s(&fp, filename, "r");

	char* restaurantInfo = (char*)malloc(MAXSTRINGLENGTH);
	char* ingredientInfo = (char*)malloc(MAXSTRINGLENGTH);
	char* instructionInfo = (char*)malloc(MAXSTRINGLENGTH);

	if (fp == NULL)
	{
		fprintf(stderr, "File failed to open, exiting\n");
		exit(EXIT_FAILURE);
	}

	// so i need to return the first directory in notepad
	fgets(restaurantInfo, MAXSTRINGLENGTH, fp);
	fgets(ingredientInfo, MAXSTRINGLENGTH, fp);
	fgets(instructionInfo, MAXSTRINGLENGTH, fp);

	// this will add the terminator to each of the char strings added
	for (unsigned int i = 0; i < strlen(ingredientInfo); i++)
		if (ingredientInfo[i] == '\n')
			ingredientInfo[i] = '\0';

	free(restaurantInfo);
	free(instructionInfo);

	return ingredientInfo;
}
char* getInstructionsFileName(char* filename)
{
	FILE* fp;
	errno_t fileError = fopen_s(&fp, filename, "r");

	char* restaurantInfo = (char*)malloc(MAXSTRINGLENGTH);
	char* ingredientInfo = (char*)malloc(MAXSTRINGLENGTH);
	char* instructionInfo = (char*)malloc(MAXSTRINGLENGTH);

	if (fp == NULL)
	{
		fprintf(stderr, "File failed to open, exiting\n");
		exit(EXIT_FAILURE);
	}

	// so i need to return the first directory in notepad
	fgets(restaurantInfo, MAXSTRINGLENGTH, fp);
	fgets(ingredientInfo, MAXSTRINGLENGTH, fp);
	fgets(instructionInfo, MAXSTRINGLENGTH, fp);

	// this will add the terminator to each of the char strings added
	for (unsigned int i = 0; i < strlen(instructionInfo); i++)
		if (instructionInfo[i] == '\n')
			instructionInfo[i] = '\0';

	free(restaurantInfo);
	free(ingredientInfo);

	return instructionInfo;
}

void saveRestaurantInfo(PRESTAURANTNODE list, char* filename)
{
	FILE* fp;
	errno_t fileError = fopen_s(&fp, filename, "r");		// this needs to be write maybe

	if (fp == NULL)
	{
		fprintf(stderr, "File failed to open, exiting\n");
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
}

void saveIngredients(PRESTAURANTNODE list, char* filename)
{

}

void saveInstructions(PRESTAURANTNODE list, char* filename)
{

}