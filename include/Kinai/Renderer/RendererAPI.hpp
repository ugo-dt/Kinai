#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Pipeline.hpp"
#include "Kinai/Renderer/VertexArray.hpp"

namespace Kinai
{

enum PolygonMode
{
	Fill,
	Line,
	Point,
};

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

	virtual void	Init() = 0;
	virtual void	SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
	virtual void	SetClearColor(const glm::vec4& color) = 0;
	virtual void	Clear() = 0;
	
	virtual void	DrawIndexed(const Ref<VertexArray>& vertexArray, PrimitiveType type, uint32_t index_count) = 0;
	virtual void	Draw(const Ref<VertexArray>& vertexArray, PrimitiveType type, uint32_t vertexCount) = 0;

	virtual void	SetLineWidth(float width) = 0;
	virtual void	SetPolygonMode(PolygonMode mode) = 0;

	static Scope<RendererAPI>	Create();
};

} // Kinai
