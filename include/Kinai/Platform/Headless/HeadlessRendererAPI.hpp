#pragma once

#include "Kinai/Renderer/RendererAPI.hpp"

namespace Kinai
{

class HeadlessRendererAPI : public RendererAPI
{
public:
	void	Init() override;
	void	SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

	void	SetClearColor(const glm::vec4& color) override;
	void	Clear() override;

	void	DrawIndexed(const Ref<VertexArray>& vertexArray, PrimitiveType type, uint32_t index_count) override;
	void	Draw(const Ref<VertexArray>& vertexArray, PrimitiveType type, uint32_t vertexCount) override;
	
	void	SetLineWidth(float width) override;
};

} // Kinai
