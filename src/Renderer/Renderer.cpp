#include "Kinai/Renderer/Renderer.hpp"
#include "Kinai/Core/Application.hpp"

namespace Kinai
{

Scope<RendererAPI>	Renderer::_renderer_api = RendererAPI::Create();

void	Renderer::Init()
{
	_renderer_api->Init();
}

void	Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	_renderer_api->SetViewport(x, y, width, height);
}

void	Renderer::SetClipRect(uint32_t x, uint32_t y, uint32_t width, uint32_t height, bool origin_top_left)
{
	y = origin_top_left ? (Application::Get().GetWindow().GetHeight() - (y + height)) : y;
	_renderer_api->SetClipRect(x, y, width, height);
}

void	Renderer::SetClearColor(const glm::vec4& color)
{
	_renderer_api->SetClearColor(color);
}

void	Renderer::SetClearColor(float r, float g, float b, float a)
{
	_renderer_api->SetClearColor({r, g, b, a});
}

void	Renderer::SetClearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	_renderer_api->SetClearColor({r / 255.f, g / 255.f, b / 255.f, a / 255.f});
}

void	Renderer::Clear()
{
	_renderer_api->Clear();
}

void	Renderer::Draw(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertex_count)
{
	_renderer_api->Draw(vertexArray, mode, vertex_count);
}

void	Renderer::DrawIndexed(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount)
{
	_renderer_api->DrawIndexed(vertexArray, mode, type, indexCount);
}

void	Renderer::DrawInstanced(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertexCount, uint32_t instanceCount)
{
	_renderer_api->DrawInstanced(vertexArray, mode, vertexCount, instanceCount);
}

void	Renderer::DrawIndexedInstanced(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount, uint32_t instanceCount)
{
	_renderer_api->DrawIndexedInstanced(vertexArray, mode, type, indexCount, instanceCount);
}

void	Renderer::SetLineWidth(float width)
{
	_renderer_api->SetLineWidth(width);
}

void	Renderer::SetPolygonMode(PolygonMode mode)
{
	_renderer_api->SetPolygonMode(mode);
}

void	Renderer::BindTexture(uint32_t renderer_id, uint32_t slot)
{
	_renderer_api->BindTexture(renderer_id, slot);
}

void	Renderer::BeginPass()
{
	glm::ivec2 size = Application::Get().GetWindow().GetSize();
	_renderer_api->SetViewport(0, 0, size.x, size.y);
	_renderer_api->SetClipRect(0, 0, size.x, size.y);
	_renderer_api->BeginPass();
}

void	Renderer::EndPass()
{
	_renderer_api->EndPass();
}

void	Renderer::ApplyPipeline(const Ref<Pipeline>& pipeline)
{
	_renderer_api->ApplyPipeline(pipeline);
}

void	Renderer::ApplyBindings(const Ref<Bindings>& bindings)
{
	_renderer_api->ApplyBindings(bindings);
}

void	Renderer::Submit(uint32_t vertexCount)
{
	_renderer_api->Submit(vertexCount);
}

void	Renderer::SubmitInstanced(uint32_t instanceCount, uint32_t vertexCount)
{
	_renderer_api->SubmitInstanced(instanceCount, vertexCount);
}


} // Kinai
