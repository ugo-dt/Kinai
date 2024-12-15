#include "Kinai/Renderer/Buffer/BufferLayout.hpp"
#include "Kinai/Renderer/Buffer/IndexBuffer.hpp"
#include "Kinai/Renderer/Buffer/VertexBuffer.hpp"
#include "Kinai/Renderer/Renderer.hpp"

#if defined(KINAI_HEADLESS)
#include "Kinai/Platform/Headless/HeadlessBuffer.hpp"
#elif defined(KINAI_OPENGL)
#include "Kinai/Platform/OpenGL/OpenGLBuffer.hpp"
#endif

namespace Kinai
{

std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	return std::make_shared<HeadlessVertexBuffer>(size);
#elif defined(KINAI_OPENGL)
	return std::make_shared<OpenGLVertexBuffer>(size);
#endif

	KN_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* vertices, uint32_t size)
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	return std::make_shared<HeadlessVertexBuffer>(vertices, size);
#elif defined(KINAI_OPENGL)
	return std::make_shared<OpenGLVertexBuffer>(vertices, size);
#endif

	KN_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t* indices, uint32_t count)
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	return std::make_shared<HeadlessIndexBuffer>(indices, count);
#elif defined(KINAI_OPENGL)
	return std::make_shared<OpenGLIndexBuffer>(indices, count);
#endif

	KN_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

} // Kinai
