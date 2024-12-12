#include "Kinai/Core/Window.hpp"
#include "Kinai/Renderer/Renderer.hpp"

#if defined(KN_HEADLESS)
#include "Kinai/Platform/Headless/HeadlessWindow.hpp"
#elif defined(KN_OPENGL)
	#if defined(KN_PLATFORM_DESKTOP)
		#include "Kinai/Platform/SDL/SDLWindow.hpp"
	#elif defined(KN_PLATFORM_WEB)
		#include "Kinai/Platform/Emscripten/Emscripten.hpp"
	#endif
#endif

namespace Kinai
{

std::unique_ptr<Window>	Window::Create(const WindowProps &props)
{
	KN_PRINT_FUNC();

#if defined(KN_HEADLESS)
		return std::make_unique<HeadlessWindow>(props);
#elif defined(KN_OPENGL)
	#if defined(KN_PLATFORM_DESKTOP)
		return std::make_unique<SDLWindow>(props);
	#elif defined(KN_PLATFORM_WEB)
		return std::make_unique<EmWindow>(props, 0);
	#endif
#endif

	KN_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

} // Kinai
