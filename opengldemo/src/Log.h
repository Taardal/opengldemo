#pragma once

#include <spdlog/spdlog.h>

#define TAG typeid(*this).name()
#define TAG_1(type) typeid(type).name()

#define GET_LOG_MESSAGE(tag, message) Demo::Log::GetLogMessage(message, tag, __func__, __LINE__)

#define LOG_TRACE(tag, message, ...) Demo::Log::Trace(GET_LOG_MESSAGE(tag, message), __VA_ARGS__)
#define LOG_DEBUG(tag, message, ...) Demo::Log::Debug(GET_LOG_MESSAGE(tag, message), __VA_ARGS__)
#define LOG_INFO(tag, message, ...) Demo::Log::Info(GET_LOG_MESSAGE(tag, message), __VA_ARGS__)
#define LOG_WARN(tag, message, ...) Demo::Log::Warn(GET_LOG_MESSAGE(tag, message), __VA_ARGS__)
#define LOG_ERROR(tag, message, ...) Demo::Log::Error(GET_LOG_MESSAGE(tag, message), __VA_ARGS__)
#define LOG_CRITICAL(tag, message, ...) Demo::Log::Critical(GET_LOG_MESSAGE(tag, message), __VA_ARGS__)

namespace Demo
{
	enum class LogLevel
	{
		Trace,
		Debug,
		Info,
		Warn,
		Error,
		Critical
	};

	class Log
	{
	private:
		Log() = default;
		~Log() = default;

	public:
		static void SetLevel(LogLevel logLevel);
		static std::string GetLogMessage(const std::string& message, const std::string& tag, const std::string& functionName, int lineNumber);

		template<typename... T>
		static void Trace(const std::string& message, const T& ... args)
		{
			spdlog::trace(message.c_str(), args...);
		}

		template<typename... T>
		static void Debug(const std::string& message, const T& ... args)
		{
			spdlog::debug(message.c_str(), args...);
		}

		template<typename... T>
		static void Info(const std::string& message, const T& ... args)
		{
			spdlog::info(message.c_str(), args...);
		}

		template<typename... T>
		static void lWarn(const std::string& message, const T& ... args)
		{
			spdlog::warn(message.c_str(), args...);
		}

		template<typename... T>
		static void Error(const std::string& message, const T& ... args)
		{
			spdlog::error(message.c_str(), args...);
		}

		template<typename... T>
		static void Critical(const std::string& message, const T& ... args)
		{
			spdlog::critical(message.c_str(), args...);
		}

	private:
		static spdlog::level::level_enum GetSpdLogLevel(LogLevel logLevel);
	};
}