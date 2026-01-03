#include "Kinai/Platform/OpenGL/OpenGLUniformBuffer.hpp"

namespace Kinai
{

#if defined(KN_PLATFORM_DESKTOP) && !defined(KN_PLATFORM_MACOS)

OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding)
{
#ifdef KN_PLATFORM_MACOS
	glGenBuffers(1, &_renderer_id);
	glBindBuffer(GL_UNIFORM_BUFFER, _renderer_id);
	glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, binding, _renderer_id);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
#else
	glCreateBuffers(1, &_renderer_id);
	glNamedBufferData(_renderer_id, size, nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, binding, _renderer_id);
#endif
	_KN_GL_CHECK_ERROR();
}

OpenGLUniformBuffer::~OpenGLUniformBuffer()
{
	glDeleteBuffers(1, &_renderer_id);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLUniformBuffer::SetData(const void *data, uint32_t size, uint32_t offset = 0)
{
	glNamedBufferSubData(_renderer_id, offset, size, data);
	_KN_GL_CHECK_ERROR();
}

#else

OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding)
{
	glGenBuffers(1, &_renderer_id);
	glBindBuffer(GL_UNIFORM_BUFFER, _renderer_id);
	glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, binding, _renderer_id);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	_KN_GL_CHECK_ERROR();
}

OpenGLUniformBuffer::~OpenGLUniformBuffer()
{
	glDeleteBuffers(1, &_renderer_id);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLUniformBuffer::SetData(const void *data, uint32_t size, uint32_t offset)
{
	glBindBuffer(GL_UNIFORM_BUFFER, _renderer_id);
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	_KN_GL_CHECK_ERROR();
}

#endif // KN_PLATFORM_DESKTOP

} // Kinai
