#pragma once

#include "Kinai/Renderer/RendererAPI.hpp"
#include "Kinai/Core/Application.hpp"

namespace Kinai
{

class Renderer
{
public:
	static void	Init()
	{
		_renderer_api->Init();
	}

	static void	SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		_renderer_api->SetViewport(x, y, width, height);
	}

	static void	SetClearColor(const glm::vec4& color)
	{
		_renderer_api->SetClearColor(color);
	}

	static void	SetClearColor(float r, float g, float b, float a)
	{
		_renderer_api->SetClearColor({r, g, b, a});
	}

	static void	SetClearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		_renderer_api->SetClearColor({r / 255.f, g / 255.f, b / 255.f, a / 255.f});
	}

	static void	Clear()
	{
		_renderer_api->Clear();
	}

	static void	Draw(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertex_count)
	{
		_renderer_api->Draw(vertexArray, mode, vertex_count);
	}

	static void	DrawIndexed(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount = 0)
	{
		_renderer_api->DrawIndexed(vertexArray, mode, type, indexCount);
	}

	static void DrawInstanced(const Ref<VertexArray>& vertexArray, PrimitiveType mode, uint32_t vertexCount, uint32_t instanceCount)
	{
		_renderer_api->DrawInstanced(vertexArray, mode, vertexCount, instanceCount);
	}

	static void	DrawIndexedInstanced(const Ref<VertexArray>& vertexArray, PrimitiveType mode, IndexType type, uint32_t indexCount = 0, uint32_t instanceCount = 1)
	{
		_renderer_api->DrawIndexedInstanced(vertexArray, mode, type, indexCount, instanceCount);
	}

	static void	SetLineWidth(float width)
	{
		_renderer_api->SetLineWidth(width);
	}

	static void	SetPolygonMode(PolygonMode mode)
	{
		_renderer_api->SetPolygonMode(mode);
	}

	static void	BindTexture(uint32_t renderer_id, uint32_t slot = 0)
	{
		_renderer_api->BindTexture(renderer_id, slot);
	}

	static void BeginPass()
	{
		glm::ivec2 size = Application::Get().GetWindow().GetSize();
		_renderer_api->SetViewport(0, 0, size.x, size.y);
		_renderer_api->BeginPass();
	}
	
	static void EndPass()
	{
		_renderer_api->EndPass();
	}

	static void ApplyPipeline(const Ref<Pipeline>& pipeline)
	{
		_renderer_api->ApplyPipeline(pipeline);
	}

	static void ApplyBindings(const Ref<Bindings>& bindings)
	{
		_renderer_api->ApplyBindings(bindings);
	}

	template <class Tp>
	static void ApplyUniforms(const Tp& params)
	{
		_renderer_api->ApplyUniforms(&params, sizeof(params));
	}

	static void Submit(uint32_t vertexCount = 0)
	{
		_renderer_api->Submit(vertexCount);
	}

	static void SubmitInstanced(uint32_t instanceCount, uint32_t vertexCount = 0)
	{
		_renderer_api->SubmitInstanced(instanceCount, vertexCount);
	}

private:
	static Scope<RendererAPI>	_renderer_api;
};

} // Kinai
