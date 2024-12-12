#pragma once

// Platform detection using predefined macros
#if defined(_WIN32)
	/* Windows x64/x86 */
	#if defined(_WIN64)
		/* Windows x64  */
		#define EG_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define EG_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define EG_PLATFORM_MACOS
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define EG_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__EMSCRIPTEN__)
	#define EG_PLATFORM_WEB
#elif defined(__linux__)
	#define EG_PLATFORM_LINUX
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

#if defined(EG_PLATFORM_WINDOWS) || defined(EG_PLATFORM_LINUX) || defined(EG_PLATFORM_MACOS)
	#define EG_PLATFORM_DESKTOP
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
#elif defined(EG_PLATFORM_WEB)
	#include <emscripten/emscripten.h>
	#include <emscripten/key_codes.h>
	#include <GLES3/gl3.h>
	#define glCreateBuffers			glGenBuffers
	#define glCreateVertexArrays	glGenVertexArrays
	#define glCreateTextures		glGenTextures
#endif

#if !defined(EG_OPENGL) && !defined(EG_HEADLESS)
# error "Please select a backend by defining EG_OPENGL or EG_HEADLESS"
#endif
