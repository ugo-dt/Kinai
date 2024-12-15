#include "Kinai/Renderer/RendererAPI.hpp"

#include "Kinai/Platform/Headless/HeadlessRendererAPI.hpp"
#include "Kinai/Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Kinai
{

std::unique_ptr<RendererAPI>	RendererAPI::Create()
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	return std::make_unique<HeadlessRendererAPI>();
#elif defined(KINAI_OPENGL)
	return std::make_unique<OpenGLRendererAPI>();
#endif

	KN_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

} // Kinai
