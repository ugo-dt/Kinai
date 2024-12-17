#include "Kinai/Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Kinai
{

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

OpenGLVertexArray::OpenGLVertexArray()
{
	KN_PRINT_FUNC();

	glCreateVertexArrays(1, &_renderer_id);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	KN_PRINT_FUNC();

	glDeleteVertexArrays(1, &_renderer_id);
}

void	OpenGLVertexArray::Bind() const
{
	KN_PRINT_FUNC();

	glBindVertexArray(_renderer_id);
}

void	OpenGLVertexArray::Unbind() const
{
	KN_PRINT_FUNC();

	glBindVertexArray(0);
}

void	OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
	KN_PRINT_FUNC();

	KN_ASSERT(vertexBuffer->GetLayout().GetElements().size() && "Vertex Buffer has no layout!");

	glBindVertexArray(_renderer_id);
	vertexBuffer->Bind();

	const auto& layout = vertexBuffer->GetLayout();
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
				glEnableVertexAttribArray(_vertex_buffer_index);
				glVertexAttribPointer(_vertex_buffer_index,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.type),
					element.normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.offset);
				_vertex_buffer_index++;
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
				glEnableVertexAttribArray(_vertex_buffer_index);
				glVertexAttribIPointer(_vertex_buffer_index,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.type),
					layout.GetStride(),
					(const void*)element.offset);
				_vertex_buffer_index++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(_vertex_buffer_index);
					glVertexAttribPointer(_vertex_buffer_index,
						count,
						ShaderDataTypeToOpenGLBaseType(element.type),
						element.normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(element.offset + sizeof(float) * count * i));
					glVertexAttribDivisor(_vertex_buffer_index, 1);
					_vertex_buffer_index++;
				}
				break;
			}
			default:
				KN_ASSERT(false, "Unknown ShaderDataType!");
		}
	}

	_vertex_buffers.push_back(vertexBuffer);
}

void	OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
	KN_PRINT_FUNC();

	glBindVertexArray(_renderer_id);
	indexBuffer->Bind();

	_index_buffer = indexBuffer;
}

} // Kinai
