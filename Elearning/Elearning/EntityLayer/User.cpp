#include "User.h"

User::User(
    std::string firstName,
    std::string lastName,
    std::string email,
    std::string address,
    std::string phone,
    int id)
    // lista de initializari
    :
    m_firstName{ firstName },
    m_lastName { lastName  },
    m_email    { email     },
    m_address  { address   },
    m_phone    { phone     },
    m_id       { id        }
{
    if (m_firstName.empty())
        LoggerSingleton::getLoggerInstance()->log("Numele utilizatorului nu poate fi gol", Logger::Level::Error);
    if (m_lastName.empty())
        LoggerSingleton::getLoggerInstance()->log("Numele utilizatorului nu poate fi gol", Logger::Level::Error);
    if (m_email.empty() || m_email.find("@")==std::string::npos)
        LoggerSingleton::getLoggerInstance()->log("Email-ul utilizatorului este invalid", Logger::Level::Error);
    if (m_address.empty())
        LoggerSingleton::getLoggerInstance()->log("Adresa utilizatorului nu este completata", Logger::Level::Error);
    if (m_phone.size() != 10)
        LoggerSingleton::getLoggerInstance()->log("Telefonul utilizatorului este invalid", Logger::Level::Error);
}

User::User(const User& other)
    :
    m_firstName{ other.m_firstName },
    m_lastName { other.m_lastName  },
    m_email    { other.m_email     },
    m_address  { other.m_address   },
    m_phone    { other.m_phone     },
    m_id       { other.m_id        }
{
}

User::User(User&& other)
    :
    m_firstName { std::move(other.m_firstName) },
    m_lastName  { std::move(other.m_lastName ) },
    m_email     { std::move(other.m_email    ) },
    m_address   { std::move(other.m_address  ) },
    m_phone     { std::move(other.m_phone    ) },
    m_id        { std::move(other.m_id       ) }
{
}

User& User::operator=(const User& other)
{
    if (this != &other) 
    {
        m_firstName = other.m_firstName;
        m_lastName  = other.m_lastName ;
        m_email     = other.m_email    ;
        m_address   = other.m_address  ;
        m_phone     = other.m_phone    ;
        m_id        = other.m_id       ;
    }
    return *this;
}

User& User::operator=(User&& other)
{
    if (this != &other)
    {
        m_firstName = std::move(other.m_firstName) ;
        m_lastName  = std::move(other.m_lastName ) ;
        m_email     = std::move(other.m_email    ) ;
        m_address   = std::move(other.m_address  ) ;
        m_phone     = std::move(other.m_phone    ) ;
        m_id        = other.m_id                   ;

    }
    return *this;
}

int User::getID() const
{
    return m_id;
}

std::string User::getFirstName() const
{
    return m_firstName;
}

std::string User::getLastName() const
{
    return m_lastName;
}

std::string User::getEmail() const
{
    return m_email;
}

std::string User::getAddress() const
{
    return m_address;
}

std::string User::getPhone() const
{
    return m_phone;
}

void User::setID(int id)
{
    m_id = id;
}

void User::setFirstName(const std::string& firstName)
{
    if (firstName.empty())
        LoggerSingleton::getLoggerInstance()->log("Numele utilizatorului nu poate fi gol", Logger::Level::Error);
    else
        m_firstName = firstName;
}

void User::setLastName(const std::string& lastName)
{
    if (lastName.empty())
        LoggerSingleton::getLoggerInstance()->log("Numele utilizatorului nu poate fi gol", Logger::Level::Error);
    else
        m_lastName = lastName;
}

void User::setEmail(const std::string& email)
{
    if (email.empty() || !email.find("@"))
        LoggerSingleton::getLoggerInstance()->log("Email-ul utilizatorului este invalid", Logger::Level::Error);
    else
        m_email = email;
}

void User::setAddress(const std::string& address)
{
    if (address.empty())
        LoggerSingleton::getLoggerInstance()->log("Adresa utilizatorului nu este completata", Logger::Level::Error);
    else
        m_address = address;
}

void User::setPhone(const std::string& phone)
{
    if (phone.size() != 10)
        LoggerSingleton::getLoggerInstance()->log("Telefonul utilizatorului este invalid", Logger::Level::Error);
    else
        m_phone = phone;
}

void User::printInformations() const
{
    std::println("User: {}, {}, {}, {}, {}, {}",
        m_firstName,
        m_lastName,
        m_email,
        m_address,
        m_phone,
        m_id);
}
