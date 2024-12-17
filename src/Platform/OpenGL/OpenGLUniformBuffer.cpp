#include "Kinai/Platform/OpenGL/OpenGLUniformBuffer.hpp"

namespace Kinai
{

OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding)
{
	glCreateBuffers(1, &_renderer_id);
	glNamedBufferData(_renderer_id, size, nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, binding, _renderer_id);
}

OpenGLUniformBuffer::~OpenGLUniformBuffer()
{
	glDeleteBuffers(1, &_renderer_id);
}

void	OpenGLUniformBuffer::SetData(const void *data, uint32_t size, uint32_t offset = 0)
{
	glNamedBufferSubData(_renderer_id, offset, size, data);
}

} // Kinai
