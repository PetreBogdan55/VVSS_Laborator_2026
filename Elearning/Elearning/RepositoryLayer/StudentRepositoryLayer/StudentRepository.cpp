#include "StudentRepository.h"

StudentRepository::StudentRepository(Database& database)
	:m_database(database)
{}

void mecanismPerCazGeneral()
{
	// 1. Verificam daca ne putem conecta la baza de date
	Database db("test");
	if (!db.getIsConnected()) return;

	// 2. Luam handle-ul de STMT din baza de date
	SQLHANDLE stmt = db.getStmtHandle();

	// 3. Scriem query-ul SQL
	SQLWCHAR query[] = L"";

	// 4. Pregatim o variabila de return
	SQLRETURN ret;

	// 5. Compilarea query-ului
	ret = SQLPrepare(stmt, query, SQL_NTS);

	// 6. (Optional) eventual binding-uri de parametrii
	// SQLBindParameter

	// 7. Executarea propriu-zis
	ret = SQLExecute(stmt);
}

void StudentRepository::deleteStudent(int id)
{
	if (!m_database.getIsConnected())
	{
		LoggerSingleton::getLoggerInstance()->log("Nu exista conexiune", Logger::Level::Error);
		return;
	}

	SQLHANDLE stmt = m_database.getStmtHandle();

	//SQLWCHAR query[] = L"{CALL dbo.DeleteStudent(?)}"; // MSSQL
	SQLWCHAR query[] = L"CALL public.deletestudent(?)"; // POSGTRES

	SQLRETURN ret;
	ret = SQLPrepare(stmt, query, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		LoggerSingleton::getLoggerInstance()->log("query invalid", Logger::Level::Error);
		return;
	}

	SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0,
		&id, 0, nullptr);

	ret = SQLExecute(stmt);
	if (ret != SQL_SUCCESS)
	{
		LoggerSingleton::getLoggerInstance()->log("executare esuata", Logger::Level::Error);
		return;
	}
}

void StudentRepository::addStudent(Student student)
{
	if (!m_database.getIsConnected()) return;

	SQLHANDLE stmt = m_database.getStmtHandle();
	//SQLWCHAR query[] = L"{CALL dbo.AddStudent(?,?,?,?,?,?,?)}"; // MSSQL
	SQLWCHAR query[] = L"CALL public.addstudent(?,?,?,?,?,?,?)"; // POSGTRES

	SQLRETURN ret;
	ret = SQLPrepare(stmt, query, SQL_NTS);

	// 6. (Optional) eventual binding-uri de parametrii
	// SQLBindParameter
	std::string firstName = student.getFirstName();
	std::string lastName = student.getLastName();
	std::string email = student.getEmail();
	std::string address = student.getAddress();
	std::string phone = student.getPhone();
	std::string matriculationNumber = student.getMatriculationNumber();
	int studyYear = student.getStudyYear();

	SQLLEN firstNameLength = firstName.size();
	SQLLEN lastNameLength = lastName.size();
	SQLLEN emailLength = email.size();
	SQLLEN addressLength = address.size();
	SQLLEN phoneLength = phone.size();
	SQLLEN matriculationNumberLength = matriculationNumber.size();

	SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		firstNameLength, 0, (SQLPOINTER)firstName.c_str(), 0, &firstNameLength);
	SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		lastNameLength, 0, (SQLPOINTER)lastName.c_str(), 0, &lastNameLength);
	SQLBindParameter(stmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		emailLength, 0, (SQLPOINTER)email.c_str(), 0, &emailLength);
	SQLBindParameter(stmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		addressLength, 0, (SQLPOINTER)address.c_str(), 0, &addressLength);
	SQLBindParameter(stmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		phoneLength, 0, (SQLPOINTER)phone.c_str(), 0, &phoneLength);
	SQLBindParameter(stmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
		matriculationNumberLength, 0, (SQLPOINTER)matriculationNumber.c_str(), 0, &matriculationNumberLength);
	SQLBindParameter(stmt, 7, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
		0, 0, &studyYear, 0, nullptr);

	ret = SQLExecute(stmt);
}