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
moodycamel::ConcurrentQueue<Log::logMessage> messageQueue;
std::thread logThread;
bool running;
inline void showMessage(const Log::logMessage &message)
{
    std::tm local_time;
    local_time = *std::localtime(&message.timestamp);

    // std::string time_str = fmt::format("{:%Y-%m-%d %H:%M:%S}", local_time); // 极为愚蠢，不知道为什么报错 call to consteval function 'fmt::basic_format_string<char, tm &>::basic_format_string<char[21], 0>' is not a constant expression
    std::ostringstream time_stream;
    time_stream << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");
    std::string time_str = time_stream.str();
    std::string level_str = std::string(magic_enum::enum_name(message.level));
    std::string msg = fmt::format("[{}] [{}] {}: {}", time_str, level_str, message.origin, message.message);
    switch (message.level)
    {
    case Log::Level::DEBUG:
        fmt::print(fmt::fg(fmt::color::gray), "{}\n", msg);
        break;
    case Log::Level::INFO:
        fmt::print(fmt::fg(fmt::color::white), "{}\n", msg);
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
inline void saveMessage(const Log::logMessage &message)
{
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
    messageQueue.enqueue(message);
}

void Log::LogManager::logMain()
{
    logMessage message;
    while (running)
    {
        if (!messageQueue.try_dequeue(message))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep to avoid busy waiting
            continue;
        }
        showMessage(message);
    }
}
