#include "Kinai/Renderer/RendererAPI.hpp"

#include "Kinai/Platform/Headless/HeadlessRendererAPI.hpp"
#include "Kinai/Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Kinai
{

std::unique_ptr<RendererAPI>	RendererAPI::Create()
{
	EG_PRINT_FUNC();

#if defined(EG_HEADLESS)
	return std::make_unique<HeadlessRendererAPI>();
#elif defined(EG_OPENGL)
	return std::make_unique<OpenGLRendererAPI>();
#endif

	EG_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

} // Kinai
