#include "pch.h"
#include "CppUnitTest.h"
#include "../lab 10.2 A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student students[3] = {
				{"Ivanov", 2, IT, 5, 5, 5},
				{"Petrenko", 1, CS, 5, 5, 4},
				{"Sydorenko", 3, ME, 4, 4, 4}
			};

			// Сортування масиву студентів
			Sort(students, 3);

			// Перевірка правильного порядку після сортування
			Assert::AreEqual(std::string("Petrenko"), students[0].lname);
			Assert::AreEqual(std::string("Ivanov"), students[1].lname);
			Assert::AreEqual(std::string("Sydorenko"), students[2].lname);
		}
	};
}
