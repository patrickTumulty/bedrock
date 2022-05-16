//
// Created by Patrick Tumulty on 5/15/22.
//

#include "Logger.h"
#include <iostream>

/**
 * Constructor
 */
Logger::Logger() : consoleLoggingEnabled(true)
{

}

void Logger::consoleLog(const std::string &str) const
{
    if (consoleLoggingEnabled)
        std::cout << str << std::endl;
}

void Logger::log(LogLevel logLevel, const std::string &str)
{
    std::string log = "[" + getLogLevelString(logLevel) + "] : " + str;
    logStack.push(log);
}

void Logger::logInfo(const std::string &str)
{
    log(INFO, str);
}

void Logger::logWarning(const std::string &str)
{
    log(WARNING, str);
}

void Logger::logError(const std::string &str)
{
    log(ERROR, str);
}

std::string Logger::getLogLevelString(LogLevel logLevel)
{
    switch (logLevel)
    {
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
    }
}



Logger::~Logger()
{
}

void Logger::setEnableConsoleLogging(bool enabled)
{
    consoleLoggingEnabled = enabled;
}

void Logger::dumpLogToConsole()
{
    while(!logStack.empty())
    {
        std::cout << logStack.top() << std::endl;
        logStack.pop();
    }
}

