#include <Logger.h>
#include <Core.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <iostream>


namespace Pinni {

Logger& Logger::GetInstance() {
	static Logger instance;
	return instance;
}

Logger::Logger() {
	try {
		// Create logs directory if it doesn't exist
		std::filesystem::path logDir = "logs";
		if (!std::filesystem::exists(logDir)) {
			std::filesystem::create_directory(logDir);
		}

		// Initialize async logging with a thread pool
		spdlog::init_thread_pool(PINNI_LOG_QUEUE_SIZE, 1);	// Queue size, thread count

		// Create sinks
		consoleSink_ = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		fileSink_ = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/pinni.log", true);

		// Set sink levels
		consoleSink_->set_level(spdlog::level::trace);
		fileSink_->set_level(spdlog::level::trace);

		// Create a logger with both sinks and make it async
		std::vector<spdlog::sink_ptr> sinks{consoleSink_, fileSink_};
		logger_ = std::make_shared<spdlog::async_logger>(
			"pinni_logger",
			sinks.begin(),
			sinks.end(),
			spdlog::thread_pool(),
			spdlog::async_overflow_policy::block);

		logger_->set_level(spdlog::level::trace);

		// Set pattern: timestamp [logger name] [level] message
		spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e [%n] [%^%l%$] %v");

		// Register logger
		spdlog::register_logger(logger_);

		// Log initialization success
		logger_->info("Asynchronous logger initialized");
	} catch (const spdlog::spdlog_ex& ex) {
		std::cerr << "Logger initialization failed: " << ex.what() << std::endl;
	}
}

Logger::~Logger() {
	try {
		if (logger_) {
			logger_->info("Logger shutting down");
			Flush();
		}

		// Let spdlog clean up
		spdlog::shutdown();
	} catch (...) {
		std::cerr << "Exception during logger shutdown" << std::endl;
	}
}

void Logger::Flush() {
	if (logger_) {
		logger_->flush();
	}
}

void Logger::EnableConsoleOutput(bool enable) {
	if (consoleSink_) {
		consoleSink_->set_level(enable ? spdlog::level::trace : spdlog::level::off);
	}
}

void Logger::SetLevel(spdlog::level::level_enum level) {
	if (logger_) {
		logger_->set_level(level);
	}
}

}  // namespace Pinni
