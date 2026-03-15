#include "Logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace edge {

    // Initialize the static shared pointer
    std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;

    void Logger::Init() {

        if(spdlog::get("EDGE")) {
            return;
        }

        // Set the global formatting pattern for spdlog.
        // %^   : Start color range (log level color)
        // %Y-%m-%d %H:%M:%S.%e : Date and Time with milliseconds
        // %t   : Thread Identifier
        // %l   : Short log level string
        // %v   : The actual text message
        // %$   : End color range
        spdlog::set_pattern("%^[%Y-%m-%d %H:%M:%S.%e] [%t] [%l] %v%$");

        // Create a multi-threaded standard output color sink named "EDGE"
        s_CoreLogger = spdlog::stdout_color_mt("EDGE");
        s_CoreLogger->set_level(spdlog::level::trace);
    }

    std::shared_ptr<spdlog::logger>& Logger::GetCoreLogger() {
        return s_CoreLogger;
    }

} // namespace edge