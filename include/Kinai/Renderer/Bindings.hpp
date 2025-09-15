#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Buffer/Buffer.hpp"

namespace Kinai
{

class Bindings
{
public:
	virtual ~Bindings() = default;

	virtual void	AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffer) = 0;
	virtual void	SetIndexBuffer(const Ref<IndexBuffer>& index_buffer) = 0;

	virtual const Ref<VertexBuffer>& GetVertexBuffer() const = 0;
	virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

	static Ref<Bindings> Create();
};

} // Kinai
