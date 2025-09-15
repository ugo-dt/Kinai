#include "Kinai/Platform/OpenGL/OpenGLBuffer.hpp"

namespace Kinai
{

OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
{
	KN_PRINT_FUNC();

#if KINAI_OPENGL_VERSION_MAJOR >= 4
	glCreateBuffers(1, &_renderer_id);
#else
	glGenBuffers(1, &_renderer_id);
#endif
	glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	_KN_GL_CHECK_ERROR();
}

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* vertices, uint32_t size)
{
	KN_PRINT_FUNC();

#if KINAI_OPENGL_VERSION_MAJOR >= 4
	glCreateBuffers(1, &_renderer_id);
#else
	glGenBuffers(1, &_renderer_id);
#endif
	glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	_KN_GL_CHECK_ERROR();
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	KN_PRINT_FUNC();

	glDeleteBuffers(1, &_renderer_id);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLVertexBuffer::Bind() const
{
	KN_PRINT_FUNC();

	glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLVertexBuffer::Unbind() const
{
	KN_PRINT_FUNC();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
{
	KN_PRINT_FUNC();

	glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	_KN_GL_CHECK_ERROR();
}

/** Index buffer */

OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, uint32_t count)
	: _count(count)
{
	KN_PRINT_FUNC();

#if KINAI_OPENGL_VERSION_MAJOR >= 4
	glCreateBuffers(1, &_renderer_id);
#else
	glGenBuffers(1, &_renderer_id);
#endif

	size_t typeSize = sizeof(uint32_t);
	
	// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
	// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
#ifdef KN_PLATFORM_DESKTOP
	glBindBuffer(GL_ARRAY_BUFFER, _renderer_id);
	glBufferData(GL_ARRAY_BUFFER, count * typeSize, indices, GL_STATIC_DRAW);
#else
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * typeSize, indices, GL_STATIC_DRAW);
#endif
	_KN_GL_CHECK_ERROR();
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	KN_PRINT_FUNC();

	glDeleteBuffers(1, &_renderer_id);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLIndexBuffer::Bind() const
{
	KN_PRINT_FUNC();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _renderer_id);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLIndexBuffer::Unbind() const
{
	KN_PRINT_FUNC();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	_KN_GL_CHECK_ERROR();
}

} // Kinai
