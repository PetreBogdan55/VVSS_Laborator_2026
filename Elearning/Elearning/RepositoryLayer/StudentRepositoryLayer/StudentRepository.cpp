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

	// 8. (Optional doar pentru SELECT-uri)
	// Facem un IF (daca avem un singur rezultat)
	// Facem un WHILE (daca avem mai multe)
	// -> fetching din STMT pt datele extrase -> salvam

	// 9. Eliberare memorie pentru STMT
	SQLFreeHandle(SQL_HANDLE_STMT, stmt); // inclusiv la orice return separat
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
	SQLWCHAR query[] = L"CALL public.deletestudent(?)"; // POSTGRES

	SQLRETURN ret;
	ret = SQLPrepare(stmt, query, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		LoggerSingleton::getLoggerInstance()->log("Invalid delete query", Logger::Level::Error);
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return;
	}

	SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0,
		&id, 0, nullptr);

	ret = SQLExecute(stmt);
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	if (ret != SQL_SUCCESS)
	{
		LoggerSingleton::getLoggerInstance()->log("Wrong delete query binding parameters", Logger::Level::Error);
		return;
	}
}

void StudentRepository::addStudent(Student student)
{
	if (!m_database.getIsConnected()) return;

	SQLHANDLE stmt = m_database.getStmtHandle();
	SQLWCHAR query[] = L"{CALL dbo.AddStudent(?,?,?,?,?,?,?)}"; // MSSQL
	//SQLWCHAR query[] = L"CALL public.addstudent(?,?,?,?,?,?,?)"; // POSTGRES

	SQLRETURN ret;
	ret = SQLPrepare(stmt, query, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		LoggerSingleton::getLoggerInstance()->log("Invalid add query", Logger::Level::Error);
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return;
	}

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
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	if (ret != SQL_SUCCESS)
	{
		LoggerSingleton::getLoggerInstance()->log("Wrong add query binding parameters", Logger::Level::Error);
		return;
	}
}

void StudentRepository::updateStudent(Student student)
{
	if (!m_database.getIsConnected()) return;

	SQLHANDLE stmt = m_database.getStmtHandle();
	//SQLWCHAR query[] = L"{CALL dbo.UpdateStudent(?,?,?,?,?,?,?,?)}"; // MSSQL
	SQLWCHAR query[] = L"CALL public.updatestudent(?,?,?,?,?,?,?,?)"; // POSTGRES

	SQLRETURN ret;
	ret = SQLPrepare(stmt, query, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		LoggerSingleton::getLoggerInstance()->log("Invalid update query", Logger::Level::Error);
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return;
	}

	std::string firstName = student.getFirstName();
	std::string lastName = student.getLastName();
	std::string email = student.getEmail();
	std::string address = student.getAddress();
	std::string phone = student.getPhone();
	std::string matriculationNumber = student.getMatriculationNumber();
	int studyYear = student.getStudyYear();
	int id = student.getID();

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
	SQLBindParameter(stmt, 8, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
		0, 0, &id, 0, nullptr);

	ret = SQLExecute(stmt);
	if (ret != SQL_SUCCESS)
	{
		LoggerSingleton::getLoggerInstance()->log("Wrong update query binding parameters", Logger::Level::Error);
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return;
	}

	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
}

