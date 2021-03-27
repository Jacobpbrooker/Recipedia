#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "search.h"
#include "SaveLoad.h"
#include "restaurant.h"
#include "queue.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RecipediaTests
{
	TEST_CLASS(SearchTests)
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
	};
}
