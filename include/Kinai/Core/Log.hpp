#pragma once

#include "Kinai/Core/Core.hpp"
#include <format>
#include <glm/gtx/string_cast.hpp>

namespace Kinai
{

static constexpr char COLOR_DEFAULT[]	= "\033[39m";
static constexpr char COLOR_RED[]		= "\033[91m";
static constexpr char COLOR_GREEN[]		= "\033[92m";
static constexpr char COLOR_YELLOW[]	= "\033[93m";
static constexpr char COLOR_BLUE[]		= "\033[94m";
static constexpr char COLOR_MAGENTA[]	= "\033[95m";
static constexpr char COLOR_CYAN[]		= "\033[96m";
static constexpr char COLOR_WHITE[]		= "\033[97m";

class Log
{
public:
	static void	Init();

	template <class... Args>
	static void	Trace(std::string_view fmt, Args&&... args);

	template <class... Args>
	static void	Info(std::string_view fmt, Args&&... args);

	template <class... Args>
	static void	Warn(std::string_view fmt, Args&&... args);

	template <class... Args>
	static void	Error(std::string_view fmt, Args&&... args);

	template <class... Args>
	static void	Critical(std::string_view fmt, Args&&... args);

private:
	template <typename OStream>
	static void	Print(OStream& stream, const char *color, const char *log_name, std::string_view fmt, std::format_args args, const std::string_view& end = "\n");

private:
	static std::vector<std::ostream*>	_output_streams;
	static std::vector<std::ostream*>	_error_streams;
};

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

template <typename OStream>
inline void
Log::Print(OStream& stream, const char *color, const char *log_name, std::string_view fmt, std::format_args args, const std::string_view& end)
{
	if (fmt.empty())
		return;

	// Enable colors only when using a terminal output.
#ifdef KN_PLATFORM_DESKTOP
	bool tty = isatty(STDOUT_FILENO);
#else
	bool tty = false;
#endif

	if (tty)
		stream << color;
	stream << "[" << log_name << "] ";
	if (tty)
		stream << COLOR_DEFAULT;
	stream << std::vformat(fmt, args) << end;
}

template <class... Args>
inline void
Log::Trace(std::string_view fmt, Args&&... args)
{
	for (auto stream : _output_streams)
		Log::Print(*stream, COLOR_BLUE, "TRACE", fmt, std::make_format_args(args...));
}

template <class... Args>
inline void
Log::Info(std::string_view fmt, Args&&... args)
{
	for (auto stream : _output_streams)
		Log::Print(*stream, COLOR_WHITE, "INFO", fmt, std::make_format_args(args...));
}

template <>
inline void
Log::Info(std::string_view fmt, const unsigned char*&& arg)
{
	Log::Info(fmt, (const char *)arg);
}

template <class... Args>
inline void
Log::Warn(std::string_view fmt, Args&&... args)
{
	for (auto stream : _error_streams)
		Log::Print(*stream, COLOR_YELLOW, "WARN", fmt, std::make_format_args(args...));
}

template <class... Args>
inline void
Log::Error(std::string_view fmt, Args&&... args)
{
	for (auto stream : _error_streams)
		Log::Print(*stream, COLOR_RED, "ERROR", fmt, std::make_format_args(args...));
}

template <class... Args>
inline void
Log::Critical(std::string_view fmt, Args&&... args)
{
	for (auto stream : _error_streams)
		Log::Print(*stream, COLOR_RED, "CRITICAL", fmt, std::make_format_args(args...));
}

} // Kinai
