#pragma once

#include "Kinai/Core/Core.hpp"
#include <fmt/format.h>

namespace Kinai
{

enum LogLevel
{
	Trace = 0,
	Info = 1,
	Warn = 2,
	Error = 3,
	Critical = 4,
	Off = 5
};

}

#ifndef KINAI_LOG_LEVEL
	#if defined(KINAI_DEBUG)
		#define KINAI_LOG_LEVEL LogLevel::Trace
	#elif defined(KINAI_DEV)
		#define KINAI_LOG_LEVEL LogLevel::Info
	#else
		#define KINAI_LOG_LEVEL LogLevel::Warn
	#endif
#endif

// #if __cplusplus >= 202002L

#include <format>
#include <unistd.h>

namespace Kinai
{

static constexpr const char* KN_COLOR_DEFAULT	= "\033[39m";
static constexpr const char* KN_COLOR_RED		= "\033[91m";
static constexpr const char* KN_COLOR_GREEN		= "\033[92m";
static constexpr const char* KN_COLOR_YELLOW	= "\033[93m";
static constexpr const char* KN_COLOR_BLUE		= "\033[94m";
static constexpr const char* KN_COLOR_MAGENTA	= "\033[95m";
static constexpr const char* KN_COLOR_CYAN		= "\033[96m";
static constexpr const char* KN_COLOR_WHITE		= "\033[97m";

class Log
{
public:
	static void	Init(LogLevel level = KINAI_LOG_LEVEL);

	static void SetLogLevel(LogLevel level) { _level = level; }
	static LogLevel GetLogLevel() { return _level; }

	template <class... Args>
	static void	Trace(fmt::string_view fmt, Args&&... args);

	template <class... Args>
	static void	Info(fmt::string_view fmt, Args&&... args);

	template <class... Args>
	static void	Warn(fmt::string_view fmt, Args&&... args);

	template <class... Args>
	static void	Error(fmt::string_view fmt, Args&&... args);

	template <class... Args>
	KN_NORETURN static void	Critical(fmt::string_view fmt, Args&&... args);

	template <class... Args>
	static void	Validate(bool condition, fmt::string_view fmt, Args&&... args);

private:
	template <typename OStream>
	static void	Print(OStream& stream, const char* color, const char *log_name, fmt::string_view fmt, fmt::format_args args, const fmt::string_view& end = "\n");

private:
	static LogLevel	_level;
	static std::vector<std::ostream*>	_output_streams;
	static std::vector<std::ostream*>	_error_streams;
};

// template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
// inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
// {
// 	return os << glm::to_string(vector);
// }

// template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
// inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
// {
// 	return os << glm::to_string(matrix);
// }

// template<typename OStream, typename T, glm::qualifier Q>
// inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
// {
// 	return os << glm::to_string(quaternion);
// }

template <typename OStream>
inline void
Log::Print(OStream& stream, const char* color, const char *log_name, fmt::string_view fmt, fmt::format_args args, const fmt::string_view& end)
{
	if (fmt.size() == 0)
		return;

#ifdef KN_PLATFORM_DESKTOP
	// Enable colors only when using a terminal output.
	bool tty = isatty(STDOUT_FILENO);
#else
	bool tty = false;
#endif

	if (tty)
		stream << color;
	stream << "[Kinai]" << "[" << log_name << "] ";
	if (tty)
		stream << KN_COLOR_DEFAULT;
	stream << fmt::vformat(fmt, args) << end.data();
}

template <class... Args>
inline void
Log::Trace(fmt::string_view fmt, Args&&... args)
{
	if (_level <= LogLevel::Trace)
		for (auto stream : _output_streams)
			Log::Print(*stream, KN_COLOR_BLUE, "TRACE", fmt, fmt::make_format_args(args...));
}

template <class... Args>
inline void
Log::Info(fmt::string_view fmt, Args&&... args)
{
	if (_level <= LogLevel::Info)
		for (auto stream : _output_streams)
			Log::Print(*stream, KN_COLOR_WHITE, "INFO", fmt, fmt::make_format_args(args...));
}

template <class... Args>
inline void
Log::Warn(fmt::string_view fmt, Args&&... args)
{
	if (_level <= LogLevel::Warn)
		for (auto stream : _error_streams)
			Log::Print(*stream, KN_COLOR_YELLOW, "WARN", fmt, fmt::make_format_args(args...));
}

template <class... Args>
inline void
Log::Error(fmt::string_view fmt, Args&&... args)
{
	if (_level <= LogLevel::Error)
		for (auto stream : _error_streams)
			Log::Print(*stream, KN_COLOR_RED, "ERROR", fmt, fmt::make_format_args(args...));
}

template <class... Args>
KN_NORETURN inline void
Log::Critical(fmt::string_view fmt, Args&&... args)
{
	if (_level <= LogLevel::Critical)
		for (auto stream : _error_streams)
			Log::Print(*stream, KN_COLOR_RED, "CRITICAL", fmt, fmt::make_format_args(args...));
	// it would be undefined behavior to continue after a critical error
	std::abort();
}

template <class... Args>
inline void
Log::Validate(bool condition, fmt::string_view fmt, Args&&... args)
{
	if (!condition)
		Log::Critical(fmt, std::forward<Args>(args)...);
}

} // Kinai

