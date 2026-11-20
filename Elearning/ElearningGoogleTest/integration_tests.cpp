#include "Database.h"
#include "StudentRepository.h"
#include "Environment.h"
#include "pch.h"

// Ce inseamna test de integritate?
// Def: avem o conexiunea activa la un serviciul real
// Ex: Baza de date, API Extern, Serviciu de autentificare, ...

TEST(IntegrationTests, CheckDatabaseConnection)
{
	auto connection = Environment::getInstance()->getValue("ceva");
	Database database(connection);
	bool actual = database.getIsConnected();
	bool expected = true;
	EXPECT_EQ(expected, actual);
}

// ⚠️ Se va executa o singura data!
TEST(IntegrationTests, DeleteStudent)
{
	auto connection = Environment::getInstance()->getValue("ceva");
	Database database(connection);
	StudentRepository repo(database);
	// 1. Luam nr de studenti de dinainte de stergere
	int nrInitial = repo.getAllStudents().value().size();
	// 2. Apelam delete-ul
	repo.deleteStudent(5);
	// 3. Luam nr de studenti de dupa stergere
	int nrFinal = repo.getAllStudents().value().size();
	EXPECT_EQ(nrFinal, nrInitial - 1);
}

TEST(IntegrationTests, AddStudent)
{
	auto connection = Environment::getInstance()->getValue("ceva");
	Database database(connection);
	StudentRepository repo(database);
	int nrInitial = repo.getAllStudents().value().size();
	Student student("ceva", "", "", "", "", "", 3);
	repo.addStudent(student);
	int nrFinal = repo.getAllStudents().value().size();
	EXPECT_EQ(nrFinal, nrInitial + 1);
}

TEST(IntegrationTests, UpdateStudent)
{
	auto connection = Environment::getInstance()->getValue("ceva");
	Database database(connection);
	StudentRepository repo(database);
	int id = 5; // vrem sa actualizam datele pt Studentul cu id 5
	Student student1 = repo.getStudentByID(id).value();
	Student studentNou("ceva", "", "", "", "", "", 3, id);
	repo.updateStudent(studentNou);
	Student student2 = repo.getStudentByID(id).value();
	EXPECT_EQ(studentNou.getFirstName(), student2.getFirstName());
	EXPECT_NE(studentNou.getFirstName(), student1.getFirstName());
}

TEST(IntegrationTests, GetStudentById)
{
	auto connection = Environment::getInstance()->getValue("ceva");
	Database database(connection);
	StudentRepository repo(database);
	auto actual = repo.getStudentByID(5);
	// Test 1 - Verificam ca student chiar exista (nu este null)
	EXPECT_TRUE(actual.has_value());
	// Test 2 - Verificam diverse atribute
	EXPECT_TRUE(actual.value().getFirstName() != "");
}

TEST(IntegrationTests, GetAllStudents)
{
	auto connection = Environment::getInstance()->getValue("ceva");
	Database database(connection);
	StudentRepository repo(database);
	auto actual = repo.getAllStudents();
	// Test 1 - Verificam ca avem un vector de studenti (minim 1)
	EXPECT_TRUE(actual.has_value());
	EXPECT_TRUE(actual.value().size()!=0);
	// Test 2 - Verificam diverse atribute pt minim un student
	EXPECT_TRUE(actual.value()[0].getFirstName() != "");
}