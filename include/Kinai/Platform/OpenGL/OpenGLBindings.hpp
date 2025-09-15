#pragma once

#include "Kinai/Renderer/Bindings.hpp"

namespace Kinai
{

class OpenGLBindings : public Bindings
{
public:
	void	AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
	void	SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

	const Ref<VertexBuffer>& GetVertexBuffer() const override { return _vertex_buffer; }
	const Ref<IndexBuffer>& GetIndexBuffer() const override { return _index_buffer; }

private:
	Ref<VertexBuffer> _vertex_buffer;
	Ref<IndexBuffer> _index_buffer;
};

} // Kinai
