#include "Kinai/Renderer/RendererAPI.hpp"

#include "Kinai/Platform/Headless/HeadlessRendererAPI.hpp"
#include "Kinai/Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Kinai
{

Scope<RendererAPI>	RendererAPI::Create()
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateScope<HeadlessRendererAPI>();
#elif defined(KINAI_OPENGL)
	return CreateScope<OpenGLRendererAPI>();
#endif

	KN_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

} // Kinai
