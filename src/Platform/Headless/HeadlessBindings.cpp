#include "Kinai/Platform/Headless/HeadlessBindings.hpp"

namespace Kinai
{

void	HeadlessBindings::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
	KN_PROFILE_FUNC();

	_vertex_buffer = vertexBuffer;
}

void	HeadlessBindings::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
	KN_PROFILE_FUNC();

	_index_buffer = indexBuffer;
}

void	HeadlessBindings::AddTexture(const Ref<Texture>& texture)
{
	KN_PROFILE_FUNC();

	_textures.push_back(texture);
}

} // Kinai
