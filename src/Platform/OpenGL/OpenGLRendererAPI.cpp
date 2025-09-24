#include "Kinai/Platform/OpenGL/OpenGLRendererAPI.hpp"
#include "Kinai/Renderer/Pipeline.hpp"

namespace Kinai
{

static size_t vb_index = 0;

static GLenum	ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
	KN_PROFILE_FUNC();

	switch (type)
	{
		case ShaderDataType::None:		return GL_FLOAT;
		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;
		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Bool:		return GL_BOOL;
		case ShaderDataType::UByte:		return GL_UNSIGNED_BYTE;
		case ShaderDataType::UByte2:	return GL_UNSIGNED_BYTE;
		case ShaderDataType::UByte3:	return GL_UNSIGNED_BYTE;
		case ShaderDataType::UByte4:	return GL_UNSIGNED_BYTE;
		case ShaderDataType::UInt:		return GL_UNSIGNED_INT;
		case ShaderDataType::UInt2:		return GL_UNSIGNED_INT;
		case ShaderDataType::UInt3:		return GL_UNSIGNED_INT;
		case ShaderDataType::UInt4:		return GL_UNSIGNED_INT;
	}

	Log::Critical("Unknown ShaderDataType!");
}

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
	KN_PROFILE_FUNC();

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
	KN_PROFILE_FUNC();
	glViewport(x, y, width, height);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	KN_PROFILE_FUNC();
	glClearColor(color.r, color.g, color.b, color.a);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLRendererAPI::Clear()
{
	KN_PROFILE_FUNC();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount)
{
	KN_PROFILE_FUNC();
	GLenum glMode = GetOpenGLPrimitiveType(mode);
	GLenum glType = IndexTypeToGLenum(type);

	vertexArray->Bind();
	glDrawElements(glMode, indexCount, glType, nullptr);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLRendererAPI::DrawIndexedInstanced(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount, uint32_t instanceCount)
{
	KN_PROFILE_FUNC();
	GLenum glMode = GetOpenGLPrimitiveType(mode);
	GLenum glType = IndexTypeToGLenum(type);

	vertexArray->Bind();
	glDrawElementsInstanced(glMode, indexCount, glType, nullptr, instanceCount);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLRendererAPI::DrawInstanced(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertexCount, uint32_t instanceCount)
{
	KN_PROFILE_FUNC();
	GLenum glMode = GetOpenGLPrimitiveType(mode);

	vertexArray->Bind();
	glDrawArraysInstanced(glMode, 0, vertexCount, instanceCount);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLRendererAPI::Draw(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertexCount)
{
	KN_PROFILE_FUNC();
	GLenum glMode = GetOpenGLPrimitiveType(mode);

	vertexArray->Bind();
	glDrawArrays(glMode, 0, vertexCount);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLRendererAPI::SetLineWidth(float width)
{
	KN_PROFILE_FUNC();
	glLineWidth(width);
}

void	OpenGLRendererAPI::SetPolygonMode(PolygonMode mode)
{
	KN_PROFILE_FUNC();
#if defined(KN_PLATFORM_DESKTOP)
	GLenum	glMode;

	switch (mode)
	{
		case PolygonMode::Fill:  glMode = GL_FILL; break;
		case PolygonMode::Line:  glMode = GL_LINE; break;
		case PolygonMode::Point: glMode = GL_POINT; break;
	}
	glPolygonMode(GL_FRONT_AND_BACK, glMode);
#else
	static bool warned = false;
	if (!warned)
	{
		Log::Warn("glPolygonMode is not supported on OpenGL ES.");
		warned = true;
	}
	KN_NOTUSED(mode);
#endif
	_KN_GL_CHECK_ERROR();
}

void	OpenGLRendererAPI::BindTexture(uint32_t id, uint32_t slot)
{
	KN_PROFILE_FUNC();
#if defined(KN_PLATFORM_DESKTOP) && !defined(KN_PLATFORM_MACOS)
	glBindTextureUnit(slot, id);
#else
	KN_NOTUSED(slot);
	glBindTexture(GL_TEXTURE_2D, id);
#endif
	_KN_GL_CHECK_ERROR();
}

void OpenGLRendererAPI::BeginPass()
{
	KN_PROFILE_FUNC();
	_KN_GL_CHECK_ERROR();
}

void	OpenGLRendererAPI::EndPass()
{
	KN_PROFILE_FUNC();

	if (_current_pipeline)
	{
		if (_current_pipeline->GetShader())
			_current_pipeline->GetShader()->Unbind();
		_current_pipeline->GetVertexArray()->Unbind();
		_current_pipeline.reset();
	}

	if (_current_bindings)
	{
		if (_current_bindings->GetIndexBuffer())
			_current_bindings->GetIndexBuffer()->Unbind();
		_current_bindings.reset();
	}
	vb_index = 0;
}

void	OpenGLRendererAPI::ApplyPipeline(const Ref<Pipeline>& pipeline)
{
	KN_PROFILE_FUNC();

	KN_ASSERT(pipeline != nullptr);
	if (pipeline != _current_pipeline)
	{
		_current_pipeline = pipeline;
		_current_pipeline->GetVertexArray()->Bind();
		_current_pipeline->GetShader()->Bind();

		switch (pipeline->GetCullMode())
		{
			case CullMode::None:			glDisable(GL_CULL_FACE); break;
			case CullMode::Front:			glEnable(GL_CULL_FACE); glCullFace(GL_FRONT); break;
			case CullMode::Back:			glEnable(GL_CULL_FACE); glCullFace(GL_BACK); break;
			case CullMode::FrontAndBack:	glEnable(GL_CULL_FACE); glCullFace(GL_FRONT_AND_BACK); break;
		}
		switch (pipeline->GetFaceWinding())
		{
			case FaceWinding::CCW: glFrontFace(GL_CCW); break;
			case FaceWinding::CW:  glFrontFace(GL_CW); break;
		}
		switch (pipeline->GetDepthState())
		{
			case DepthState::None:         glDisable(GL_DEPTH_TEST); break;
			case DepthState::Less:         glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LESS); break;
			case DepthState::LessEqual:    glEnable(GL_DEPTH_TEST); glDepthFunc(GL_LEQUAL); break;
			case DepthState::Equal:        glEnable(GL_DEPTH_TEST); glDepthFunc(GL_EQUAL); break;
			case DepthState::Greater:      glEnable(GL_DEPTH_TEST); glDepthFunc(GL_GREATER); break;
			case DepthState::GreaterEqual: glEnable(GL_DEPTH_TEST); glDepthFunc(GL_GEQUAL); break;
			case DepthState::Always:       glEnable(GL_DEPTH_TEST); glDepthFunc(GL_ALWAYS); break;
		}
	}
}

void	OpenGLRendererAPI::ApplyBindings(const Ref<Bindings>& bindings)
{
	KN_PROFILE_FUNC();

	KN_ASSERT(bindings != nullptr);

	Log::Validate(_current_pipeline != nullptr, "can't apply bindings: no current rendering pipeline!");
	vb_index = 0;
	if (_current_bindings != bindings)
	{
		_current_bindings = bindings;
		
		const auto& layout = _current_pipeline->GetLayout();
		Log::Validate(layout.GetElements().size(), "{} has no layout!", _current_pipeline->GetLabel());
		
		for (const auto& texture : _current_bindings->GetTextures())
			texture->Bind();

		const auto& vb = _current_bindings->GetVertexBuffer();
		vb->Bind();

		for (const auto& element : layout)
		{
			uint32_t divisor = element.GetDivisor();
			switch (element.type)
			{
				case ShaderDataType::None:
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				{
					glEnableVertexAttribArray(vb_index);
					glVertexAttribPointer(vb_index,
						element.GetComponentCount(),
						ShaderDataTypeToOpenGLBaseType(element.type),
						element.normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)element.offset
					);
					// set divisor (0 -> per-vertex, > 0 -> per-instance)
					glVertexAttribDivisor(vb_index, divisor);
					vb_index++;
					break;
				}
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
				case ShaderDataType::UByte:
				case ShaderDataType::UByte2:
				case ShaderDataType::UByte3:
				case ShaderDataType::UByte4:
				case ShaderDataType::UInt:
				case ShaderDataType::UInt2:
				case ShaderDataType::UInt3:
				case ShaderDataType::UInt4:
				{
					glEnableVertexAttribArray(vb_index);
					glVertexAttribIPointer(vb_index,
						element.GetComponentCount(),
						ShaderDataTypeToOpenGLBaseType(element.type),
						layout.GetStride(),
						(const void*)element.offset
					);
            		glVertexAttribDivisor(vb_index, divisor);
					vb_index++;
					break;
				}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
				{
					uint8_t count = element.GetComponentCount();
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(vb_index);
						glVertexAttribPointer(vb_index,
							count,
							ShaderDataTypeToOpenGLBaseType(element.type),
							element.normalized ? GL_TRUE : GL_FALSE,
							layout.GetStride(),
							(const void*)(element.offset + sizeof(float) * count * i));
						glVertexAttribDivisor(vb_index, divisor ? divisor : 1u);
						vb_index++;
					}
					break;
				}
				default:
					Log::Critical("Unknown ShaderDataType!");
			}
		}
	}
}

void	OpenGLRendererAPI::ApplyUniforms(const void* params, size_t size)
{
	KN_PROFILE_FUNC();

	Log::Validate(_current_pipeline != nullptr, "can't apply uniforms: no current rendering pipeline!");
	Log::Validate(_current_pipeline->GetShader() != nullptr, "can't apply uniforms: no shader in current rendering pipeline!");

	const auto& shd = _current_pipeline->GetShader();
	shd->ApplyUniforms(params, size);
}

} // Kinai
