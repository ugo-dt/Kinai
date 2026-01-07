#include "Kinai/Core/Log.hpp"

namespace Kinai
{

LogLevel					Log::_level;
std::vector<std::ostream*>	Log::_output_streams;
std::vector<std::ostream*>	Log::_error_streams;

#if __cplusplus >= 202002L
#else
// std::mutex					Log::_mutex;
#endif

void	Log::Init(LogLevel level)
{
	_level = level;
	_output_streams.emplace_back(&std::cout);
	_error_streams.emplace_back(&std::cerr);
}

} // Kinai
