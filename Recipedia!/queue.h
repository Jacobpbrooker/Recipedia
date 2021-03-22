#pragma once

#define MAXSTRINGLENGTH 100
#define MAXINSTRUCTIONLENGTH 1000
#define MENUSIZE 3
#define MAXRECIPEINGRDIENT 15

typedef struct ingredient {								// ingredient will be stored individually in a linked list 
	char ingredient[MAXSTRINGLENGTH];					// the name of the ingredient (i.e. salt, pepper, chicken breast etc.)
	float measurement;									// number of below (i.e 1 cup, 0.5 kg etc.) - needs to be able to have a decimal place
	char unitOfMeasurement[MAXSTRINGLENGTH];			// cup, gram, kg, pound etc.
	struct ingredient* nextNode;						// pointer to next ingredient node
}INGREDIENT, * PINGREDIENT;

typedef struct ingredientQueue {
	struct ingredient* head;
	struct ingredient* tail;
}INGREDIENTQUEUE, * PINGREDIENTQUEUE;

typedef struct instruction {							// instrucions will be stored individually in a linked list
	char instruction[MAXINSTRUCTIONLENGTH];				// simple text instruction for that specific step in the recipe
	struct instruction* nextNode;						// pointer to next ingredient node 
}INSTRUCTION, * PINSTRUCTION;

typedef struct instructionQueue {
	struct instruction* head;
	struct instruction* tail;
} INSTRUCTIONQUEUE, * PINSTRUCTIONQUEUE;

// create
PINGREDIENT createIngredient(char*, float, char*);
PINSTRUCTION createInstruction(char*);

// create the queues loaded from file and return the queue to be saved in restaurant
PINGREDIENTQUEUE loadIngredientQueue(char*);
PINSTRUCTIONQUEUE loadInstructionQueue(char*);

// free functions (worry about after)
void freeNode(PRESTAURANTNODE);
void freeIngredientQueue(PINGREDIENTQUEUE);
void freeIngredient(PINGREDIENT);
void freeInstructionQueue(PINSTRUCTIONQUEUE);
void freeInstruction(PINSTRUCTION);

//queue functions
PINGREDIENTQUEUE initializeIngredientQueue();
PINSTRUCTIONQUEUE initalizeInstructionQueue();
bool enqueueIngredient(PINGREDIENTQUEUE, PINGREDIENT);
bool enqueueInstruction(PINSTRUCTIONQUEUE, PINSTRUCTION);
void dequeueIngredient(PINGREDIENTQUEUE);
void dequeueInstruction(PINSTRUCTIONQUEUE);
