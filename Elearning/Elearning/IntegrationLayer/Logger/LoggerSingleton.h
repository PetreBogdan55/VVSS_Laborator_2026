#pragma once

#include "Logger.h"

class LoggerSingleton
{
public:
	LoggerSingleton(Logger const&) = delete;
	LoggerSingleton(Logger&&) = delete;
	LoggerSingleton& operator=(Logger const&) = delete;
	LoggerSingleton& operator=(Logger&&) = delete;

public:
	static Logger* getLoggerInstance();

protected:
	LoggerSingleton() = default;
	~LoggerSingleton() = default;

private:
	inline static Logger* m_instance = nullptr;
};

