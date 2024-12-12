#pragma once

#include "Kinai/Core/Core.hpp"

#ifdef EG_ENABLE_ASSERTS
	#define EG_ASSERT(expression, ...) \
		{ if(!(expression)) { \
			::Kinai::Log::Error("Assertion failed: {0}:{1}: {2}", __FILE__, __LINE__, #expression); \
			::Kinai::Log::Error("" __VA_ARGS__); exit(1); }}
#else
	#define EG_ASSERT(expression, ...)
#endif
