
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "restaurant.h"
#include "queue.h"
//#include "SaveLoad.h"

#define NUMBEROFDOCUMENTSTOOPEN 3
#define FILENAMELENGTH 50
#define INGREDIENTQUEUEFILE "ingredientList.txt"
#define INSTRUCTIONQUEUEFILE "instructionList.txt"

PRESTAURANT returnRestaurant(char* fileControlDoc) // there is so many magic numbers here
{
	FILE* fpControlDoc;
	errno_t errControl = fopen_s(&fpControlDoc, fileControlDoc, "r");

	if (fpControlDoc == NULL)
	{
		fprintf(stderr, "File - (%s) failed to open, exiting\n", fileControlDoc);
		exit(EXIT_FAILURE);
	}

	char filePathRestaurantInformation[FILENAMELENGTH] = { '\0' };
	char filePathIngredients[FILENAMELENGTH] = { '\0' };
	char filePathInstructions[FILENAMELENGTH] = { '\0' };

	fgets(filePathRestaurantInformation, FILENAMELENGTH, fpControlDoc);
	fgets(filePathIngredients, FILENAMELENGTH, fpControlDoc);
	fgets(filePathInstructions, FILENAMELENGTH, fpControlDoc);

	for (unsigned int i = 0; i < strlen(filePathRestaurantInformation); i++)
	{
		if (filePathRestaurantInformation[i] == '\n')
		{
			filePathRestaurantInformation[i] = '\0';
		}
	}

	for (unsigned int i = 0; i < strlen(filePathIngredients); i++)
	{
		if (filePathIngredients[i] == '\n')
		{
			filePathIngredients[i] = '\0';
		}
	}

	for (unsigned int i = 0; i < strlen(filePathInstructions); i++)
	{
		if (filePathInstructions[i] == '\n')
		{
			filePathInstructions[i] = '\0';
		}
	}

	fclose(fpControlDoc);

	FILE* fpRestaurantDoc;
	errno_t errRest = fopen_s(&fpRestaurantDoc, filePathRestaurantInformation, "r");				// reads text file and loads file path of restaurant information to array
	if (fpRestaurantDoc == NULL)
	{
		fprintf(stderr, "File - (%s) failed to open, exiting\n", filePathRestaurantInformation);
		exit(EXIT_FAILURE);
	}
	
	FILE* fpIngredientDoc;
	errno_t errIngr = fopen_s(&fpIngredientDoc, filePathIngredients, "r");				// reads text file and loads file path of ingredients information to array

	if (fpIngredientDoc == NULL)
	{
		fprintf(stderr, "File - (%s) failed to open, exiting\n", filePathIngredients);
		exit(EXIT_FAILURE);
	}
	
	FILE* fpInstructionDoc;
	errno_t errInstr = fopen_s(&fpInstructionDoc, filePathInstructions, "r");				// reads text file and loads file path of ingredients information to array
	if (fpInstructionDoc == NULL)
	{
		fprintf(stderr, "File - (%s) failed to open, exiting\n", filePathInstructions);
		exit(EXIT_FAILURE);
	}


	PRESTAURANT returnRestaurant = (PRESTAURANT)malloc(sizeof(RESTAURANT));
	
	char* restaurantName = (char*)malloc(MAXSTRINGLENGTH);		
	memset(restaurantName, '\0', MAXSTRINGLENGTH);
	char* headChef = (char*)malloc(MAXSTRINGLENGTH);
	memset(headChef, '\0', MAXSTRINGLENGTH);
	char* sypnopsis = (char*)malloc(MAXSTRINGLENGTH);
	memset(sypnopsis, '\0', MAXSTRINGLENGTH);
	char* firstSpeciality = (char*)malloc(MAXSTRINGLENGTH);
	memset(firstSpeciality, '\0', MAXSTRINGLENGTH);
	char* secondSpeciality = (char*)malloc(MAXSTRINGLENGTH);
	memset(secondSpeciality, '\0', MAXSTRINGLENGTH);
	char* thirdSpeciality = (char*)malloc(MAXSTRINGLENGTH);
	memset(thirdSpeciality, '\0', MAXSTRINGLENGTH);

	fgets(restaurantName, MAXSTRINGLENGTH, fpRestaurantDoc);
	fgets(headChef, MAXSTRINGLENGTH, fpRestaurantDoc);
	fgets(sypnopsis, MAXSTRINGLENGTH, fpRestaurantDoc);
	fgets(firstSpeciality, MAXSTRINGLENGTH, fpRestaurantDoc);
	fgets(secondSpeciality, MAXSTRINGLENGTH, fpRestaurantDoc);
	fgets(thirdSpeciality, MAXSTRINGLENGTH, fpRestaurantDoc);

	// this will add the terminator to each of the char strings added
	for (unsigned int i = 0; i < strlen(restaurantName); i++)
	{
		if (restaurantName[i] == '\n')
		{
			restaurantName[i] = '\0';
		}
	}
	for (unsigned int i = 0; i < strlen(headChef); i++)
	{
		if (headChef[i] == '\n')
		{
			headChef[i] = '\0';
		}
	}
	for (unsigned int i = 0; i < strlen(sypnopsis); i++)
	{
		if (sypnopsis[i] == '\n')
		{
			sypnopsis[i] = '\0';
		}
	}
	for (unsigned int i = 0; i < strlen(firstSpeciality); i++)
	{
		if (firstSpeciality[i] == '\n')
		{
			firstSpeciality[i] = '\0';
		}
	}
	for (unsigned int i = 0; i < strlen(secondSpeciality); i++)
	{
		if (secondSpeciality[i] == '\n')
		{
			secondSpeciality[i] = '\0';
		}
	}
	for (unsigned int i = 0; i < strlen(thirdSpeciality); i++)
	{
		if (thirdSpeciality[i] == '\n')
		{
			thirdSpeciality[i] = '\0';
		}
	}

	// this is broken
	returnRestaurant->restaurantName = restaurantName;
	returnRestaurant->headChef = headChef;
	returnRestaurant->restaurantSypnopsis = sypnopsis;
	strcpy_s(&returnRestaurant->specialityMenu[0], MAXSTRINGLENGTH, firstSpeciality);
	strcpy_s(&returnRestaurant->specialityMenu[1], MAXSTRINGLENGTH, secondSpeciality);
	strcpy_s(&returnRestaurant->specialityMenu[2], MAXSTRINGLENGTH, thirdSpeciality);
	
	returnRestaurant->ingredientQueueHead = loadIngredientQueue(&filePathIngredients);
	returnRestaurant->instructionQueueHead = loadInstructionQueue(&filePathInstructions);


	fclose(fpControlDoc);
	fclose(fpRestaurantDoc);
	fclose(fpIngredientDoc);
	fclose(fpInstructionDoc);

	return returnRestaurant;
}


