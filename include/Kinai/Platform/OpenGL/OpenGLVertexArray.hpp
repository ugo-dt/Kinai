#pragma once

#include "Kinai/Renderer/VertexArray.hpp"

namespace Kinai
{

class OpenGLVertexArray : public VertexArray
{
public:
	OpenGLVertexArray();
	~OpenGLVertexArray();

	void	Bind() const override;
	void	Unbind() const override;

	void	AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
	void	SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

	const std::vector<std::shared_ptr<VertexBuffer>>&	GetVertexBuffers() const override { return _vertex_buffers; }
	const std::shared_ptr<IndexBuffer>&					GetIndexBuffer()   const override { return _index_buffer; }

private:
	uint32_t _renderer_id;
	uint32_t _vertex_buffer_index = 0;
	std::vector<std::shared_ptr<VertexBuffer>> _vertex_buffers;
	std::shared_ptr<IndexBuffer> _index_buffer;
};

} // Kinai
