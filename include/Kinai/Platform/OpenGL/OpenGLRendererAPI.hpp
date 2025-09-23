#pragma once

#include "Kinai/Renderer/RendererAPI.hpp"

namespace Kinai
{

GLenum	IndexTypeToGLenum(IndexType type);

class OpenGLRendererAPI : public RendererAPI
{
public:
	void	Init() override;
	void	SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

	void	SetClearColor(const glm::vec4& color) override;
	void	Clear() override;

	void	DrawIndexed(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount = 0) override;
	void	Draw(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertexCount) override;
	
	void	SetLineWidth(float width) override;
	void	SetPolygonMode(PolygonMode mode) override;

	void	BindTexture(uint32_t id, uint32_t slot = 0) override;
};

} // Kinai
