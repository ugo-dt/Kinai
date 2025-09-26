#pragma once

#include "Kinai/Core/Core.hpp"

namespace Kinai
{

class Timer
{
public:
	using Clock = std::chrono::high_resolution_clock;

	Timer() { Reset(); }

	void	Reset()
	{
	#ifdef KINAI_OPENGL
		_start = SDL_GetPerformanceCounter();
	#else
		_start = Clock::now();
	#endif
	}

	float	ElapsedSeconds()
	{
	#ifdef KINAI_OPENGL
		return (SDL_GetPerformanceCounter() - _start) / (float)SDL_GetPerformanceFrequency();
	#else
			return std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - _start).count();
	#endif
	}

	float	ElapsedMS()
	{
	#ifdef KINAI_OPENGL
		return ElapsedSeconds() * 1000.0f;
	#else
		return std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - _start).count();
	#endif
	}

private:
#ifdef KINAI_OPENGL
	uint64_t _start;
#else
	Clock::time_point _start;
#endif
};

} // Kinai