std::optional<Student> StudentRepository::getStudentByID(int id)
{
	if (!m_database.getIsConnected()) return std::nullopt;

	SQLHANDLE stmt = m_database.getStmtHandle();
	SQLWCHAR query[] = L"{CALL dbo.GetStudentById(?)}"; // MSSQL
	//SQLWCHAR query[] = L"SELECT * FROM public.getstudentbyid(?)"; // POSTGRES

	SQLRETURN ret;
	ret = SQLPrepare(stmt, query, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		LoggerSingleton::getLoggerInstance()->log("Invalid get query", Logger::Level::Error);
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return std::nullopt;
	}

	SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
		0, 0, &id, 0, nullptr);

	ret = SQLExecute(stmt);
	if (ret != SQL_SUCCESS)
	{
		LoggerSingleton::getLoggerInstance()->log("Wrong get query binding parameters", Logger::Level::Error);
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return std::nullopt;
	}

	SQLINTEGER returned_id;
	SQLINTEGER studyYear;
	char firstName[100];
	char lastName[100];
	char email[100];
	char address[100];
	char phone[100];
	char matriculationNumber[100];

	if (SQLFetch(stmt) == SQL_SUCCESS)
	{
		SQLGetData(stmt, 1, SQL_C_LONG, &returned_id, 0, nullptr);
		SQLGetData(stmt, 2, SQL_C_CHAR, firstName, sizeof(firstName), nullptr);
		SQLGetData(stmt, 3, SQL_C_CHAR, lastName, sizeof(lastName), nullptr);
		SQLGetData(stmt, 4, SQL_C_CHAR, email, sizeof(email), nullptr);
		SQLGetData(stmt, 5, SQL_C_CHAR, address, sizeof(address), nullptr);
		SQLGetData(stmt, 6, SQL_C_CHAR, phone, sizeof(phone), nullptr);
		SQLGetData(stmt, 7, SQL_C_CHAR, matriculationNumber, sizeof(matriculationNumber), nullptr);
		SQLGetData(stmt, 8, SQL_C_LONG, &studyYear, 0, nullptr);

		//Student student(firstName, lastName, email, address, phone, matriculationNumber,
		//	studyYear, returned_id);
		Student student;
		student.setID(returned_id);
		student.setStudyYear(studyYear);
		student.setMatriculationNumber(std::string(matriculationNumber));
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return student;
	}
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	return std::nullopt;
}

std::optional<std::vector<Student>> StudentRepository::getAllStudents()
{
	if (!m_database.getIsConnected()) return std::nullopt;

	SQLHANDLE stmt = m_database.getStmtHandle();
	//SQLWCHAR query[] = L"{CALL dbo.GetAllStudents}"; // MSSQL
	SQLWCHAR query[] = L"SELECT * FROM public.getallstudents()"; // POSGTRES

	SQLRETURN ret;
	ret = SQLPrepare(stmt, query, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		LoggerSingleton::getLoggerInstance()->log("Invalid get query", Logger::Level::Error);
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return std::nullopt;
	}

	ret = SQLExecute(stmt);
	if (ret != SQL_SUCCESS)
	{
		LoggerSingleton::getLoggerInstance()->log("Wrong get query binding parameters", Logger::Level::Error);
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return std::nullopt;
	}

	SQLINTEGER returned_id;
	SQLINTEGER studyYear;
	char firstName[100];
	char lastName[100];
	char email[100];
	char address[100];
	char phone[100];
	char matriculationNumber[100];
	std::vector<Student> students;

	while (SQLFetch(stmt) == SQL_SUCCESS)
	{
		SQLGetData(stmt, 1, SQL_C_LONG, &returned_id, 0, nullptr);
		SQLGetData(stmt, 2, SQL_C_CHAR, firstName, sizeof(firstName), nullptr);
		SQLGetData(stmt, 3, SQL_C_CHAR, lastName, sizeof(lastName), nullptr);
		SQLGetData(stmt, 4, SQL_C_CHAR, email, sizeof(email), nullptr);
		SQLGetData(stmt, 5, SQL_C_CHAR, address, sizeof(address), nullptr);
		SQLGetData(stmt, 6, SQL_C_CHAR, phone, sizeof(phone), nullptr);
		SQLGetData(stmt, 7, SQL_C_CHAR, matriculationNumber, sizeof(matriculationNumber), nullptr);
		SQLGetData(stmt, 8, SQL_C_LONG, &studyYear, 0, nullptr);

		//Student student(firstName, lastName, email, address, phone, matriculationNumber,
		//	studyYear, returned_id);
		Student student;
		student.setID(returned_id);
		student.setStudyYear(studyYear);
		student.setMatriculationNumber(std::string(matriculationNumber));
		students.push_back(student);
	}
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	if (students.size() != 0)
		return students;
	return std::nullopt;
}
