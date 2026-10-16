#include "LoggerSingleton.h"

Logger* LoggerSingleton::getLoggerInstance()
{
    if (m_instance == nullptr)
    {
        // instantiem o singura data
        static Logger log("log.txt");
        m_instance = &log;
    }

    return m_instance;
}
