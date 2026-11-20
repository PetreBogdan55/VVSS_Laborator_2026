#include "pch.h"
#include "MockStudentRepository.h"

// ⚠️ Este recomandat ca testele de mocking sa fie facute
// in special pentru date care necesita conexiune reala, dar
// care returneaza valori ==> in mod special pentru GET-uri.

TEST(MockTests, GetStudentById)
{
	MockStudentRepository mock;
	int id = 5;
	Student student("Ion", "Popescu", "ion.popescu@unitbv.ro", "", "", "", 3, id);

	// Test 1 ---> Ne asteptam ca metoda testata sa fie apela de un nr de ori
	// EXPECT_CALL(mock-ul, functia marcata ca si mocking)
	// Vrem un return specific putem sa folosim:
	// WillOnce -- o singura data
	// WillRepeatedly -- pt mai multe ori
	// testing::Return(obiectul returnat)
	EXPECT_CALL(mock, getStudentByID(id)).WillOnce(testing::Return(student));
	auto actual = mock.getStudentByID(id);

	// Test 2 --> Ne asteptam ca datele returnate sa fie cele specificate
	// de noi, pe care le putem testa separat
	EXPECT_TRUE(actual.value().getFirstName() == "Ion");
}

TEST(MockTests, GetStudentByIdFiveTimes)
{
	MockStudentRepository mock;
	int id = 5;
	Student student("Ion", "Popescu", "ion.popescu@unitbv.ro", "", "", "", 3, id);
	// Controlul exact de nr de apuluri se face cu functia de Times(numar)
	EXPECT_CALL(mock, getStudentByID(id)).Times(5).WillRepeatedly(testing::Return(student));
	mock.getStudentByID(id);
	mock.getStudentByID(id);
	mock.getStudentByID(id);
	mock.getStudentByID(id);
	mock.getStudentByID(id);
}

TEST(MockTests, GetAllStudents)
{
	MockStudentRepository mock;
	std::vector<Student> students;
	Student student("Ion", "Popescu", "ion.popescu@unitbv.ro", "", "", "", 3);
	students.push_back(student);
	students.push_back(student);
	students.push_back(student);
	EXPECT_CALL(mock, getAllStudents()).WillOnce(testing::Return(students));
	auto actual = mock.getAllStudents().value();
	EXPECT_TRUE(actual.size() == 3);
	//EXPECT_TRUE(actual[0] == student); // daca luam fiecare atribut
}

// Optional - Pentru testele de mocking care nu returneaza niciun tip de date
TEST(MockTests, DeleteStudent)
{
	MockStudentRepository mock;
	int id = 5;
	EXPECT_CALL(mock, deleteStudent(id)).WillOnce(testing::Return());
	mock.deleteStudent(id);
}

// * - extra pt fortarea unui parametru parametru neconstat
// In momentul in care dam ca parametru un obiect, o sa folosim o functie lambda
// unde setam toate atributele si ne asiguram ca toate coincid == testing::Truly
TEST(MockTest, AddStudent)
{
	MockStudentRepository mock;
	Student student("Ion", "Popescu", "ion.popescu@unitbv.ro", "", "", "", 3);
	EXPECT_CALL(mock, addStudent(testing::Truly(
		[](const Student& student) {
			return student.getFirstName() == "Ion" &&
				student.getLastName() == "Popescu"; // la fel si pt celelalte
		}
	)));
	mock.addStudent(student);
}