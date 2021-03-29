#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "admin.h"
#include "queue.h"
#include "restaurant.h"
#include "SaveLoad.h"
}

#define TESTDIRECTORY "../RecipediaSaveLoad.tests/restaurants/toptenrestaurants.txt"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RecipediaSaveLoadtests
{
	TEST_CLASS(adminFunctions)
	{
	public:
		TEST_METHOD(T01_adminMode_returnAdminConfirmation_Return1)
		{
			// arrange
			unsigned char x[9] = "10011001";
			int y = 8;
			int expectedReturn = 1;
			// act
			int testReturn = returnAdminConfirmation(x, y);
			// assert
			Assert::AreEqual(testReturn, expectedReturn);
		}
	};
	TEST_CLASS(queueFunctions)
	{
	public:
		TEST_METHOD(T01_queue_enqueueIngredient_Return1)
		{
			// arrange
			PINGREDIENTQUEUE ingredientQueue = initializeIngredientQueue();
			
			FILE* fp;
			errno_t fileError = fopen_s(&fp, "../RecipediaSaveLoad.tests/restaurants/noma/nomaingredients.txt", "r");

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

			int expectedReturn = 1;
			// act
			int testReturn = enqueueIngredient(ingredientQueue, createIngredient(ingredient, measurement, unitOfMeasurement));
			// assert
			Assert::AreEqual(testReturn, expectedReturn);
		}
		TEST_METHOD(T02_queue_enqueueInstruction_Return1)
		{
			//// arrange
			PINSTRUCTIONQUEUE instructionQueue = initalizeInstructionQueue();

			FILE* fp;
			errno_t fileError = fopen_s(&fp, "../RecipediaSaveLoad.tests/restaurants/noma/nomainstructions.txt", "r");

			if (fp == NULL)
			{
				fprintf(stderr, "Failed to open file %s", "../RecipediaSaveLoad.tests/restaurants/noma/nomainstructions.txt");
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

			int expectedReturn = 1;
			
			// act
			int testReturn = enqueueInstruction(instructionQueue, createInstruction(instruction));
			fclose(fp);
			
			// assert
			Assert::AreEqual(testReturn, expectedReturn);
		}
	};
	TEST_CLASS(SaveLoadFunctions)
	{
	public:
		TEST_METHOD(T01_saveLoad_saveFile_Return1)
		{
			// arrange
			PRESTAURANTNODE x = loadRestaurants(TESTDIRECTORY);
			int expectedReturn = 1;
			// act
			int testReturn = saveFile(x, TESTDIRECTORY);;
			// assert
			Assert::AreEqual(testReturn, expectedReturn);
		}
	};
}
