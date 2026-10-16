#pragma once

#include "User.h"

class Student : public User
{
public:
	Student() = default;
	Student(
		std::string firstName,
		std::string lastName,
		std::string email,
		std::string address,
		std::string phone,
		std::string matriculationNumber,
		int studyYear,
		int id = 0
	);
	Student(const Student& other);
	Student(Student&& other);
	Student& operator=(const Student& other);
	Student& operator=(Student&& other);
	virtual ~Student() = default;

public:
	std::string getMatriculationNumber() const;
	int         getStudyYear()           const;

public:
	void setMatriculationNumber(const std::string& matriculationNumber);
	void setStudyYear          (int studyYear                         );

public:
	void printInformations() const override;

private:
	std::string m_matriculationNumber;
	int         m_studyYear          ;
};

