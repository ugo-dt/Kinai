#include "Kinai/Core/Application.hpp"
#include "Kinai/Renderer/Renderer.hpp"
#include "Kinai/Renderer/RenderCommand.hpp"
#include "Kinai/Renderer/2D/Painter.hpp"

namespace Kinai
{

static size_t vb_index = 0;	
Ref<Pipeline>	Renderer::_current_pipeline = nullptr;
Ref<Bindings>	Renderer::_current_bindings = nullptr;

void	Renderer::Init()
{
	KN_PRINT_FUNC();

	RenderCommand::Init();
	Painter::Init();
	_KN_GL_CHECK_ERROR();
}

void	Renderer::Shutdown()
{
	KN_PRINT_FUNC();

	Painter::Shutdown();
}

void	Renderer::BeginPass()
{
	KN_PRINT_FUNC();

	glm::ivec2 size = Kinai::Application::Get().GetWindow().GetSize();
	RenderCommand::SetViewport(0, 0, size.x, size.y);
}

void	Renderer::ApplyPipeline(const Ref<Pipeline>& pipeline)
{
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
	}
}

static GLenum	ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
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

	KN_ASSERT(false, "Unknown ShaderDataType!");
	return 0;
}

void	Renderer::ApplyBindings(const Ref<Bindings>& bindings)
{
	KN_ASSERT(_current_pipeline != nullptr, "No current pipeline!");
	KN_ASSERT(bindings != nullptr);

	vb_index = 0;
	if (_current_bindings != bindings)
	{
		_current_bindings = bindings;
		
		const auto& layout = _current_pipeline->GetLayout();
		KN_ASSERT(layout.GetElements().size(), "{} has no layout!", _current_pipeline->GetLabel());
		
		for (const auto& texture : _current_bindings->GetTextures())
			texture->Bind();

		const auto& vb = _current_bindings->GetVertexBuffer();
		vb->Bind();
		for (const auto& element : layout)
		{
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
						(const void*)element.offset);
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
						(const void*)element.offset);
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
						glVertexAttribDivisor(vb_index, 1);
						vb_index++;
					}
					break;
				}
				default:
					KN_ASSERT(false, "Unknown ShaderDataType!");
			}
		}
	}
}

void	Renderer::EndPass()
{
	KN_PRINT_FUNC();

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

void	Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
	KN_PRINT_FUNC();

	RenderCommand::SetViewport(0, 0, width, height);
	// Renderer2D::UpdateViewport();
}

void	Renderer::Submit(uint32_t vertexCount)
{
	KN_PRINT_FUNC();

	Log::Validate(_current_pipeline != nullptr, "no current rendering pipeline!");
	Log::Validate(_current_bindings != nullptr, "no current bindings!");

	Ref<VertexArray> vao = _current_pipeline->GetVertexArray();
	if (_current_pipeline->GetIndexType() != IndexType::None)
	{
		KN_ASSERT(_current_bindings->GetVertexBuffer() != nullptr, "No vertex buffer set in bindings!");
		KN_ASSERT(_current_bindings->GetIndexBuffer() != nullptr, "No index buffer set in bindings!");
		KN_ASSERT(_current_bindings->GetIndexBuffer()->GetCount() > 0, "Index buffer has no indices!");
		#ifdef KN_ENABLE_ASSERTS
			static bool warned = false;
			if (vertexCount && !warned)
			{
				warned = true;
				Log::Warn("Renderer::Submit(): 'vertexCount' ({}) is unused because an index buffer was provided. This warning is only shown once.", vertexCount);
			}
		#endif

		_current_bindings->GetIndexBuffer()->Bind();
		RenderCommand::DrawIndexed(
			_current_pipeline->GetVertexArray(),
			_current_pipeline->GetPrimitiveType(),
			_current_bindings->GetIndexBuffer()->GetCount()
		);
	}
	else
	{
		RenderCommand::Draw(
			_current_pipeline->GetVertexArray(),
			_current_pipeline->GetPrimitiveType(),
			vertexCount
		);
	}
}

}
