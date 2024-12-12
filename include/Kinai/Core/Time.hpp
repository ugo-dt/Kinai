#pragma once

#include "Kinai/Core/Core.hpp"

struct Time
{
	uint64_t	fps;
	uint64_t	frames;
	uint64_t	last;
	uint64_t	last_second;
	float		frame_time;
	float		delta;
};
