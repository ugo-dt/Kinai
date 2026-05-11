#pragma once

// Platform detection using predefined macros
#if defined(_WIN32)
	/* Windows x64/x86 */
	#if defined(_WIN64)
		/* Windows x64  */
		#define KN_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__EMSCRIPTEN__)
	#define KN_PLATFORM_WEB
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define KN_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define KN_PLATFORM_MACOS
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__linux__)
	#define KN_PLATFORM_LINUX
#elif defined(__ANDROID__)
	#define KN_PLATFORM_ANDROID
	#error "Android is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

#if defined(KN_PLATFORM_WINDOWS) || defined(KN_PLATFORM_LINUX) || defined(KN_PLATFORM_MACOS)
	#define KN_PLATFORM_DESKTOP 
	#define KINAI_HAS_THREADS 1
	#include <glad/glad.h>
	#if defined(_WIN32)
		#define WIN32_MEAN_AND_LEAN
		#include <windows.h>
		#include <direct.h>
	#elif defined(__APPLE__)
		#include <OpenGL/gl.h>
		#include <OpenGL/glu.h>
		#include <curses.h>
	#else
		#include <GL/gl.h>
		#include <GL/glu.h>
	#endif
#elif defined(KN_PLATFORM_WEB)
	#include <emscripten/emscripten.h>
	#include <emscripten/html5.h>
	#include <emscripten/key_codes.h>
	#include <GLES3/gl3.h>
#endif

#if defined(KINAI_OPENGL)
	#ifndef KINAI_OPENGL_VERSION_MAJOR
		#if defined(KN_PLATFORM_WEB)
			#define KINAI_OPENGL_VERSION_MAJOR 3
			#define KN_GL_VERSION 300
		#else
			#define KINAI_OPENGL_VERSION_MAJOR 4
			#define KN_GL_VERSION 410
		#endif
	#endif
	#ifndef KINAI_OPENGL_VERSION_MINOR
		#if defined(KN_PLATFORM_WEB)
			#define KINAI_OPENGL_VERSION_MINOR 0
		#elif defined(KN_PLATFORM_MACOS)
			#define KINAI_OPENGL_VERSION_MINOR 1
		#else
			#define KINAI_OPENGL_VERSION_MINOR 5
		#endif
	#endif

	// direct state access is only available in OpenGL 4.5 and above
	#if KINAI_OPENGL_VERSION_MAJOR >= 4 && KINAI_OPENGL_VERSION_MINOR >= 5
		#define KN_GL_HAS_DSA 1
	#else
		#define KN_GL_HAS_DSA 0
	#endif
	#include <imgui/backends/imgui_impl_sdl3.h>
	#include <imgui/backends/imgui_impl_opengl3.h>
#endif

#if !defined(KINAI_OPENGL) && !defined(KINAI_HEADLESS)
# error "Please select a backend by defining KINAI_OPENGL or KINAI_HEADLESS"
#endif
