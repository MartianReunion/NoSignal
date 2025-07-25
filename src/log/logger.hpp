#pragma once
#include <string>
#include "log/logManager.hpp"
#include <system_error>
namespace Log
{
    class Logger
    {
    public:
        std::string name;
        inline Logger(std::string name = "unknown") : name(name) {}
        inline ~Logger() = default;

        void log(std::string message, Level level) const;

        inline void debug(std::string message) const { log(message, Level::DEBUG); }
        inline void info(std::string message) const { log(message, Level::INFO); }
        inline void success(std::string message) const { log(message, Level::SUCCESS); }
        inline void warning(std::string message) const { log(message, Level::WARNING); }
        inline void error(std::string message) const { log(message, Level::ERROR); }
        inline void fatal(std::string message) const { log(message, Level::FATAL); }

        inline void log(std::error_code ec, Level level) const { log(ec.message(), level); }
        inline void debug(std::error_code ec) const { log(ec, Level::DEBUG); }
        inline void info(std::error_code ec) const { log(ec, Level::INFO); }
        inline void success(std::error_code ec) const { log(ec, Level::SUCCESS); }
        inline void warning(std::error_code ec) const { log(ec, Level::WARNING); }
        inline void error(std::error_code ec) const { log(ec, Level::ERROR); }
        inline void fatal(std::error_code ec) const { log(ec, Level::FATAL); }
        inline void log(std::error_code ec) const
        {
            if (ec)
                log(ec, Level::ERROR);
            else
                log(ec, Level::INFO);
        }
    };
} // namespace Log
