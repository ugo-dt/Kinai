#include "Kinai/Core/Window.hpp"
#include "Kinai/Renderer/Renderer.hpp"

#if defined(EG_HEADLESS)
#include "Kinai/Platform/Headless/HeadlessWindow.hpp"
#elif defined(EG_OPENGL)
	#if defined(EG_PLATFORM_DESKTOP)
		#include "Kinai/Platform/SDL/SDLWindow.hpp"
	#elif defined(EG_PLATFORM_WEB)
		#include "Kinai/Platform/Emscripten/Emscripten.hpp"
	#endif
#endif

namespace Kinai
{

std::unique_ptr<Window>	Window::Create(const WindowProps &props)
{
	EG_PRINT_FUNC();

#if defined(EG_HEADLESS)
		return std::make_unique<HeadlessWindow>(props);
#elif defined(EG_OPENGL)
	#if defined(EG_PLATFORM_DESKTOP)
		return std::make_unique<SDLWindow>(props);
	#elif defined(EG_PLATFORM_WEB)
		return std::make_unique<EmWindow>(props, 0);
	#endif
#endif

	EG_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

} // Kinai
