#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Buffer/Buffer.hpp"
#include "Kinai/Renderer/Texture.hpp"

namespace Kinai
{

class Bindings
{
public:
	virtual ~Bindings() = default;

	virtual void	AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffer) = 0;
	virtual void	SetIndexBuffer(const Ref<IndexBuffer>& index_buffer) = 0;

	virtual void	AddTexture(const Ref<Texture>& texture) = 0;

	virtual const Ref<VertexBuffer>& GetVertexBuffer() const = 0;
	virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
	virtual const std::vector<Ref<Texture>>& GetTextures() const = 0;

	static Ref<Bindings> Create();
};

} // Kinai