// #else // if __cplusplus >= 202002L

// #pragma once

// #include "Kinai/Core/Core.hpp"
// #include <cstdarg>
// #include <cstdio>
// #include <unistd.h>
// #include <mutex>

// namespace Kinai
// {

// static constexpr char LOG_COLOR_DEFAULT[]    = "\033[39m";
// static constexpr char LOG_COLOR_RED[]        = "\033[91m";
// static constexpr char LOG_COLOR_GREEN[]      = "\033[92m";
// static constexpr char LOG_COLOR_YELLOW[]     = "\033[93m";
// static constexpr char LOG_COLOR_BLUE[]       = "\033[94m";
// static constexpr char LOG_COLOR_MAGENTA[]    = "\033[95m";
// static constexpr char LOG_COLOR_CYAN[]       = "\033[96m";
// static constexpr char LOG_COLOR_WHITE[]      = "\033[97m";

// class Log
// {
// public:
// 	static void	Init(LogLevel level = KINAI_LOG_LEVEL);

// 	static void Trace(const char* fmt, ...);
// 	static void Info(const char* fmt, ...);
// 	static void Warn(const char* fmt, ...);
// 	static void Error(const char* fmt, ...);
// 	KN_NORETURN static void Critical(const char* fmt, ...);
// 	static void Validate(bool condition, const char* fmt, ...);

// private:
// 	// Helper function for printing formatted log messages
// 	static void Print(FILE* stream, const char* color, const char* log_name, const char* fmt, va_list args, const char* end = "\n");

// private:
// 	static LogLevel	_level;
// 	static std::vector<std::ostream*> _output_streams;
// 	static std::vector<std::ostream*> _error_streams;
// 	static std::mutex _mutex;
// };

// inline void Log::Print(FILE* stream, const char* color, const char* log_name, const char* fmt, va_list args, const char* end)
// {
// 	if (fmt == nullptr || fmt[0] == '\0')
// 		return;

// 	_mutex.lock();
// 	bool tty = isatty(STDOUT_FILENO);

// 	if (tty)
// 		std::fprintf(stream, "%s", color);
// 	std::fprintf(stream, "[%s] ", log_name);
// 	if (tty)
// 		std::fprintf(stream, "%s", LOG_COLOR_DEFAULT);

// 	std::vfprintf(stream, fmt, args);
// 	std::fprintf(stream, "%s", end);
// 	_mutex.unlock();
// }

// inline void Log::Trace(const char* fmt, ...)
// {
// 	if (_level <= LogLevel::Trace)
// 	{
// 		va_list args;
// 		va_start(args, fmt);
// 		Log::Print(stdout, LOG_COLOR_BLUE, "TRACE", fmt, args);
// 		va_end(args);
// 	}
// }

// inline void Log::Info(const char* fmt, ...)
// {
// 	if (_level <= LogLevel::Info)
// 	{
// 		va_list args;
// 		va_start(args, fmt);
// 		Log::Print(stdout, LOG_COLOR_WHITE, "INFO", fmt, args);
// 		va_end(args);
// 	}
// }

// inline void Log::Warn(const char* fmt, ...)
// {
// 	if (_level <= LogLevel::Warn)
// 	{
// 		va_list args;
// 		va_start(args, fmt);
// 		Log::Print(stderr, LOG_COLOR_YELLOW, "WARN", fmt, args);
// 		va_end(args);
// 	}
// }

// inline void Log::Error(const char* fmt, ...)
// {
// 	if (_level <= LogLevel::Error)
// 	{
// 		va_list args;
// 		va_start(args, fmt);
// 		Log::Print(stderr, LOG_COLOR_RED, "ERROR", fmt, args);
// 		va_end(args);
// 	}
// }

// KN_NORETURN inline void Log::Critical(const char* fmt, ...)
// {
// 	if (_level <= LogLevel::Critical)
// 	{
// 		va_list args;
// 		va_start(args, fmt);
// 		Log::Print(stderr, LOG_COLOR_RED, "CRITICAL", fmt, args);
// 		va_end(args);
// 	}
// 	// it would be undefined behavior to continue after a critical error
// 	std::exit(1);
// }

// inline void
// Log::Validate(bool condition, const char* fmt, ...)
// {
// 	if (!condition)
// 	{
// 		// Critical
// 		if (_level <= LogLevel::Critical)
// 		{
// 			va_list args;
// 			va_start(args, fmt);
// 			Log::Print(stderr, LOG_COLOR_RED, "CRITICAL", fmt, args);
// 			va_end(args);
// 		}
// 		// it would be undefined behavior to continue after a critical error
// 		std::exit(1);
// 	}
// }

// } // Kinai

// #endif
