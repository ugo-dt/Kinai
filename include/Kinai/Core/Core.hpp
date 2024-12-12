#pragma once

#include "Kinai/Platform/Platform.hpp"

#include <SDL3/SDL.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_sdl3.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <sokol/sokol_gfx.h>
#include <sokol/sokol_log.h>

#include <algorithm>
#include <cassert>
#include <csignal>
#include <cstddef>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#define BIT(x) (1 << x)
#define KN_EXPAND_MACRO(x) x
#define KN_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#if defined(KN_DEBUG)
	#define KN_PRINT_FUNC() printf("%s at '%s:%d'\n", __PRETTY_FUNCTION__, __FILE__, __LINE__);
#else
	#define KN_PRINT_FUNC()
#endif

#if defined(KN_DEBUG) || defined(KN_DEV)
	#define KN_ENABLE_ASSERTS
#endif

#if defined(__clang__) || defined(__GNUC__)
	#define KN_INLINE		inline __attribute__((__always_inline__))
	#define KN_NEVER_INLINE	__attribute__((__noinline__))
	#define KN_NORETURN		__attribute__ ((noreturn))
	#define KN_UNUSED		__attribute__ ((unused))
	#define KN_NOTUSED(x)	((void)(x));
	#define KN_NODISCARD	[[nodiscard]]
#else
	#define KN_INLINE		inline
	#define KN_NEVER_INLINE
	#define KN_NORETURN
	#define KN_UNUSED
	#define KN_NOTUSED(x)
	#define KN_NODISCARD
#endif // defined(__clang__) || defined(__GNUC__)

#include "Kinai/Core/Log.hpp"
#include "Kinai/Core/Assert.hpp"
