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
    // Empty
}

/**
 * Console log
 *
 * @param message string message
 */
void Logger::consoleLog(const std::string &message)
{
    log(CONSOLE, message);

    if (consoleLoggingEnabled)
        std::cout << message << std::endl;

}

/**
 * Log a message with a log level
 *
 * @param logLevel log level
 * @param message string message
 */
void Logger::log(LogLevel logLevel, const std::string &message)
{
    Log newLog;
    newLog.logLevel = logLevel;
    newLog.message = message;
    currentLog.push_back(newLog);
}

/**
 * Log info message
 *
 * @param message string message
 */
void Logger::logInfo(const std::string &message)
{
    log(INFO, message);
}

/**
 * Log warning message
 *
 * @param message string message
 */
void Logger::logWarning(const std::string &message)
{
    log(WARNING, message);
}

/**
 * Log error message
 *
 * @param message string message
 */
void Logger::logError(const std::string &message)
{
    log(ERROR, message);
}

/**
 * Get the log level string
 *
 * @param logLevel log level
 * @return log level string
 */
std::string Logger::getLogLevelString(LogLevel logLevel)
{
    switch (logLevel)
    {
        case CONSOLE: return "CONSOLE";
        case INFO:    return "INFO";
        case WARNING: return "WARNING";
        case ERROR:   return "ERROR";
    }
}

/**
 * Set enable console logging (default = true)
 *
 * @param enabled console logging enabled
 */
void Logger::setEnableConsoleLogging(bool enabled)
{
    consoleLoggingEnabled = enabled;
}

/**
 * Dump logs to console
 */
void Logger::dumpLogToConsole(LogLevel logLevel)
{
    for (int i = (int) currentLog.size() - 1; i > -1; i--)
    {
        Log current = currentLog[i];
        if (current.logLevel >= logLevel)
        {
            std::cout << currentLog[i].getFormattedLog() << std::endl;
        }
    }
}

/**
 * Get the formatted log string for this log struct
 *
 * @return formatted log string
 */
std::string Logger::Log::getFormattedLog() const
{
    return "[" + getLogLevelString(logLevel) + "] : " + message;
}
