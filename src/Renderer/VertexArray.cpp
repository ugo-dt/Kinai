#include "Kinai/Renderer/VertexArray.hpp"
#include "Kinai/Renderer/Renderer.hpp"

#include "Kinai/Platform/Headless/HeadlessVertexArray.hpp"
#include "Kinai/Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Kinai
{

Ref<VertexArray>	VertexArray::Create()
{
	KN_PRINT_FUNC();

#ifdef KINAI_HEADLESS
	return CreateRef<HeadlessVertexArray>();
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLVertexArray>();
#endif

	KN_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

} // Kinai
