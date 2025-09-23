#include "Kinai/Platform/OpenGL/OpenGLRendererAPI.hpp"
#include "Kinai/Renderer/Pipeline.hpp"

namespace Kinai
{

static GLenum	GetOpenGLPrimitiveType(PrimitiveType type)
{
	switch (type)
	{
		case PrimitiveType::Points:        return GL_POINTS;
		case PrimitiveType::Lines:         return GL_LINES;
		case PrimitiveType::LineStrip:     return GL_LINE_STRIP;
		case PrimitiveType::Triangles:     return GL_TRIANGLES;
		case PrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
	}

	Log::Critical("Unknown PrimitiveType!");
	return 0;
}

GLenum	IndexTypeToGLenum(IndexType type)
{
	switch (type)
	{
		case IndexType::None:   return 0;
		case IndexType::Uint16: return GL_UNSIGNED_SHORT;
		case IndexType::Uint32: return GL_UNSIGNED_INT;
	}

	Log::Critical("Unknown IndexType");
	return 0;
}

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

	Log::Critical("Unknown severity level!");
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

void	OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount)
{
	GLenum glMode = GetOpenGLPrimitiveType(mode);
	GLenum glType = IndexTypeToGLenum(type);

	vertexArray->Bind();
	glDrawElements(glMode, indexCount, glType, nullptr);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLRendererAPI::Draw(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertexCount)
{
	GLenum glMode = GetOpenGLPrimitiveType(mode);

	vertexArray->Bind();
	glDrawArrays(glMode, 0, vertexCount);
	_KN_GL_CHECK_ERROR();
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
	static bool warned = false;
	if (!warned)
	{
		Log::Warn("glPolygonMode is not supported on OpenGL ES.");
		warned = true;
	}
	KN_NOTUSED(mode);
#endif
}

void	OpenGLRendererAPI::BindTexture(uint32_t id, uint32_t slot)
{
#if defined(KN_PLATFORM_DESKTOP) && !defined(KN_PLATFORM_MACOS)
	glBindTextureUnit(slot, id);
#else
	KN_NOTUSED(slot);
	glBindTexture(GL_TEXTURE_2D, id);
#endif
	_KN_GL_CHECK_ERROR();
}

} // Kinai
