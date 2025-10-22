#pragma once

#include "Kinai/Renderer/RendererAPI.hpp"

namespace Kinai
{

class Renderer
{
public:
	static void	Init();
	static void	SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	static void	SetClearColor(const math::vec4& color);
	static void	SetClearColor(float r, float g, float b, float a);
	static void	SetClearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	static void	Clear();
	static void	Draw(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertex_count);
	static void	DrawIndexed(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount = 0);
	static void DrawInstanced(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertexCount, uint32_t instanceCount);
	static void	DrawIndexedInstanced(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount = 0, uint32_t instanceCount = 1);
	static void	SetLineWidth(float width);
	static void	SetPolygonMode(PolygonMode mode);
	static void	BindTexture(uint32_t renderer_id, uint32_t slot = 0);
	static void BeginPass();
	static void EndPass();
	static void ApplyPipeline(const Ref<Pipeline>& pipeline);
	static void ApplyBindings(const Ref<Bindings>& bindings);
	template <class Tp>
	static void ApplyUniforms(const Tp& params);
	static void Submit(uint32_t vertexCount = 0);
	static void SubmitInstanced(uint32_t instanceCount, uint32_t vertexCount = 0);

private:
	static Scope<RendererAPI>	_renderer_api;
};

template <class Tp>
void Renderer::ApplyUniforms(const Tp& params)
{
	_renderer_api->ApplyUniforms(&params, sizeof(params));
}

} // Kinai