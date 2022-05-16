//
// Created by Patrick Tumulty on 5/15/22.
//

#ifndef RHC_LOGGER_H
#define RHC_LOGGER_H

#include <string>
#include <stack>

enum LogLevel
{
    INFO,
    WARNING,
    ERROR
};

class Logger
{
public:
    static Logger& get()
    {
        static Logger instance;
        return instance;
    }

    void logInfo(const std::string& str);
    void logWarning(const std::string& str);
    void logError(const std::string& str);
    void consoleLog(const std::string& str) const;
    void dumpLogToConsole();
private:
    Logger();
    ~Logger();
    void log(LogLevel logLevel, const std::string &str);
    static std::string getLogLevelString(LogLevel logLevel);
    void setEnableConsoleLogging(bool enabled);

    bool consoleLoggingEnabled{};
    std::stack<std::string> logStack;

};


#endif //RHC_LOGGER_H
