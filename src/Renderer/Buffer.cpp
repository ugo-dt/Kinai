#include "Kinai/Renderer/Buffer/BufferLayout.hpp"
#include "Kinai/Renderer/Buffer/IndexBuffer.hpp"
#include "Kinai/Renderer/Buffer/VertexBuffer.hpp"

#if defined(KINAI_HEADLESS)
	#include "Kinai/Platform/Headless/HeadlessBuffer.hpp"
#elif defined(KINAI_OPENGL)
	#include "Kinai/Platform/OpenGL/OpenGLBuffer.hpp"
#endif

namespace Kinai
{

Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
{
	KN_PROFILE_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateRef<HeadlessVertexBuffer>(size);
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLVertexBuffer>(size);
#endif

	Log::Critical("Unknown RendererAPI");
	return nullptr;
}

Ref<VertexBuffer> VertexBuffer::Create(const void* vertices, uint32_t size)
{
	KN_PROFILE_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateRef<HeadlessVertexBuffer>(vertices, size);
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLVertexBuffer>(vertices, size);
#endif

	Log::Critical("Unknown RendererAPI");
	return nullptr;
}

Ref<IndexBuffer> IndexBuffer::Create(const void* indices, uint32_t count, IndexType type)
{
	KN_PROFILE_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateRef<HeadlessIndexBuffer>(indices, count, type);
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLIndexBuffer>(indices, count, type);
#endif

	Log::Critical("Unknown RendererAPI");
	return nullptr;
}

Ref<IndexBuffer> IndexBuffer::Create(const uint16_t* indices, uint32_t count, IndexType type)
{
	return Create(static_cast<const void*>(indices), count, type);
}
Ref<IndexBuffer> IndexBuffer::Create(const uint32_t* indices, uint32_t count, IndexType type)
{
	return Create(static_cast<const void*>(indices), count, type);
}

} // Kinai
