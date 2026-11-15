#include "pch.h"
#include "Student.h"
#include "Helper.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(false);
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(false);
}

TEST(TestCaseName, CheckStudent)
{
	Student student("Ion", "Popescu", "ion.popescu@student.unitbv.ro",
		"Str. Lunga nr 5", "0771123456", "123A", 3);
	EXPECT_TRUE(student.getFirstName() != "");
	EXPECT_TRUE(student.getLastName() != "");
	EXPECT_TRUE(student.getPhone().size() == 10);
	EXPECT_TRUE(student.getEmail().find("@student.unitbv.ro")!=std::string::npos);
}

TEST(TestCaseName, AverageVector)
{
	std::vector<double> vector = { 1,2,3,4,5 };
	double actual = calculateAverageInVector(vector);
	double expected = 3;
	EXPECT_EQ(expected, actual);
}

TEST(TestCaseName, AverageEmptyVector)
{
	std::vector<double> vector = {};
	try {
		calculateAverageInVector(vector);
	}
	catch (const std::invalid_argument& e)
	{
		EXPECT_TRUE((std::string)e.what() == "Empty vector!");
	}
}