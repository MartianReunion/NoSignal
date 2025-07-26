#include "log/logManager.hpp"
#include <thread>
#include <fmt/format.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <string>
#include <magic_enum/magic_enum.hpp>
#include <concurrentqueue/concurrentqueue.h>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <chrono>
moodycamel::ConcurrentQueue<Log::logMessage> messageQueue;
std::thread logThread;
bool running;
std::fstream logFile;
inline std::string getTimeString(std::time_t &timestamp)
{
    std::tm local_time;
    local_time = *std::localtime(&timestamp);

    // std::string time_str = fmt::format("{:%Y-%m-%d %H:%M:%S}", local_time); // 极为愚蠢，不知道为什么报错 call to consteval function 'fmt::basic_format_string<char, tm &>::basic_format_string<char[21], 0>' is not a constant expression
    std::ostringstream time_stream;
    time_stream << std::put_time(&local_time, "%Y-%m-%d %H.%M.%S");
    return time_stream.str();
}
inline void showMessage(const std::string &msg, const Log::Level level)
{
    switch (level)
    {
    case Log::Level::DEBUG:
        fmt::print(fmt::fg(fmt::color::gray), "{}\n", msg);
        break;
    case Log::Level::INFO:
        fmt::print(fmt::fg(fmt::color::white), "{}\n", msg);
        break;
    case Log::Level::SUCCESS:
        fmt::print(fmt::fg(fmt::color::lime_green), "{}\n", msg);
        break;
    case Log::Level::WARNING:
        fmt::print(fmt::fg(fmt::color::yellow), "{}\n", msg);
        break;
    case Log::Level::ERROR:
        fmt::print(fmt::fg(fmt::color::red), "{}\n", msg);
        break;
    case Log::Level::FATAL:
        fmt::print(fmt::fg(fmt::color::dark_red), "{}\n", msg);
        break;
    default:
        fmt::print(fmt::fg(fmt::color::aqua), "{}\n", msg);
        break;
    }
}
inline void saveMessage(const std::string &msg, const Log::Level level)
{
    logFile << msg << std::endl;
}

bool Log::LogManager::isRunning()
{
    return running;
}

void Log::LogManager::start()
{
    if (!running)
    {
        running = true;
    }
    logThread = std::thread(logMain);
}
void Log::LogManager::stop()
{
    if (running)
    {
        running = false;
    }
    logThread.join();
}

void Log::LogManager::log(const logMessage message)
{
    if (running)
        messageQueue.enqueue(message);
}

void Log::LogManager::logMain()
{
    logMessage message;
    if (!std::filesystem::exists("logs"))
    {
        std::filesystem::create_directory("logs");
    }
    auto now = std::time(nullptr);
    std::string ts = getTimeString(now);
    std::string fileName = "./logs/" + ts + ".log";
    logFile.open(fileName, std::ios::out | std::ios::app);
    if (!logFile)
    {
        messageQueue.enqueue({"LogManager",
                              "Failed to open log file",
                              Level::FATAL,
                              std::time(nullptr)});
        return;
    }
    while (running)
    {
        if (!messageQueue.try_dequeue(message))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep to avoid busy waiting
            continue;
        }
        std::string level_str = std::string(magic_enum::enum_name(message.level));
        std::string time_str = getTimeString(message.timestamp);
        std::string msg = fmt::format("[{}] [{}] {}: {}", time_str, level_str, message.origin, message.message);
        showMessage(msg, message.level);
        saveMessage(msg, message.level);
    }
    logFile.close();
}
