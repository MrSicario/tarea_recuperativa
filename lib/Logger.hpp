#pragma once
#include <fstream>

namespace lib
{
    enum LogLevel
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };
    class Logger
    {
        private:
            std::ofstream log_file;
            std::string level_to_string(LogLevel level);
        public:
            Logger(const std::string &filename);
            ~Logger();
            void log(LogLevel level, std::string const &message);
    };
}