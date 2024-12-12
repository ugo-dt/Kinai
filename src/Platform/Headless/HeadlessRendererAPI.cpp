#include "Kinai/Platform/Headless/HeadlessRendererAPI.hpp"

namespace Kinai
{

void	HeadlessRendererAPI::Init()
{
	KN_PRINT_FUNC();
}

void	HeadlessRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	KN_PRINT_FUNC();

	(void)x;
	(void)y;
	(void)width;
	(void)height;
}

void	HeadlessRendererAPI::SetClearColor(const glm::vec4& color)
{
	KN_PRINT_FUNC();

	(void)color;
}

void	HeadlessRendererAPI::Clear()
{
	KN_PRINT_FUNC();
}

void	HeadlessRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
{
	KN_PRINT_FUNC();

	(void)vertexArray;
	(void)indexCount;
}

void	HeadlessRendererAPI::DrawLines(const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount)
{
	KN_PRINT_FUNC();

	(void)vertexArray;
	(void)vertexCount;
}

void	HeadlessRendererAPI::DrawTriangles(const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertexCount)
{
	KN_PRINT_FUNC();

	(void)vertexArray;
	(void)vertexCount;
}

void	HeadlessRendererAPI::SetLineWidth(float width)
{
	KN_PRINT_FUNC();

	(void)width;
}

} // Kinai
