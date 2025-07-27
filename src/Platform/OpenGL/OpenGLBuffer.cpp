#include "Kinai/Platform/OpenGL/OpenGLBuffer.hpp"

namespace Kinai
{

OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
{
	KN_PRINT_FUNC();

#ifdef __APPLE__
	glGenBuffers(1, &_renderer_id);
#else
	glCreateBuffers(1, &_renderer_id);
#endif
	glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* vertices, uint32_t size)
{
	KN_PRINT_FUNC();

#ifdef __APPLE__
	glGenBuffers(1, &_renderer_id);
#else
	glCreateBuffers(1, &_renderer_id);
#endif
	glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	KN_PRINT_FUNC();

	glDeleteBuffers(1, &_renderer_id);
}

void	OpenGLVertexBuffer::Bind() const
{
	KN_PRINT_FUNC();

	glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
}

void	OpenGLVertexBuffer::Unbind() const
{
	KN_PRINT_FUNC();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void	OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
{
	KN_PRINT_FUNC();

	glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

/** Index buffer */

OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, uint32_t count)
	: _count(count)
{
	KN_PRINT_FUNC();

#ifdef __APPLE__
	glGenBuffers(1, &_renderer_id);
#else
	glCreateBuffers(1, &_renderer_id);
#endif
	
	// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
	// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
	glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	KN_PRINT_FUNC();

	glDeleteBuffers(1, &_renderer_id);
}

void	OpenGLIndexBuffer::Bind() const
{
	KN_PRINT_FUNC();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderer_id);
}

void	OpenGLIndexBuffer::Unbind() const
{
	KN_PRINT_FUNC();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // Kinai
