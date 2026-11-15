#include "pch.h"
#include "CppUnitTest.h"
#include "Student.h"
#include "Helper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ElearningNativeTest
{
	TEST_CLASS(ElearningNativeTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(5, 2+3);
			Assert::AreEqual(5, 3+3);
			Assert::AreEqual(5, 1+4);
			Assert::AreEqual(5, 4+1);
		}

		TEST_METHOD(CheckStudent)
		{
			Student student("Maria", "Daria", "maria.daria@student.unitbv.ro",
				"Str. Lunga nr 5", "0771123456", "123A", 3);

			// teste pe atribute
			// ex: sa nu fie goale / invalide
			Assert::IsTrue(student.getFirstName() != "");
			Assert::IsTrue(student.getLastName() != "");
			Assert::IsTrue(student.getPhone().size() == 10);

			// ex: criteriile de business
			Assert::IsTrue(student.getStudyYear() >= 1 && student.getStudyYear() <= 3);
			Assert::IsTrue(student.getEmail().find("@student.unitbv.ro") != std::string::npos);
		}

		TEST_METHOD(MaxInVector)
		{
			std::vector<double> vector = { 27.5, 13.8, 7.9, 1.3, -6.7 };
			double actual = calculateMaxInVector(vector);
			double expected = 27.5;
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(MaxInNegativeVector)
		{
			std::vector<double> vector = { -27.5, -13.8, -7.9, -1.3, -6.7 };
			double actual = calculateMaxInVector(vector);
			double expected = -1.3;
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(MaxInEmptyVector)
		{
			std::vector<double> vector = {};
			try {
				calculateMaxInVector(vector);
			}
			catch (const std::invalid_argument& e)
			{
				Assert::IsTrue((std::string)e.what() == "Empty vector!");
			}
		}
	};
}
