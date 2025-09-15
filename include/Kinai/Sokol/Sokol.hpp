#pragma once

#include "Kinai/Core/Core.hpp"

#ifdef KINAI_SOKOL

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

#endif // KINAI_SOKOL
