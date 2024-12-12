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
#define EG_EXPAND_MACRO(x) x
#define EG_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#if defined(EG_DEBUG)
	#define EG_PRINT_FUNC() printf("%s at '%s:%d'\n", __PRETTY_FUNCTION__, __FILE__, __LINE__);
#else
	#define EG_PRINT_FUNC()
#endif

#if defined(EG_DEBUG) || defined(EG_DEV)
	#define EG_ENABLE_ASSERTS
#endif

#if defined(__clang__) || defined(__GNUC__)
	#define EG_INLINE		inline __attribute__((__always_inline__))
	#define EG_NEVER_INLINE	__attribute__((__noinline__))
	#define EG_NORETURN		__attribute__ ((noreturn))
	#define EG_UNUSED		__attribute__ ((unused))
	#define EG_NOTUSED(x)	((void)(x));
	#define EG_NODISCARD	[[nodiscard]]
#else
	#define EG_INLINE		inline
	#define EG_NEVER_INLINE
	#define EG_NORETURN
	#define EG_UNUSED
	#define EG_NOTUSED(x)
	#define EG_NODISCARD
#endif // defined(__clang__) || defined(__GNUC__)

#include "Kinai/Core/Log.hpp"
#include "Kinai/Core/Assert.hpp"
