#include <fstream>
#include <print>
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
        auto const timestamp = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
        // Create log entry
        std::string const log_entry = std::format("[{0:%Y-%m-%d %X}] {1}: {2}", timestamp, level_to_string(level), message);

        // Output to console
        std::println("{}", log_entry);

        // Output to log file
        if (log_file.is_open()) {
            std::println(log_file, "{}", log_entry);
            log_file.flush(); // Ensure immediate write to file
        }
    }
}