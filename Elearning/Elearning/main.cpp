#include "Environment.h"
#include "StudentRepository.h"

int main()
{
	Student student("Ion", "Popescu", "ion.popescu@student.unitbv.ro", "Str. Lunga, nr 5", "0771123456", "123A", 3);

	std::string mssql_conn_string    = Environment::getInstance()->getValue("MSSQLSERVER_CONN_STRING");
	std::string postgres_conn_string = Environment::getInstance()->getValue("POSTGRESQL_CONN_STRING");

	Database mssql_database(mssql_conn_string);
	std::cout << mssql_database.getIsConnected() << "\n";

	Database postgresql_database(postgres_conn_string);
	std::cout << postgresql_database.getIsConnected() << "\n";

	StudentRepository repo(postgresql_database);
	repo.deleteStudent(2);
	repo.addStudent(student);

	return 0;
}