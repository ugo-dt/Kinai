#pragma once

#include "Kinai/Core/Core.hpp"

namespace Kinai
{

class Timer
{
public:
	Timer() { Reset(); }

	void	Reset()
	{
		_start = SDL_GetPerformanceCounter();
	}

	float	ElapsedSeconds()
	{
		return (SDL_GetPerformanceCounter() - _start) / (float)SDL_GetPerformanceFrequency();
	}

	float	ElapsedMS()
	{
		return ElapsedSeconds() * 1000.0f;
	}

private:
	uint64_t	_start;
};

} // Kinai
