#pragma once

#include "Student.h"

class IStudentRepository
{
public:
	virtual void deleteStudent(int id) = 0;
	virtual void addStudent(Student student) = 0;
};