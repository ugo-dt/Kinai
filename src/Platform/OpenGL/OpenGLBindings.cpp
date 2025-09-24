#include "Kinai/Platform/OpenGL/OpenGLBindings.hpp"

namespace Kinai
{

void	OpenGLBindings::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
	KN_PROFILE_FUNC();

	_vertex_buffer = vertexBuffer;
}

void	OpenGLBindings::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
	KN_PROFILE_FUNC();

	_index_buffer = indexBuffer;
}

void	OpenGLBindings::AddTexture(const Ref<Texture>& texture)
{
	KN_PROFILE_FUNC();

	_textures.push_back(texture);
}

} // Kinai
