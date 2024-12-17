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

void	HeadlessVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
{
	KN_PRINT_FUNC();

	KN_NOTUSED(vertexBuffer);
}

void	HeadlessVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
{
	KN_PRINT_FUNC();

	KN_NOTUSED(indexBuffer);
}

} // Kinai
