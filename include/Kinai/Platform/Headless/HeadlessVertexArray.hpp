#pragma once

#include "Kinai/Renderer/VertexArray.hpp"

namespace Kinai
{

class HeadlessVertexArray : public VertexArray
{
public:
	HeadlessVertexArray();
	~HeadlessVertexArray();

	void	Bind() const override;
	void	Unbind() const override;

	void	AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
	void	SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
	
	const std::vector<Ref<VertexBuffer>>&	GetVertexBuffers() const override { return _vertex_buffers; }
	const Ref<IndexBuffer>&					GetIndexBuffer()   const override { return _index_buffer; }

private:
	std::vector<Ref<VertexBuffer>>	_vertex_buffers;
	Ref<IndexBuffer>				_index_buffer;
};

} // Kinai
