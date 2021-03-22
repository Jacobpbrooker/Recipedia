
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "queue.h"

#define INGREDIENTQUEUEFILE "ingredientList.txt"
#define INSTRUCTIONQUEUEFILE "instructionList.txt"
#define INGREDIENTLINES 3

// free functions (worry about after)
//void freeNode(PRESTAURANTNODE);
void freeIngredientQueue(PINGREDIENTQUEUE queue) // this gets called last right before next loop of save
{
	free(queue);
}

void freeIngredient(PINGREDIENT ingredient) // this should get called while i loop the save
{
	free(ingredient);
}

void freeInstructionQueue(PINSTRUCTIONQUEUE queue)
{
	free(queue);
}

void freeInstruction(PINSTRUCTION instruction)
{
	free(instruction);
}

//void freeQueue(PQUEUE queue)
//{
//	free(queue);											// free the queue
//}
//
//void freeNode(PNODE node)
//{
//	freePatient(node->patientData);							// dive deeper and free the patient
//	free(node);												// free the node
//}
//
//void freePatient(PPATIENT patient)
//{
//
//	free(patient);											// free patient
//}

// create 

PINGREDIENT createIngredient(char* ingredient, float measurement, char* unitOfMeasurement)
{
	PINGREDIENT node;												// create node pointer

	if (!(node = (PINGREDIENT)malloc(sizeof(INGREDIENT))))				// malloc the size of node at the pointer to node location
	{
		fprintf(stderr, "Failed to allocate memory for queue - Now Exiting\n");
		exit(EXIT_FAILURE);
	}

	memset(node, '\0', sizeof(INGREDIENT));						// set the malloc(ed?) memory to '\0'

	strcpy_s(node->ingredient, MAXSTRINGLENGTH, ingredient);
	strcpy_s(node->unitOfMeasurement, MAXSTRINGLENGTH, unitOfMeasurement);
	node->measurement = measurement;
															// create the patient and assign to the patient data within the node
															// node->pNext intentially left unassigned to be assigned in enqueue function
	return node;
}

PINSTRUCTION createInstruction(char* instruction)
{
	PINSTRUCTION node;												// create node pointer

	if (!(node = (PINSTRUCTION)malloc(sizeof(INSTRUCTION))))				// malloc the size of node at the pointer to node location
	{
		fprintf(stderr, "Failed to allocate memory for queue - Now Exiting\n");
		exit(EXIT_FAILURE);
	}

	memset(node, '\0', sizeof(INSTRUCTION));						// set the malloc(ed?) memory to '\0'

	strcpy_s(node->instruction, MAXINSTRUCTIONLENGTH, instruction);

	return node;
}

// Queue Functions

PINGREDIENTQUEUE initializeIngredientQueue()
{
	PINGREDIENTQUEUE queue;											// create pointer to a queue variable

	if (!(queue = (PINGREDIENTQUEUE)malloc(sizeof(INGREDIENTQUEUE))))			// malloc the queue size of queue
	{
		fprintf(stderr, "Failed to allocate memory for queue - Now Exiting\n");
		exit(EXIT_FAILURE);
	}

	memset(queue, '\0', sizeof(INGREDIENTQUEUE));						// set memory at queue pointer to '\0'

	return queue;
}

PINGREDIENTQUEUE initalizeIngredientQueue()
{
	PINGREDIENTQUEUE queue;											// create pointer to a queue variable

	if (!(queue = (PINGREDIENTQUEUE)malloc(sizeof(INGREDIENTQUEUE))))			// malloc the queue size of queue
	{
		fprintf(stderr, "Failed to allocate memory for queue - Now Exiting\n");
		exit(EXIT_FAILURE);
	}

	memset(queue, '\0', sizeof(INGREDIENTQUEUE));						// set memory at queue pointer to '\0'

	return queue;
}

PINSTRUCTIONQUEUE initalizeInstructionQueue()
{
	PINSTRUCTIONQUEUE queue;											// create pointer to a queue variable

	if (!(queue = (PINSTRUCTIONQUEUE)malloc(sizeof(INSTRUCTIONQUEUE))))			// malloc the queue size of queue
	{
		fprintf(stderr, "Failed to allocate memory for queue - Now Exiting\n");
		exit(EXIT_FAILURE);
	}

	memset(queue, '\0', sizeof(INSTRUCTIONQUEUE));						// set memory at queue pointer to '\0'

	return queue;
}

