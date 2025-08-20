#pragma once
#include <sstream>
#include <iostream>

namespace Logger
{
    enum class LogLevel
    {
        INFO,
        DEBUG,
        WARN,
        ERROR
    };

    inline std::string getLogString(const LogLevel lv)
    {
        switch (lv)
        {
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::WARN:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
        default:
            return "ERROR";
        }
    }

    template <typename... Args>
    void Log(const LogLevel logLevel, const Args &...args)
    {
        std::ostringstream oss;
        oss << "[" + getLogString(logLevel) + "] ";

        // Handle all arguments with spaces between them
        ((oss << args << " "), ...);

        std::string message = oss.str();
        // Remove trailing space
        if (!message.empty() && message.back() == ' ')
            message.pop_back();

        std::cout << message << std::endl;
    }

    template <typename... Args>
    void Info(const Args &...args)
    {
        Log(LogLevel::INFO, args...);
    }

    template <typename... Args>
    void Debug(const Args &...args)
    {
        Log(LogLevel::DEBUG, args...);
    }

    template <typename... Args>
    void Warn(const Args &...args)
    {
        Log(LogLevel::WARN, args...);
    }

    template <typename... Args>
    void Error(const Args &...args)
    {
        Log(LogLevel::ERROR, args...);
    }
}