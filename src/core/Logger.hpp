#pragma once
#include <spdlog/spdlog.h>
#include <memory>

namespace edge {

/**
 * @class Logger
 * @brief A static wrapper class for the spdlog logging system.
 * 
 * This class initializes and holds the reference to the core application logger.
 */
class Logger {
public:
    /**
     * @brief Initializes the logging system.
     * 
     * Sets up the log patterns and creates the logger sinks.
     */
    static void Init();

    /**
     * @brief Retrieves the core logger instance.
     * 
     * @return std::shared_ptr<spdlog::logger>& Reference to the core logger.
     */
    static std::shared_ptr<spdlog::logger>& GetCoreLogger();

private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
};

}// namespace edge

// Core logging macros
#define EDGE_TRACE(...) ::edge::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define EDGE_INFO(...)     ::edge::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define EDGE_WARN(...)     ::edge::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define EDGE_ERROR(...)    ::edge::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define EDGE_CRITICAL(...) ::edge::Logger::GetCoreLogger()->critical(__VA_ARGS__)