#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <format>
#include "Logger.hpp"

namespace lib
{
    std::string Logger::level_to_string(LogLevel level)
    {
        switch (level)
        {
            case DEBUG:
                return "DEBUG";
            case INFO:
                return "INFO";
            case WARNING:
                return "WARNING";
            case ERROR:
                return "ERROR";
            case CRITICAL:
                return "CRITICAL";
            default:
                return "UNKNOWN";
        }
    }

    Logger::Logger(const std::string &filename)
    {
        log_file.open(filename, std::ios::trunc);
        if (!log_file.is_open())
        {
            std::ofstream new_log(filename);
            new_log.close();
            log_file.open(filename, std::ios::trunc);
        }
    }

    Logger::~Logger()
    {
        if (log_file.is_open())
            log_file.close();
    }

    void Logger::log(LogLevel level, std::string const &message)
    {
        // Timestamp
        auto const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
        std::string const timestamp = std::format("[{:%Y-%m-%d %X}] ", time);
        // Create log entry
        std::ostringstream logEntry;
        logEntry << timestamp << level_to_string(level) << ": " << message
                 << std::endl;

        /*
        // Output to console
        std::cout << logEntry.str();
        */

        // Output to log file
        if (log_file.is_open()) {
            log_file << logEntry.str();
            log_file
                .flush(); // Ensure immediate write to file
        }
    }
}