// create the queues to be loaded
PINGREDIENTQUEUE loadIngredientQueue(char* queueFile)
{
	PINGREDIENTQUEUE ingredientQueue = initializeIngredientQueue();

	//FILE* fp = fopen(queueFile, "r");		// Attempts to find a file with the correct name in the same directory
	//if (fp == NULL)
	//{
	//	fprintf(stderr, "Failed to open file %s", INGREDIENTQUEUEFILE);
	//	exit(EXIT_FAILURE);
	//}

	FILE* fp;
	errno_t fileError = fopen_s(&fp, queueFile, "r");

	if (fp == NULL)
	{
		fprintf(stderr, "Failed to open file %s", INGREDIENTQUEUEFILE);
		exit(EXIT_FAILURE);

	}

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
	for (int i = lines / INGREDIENTLINES; i > 0; i--) // get the number of lines (every 3 lines will be one ingredient)
	{
		char* ingredient = (char*)malloc(MAXSTRINGLENGTH);
		memset(ingredient, '\0', sizeof(char) * MAXSTRINGLENGTH);

		char* unitOfMeasurement = (char*)malloc(MAXSTRINGLENGTH);
		memset(unitOfMeasurement, '\0', sizeof(char) * MAXSTRINGLENGTH);

		char* measurementString = (char*)malloc(sizeof(char) * MAXSTRINGLENGTH);
		memset(measurementString, '\0', sizeof(char) * MAXSTRINGLENGTH);

		fgets(ingredient, MAXSTRINGLENGTH, fp);
		float measurement = atof(fgets(measurementString, MAXSTRINGLENGTH, fp));
		fgets(unitOfMeasurement, MAXSTRINGLENGTH, fp);
		

		// this will add the terminator to each of the char strings added
		for (unsigned int i = 0; i < strlen(ingredient); i++)
		{
			if (ingredient[i] == '\n')
			{
				ingredient[i] = '\0';
			}
		}

		for (unsigned int i = 0; i < strlen(unitOfMeasurement); i++)
		{
			if (unitOfMeasurement[i] == '\n')
			{
				unitOfMeasurement[i] = '\0';
			}
		}

		// now i create the ingredient node
		// then i enqueue the ingredient node to the ingredient queue
		if (!enqueueIngredient(ingredientQueue, createIngredient(ingredient, measurement, unitOfMeasurement)))
		{
			fprintf(stderr, "Failed to enqueue function - Now Exiting\n");
			exit(EXIT_FAILURE);
		}

	}

	fclose(fp);

	return ingredientQueue;
}

PINSTRUCTIONQUEUE loadInstructionQueue(char* queueFile)
{
	PINSTRUCTIONQUEUE instructionQueue = initalizeInstructionQueue();

	//FILE* fp = fopen(queueFile, "r");		// Attempts to find a file with the correct name in the same directory
	//if (fp == NULL)
	//{
	//	fprintf(stderr, "Failed to open file %s", INGREDIENTQUEUEFILE);
	//	exit(EXIT_FAILURE);
	//}

	FILE* fp;
	errno_t fileError = fopen_s(&fp, queueFile, "r");

	if (fp == NULL)
	{
		fprintf(stderr, "Failed to open file %s", INSTRUCTIONQUEUEFILE);
		exit(EXIT_FAILURE);

	}

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
	for (int i = 0; i < lines; i++) // get the number of lines (each line will be one instruction)
	{
		char* instruction = (char*)malloc(MAXSTRINGLENGTH);
		memset(instruction, '\0', sizeof(char) * MAXSTRINGLENGTH);

		fgets(instruction, MAXSTRINGLENGTH, fp);

		// this will add the terminator to each of the char strings added
		for (unsigned int i = 0; i < strlen(instruction); i++)
		{
			if (instruction[i] == '\n')
			{
				instruction[i] = '\0';
			}
		}

		// now i create the ingredient node
		// then i enqueue the ingredient node to the ingredient queue
		if (!enqueueInstruction(instructionQueue, createInstruction(instruction)))
		{
			fprintf(stderr, "Failed to enqueue function - Now Exiting\n");
			exit(EXIT_FAILURE);
		}

	}

	fclose(fp);

	return instructionQueue;
}
bool enqueueIngredient(PINGREDIENTQUEUE queue, PINGREDIENT node)
{
	bool returnBool = false;								// set return bool

	if (queue->head == NULL)
	{
		queue->head = node;									// if the head of the queue is null set the head to this node
		queue->tail = node;									// then set the tail to the same location in the queue
		returnBool = true;									// set the return bool to true
	}
	else
	{
		queue->tail->nextNode = node;							// if there is a head in the queue we set the queue tail next to the node
		queue->tail = node;									// set the queue tail to the node
		returnBool = true;									// set the return bool to true
	}

	queue->tail->nextNode = NULL;								// set the queue tail pNext to NULL with each interation  	

	return returnBool;										// return bool
}

