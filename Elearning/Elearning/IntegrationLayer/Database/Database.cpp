#include "Database.h"

#define SQL_RETURN_CODE_LENGTH 1000

Database::Database(const std::string& connString)
    :m_connString{ connString },
    m_isConnected{ false },
    m_sqlEnvHandle{ NULL },
    m_sqlConnHandle{ NULL },
    m_sqlStmtHandle{ NULL }
{
    connectToDatabase();
}

Database::~Database()
{
    disconnectToDatabase();
}

void Database::connectToDatabase()
{
    // toti cei 3 Handle trebuie alocati in memorie -> SQLAllocHandle(tip_handle, parinte, variabila)

    // 1. Handle de Env --> aloc + setam proprietati de ODBC suplimentare (ODBC v3)
    // SQLSetEnvAttr(handle, ATRIBUTUL, VALOAREA LUI)
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_sqlEnvHandle))
    {
        LoggerSingleton::getLoggerInstance()->log("Nu s-a putut aloca ENV", Logger::Level::Error);
        disconnectToDatabase();
        return;
    }
    if (SQL_SUCCESS != SQLSetEnvAttr(m_sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
    {
        LoggerSingleton::getLoggerInstance()->log("Nu s-a putut seta ODBC v3", Logger::Level::Error);
        disconnectToDatabase();
        return;
    }

    // 2. Folosim env -> Handle de Conn + conectarea propriu-zisa la baza de date
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, m_sqlEnvHandle, &m_sqlConnHandle))
    {
        LoggerSingleton::getLoggerInstance()->log("Nu s-a putut aloca CONN", Logger::Level::Error);
        disconnectToDatabase();
        return;
    }

    SQLWCHAR retConnString[SQL_RETURN_CODE_LENGTH]; // echivalentul lui std::wstring
    //conversie pt connString din std::string -> wstring
    const std::wstring wConnString(m_connString.begin(), m_connString.end());

    auto status = SQLDriverConnect(
        m_sqlConnHandle,
        NULL,
        (SQLWCHAR*)wConnString.c_str(),
        SQL_NTS,
        retConnString,
        1024,
        NULL,
        SQL_DRIVER_NOPROMPT
    );

    switch (status)
    {
    case SQL_SUCCESS:
    case SQL_SUCCESS_WITH_INFO:
        m_isConnected = true;
        break;

    case SQL_INVALID_HANDLE:
    case SQL_ERROR:
        disconnectToDatabase();
        break;

    default:
        break;
    }

    // 3. Folosim conn -> Handle de Stmt
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, m_sqlConnHandle, &m_sqlStmtHandle))
    {
        LoggerSingleton::getLoggerInstance()->log("Nu s-a putut aloca STMT", Logger::Level::Error);
        disconnectToDatabase();
        return;
    }
}

void Database::disconnectToDatabase()
{
    // Dealocam din memorie handle-urile --> in ordinea inversa fata de alocare
    // Mutam flag-ul de isConnected pe false
    m_isConnected = false;
    SQLFreeHandle(SQL_HANDLE_STMT, m_sqlStmtHandle);
    SQLDisconnect(m_sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, m_sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, m_sqlEnvHandle);
}

bool Database::getIsConnected() const
{
    return m_isConnected;
}

SQLHANDLE Database::getEnvHandle() const
{
    return m_sqlEnvHandle;
}

SQLHANDLE Database::getConnHandle() const
{
    return m_sqlConnHandle;
}

SQLHANDLE Database::getStmtHandle() const
{
    return m_sqlStmtHandle;
}

void Database::setStmtHandle(const SQLHANDLE& stmtHandle)
{
    m_sqlStmtHandle = stmtHandle;
}
