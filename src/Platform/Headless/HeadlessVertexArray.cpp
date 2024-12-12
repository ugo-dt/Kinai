#include "Kinai/Platform/Headless/HeadlessVertexArray.hpp"

namespace Kinai
{

HeadlessVertexArray::HeadlessVertexArray()
{
	EG_PRINT_FUNC();
}

HeadlessVertexArray::~HeadlessVertexArray()
{
	EG_PRINT_FUNC();
}

void	HeadlessVertexArray::Bind() const
{
	EG_PRINT_FUNC();
}

void	HeadlessVertexArray::Unbind() const
{
	EG_PRINT_FUNC();
}

void	HeadlessVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	EG_PRINT_FUNC();

	(void)vertexBuffer;
}

void	HeadlessVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	EG_PRINT_FUNC();

	(void)indexBuffer;
}

} // Kinai
