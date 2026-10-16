#include "LoggerSingleton.h"
#include "Student.h"

int main()
{
#pragma region RecapitulareCpp
	int a = 59'879'887;
	int b = 7;
	int c = a + b;
	std::cout << "Suma lui " << a << " si a lui " << b
		<< " este " << c << "\n";
	std::ofstream fisier("log.txt");
	std::println(fisier, "Suma lui {} si a lui {} este {}",
		a, b, c);
	fisier.close();
#pragma endregion

#pragma region MultiLayer Application
	User utilizator("Ion", "Popescu", "ion.popescu@student.unitbv.ro", "Str. Lunga, nr 5", "0771123456");
	utilizator.printInformations();

	Student student("Ion", "Popescu", "ion.popescu@student.unitbv.ro", "Str. Lunga, nr 5", "0771123456", "123A", 3);
	student.printInformations();

	User utilizator2 = student;
	utilizator2.printInformations();

	LoggerSingleton::getLoggerInstance()->log("Eroare", Logger::Level::Info);
	LoggerSingleton::getLoggerInstance()->log("Eroare", Logger::Level::Warning);
	LoggerSingleton::getLoggerInstance()->log("Eroare", Logger::Level::Error);
#pragma endregion

	return 0;
}