#include "Logger.h"

Logger::Logger(const std::string& filename)
	:m_fout(filename),
	m_os(m_fout),
	m_minimumLevel(Level::Info)
{
}

void Logger::log(const std::string& message, Level level)
{
	if (level < m_minimumLevel)
		return;
	switch (level)
	{
	case Level::Info:
		m_os << "[INFO]   ";
		break;
	case Level::Warning:
		m_os << "[WARNING]";
		break;
	case Level::Error:
		m_os << "[ERROR]  ";
		break;
	}
	std::time_t now = std::time(nullptr);
	std::tm tm_local;
	localtime_s(&tm_local, &now);
	m_os << "[" << std::put_time(&tm_local, "%Y-%m-%d %H:%M:%S") << "]";
	m_os << " - " << message << "\n";
}

void Logger::setMinimumLevel(const Level& level)
{
	m_minimumLevel = level;
}
