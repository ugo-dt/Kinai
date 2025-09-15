#include "Kinai/Platform/OpenGL/OpenGLBindings.hpp"

namespace Kinai
{

void	OpenGLBindings::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
	KN_PRINT_FUNC();

	_vertex_buffer = vertexBuffer;
}

void	OpenGLBindings::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
	KN_PRINT_FUNC();

	_index_buffer = indexBuffer;
}

} // Kinai
