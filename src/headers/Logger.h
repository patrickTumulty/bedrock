//
// Created by Patrick Tumulty on 5/15/22.
//

#ifndef RHC_LOGGER_H
#define RHC_LOGGER_H

#include <string>
#include <vector>

enum LogLevel
{
    CONSOLE = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
};

class Logger
{
public:
    static Logger& get()
    {
        static Logger instance;
        return instance;
    }

    void logInfo(const std::string& message);
    void logWarning(const std::string& message);
    void logError(const std::string& message);
    void consoleLog(const std::string& message);
    void dumpLogToConsole(LogLevel logLevel = INFO);
private:
    Logger();
    void log(LogLevel logLevel, const std::string &message);
    static std::string getLogLevelString(LogLevel logLevel);
    void setEnableConsoleLogging(bool enabled);

    struct Log
    {
        LogLevel logLevel;
        std::string message;
        [[nodiscard]] std::string getFormattedLog() const;
    };

    bool consoleLoggingEnabled{};
    std::vector<Log> currentLog;
};


#endif //RHC_LOGGER_H
