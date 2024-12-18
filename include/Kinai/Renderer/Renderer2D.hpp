#pragma once

#include "Kinai/Renderer/OrthographicCamera.hpp"
#include "Kinai/Renderer/Texture.hpp"

namespace Kinai
{

class Renderer2D
{
public:
	static void	Init();
	static void	Shutdown();

	static void	BeginFrame(const Camera& camera, const glm::mat4& transform);
	static void	BeginFrame(const OrthographicCamera& camera);
	static void	BeginFrame(const PerspectiveCamera& camera);
	static void	EndFrame();
	static void	Flush();

	static void	DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	static void	DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	static void	DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
	static void	DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));

	static void	DrawQuad(const glm::mat4& transform, const glm::vec4& color);
	static void	DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));

	static void	DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void	DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void	DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	static void	DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

	static void	DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness = 1.0f, float fade = 0.005f);
	
	static void	DrawLine(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color);

	static void	DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	static void	DrawRect(const glm::mat4& transform, const glm::vec4& color);

	static float GetLineWidth();
	static void	SetLineWidth(float width);

	// Stats
	struct Statistics
	{
		uint32_t	DrawCalls = 0;
		uint32_t	QuadCount = 0;
		uint32_t	GetTotalVertexCount() { return QuadCount * 4; }
		uint32_t	GetTotalIndexCount() { return QuadCount * 6; }
		void		Reset();
	};
	
	static Statistics&	GetStats();

private:
	static void	StartBatch();
	static void	NextBatch();
};

} // Kinai
