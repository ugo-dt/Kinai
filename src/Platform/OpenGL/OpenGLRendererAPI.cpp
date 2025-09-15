#include "Kinai/Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Kinai
{

#ifdef KN_PLATFORM_DESKTOP
void	OpenGLMessageCallback(
	unsigned source,
	unsigned type,
	unsigned id,
	unsigned severity,
	int length,
	const char* message,
	const void* userParam)
{
	KN_NOTUSED(source);
	KN_NOTUSED(type);
	KN_NOTUSED(id);
	KN_NOTUSED(length);
	KN_NOTUSED(userParam);
	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:         Log::Error("{}", message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       Log::Warn("{}", message); return;
		case GL_DEBUG_SEVERITY_LOW:
		case GL_DEBUG_SEVERITY_NOTIFICATION: Log::Info("{}", message); return;
	}

	KN_ASSERT(false, "Unknown severity level!");
}
#endif

void	OpenGLRendererAPI::Init()
{
	KN_PRINT_FUNC();

#if defined(KINAI_DEV) && KN_OPENGL_VERSION_MAJOR >= 4
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(OpenGLMessageCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glDisable(GL_BLEND);
	glDisable(GL_STENCIL_TEST);

#ifdef KN_PLATFORM_DESKTOP
	glEnable(GL_LINE_SMOOTH);
#endif

	_KN_GL_CHECK_ERROR();
}

void	OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void	OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void	OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void	OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
{
	vertexArray->Bind();
	uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void	OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
{
	vertexArray->Bind();
	glDrawArrays(GL_LINES, 0, vertexCount);
}

void	OpenGLRendererAPI::DrawTriangles(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
{
	vertexArray->Bind();
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void	OpenGLRendererAPI::SetLineWidth(float width)
{
	glLineWidth(width);
}

void	OpenGLRendererAPI::SetPolygonMode(PolygonMode mode)
{
#if defined(KN_PLATFORM_DESKTOP)
	GLenum	glMode;

	switch (mode)
	{
		case PolygonMode::Fill:  glMode = GL_FILL; break;
		case PolygonMode::Line:  glMode = GL_LINE; break;
		case PolygonMode::Point: glMode = GL_POINT; break;
	}
	glPolygonMode(GL_FRONT_AND_BACK, glMode);
	_KN_GL_CHECK_ERROR();
#else
	KN_NOTUSED(mode);
	Log::Warn("glPolygonMode is not supported on OpenGL ES.");
#endif
}

} // Kinai
