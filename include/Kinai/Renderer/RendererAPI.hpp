#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Pipeline.hpp"
#include "Kinai/Renderer/Bindings.hpp"
#include "Kinai/Renderer/VertexArray.hpp"

namespace Kinai
{

enum PolygonMode
{
	Fill,
	Line,
	Point,
};

size_t	IndexTypeSize(IndexType type);

class RendererAPI
{
public:
	enum class API
	{
		None = 0,
		OpenGL = 1,
	};

public:
	virtual ~RendererAPI() = default;

	virtual void Init() = 0;
	virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
	virtual void SetClearColor(const glm::vec4& color) = 0;
	virtual void Clear() = 0;

	virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t index_count) = 0;
	virtual void DrawIndexedInstanced(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount, uint32_t instanceCount) = 0;
	virtual void Draw(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertexCount) = 0;

	virtual void SetLineWidth(float width) = 0;
	virtual void SetPolygonMode(PolygonMode mode) = 0;

	virtual void BindTexture(uint32_t id, uint32_t slot = 0) = 0;

	virtual void BeginPass() = 0;
	virtual void EndPass() = 0;
	virtual void ApplyPipeline(const Ref<Pipeline>& pipeline) = 0;
	virtual void ApplyBindings(const Ref<Bindings>& bindings) = 0;
	virtual void ApplyUniforms(const void* params, size_t size) = 0;

	void	Submit(uint32_t vertexCount);

	static Scope<RendererAPI>	Create();

protected:
	Ref<Pipeline> _current_pipeline = nullptr;
	Ref<Bindings> _current_bindings = nullptr;

#if defined(KN_DEBUG_STATS)
public:
	class Stats
	{
	public:
		static void Reset() { _stats._drawCalls = 0; _stats._vertexCount = 0; }
		static uint64_t GetDrawCalls() { return _stats._drawCalls; }
		static uint64_t GetTotalDrawCalls() { return _stats._totalDrawCalls; }
		static uint64_t GetVertexCount() { return _stats._vertexCount; }
	private:
		friend class RendererAPI;
		uint64_t _drawCalls = 0;
		uint64_t _totalDrawCalls = 0;
		uint64_t _vertexCount = 0;
	};
private:
	static Stats _stats;
#endif
};

} // Kinai
