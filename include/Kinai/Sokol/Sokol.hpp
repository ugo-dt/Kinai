#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Sokol/Types.hpp"

#ifdef __clang__
	#pragma clang diagnostic ignored "-Wc99-designator"
	#pragma clang diagnostic ignored "-Wmissing-field-initializers"
	#pragma clang diagnostic ignored "-Wreorder-init-list"
#endif

#ifdef __GNUC__
	#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

namespace Kinai
{

class Sokol
{
public:
	static void	Init();
	static void	Shutdown();

	static sg_environment	GetEnvironment();
	static sg_swapchain		GetSwapchain();
};

} // Kinai
