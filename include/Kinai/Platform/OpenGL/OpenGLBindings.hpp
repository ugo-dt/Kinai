#pragma once

#include "Kinai/Renderer/Bindings.hpp"

namespace Kinai
{

class OpenGLBindings : public Bindings
{
public:
	~OpenGLBindings() = default;

	void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
	void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
	
	void AddTexture(const Ref<Texture>& texture) override;

	const Ref<VertexBuffer>& GetVertexBuffer() const override { return _vertex_buffer; }
	const Ref<IndexBuffer>& GetIndexBuffer() const override { return _index_buffer; }
	const std::vector<Ref<Texture>>& GetTextures() const override { return _textures; }

private:
	Ref<VertexBuffer> _vertex_buffer;
	Ref<IndexBuffer> _index_buffer;
	std::vector<Ref<Texture>> _textures;
};

} // Kinai
