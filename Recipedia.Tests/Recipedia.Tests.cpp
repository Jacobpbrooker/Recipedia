#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "search.h"
#include "queue.h"
#include "restaurant.h"
#include "SaveLoad.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RecipediaTests
{
	TEST_CLASS(SearchNumTests)
	{
	public:
		
		TEST_METHOD(T001_Five)
		{
			//Arrange
			int input = 5;
			char* expected = "centraltestname3";
			PRESTAURANTNODE	list = testLoad("restaurants/toptenrestaurants.txt");

			//Act
			PRESTAURANTNODE p = searchNum(list, input);

			//Assert
			Assert::AreEqual(expected, p->restaurant.restaurantName);
		}

		TEST_METHOD(T002_One)
		{
			//Arrange
			int input = 1;
			char* expected = "maidotestname3";
			PRESTAURANTNODE	list = testLoad("restaurants/toptenrestaurants.txt");

			//Act
			PRESTAURANTNODE p = searchNum(list, input);

			//Assert
			Assert::AreEqual(expected, p->restaurant.restaurantName);
		}

		TEST_METHOD(T003_Ten)
		{
			//Arrange
			int input = 1;
			char* expected = "mirazurtestname3";
			PRESTAURANTNODE	list = testLoad("restaurants/toptenrestaurants.txt");

			//Act
			PRESTAURANTNODE p = searchNum(list, input);

			//Assert
			Assert::AreEqual(expected, p->restaurant.restaurantName);
		}
	};


}