bool enqueueInstruction(PINSTRUCTIONQUEUE queue, PINSTRUCTION node)
{
	bool returnBool = false;								// set return bool

	if (queue->head == NULL)
	{
		queue->head = node;									// if the head of the queue is null set the head to this node
		queue->tail = node;									// then set the tail to the same location in the queue
		returnBool = true;									// set the return bool to true
	}
	else
	{
		queue->tail->nextNode = node;							// if there is a head in the queue we set the queue tail next to the node
		queue->tail = node;									// set the queue tail to the node
		returnBool = true;									// set the return bool to true
	}

	queue->tail->nextNode = NULL;								// set the queue tail pNext to NULL with each interation  	
	return returnBool;										// return bool
}
//PINSTRUCTIONQUEUE fillInstructionQueue(PINSTRUCTIONQUEUE queue, char* nameOfTextFile)
//{
//	for (int i = 0; i < numPatients; i++)
//	{
//		if (enqueue(queue, ))				// enqueue the node into the queue passed argument using the createPatientNode() to fill values
//			comparisonInt++;									// if node is enqueue(d?) into queue increment comparisson for return value	
//	}
//}
//
//PINGREDIENTQUEUE fillInstructionQueue(PINGREDIENTQUEUE, char*);
//bool enqueueIngredient(PINGREDIENTQUEUE, PINGREDIENT);
//bool enqueueInstruction(PINSTRUCTIONQUEUE, PINSTRUCTION);
//void dequeueIngredient(PINGREDIENTQUEUE);
//void dequeueInstruction(PINSTRUCTIONQUEUE);
//
//int fillQueue(PQUEUE queue, int numPatients)
//{
//	int comparisonInt = 0;									// int will be used as comparison against number of patients created
//	int returnInt = 1;										// set comparison int to failure to be changed upon success
//
//	for (int i = 0; i < numPatients; i++)
//	{
//		if (enqueue(queue, createPatientNode()))				// enqueue the node into the queue passed argument using the createPatientNode() to fill values
//			comparisonInt++;								// if node is enqueue(d?) into queue increment comparisson for return value	
//	}
//
//	if (comparisonInt == numPatients)						// compare number of patients passed as parameter and number of patients created
//		returnInt = 0;										// if they are the same, return 0
//	else
//		returnInt = 1;										// return 1 if they are not 
//
//	return returnInt;										// return the returnInt
//}
//
//bool enqueue(PQUEUE queue, PNODE node)
//{
//	bool returnBool = false;								// set return bool
//
//	if (queue->head == NULL)
//	{
//		queue->head = node;									// if the head of the queue is null set the head to this node
//		queue->tail = node;									// then set the tail to the same location in the queue
//		returnBool = true;									// set the return bool to true
//	}
//	else
//	{
//		queue->tail->pNext = node;							// if there is a head in the queue we set the queue tail next to the node
//		queue->tail = node;									// set the queue tail to the node
//		returnBool = true;									// set the return bool to true
//	}
//
//	queue->tail->pNext = NULL;								// set the queue tail pNext to NULL with each interation  	
//
//	return returnBool;										// return bool
//}
//
//void dequeue(PQUEUE queue)
//{
//	simpleDisplayPatient(queue->head->patientData);			// dispay the patient
//
//	QUEUE tempQUEUE;										// create a temporary copy of the queue
//
//	tempQUEUE.head = queue->head->pNext;					// assign the head of temporary queue to the pNext of queue head
//	freeNode(queue->head);									// free the node
//	queue->head = tempQUEUE.head;							// set the head of the queue to the head of the temporary queue
//}