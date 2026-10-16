#pragma once

#include "pch.h"

class Logger
{
public:
	enum class Level
	{
		Info,
		Warning,
		Error
	};

public:
	Logger(const std::string& filename);
	void log(const std::string& message, Level level);
	void setMinimumLevel(const Level& level);

private:
	Level m_minimumLevel;
	std::ofstream m_fout;
	std::ostream& m_os;
};

