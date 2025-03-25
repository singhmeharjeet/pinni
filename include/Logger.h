#pragma once

#include <memory>
#include <string>

#include <spdlog/spdlog.h>
#include <spdlog/async.h>

namespace Pinni {

/**
 * @brief An asynchronous logger wrapper around spdlog
 */
class Logger {
public:
    // Get singleton instance
    static Logger& GetInstance();

    // Different log levels with variadic template arguments for formatting
    template<typename... Args>
    void Trace(fmt::format_string<Args...> fmt, Args&&... args) {
        logger_->trace(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Debug(fmt::format_string<Args...> fmt, Args&&... args) {
        logger_->debug(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Info(fmt::format_string<Args...> fmt, Args&&... args) {
        logger_->info(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Warn(fmt::format_string<Args...> fmt, Args&&... args) {
        logger_->warn(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Error(fmt::format_string<Args...> fmt, Args&&... args) {
        logger_->error(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void Critical(fmt::format_string<Args...> fmt, Args&&... args) {
        logger_->critical(fmt, std::forward<Args>(args)...);
    }

    // For backward compatibility - uses info level
    template<typename T>
    void Log(T&& message) {
        logger_->info(std::forward<T>(message));
    }

    // Additional control functions
    void Flush();
    void EnableConsoleOutput(bool enable);
    void SetLevel(spdlog::level::level_enum level);

    ~Logger();

private:
    Logger();

    std::shared_ptr<spdlog::logger> logger_;
    std::shared_ptr<spdlog::sinks::sink> consoleSink_;
    std::shared_ptr<spdlog::sinks::sink> fileSink_;

    // Non-copyable
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

}  // namespace Pinni
