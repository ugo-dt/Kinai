#include "Kinai/Platform/Headless/HeadlessVertexArray.hpp"

namespace Kinai
{

HeadlessVertexArray::HeadlessVertexArray()
{
	KN_PRINT_FUNC();
}

HeadlessVertexArray::~HeadlessVertexArray()
{
	KN_PRINT_FUNC();
}

void	HeadlessVertexArray::Bind() const
{
	KN_PRINT_FUNC();
}

void	HeadlessVertexArray::Unbind() const
{
	KN_PRINT_FUNC();
}

void	HeadlessVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	KN_PRINT_FUNC();

	(void)vertexBuffer;
}

void	HeadlessVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	KN_PRINT_FUNC();

	(void)indexBuffer;
}

} // Kinai