PRESTAURANTNODE createRestaurant(PRESTAURANTNODE restaurantListPointer, PRESTAURANT restaurant)
{
	PRESTAURANT tempRestaurant = (PRESTAURANT)malloc(sizeof(RESTAURANT));

	if (!tempRestaurant) {										// If memory was unsuccessfully allocated 
		printf("Error found in memory allocation\n");
		exit(EXIT_FAILURE);												// exit with code -1
	}

	//tempRestaurant = restaurant;
	tempRestaurant->restaurantName = restaurant->restaurantName;
	tempRestaurant->headChef = restaurant->headChef;
	tempRestaurant->restaurantSypnopsis = restaurant->restaurantSypnopsis;
	// Put everything into a new, temporary struct

	strcpy_s(tempRestaurant->specialityMenu[0], MAXSTRINGLENGTH, restaurant->specialityMenu[0]);
	strcpy_s(tempRestaurant->specialityMenu[1], MAXSTRINGLENGTH, restaurant->specialityMenu[1]);
	strcpy_s(tempRestaurant->specialityMenu[2], MAXSTRINGLENGTH, restaurant->specialityMenu[2]);
	tempRestaurant->ingredientQueueHead = restaurant->ingredientQueueHead;
	tempRestaurant->instructionQueueHead = restaurant->instructionQueueHead;


	//tempRestaurant->ingredientQueueHead = loadIngredientQueue(INGREDIENTQUEUEFILE);
	//tempRestaurant->instructionQueueHead = loadInstructionQueue(INSTRUCTIONQUEUEFILE);

	// Push task to linked list
	// I think this push function is pushing to the head of the list instead of the back
	// I can probably fix it by search for the end of the linked list and then passing that into the function
	push(&restaurantListPointer, *tempRestaurant);

	return restaurantListPointer;
}


//PRESTAURANTNODE createRestaurant(PRESTAURANTNODE restaurantListPointer, char* restaurantName, char* headChef, char* sypnopsis, char* firstSpecialty, char* secondSpecialty, char* thirdSpeciality) 
//{
//	PRESTAURANT tempRestaurant = (PRESTAURANT)malloc(sizeof(RESTAURANT));
//
//	if (!tempRestaurant) {										// If memory was unsuccessfully allocated 
//		printf("Error found in memory allocation\n");
//		exit(EXIT_FAILURE);												// exit with code -1
//	}
//
//	// Put everything into a new, temporary struct
//	tempRestaurant->resturantName = restaurantName;
//	tempRestaurant->headChef = headChef;
//	tempRestaurant->restaurantSypnopsis = sypnopsis;
//	
//	strcpy_s(tempRestaurant->specialityMenu[0], MAXSTRINGLENGTH, firstSpecialty);
//	strcpy_s(tempRestaurant->specialityMenu[1], MAXSTRINGLENGTH, secondSpecialty);
//	strcpy_s(tempRestaurant->specialityMenu[2], MAXSTRINGLENGTH, thirdSpeciality);
//
//	tempRestaurant->ingredientQueueHead = loadIngredientQueue(INGREDIENTQUEUEFILE);
//	tempRestaurant->instructionQueueHead = loadInstructionQueue(INSTRUCTIONQUEUEFILE);
//
//	// Push task to linked list
//	// I think this push function is pushing to the head of the list instead of the back
//	// I can probably fix it by search for the end of the linked list and then passing that into the function
//	push(&restaurantListPointer, *tempRestaurant);
//
//	return restaurantListPointer;
//}

void push(PRESTAURANTNODE* PassedData, RESTAURANT NewTask) {
	PRESTAURANTNODE taskNode = newNode(NewTask);
	taskNode->nextNode = *PassedData;
	*PassedData = taskNode;
}

PRESTAURANTNODE newNode(RESTAURANT NewTask) {
	PRESTAURANTNODE newTaskNode = (PRESTAURANTNODE)malloc(sizeof(RESTAURANTNODE));

	if (!newTaskNode) {
		printf("Error in memory allocation\n");
		exit(EXIT_FAILURE);
	}

	newTaskNode->restaurant = NewTask;
	newTaskNode->nextNode = NULL;

	return newTaskNode;
}

PRESTAURANTNODE fetchNextNode(PRESTAURANTNODE restaurantNode)
{
	return restaurantNode->nextNode;
}


