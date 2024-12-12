#pragma once

#include "Kinai/Renderer/RendererAPI.hpp"

namespace Kinai
{

class RenderCommand
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

	static void	DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array, uint32_t index_count = 0)
	{
		_renderer_api->DrawIndexed(vertex_array, index_count);
	}

	static void	DrawLines(const std::shared_ptr<VertexArray>& vertex_array, uint32_t vertex_count)
	{
		_renderer_api->DrawLines(vertex_array, vertex_count);
	}

	static void	DrawTriangles(const std::shared_ptr<VertexArray>& vertex_array, uint32_t vertex_count)
	{
		_renderer_api->DrawTriangles(vertex_array, vertex_count);
	}

	static void	SetLineWidth(float width)
	{
		_renderer_api->SetLineWidth(width);
	}

private:
	static std::unique_ptr<RendererAPI>	_renderer_api;
};

} // Kinai
