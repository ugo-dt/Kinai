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

	void	AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
	void	SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
	
	const std::vector<std::shared_ptr<VertexBuffer>>&	GetVertexBuffers() const override { return _vertex_buffers; }
	const std::shared_ptr<IndexBuffer>&					GetIndexBuffer()   const override { return _index_buffer; }

private:
	std::vector<std::shared_ptr<VertexBuffer>>	_vertex_buffers;
	std::shared_ptr<IndexBuffer>				_index_buffer;
};

} // Kinai
