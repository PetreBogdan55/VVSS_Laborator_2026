#pragma once

#include "pch.h"

class Environment
{

public:
	Environment(const Environment&) = delete;
	Environment& operator=(const Environment&) = delete;

public:
	static Environment* getInstance();
	std::string getValue(const std::string& key) const;

private:
	Environment() = default;

private:
	inline static Environment* m_instance = nullptr;
};