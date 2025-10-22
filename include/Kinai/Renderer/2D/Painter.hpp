#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Pipeline.hpp"
#include "Kinai/Renderer/Bindings.hpp"
#include "Kinai/Renderer/Texture.hpp"
#include "Kinai/Renderer/Buffer/VertexBuffer.hpp"
#include "Kinai/Renderer/OrthographicCamera.hpp"

namespace Kinai
{

namespace Painter
{

enum BlendMode
{
	None = 0,
	Blend,
	BlendPremultiplied,
	Add,
	AddPremultiplied,
	Mod,
	Mul,
	_BlendMode_NUM
};

void Init();
void Shutdown();

void BeginPass();
void EndPass();

void SetImage(int channel, const Ref<Texture2D>& texture);
void ResetImage(int channel = 0);
void SetBlendMode(BlendMode mode);
void ResetBlendMode();

void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color = glm::vec4(1.0f));
void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color = glm::vec4(1.0f));
void DrawQuad(const glm::mat4& transform);
void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
void DrawQuad(const glm::mat4& transform, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color = glm::vec4(1.0f));

void MakePipelines();
void Flush();
void StartBatch();
void NextBatch();

void SetContextCamera(const OrthographicCameraController& camera);

inline void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	KN_PROFILE_FUNC();

	DrawQuad({ position.x, position.y, 0.0f }, size, color);
}

inline void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	KN_PROFILE_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, color);
}

inline void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color)
{
	KN_PROFILE_FUNC();

	DrawQuad( { position.x, position.y, 0.0f }, size, uvStart, uvEnd, tint_color);
}

inline void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color)
{
	KN_PROFILE_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	DrawQuad(transform, uvStart, uvEnd, tint_color);
}

inline void DrawQuad(const glm::mat4& transform, const glm::vec4& color)
{
	DrawQuad(transform, glm::vec2(0.f), glm::vec2(1.f), color);
}

inline void DrawQuad(const glm::mat4& transform)
{
	KN_PROFILE_FUNC();

	DrawQuad(transform, glm::vec4(1.0f));
}

} // Painter

} // Kinai
