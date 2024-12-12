#include "Kinai/Core/Log.hpp"

namespace Kinai
{

std::vector<std::ostream*>	Log::_output_streams;
std::vector<std::ostream*>	Log::_error_streams;

void	Log::Init()
{
	_output_streams.emplace_back(&std::cout);
	_error_streams.emplace_back(&std::cerr);
}

} // Kinai
