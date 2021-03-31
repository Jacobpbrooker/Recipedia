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
		fgets(restaurantFiles[i], MAXSTRINGLENGTH, fp);

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
	
	// i need to find the \0 and replace with \n (only the first one)
	// this is literally the jankiest thing I have ever written

	int i = 0;
	while (list->restaurant.restaurantName[i] != '\0')
		i++;
	list->restaurant.restaurantName[i] = '\n';

	i = 0;
	while (list->restaurant.headChef[i] != '\0')
		i++;
	list->restaurant.headChef[i] = '\n';

	i = 0;
	while (list->restaurant.restaurantSypnopsis[i] != '\0')
		i++;
	list->restaurant.restaurantSypnopsis[i] = '\n';

	i = 0;
	while (list->restaurant.specialityMenu[0][i] != '\0')
		i++;
	list->restaurant.specialityMenu[0][i] = '\n';
	list->restaurant.specialityMenu[0][++i] = '\0';

	i = 0;
	while (list->restaurant.specialityMenu[1][i] != '\0')
		i++;
	list->restaurant.specialityMenu[1][i] = '\n';
	list->restaurant.specialityMenu[1][++i] = '\0';

	i = 0;
	while (list->restaurant.specialityMenu[2][i] != '\0')
		i++;
	list->restaurant.specialityMenu[2][i] = '\n';
	list->restaurant.specialityMenu[2][++i] = '\0';

	// write the restaurant information to txt file 
	fputs(list->restaurant.restaurantName, fp);
	fputs(list->restaurant.headChef, fp);
	fputs(list->restaurant.restaurantSypnopsis, fp);
	fputs(list->restaurant.specialityMenu[0], fp);
	fputs(list->restaurant.specialityMenu[1], fp);
	fputs(list->restaurant.specialityMenu[2], fp);
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