#pragma once

#include "Kinai/Renderer/RendererAPI.hpp"
#include "Kinai/Renderer/Pipeline.hpp"
#include "Kinai/Renderer/Bindings.hpp"

namespace Kinai
{

GLenum	IndexTypeToGLenum(IndexType type);

class OpenGLRendererAPI : public RendererAPI
{
public:
	void Init() override;
	void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

	void SetClearColor(const glm::vec4& color) override;
	void Clear() override;

	void Draw(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertexCount) override;
	void DrawInstanced(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertexCount, uint32_t instanceCount) override;
	void DrawIndexed(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount = 0) override;
	void DrawIndexedInstanced(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount, uint32_t instanceCount) override;

	void SetLineWidth(float width) override;
	void SetPolygonMode(PolygonMode mode) override;

	void BindTexture(uint32_t id, uint32_t slot = 0) override;

	void BeginPass() override;
	void EndPass() override;
	void ApplyPipeline(const Ref<Pipeline>& pipeline) override;
	void ApplyBindings(const Ref<Bindings>& bindings) override;
	void ApplyUniforms(const void* params, size_t size) override;
};

} // Kinai
