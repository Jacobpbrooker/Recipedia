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
	TEST_CLASS(restaurantFunctions)
	{
	public:
		TEST_METHOD(T01_restaurant_returnAdminConfirmation_Return1)
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
	TEST_CLASS(SaveLoadFunctions)
	{
	public:
		TEST_METHOD(T01_saveFile_Return1)
		{
			// arrange
			// open notepad++ and edit every single link to be the full file path as done above
			//PRESTAURANTNODE X = (PRESTAURANTNODE)malloc(sizeof(RESTAURANTNODE));
			PRESTAURANTNODE x = loadRestaurants(TESTDIRECTORY);
			int expectedReturn = 1;
			// act
			int testReturn = saveFile(x, TESTDIRECTORY);;
			// assert
			Assert::AreEqual(testReturn, expectedReturn);
		}
	};
}
