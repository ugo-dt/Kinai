#include "Kinai/Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Kinai
{

OpenGLVertexArray::OpenGLVertexArray()
{
	KN_PROFILE_FUNC();

#if KINAI_OPENGL_VERSION_MAJOR >= 4
	glCreateVertexArrays(1, &_renderer_id);
#else
	glGenVertexArrays(1, &_renderer_id);
#endif
	_KN_GL_CHECK_ERROR();
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	KN_PROFILE_FUNC();

	glDeleteVertexArrays(1, &_renderer_id);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLVertexArray::Bind() const
{
	KN_PROFILE_FUNC();

	glBindVertexArray(_renderer_id);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLVertexArray::Unbind() const
{
	KN_PROFILE_FUNC();

	glBindVertexArray(0);
	_KN_GL_CHECK_ERROR();
}

} // Kinai
