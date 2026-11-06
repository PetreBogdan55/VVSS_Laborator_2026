#include "Environment.h"
#include "StudentRepository.h"

int main()
{
	Student student("Alex", "Darius", "ion.popescu@student.unitbv.ro", "Str. Bradului, nr 5", "0771123456", "123A", 3, 4);

	std::string mssql_conn_string    = Environment::getInstance()->getValue("MSSQLSERVER_CONN_STRING");
	std::string postgres_conn_string = Environment::getInstance()->getValue("POSTGRESQL_CONN_STRING");

	Database mssql_database(mssql_conn_string);
	std::cout << mssql_database.getIsConnected() << "\n";

	Database postgresql_database(postgres_conn_string);
	std::cout << postgresql_database.getIsConnected() << "\n";

	StudentRepository repo(postgresql_database);
	//repo.deleteStudent(2);
	//repo.addStudent(student);
	//repo.updateStudent(student);
	//auto result = repo.getStudentByID(3);
	//if (result.has_value())
	//	result.value().printInformations();
	//else std::cout << "Nu s-a gasit!";
	auto result = repo.getAllStudents();
	if (result.has_value())
		for (const auto& student : result.value())
			student.printInformations();
	else
		std::cout << "Nu s-a gasit";

	return 0;
}