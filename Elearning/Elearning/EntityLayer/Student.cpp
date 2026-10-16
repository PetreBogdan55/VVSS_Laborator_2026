#include "Student.h"

Student::Student(
	std::string firstName,
	std::string lastName,
	std::string email,
	std::string address,
	std::string phone,
	std::string matriculationNumber,
	int studyYear,
	int id)
	: User(firstName, lastName, email, address, phone, id),
	m_matriculationNumber { matriculationNumber },
	m_studyYear           { studyYear           }
{
	if (m_matriculationNumber.empty())
		LoggerSingleton::getLoggerInstance()->log("Numarul matricol nu poate fi gol", Logger::Level::Error);
	if (m_studyYear <= 0 || m_studyYear > 3)
		LoggerSingleton::getLoggerInstance()->log("Anul de studiu este invalid", Logger::Level::Error);
}

Student::Student(const Student& other)
	: User(other),
	m_matriculationNumber { other.m_matriculationNumber },
	m_studyYear           { other.m_studyYear           }
{
}

Student::Student(Student&& other)
	: User(std::move(other)),
	m_matriculationNumber{ std::move(other.m_matriculationNumber) },
	m_studyYear          { other.m_studyYear                      }
{
}

Student& Student::operator=(const Student& other)
{
	if (this != &other)
	{
		User::operator=(other);
		m_matriculationNumber = other.m_matriculationNumber;
		m_studyYear           = other.m_studyYear          ;
	}
	return *this;
}

Student& Student::operator=(Student&& other)
{
	if (this != &other)
	{
		User::operator=(std::move(other));
		m_matriculationNumber = std::move(other.m_matriculationNumber);
		m_studyYear           = other.m_studyYear                     ;
	}
	return *this;
}

std::string Student::getMatriculationNumber() const
{
	return m_matriculationNumber;
}

int Student::getStudyYear() const
{
	return m_studyYear;
}

void Student::setMatriculationNumber(const std::string& matriculationNumber)
{
	if (matriculationNumber.empty())
		LoggerSingleton::getLoggerInstance()->log("Numarul matricol nu poate fi gol", Logger::Level::Error);
	else
		m_matriculationNumber = matriculationNumber;
}

void Student::setStudyYear(int studyYear)
{
	if (studyYear <= 0 || studyYear > 3)
		LoggerSingleton::getLoggerInstance()->log("Anul de studiu este invalid", Logger::Level::Error);
	else
		m_studyYear = studyYear;
}

void Student::printInformations() const
{
	// Optional: se pot printa si atributele din User
	std::println("Student: {}, {}", 
		m_matriculationNumber,
		m_studyYear);
}
