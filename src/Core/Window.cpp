#include "Kinai/Core/Window.hpp"
#include "Kinai/Renderer/Renderer.hpp"

#if defined(KINAI_HEADLESS)
	#include "Kinai/Platform/Headless/HeadlessWindow.hpp"
#elif defined(KINAI_OPENGL)
	#if defined(KN_PLATFORM_DESKTOP)
		#include "Kinai/Platform/SDL/SDLWindow.hpp"
	#elif defined(KN_PLATFORM_WEB)
		#include "Kinai/Platform/Emscripten/Emscripten.hpp"
	#endif
#endif

namespace Kinai
{

Scope<Window>	Window::Create(const WindowProps &props)
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateScope<HeadlessWindow>(props);
#elif defined(KINAI_OPENGL)
	#if defined(KN_PLATFORM_DESKTOP)
		return CreateScope<SDLWindow>(props);
	#elif defined(KN_PLATFORM_WEB)
		return CreateScope<EmWindow>(props, 0);
	#endif
#endif

	KN_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

} // Kinai
