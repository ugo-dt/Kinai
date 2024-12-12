#include "Kinai/Renderer/RendererAPI.hpp"

#include "Kinai/Platform/Headless/HeadlessRendererAPI.hpp"
#include "Kinai/Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Kinai
{

std::unique_ptr<RendererAPI>	RendererAPI::Create()
{
	KN_PRINT_FUNC();

#if defined(KN_HEADLESS)
	return std::make_unique<HeadlessRendererAPI>();
#elif defined(KN_OPENGL)
	return std::make_unique<OpenGLRendererAPI>();
#endif

	KN_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

} // Kinai
