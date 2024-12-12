#pragma once

#include "Kinai/Core/Core.hpp"

#ifdef KN_ENABLE_ASSERTS
	#define KN_ASSERT(expression, ...) \
		{ if(!(expression)) { \
			::Kinai::Log::Error("Assertion failed: {0}:{1}: {2}", __FILE__, __LINE__, #expression); \
			::Kinai::Log::Error("" __VA_ARGS__); exit(1); }}
#else
	#define KN_ASSERT(expression, ...)
#endif
