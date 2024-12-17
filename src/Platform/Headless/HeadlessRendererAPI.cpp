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

	KN_NOTUSED(x);
	KN_NOTUSED(y);
	KN_NOTUSED(width);
	KN_NOTUSED(height);
}

void	HeadlessRendererAPI::SetClearColor(const glm::vec4& color)
{
	KN_PRINT_FUNC();

	KN_NOTUSED(color);
}

void	HeadlessRendererAPI::Clear()
{
	KN_PRINT_FUNC();
}

void	HeadlessRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
{
	KN_PRINT_FUNC();

	KN_NOTUSED(vertexArray);
	KN_NOTUSED(indexCount);
}

void	HeadlessRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
{
	KN_PRINT_FUNC();

	KN_NOTUSED(vertexArray);
	KN_NOTUSED(vertexCount);
}

void	HeadlessRendererAPI::DrawTriangles(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
{
	KN_PRINT_FUNC();

	KN_NOTUSED(vertexArray);
	KN_NOTUSED(vertexCount);
}

void	HeadlessRendererAPI::SetLineWidth(float width)
{
	KN_PRINT_FUNC();

	KN_NOTUSED(width);
}

} // Kinai
