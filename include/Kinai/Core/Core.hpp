#pragma once

#include "Kinai/Platform/Platform.hpp"
#include "Kinai/Math/Math.hpp"

#include <SDL3/SDL.h>

#include <array>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <csignal>
#include <cstddef>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <utility>
#include <vector>

#define BIT(x) (1 << x)
#define KN_EXPAND_MACRO(x) x
#define KN_STRINGIFY(x) #x
#define KN_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#if defined(KINAI_DEBUG)
	#define KINAI_BUILD "Debug"
	#ifndef KINAI_PROFILER
		#define KINAI_PROFILER 1
	#endif
#elif defined(KINAI_DEV)
	#define KINAI_BUILD "Dev"
#elif defined(KINAI_RELEASE)
	#define KINAI_BUILD "Release"
#else
	#warning "Unknown build! Define KINAI_DEBUG, KINAI_DEV or KINAI_RELEASE"
#endif

#if defined(KINAI_PROFILER) && defined(KINAI_DEBUG)
	#define KN_PROFILE_FUNC() printf("%s at '%s:%d'\n", __PRETTY_FUNCTION__, __FILE__, __LINE__);
#else
	#define KN_PROFILE_FUNC()
#endif

#if defined(KINAI_DEBUG) || defined(KINAI_DEV)
	#define KN_ENABLE_ASSERTS
	#define KN_DEBUG_STATS
#endif

#define KN_PRAGMA(x) _Pragma(#x)
#if defined(__clang__) || defined(__GNUC__)
	#define KN_INLINE		inline __attribute__((__always_inline__))
	#define KN_NEVER_INLINE	__attribute__((__noinline__))
	#define KN_NORETURN		__attribute__ ((noreturn))
	#define KN_UNUSED		__attribute__ ((unused))
	#define KN_NOTUSED(x)	((void)(x))
	#define KN_NODISCARD	[[nodiscard]]
	#define KN_PRINTF_LIKE(fmt, arg) __attribute__((format(printf, fmt, arg)))
#else
	#define KN_INLINE		inline
	#define KN_NEVER_INLINE
	#define KN_NORETURN
	#define KN_UNUSED
	#define KN_NOTUSED(x)
	#define KN_NODISCARD
	#define KN_UNROLL(n)
#endif // defined(__clang__) || defined(__GNUC__)

#if defined(__clang__)
	#define KN_UNROLL(n) KN_PRAGMA(clang loop unroll_count(n))
#elif defined(__GNUC__)
	#define KN_UNROLL(n) KN_PRAGMA(GCC unroll n)
#endif

namespace Kinai
{

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

} // Kinai

#include "Kinai/Core/Log.hpp"
#include "Kinai/Core/Assert.hpp"
