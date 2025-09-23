#include "Kinai/Renderer/Framebuffer.hpp"

#include "Kinai/Platform/Headless/HeadlessFramebuffer.hpp"
#include "Kinai/Platform/OpenGL/OpenGLFramebuffer.hpp"

namespace Kinai
{

Ref<Framebuffer> Framebuffer::Create(const FramebufferConfig& config)
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateScope<HeadlessFramebuffer>(config);
#elif defined(KINAI_OPENGL)
	return CreateScope<OpenGLFramebuffer>(config);
#endif

	Log::Critical("Unknown RendererAPI");
	return nullptr;
}

} // Kinai
