#include "logger.hpp"
#include <ctime>
#include <stdexcept>
void Log::Logger::log(std::string message, Level level) const
{
    Log::logMessage logMsg;
    logMsg.message = std::move(message);
    logMsg.level = level;
    logMsg.origin = name;
    logMsg.timestamp = std::time(nullptr);
    Log::LogManager::log(logMsg);
}