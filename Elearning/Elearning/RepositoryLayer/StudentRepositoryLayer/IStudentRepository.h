#pragma once

#include "Student.h"

class IStudentRepository
{
public:
	virtual void deleteStudent(int id) = 0;
	virtual void addStudent(Student student) = 0;
	virtual void updateStudent(Student student) = 0;
	virtual std::optional<Student> getStudentByID(int id) = 0;
	virtual std::optional<std::vector<Student>> getAllStudents() = 0;
};