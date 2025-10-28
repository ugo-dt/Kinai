#include "Kinai/Platform/Headless/HeadlessRendererAPI.hpp"
#include "Kinai/Renderer/Pipeline.hpp"

namespace Kinai
{

void	HeadlessRendererAPI::Init()
{
	KN_PROFILE_FUNC();
}

void	HeadlessRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(x);
	KN_NOTUSED(y);
	KN_NOTUSED(width);
	KN_NOTUSED(height);
}

void	HeadlessRendererAPI::SetClipRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(x);
	KN_NOTUSED(y);
	KN_NOTUSED(width);
	KN_NOTUSED(height);
}

void	HeadlessRendererAPI::SetClearColor(const math::vec4& color)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(color);
}

void	HeadlessRendererAPI::Clear()
{
	KN_PROFILE_FUNC();
}

void	HeadlessRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(vertexArray);
	KN_NOTUSED(mode);
	KN_NOTUSED(type);
	KN_NOTUSED(indexCount);
}

void	HeadlessRendererAPI::DrawIndexedInstanced(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount, uint32_t instanceCount)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(vertexArray);
	KN_NOTUSED(mode);
	KN_NOTUSED(type);
	KN_NOTUSED(indexCount);
	KN_NOTUSED(instanceCount);
}

void	HeadlessRendererAPI::DrawInstanced(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertexCount, uint32_t instanceCount)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(vertexArray);
	KN_NOTUSED(mode);
	KN_NOTUSED(vertexCount);
	KN_NOTUSED(instanceCount);
}

void	HeadlessRendererAPI::Draw(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertexCount)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(vertexArray);
	KN_NOTUSED(mode);
	KN_NOTUSED(vertexCount);
}

void	HeadlessRendererAPI::SetLineWidth(float width)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(width);
}

void	HeadlessRendererAPI::SetPolygonMode(PolygonMode mode)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(mode);
}

void	HeadlessRendererAPI::BindTexture(uint32_t id, uint32_t slot)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(id);
	KN_NOTUSED(slot);
}

void HeadlessRendererAPI::BeginPass()
{
	KN_PROFILE_FUNC();
}

void	HeadlessRendererAPI::EndPass()
{
	KN_PROFILE_FUNC();

	_current_bindings.reset();
	_current_pipeline.reset();
}

void	HeadlessRendererAPI::ApplyPipeline(const Ref<Pipeline>& pipeline)
{
	KN_PROFILE_FUNC();

	KN_ASSERT(pipeline != nullptr);
	_current_pipeline = pipeline;
}

void	HeadlessRendererAPI::ApplyBindings(const Ref<Bindings>& bindings)
{
	KN_PROFILE_FUNC();

	KN_ASSERT(bindings != nullptr);
	_current_bindings = bindings;
}

void	HeadlessRendererAPI::ApplyUniforms(const void* params, size_t size)
{
	KN_PROFILE_FUNC();
	KN_NOTUSED(params);
	KN_NOTUSED(size);
}

} // Kinai
