#pragma once

#include "Database.h"
#include "IStudentRepository.h"

class StudentRepository : public IStudentRepository
{
public:
	StudentRepository(Database& database);

public:
	// Inherited via IStudentRepository
	void deleteStudent(int id) override;
	void addStudent(Student student) override;
	void updateStudent(Student student) override;
	std::optional<Student> getStudentByID(int id) override;
	std::optional<std::vector<Student>> getAllStudents() override;

private:
	Database& m_database;
};