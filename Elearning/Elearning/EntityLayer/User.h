#pragma once

#include "pch.h"
#include "LoggerSingleton.h"

class User
{
public: // constructori si destructori
	User() = default;
	User(
		std::string firstName,
		std::string lastName,
		std::string email,
		std::string address,
		std::string phone,
		int id = 0
	);
	User(const User& other);
	User(User&& other);
	User& operator=(const User& other);
	User& operator=(User&& other);
	virtual ~User() = default;

public: // getteri
	int         getID()        const;
	std::string getFirstName() const;
	std::string getLastName()  const;
	std::string getEmail()     const;
	std::string getAddress()   const;
	std::string getPhone()     const;

public: // setteri
	void setID(int id);
	void setFirstName (const std::string& firstName);
	void setLastName  (const std::string& lastName );
	void setEmail     (const std::string& email    );
	void setAddress   (const std::string& address  );
	void setPhone     (const std::string& phone    );

public: // metode specifice
	virtual void printInformations() const;

protected: // membrii/atribute
	std::string m_firstName;
	std::string m_lastName ;
	std::string m_email    ;
	std::string m_address  ;
	std::string m_phone    ;
	int         m_id       ; // std::string daca in baza de date este un (uuid)
};

