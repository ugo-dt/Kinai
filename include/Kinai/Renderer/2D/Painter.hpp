#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Pipeline.hpp"
#include "Kinai/Renderer/Bindings.hpp"
#include "Kinai/Renderer/Texture.hpp"
#include "Kinai/Renderer/Buffer/VertexBuffer.hpp"

namespace Kinai
{

struct QuadVertex
{
	glm::vec4 position;
	glm::vec4 color;
};

class Painter
{
public:
	static void Init();
	static void Shutdown();

	static void BeginPass();
	static void EndPass();

	static void SetImage(const Ref<Texture2D>& texture) { _current_texture = texture; }

	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color = glm::vec4(1.0f));
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color = glm::vec4(1.0f));
	static void DrawQuad(const glm::mat4& transform);
	static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
	static void DrawQuad(const glm::mat4& transform, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color = glm::vec4(1.0f));

private:
	static constexpr uint32_t MAX_QUADS = 20000;
	static constexpr uint32_t MAX_VERTICES = MAX_QUADS * 4;
	static constexpr uint32_t MAX_INDICES = MAX_QUADS * 6;
	static constexpr uint32_t MAX_TEXTURE_SLOTS = 31;

private:
	static void MakePipelines();
	static void Flush();
	static void StartBatch();
	static void NextBatch();

private:
	static Ref<VertexArray> _vao;
	static Ref<Shader> _shader;
	static Ref<Texture2D> _white_texture, _current_texture;

	static struct QuadPipeline {
		Ref<Pipeline> pipeline;
		Ref<Bindings> bindings;
		BlendState blend_state;
		uint32_t index;
		QuadVertex* vertex_buffer_base = nullptr;
		QuadVertex* vertex_buffer_ptr = nullptr;
	} _quad;
};

} // Kinai
