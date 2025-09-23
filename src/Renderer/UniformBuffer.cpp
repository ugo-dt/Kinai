#include "Kinai/Renderer/UniformBuffer.hpp"

#include "Kinai/Platform/Headless/HeadlessUniformBuffer.hpp"
#include "Kinai/Platform/OpenGL/OpenGLUniformBuffer.hpp"

namespace Kinai
{

Ref<UniformBuffer>	UniformBuffer::Create(uint32_t size, uint32_t binding)
{
	KN_PRINT_FUNC();

#ifdef KINAI_HEADLESS
	return CreateRef<HeadlessUniformBuffer>(size, binding);
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLUniformBuffer>(size, binding);
#endif

	Log::Critical("Unknown RendererAPI");
	return nullptr;
}

} // Kinai
