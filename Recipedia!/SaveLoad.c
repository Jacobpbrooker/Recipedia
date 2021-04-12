#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "restaurant.h"
#include "SaveLoad.h"

#define FILENAME "restaurantList.txt"

#define INGREDIENTLINES 3
#define RESTAURANTLINES 6
#define MAXSTRINGLENGTH 100
#define NUMBEROFRESTAURANTS 10
#define RESTAURANTNAME 100

// load restaurants to list
PRESTAURANTNODE loadRestaurants(char* filename)
{
	FILE* fp;
	errno_t fileError = fopen_s(&fp, filename, "r");

	if (fp == NULL)
	{
		fprintf(stderr, "File failed to open %s, exiting\n", filename);
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
		//strcpy_s(restaurantFiles[i], MAXSTRINGLENGTH, nullTerminate(restaurantFiles[i]));
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
	// open and read master file (don't need to write to this file only read)
	FILE* fp;
	errno_t fileError = fopen_s(&fp, filename, "r");

	if (fp == NULL)
	{
		fprintf(stderr, "File - %s failed to open, exiting\n", filename);
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
		// this loop will add all the restaurants to a list
		fgets(restaurantFiles[i], MAXSTRINGLENGTH, fp);

	}

	// now I need a loop that saves them backwards

	for (int i = 9; i > 0; i--)
	{
		// this will add the terminator to each of the char strings added

		for (unsigned int j = 0; j < strlen(restaurantFiles[i]); j++)
		{
			if (restaurantFiles[i][j] == '\n')
			{
				restaurantFiles[i][j] = '\0';
			}
		}

		// Save the specific restaurant by using the text file directory
		saveRestaurantInfo(list, getRestaurantFileName(restaurantFiles[i]));
		saveIngredients(list, getIngredientsFileName(restaurantFiles[i]));
		saveInstructions(list, getInstructionsFileName(restaurantFiles[i]));

		// Move the list to the next node
		list = list->nextNode;
	}

	fclose(fp);

	return true;
}

char* getRestaurantFileName(char* filename)
{
	FILE* fp;
	errno_t fileError = fopen_s(&fp, filename, "r");

	char* restaurantInfo = (char*)malloc(sizeof(char) * MAXSTRINGLENGTH);
	char* ingredientInfo = (char*)malloc(sizeof(char) * MAXSTRINGLENGTH);
	char* instructionInfo = (char*)malloc(sizeof(char) * MAXSTRINGLENGTH);

	if (fp == NULL)
	{
		fprintf(stderr, "File - %s failed to open, exiting\n", filename);
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
		fprintf(stderr, "File - %s failed to open, exiting\n", filename);
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
		fprintf(stderr, "File - %s failed to open, exiting\n", filename);
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
	errno_t fileError = fopen_s(&fp, filename, "w");		// this needs to be write maybe

	if (fp == NULL)
	{
		fprintf(stderr, "File - %s failed to open, exiting\n", filename);
		exit(EXIT_FAILURE);
	}
	
	list->restaurant.restaurantName[strlen(list->restaurant.restaurantName)] = '\n';
	list->restaurant.headChef[strlen(list->restaurant.headChef)] = '\n';
	list->restaurant.restaurantSypnopsis[strlen(list->restaurant.restaurantSypnopsis)] = '\n';

	for (int i = 0; i < 3; i++)
	{
		list->restaurant.specialityMenu[i][strlen(list->restaurant.specialityMenu[i])] = '\n';
		//list->restaurant.specialityMenu[i][strlen(list->restaurant.specialityMenu[i])+1] = '\0';
		for (unsigned int j = 0; j < strlen(list->restaurant.specialityMenu[i]); j++)
		{
			if (list->restaurant.specialityMenu[i][j] == '\n')
			{
				j++;
				list->restaurant.specialityMenu[i][j] = '\0';
			}
		}
	}

	// write the restaurant information to txt file 
	fputs(list->restaurant.restaurantName, fp);
	fputs(list->restaurant.headChef, fp);
	fputs(list->restaurant.restaurantSypnopsis, fp);
	fputs(list->restaurant.specialityMenu[0], fp);
	fputs(list->restaurant.specialityMenu[1], fp);
	fputs(list->restaurant.specialityMenu[2], fp);

	fclose(fp);
}

void saveIngredients(PRESTAURANTNODE list, char* filename)
{
	FILE* fp;
	errno_t fileError = fopen_s(&fp, filename, "w");

	if (fp == NULL)
	{
		fprintf(stderr, "File - %s failed to open, exiting\n", filename);
		exit(EXIT_FAILURE);

	}
	// i think this needs to be a do while loop not a while loop
	while (list->restaurant.ingredientQueueHead->head != NULL)
	{
		// print the ingredients to the text file
		fprintf(fp, "%s\n", list->restaurant.ingredientQueueHead->head->ingredient);
		fprintf(fp, "%f\n", list->restaurant.ingredientQueueHead->head->measurement); // does this print properly?
		fprintf(fp, "%s\n", list->restaurant.ingredientQueueHead->head->unitOfMeasurement);
		
		// set the head to the next
		list->restaurant.ingredientQueueHead->head = list->restaurant.ingredientQueueHead->head->nextNode;
	}
	//do
	//{
	//	// print the ingredients to the text file
	//	fprintf(fp, "%s\n", list->restaurant.ingredientQueueHead->head->ingredient);
	//	fprintf(fp, "%f\n", list->restaurant.ingredientQueueHead->head->measurement); // does this print properly?
	//	fprintf(fp, "%s\n", list->restaurant.ingredientQueueHead->head->unitOfMeasurement);
	//	
	//	// set the head to the next
	//	list->restaurant.ingredientQueueHead->head = list->restaurant.ingredientQueueHead->head->nextNode;
	//} while (list->restaurant.ingredientQueueHead->head != list->restaurant.ingredientQueueHead->tail);

	fclose(fp);
}

void saveInstructions(PRESTAURANTNODE list, char* filename)
{
	FILE* fp;
	errno_t fileError = fopen_s(&fp, filename, "w");

	if (fp == NULL)
	{
		fprintf(stderr, "File - %s failed to open, exiting\n", filename);
		exit(EXIT_FAILURE);

	}

	while (list->restaurant.instructionQueueHead->head != NULL)
	{
		// print the instructions to the text file
		fprintf(fp, "%s\n", list->restaurant.instructionQueueHead->head->instruction);

		// set the head to the next
		list->restaurant.instructionQueueHead->head = list->restaurant.instructionQueueHead->head->nextNode;
	}

	fclose(fp);
}