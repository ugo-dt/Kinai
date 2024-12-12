#include "Kinai/Renderer/VertexArray.hpp"
#include "Kinai/Renderer/Renderer.hpp"

#include "Kinai/Platform/Headless/HeadlessVertexArray.hpp"
#include "Kinai/Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Kinai
{

std::shared_ptr<VertexArray>	VertexArray::Create()
{
	EG_PRINT_FUNC();

#ifdef EG_HEADLESS
	return std::make_shared<HeadlessVertexArray>();
#elif defined(EG_OPENGL)
	return std::make_shared<OpenGLVertexArray>();
#endif

	EG_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

} // Kinai
