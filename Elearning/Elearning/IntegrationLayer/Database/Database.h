
#pragma once

#define byte win_byte_override
#include "Windows.h"

#include <sqlext.h> // ODBC
#include <sqltypes.h> 
#include <sql.h>

#include "pch.h"
#include "LoggerSingleton.h"

class Database
{
public:
	Database(const std::string& connString);
	~Database();

private:
	void connectToDatabase();
	void disconnectToDatabase();

public:
	bool getIsConnected() const;
	SQLHANDLE getEnvHandle() const;
	SQLHANDLE getConnHandle() const;
	SQLHANDLE getStmtHandle() const;
	void setStmtHandle(const SQLHANDLE& stmtHandle);

private:
	SQLHANDLE m_sqlEnvHandle; // mediu din baza de date (sandbox)
	SQLHANDLE m_sqlConnHandle; // conexiune la baza de date
	SQLHANDLE m_sqlStmtHandle; // query-uri SQL
	bool m_isConnected;
	std::string m_connString;
};

