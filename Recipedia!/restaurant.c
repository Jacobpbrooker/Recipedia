
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "restaurant.h"
#include "queue.h"
//#include "SaveLoad.h"

#define NUMBEROFDOCUMENTSTOOPEN 3
#define FILENAMELENGTH 100
#define INGREDIENTQUEUEFILE "ingredientList.txt"
#define INSTRUCTIONQUEUEFILE "instructionList.txt"
#define MAXINPUT 150
#define MAXMENUITEM 100

PRESTAURANT returnRestaurant(char* fileControlDoc) // there is so many magic numbers here
{
	FILE* fpControlDoc;
	errno_t errControl = fopen_s(&fpControlDoc, fileControlDoc, "r");

	if (fpControlDoc == NULL)
	{
		fprintf(stderr, "(return Restaurant) File - (%s) failed to open, exiting\n", fileControlDoc);
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
		fprintf(stderr, "(return Restaurant2) File - (%s) failed to open, exiting\n", filePathRestaurantInformation);
		exit(EXIT_FAILURE);
	}
	
	FILE* fpIngredientDoc;
	errno_t errIngr = fopen_s(&fpIngredientDoc, filePathIngredients, "r");				// reads text file and loads file path of ingredients information to array

	if (fpIngredientDoc == NULL)
	{
		fprintf(stderr, "(return Restaurant3) File - (%s) failed to open, exiting\n", filePathIngredients);
		exit(EXIT_FAILURE);
	}
	
	FILE* fpInstructionDoc;
	errno_t errInstr = fopen_s(&fpInstructionDoc, filePathInstructions, "r");				// reads text file and loads file path of ingredients information to array
	if (fpInstructionDoc == NULL)
	{
		fprintf(stderr, " (return Restaurant3) File - (%s) failed to open, exiting\n", filePathInstructions);
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

	// Push restaurant to linked list
	push(&restaurantListPointer, *tempRestaurant);

	return restaurantListPointer;
}

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

PRESTAURANT returnNewRestaurant(void)
{
	PRESTAURANT newRestaurant = (PRESTAURANT)malloc(sizeof(RESTAURANT));
	if (!newRestaurant)
		exit(EXIT_FAILURE);

	newRestaurant->restaurantName = (char*)malloc(sizeof(char) * MAXINPUT);
	newRestaurant->headChef = (char*)malloc(sizeof(char) * MAXINPUT);
	newRestaurant->restaurantSypnopsis = (char*)malloc(sizeof(char) * MAXINPUT);

	char name[MAXINPUT];
	char chef[MAXINPUT];
	char sypnopsis[MAXINPUT];
	char one[MAXINPUT];
	char two[MAXINPUT];
	char three[MAXINPUT];
	char test[50];
	fgets(test, 50, stdin);

	printf("Please enter restaurant name - ");
	fgets(name, MAXINPUT, stdin);

	printf("Please enter chef name - ");
	fgets(chef, MAXINPUT, stdin);

	printf("Please enter restaurant sypnopsis - ");
	fgets(sypnopsis, MAXINPUT, stdin);

	printf("Please enter first menu item - ");
	fgets(one, MAXINPUT, stdin);

	printf("Please enter second menu item - ");
	fgets(two, MAXINPUT, stdin);

	printf("Please enter third menu item - ");
	fgets(three, MAXINPUT, stdin);

	for (unsigned int i = 0; i < strlen(name); i++)
	{
		if (name[i] == '\n')
		{
			name[i] = '\0';
		}
	}
	for (unsigned int i = 0; i < strlen(chef); i++)
	{
		if (chef[i] == '\n')
		{
			chef[i] = '\0';
		}
	}
	for (unsigned int i = 0; i < strlen(sypnopsis); i++)
	{
		if (sypnopsis[i] == '\n')
		{
			sypnopsis[i] = '\0';
		}
	}
	for (unsigned int i = 0; i < strlen(one); i++)
	{
		if (one[i] == '\n')
		{
			one[i] = '\0';
		}
	}
	for (unsigned int i = 0; i < strlen(two); i++)
	{
		if (two[i] == '\n')
		{
			two[i] = '\0';
		}
	}
	for (unsigned int i = 0; i < strlen(three); i++)
	{
		if (three[i] == '\n')
		{
			three[i] = '\0';
		}
	}

	strcpy_s(newRestaurant->restaurantName, MAXINPUT, name);
	strcpy_s(newRestaurant->headChef, MAXINPUT, chef);
	strcpy_s(newRestaurant->restaurantSypnopsis, MAXINPUT, sypnopsis);
	strcpy_s(newRestaurant->specialityMenu[0], MAXMENUITEM, one);
	strcpy_s(newRestaurant->specialityMenu[1], MAXMENUITEM, two);
	strcpy_s(newRestaurant->specialityMenu[2], MAXMENUITEM, three);

	newRestaurant->ingredientQueueHead = initializeIngredientQueue();
	newRestaurant->instructionQueueHead = initalizeInstructionQueue();

	return newRestaurant;
}

// free functions (worry about after)
void freeRestaurantList(PRESTAURANTNODE list)
{
	if (list == NULL)
		return;
	else
		freeRestaurantList(list->nextNode);

	freeNode(list);	// free on the return 
}

void freeNode(PRESTAURANTNODE list)
{
	free(list->restaurant.ingredientQueueHead);
	free(list->restaurant.instructionQueueHead);
	free(list);
}