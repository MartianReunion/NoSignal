#pragma once
#include <ctime>
#include <thread>
#include <string>
namespace Log
{
    enum class Level
    {
        DEBUG = 0,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };
    struct logMessage
    {
        std::string origin = "unknown"; // Default origin
        std::string message = "";
        Level level = Level::INFO;
        std::time_t timestamp = std::time(nullptr);
    };
    namespace LogManager
    {
        bool isRunning();
        void start();
        void stop();
        void log(const logMessage message);
        void logMain();
        
    }
}