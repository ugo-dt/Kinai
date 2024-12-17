#include "Kinai/Renderer/VertexArray.hpp"
#include "Kinai/Renderer/Renderer.hpp"

#include "Kinai/Platform/Headless/HeadlessVertexArray.hpp"
#include "Kinai/Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Kinai
{

std::shared_ptr<VertexArray>	VertexArray::Create()
{
	KN_PRINT_FUNC();

#ifdef KINAI_HEADLESS
	return std::make_shared<HeadlessVertexArray>();
#elif defined(KINAI_OPENGL)
	return std::make_shared<OpenGLVertexArray>();
#endif

	KN_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

using VertexArrayRef = std::shared_ptr<VertexArray>;

} // Kinai
