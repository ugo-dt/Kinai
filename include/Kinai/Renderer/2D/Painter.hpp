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

void DrawQuad(const math::vec2& position, const math::vec2& size, const math::vec4& color);
void DrawQuad(const math::vec3& position, const math::vec2& size, const math::vec4& color);
void DrawQuad(const math::vec2& position, const math::vec2& size, const math::vec2& uvStart, const math::vec2& uvEnd, const math::vec4& tint_color = math::vec4(1.0f));
void DrawQuad(const math::vec3& position, const math::vec2& size, const math::vec2& uvStart, const math::vec2& uvEnd, const math::vec4& tint_color = math::vec4(1.0f));
void DrawQuad(const math::mat4& transform);
void DrawQuad(const math::mat4& transform, const math::vec4& color);
void DrawQuad(const math::mat4& transform, const math::vec2& uvStart, const math::vec2& uvEnd, const math::vec4& tint_color = math::vec4(1.0f));

void MakePipelines();
void Flush();
void StartBatch();
void NextBatch();

void SetContextCamera(const OrthographicCameraController& camera);

void SetContextCamera(const OrthographicCameraController& camera);

inline void DrawQuad(const math::vec2& position, const math::vec2& size, const math::vec4& color)
{
	KN_PROFILE_FUNC();

	DrawQuad({ position.x, position.y, 0.0f }, size, color);
}

inline void DrawQuad(const math::vec3& position, const math::vec2& size, const math::vec4& color)
{
	KN_PROFILE_FUNC();

	math::mat4 transform = math::translate(math::mat4(1.0f), position)
		* math::scale(math::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, color);
}

inline void DrawQuad(const math::vec2& position, const math::vec2& size, const math::vec2& uvStart, const math::vec2& uvEnd, const math::vec4& tint_color)
{
	KN_PROFILE_FUNC();

	DrawQuad( { position.x, position.y, 0.0f }, size, uvStart, uvEnd, tint_color);
}

inline void DrawQuad(const math::vec3& position, const math::vec2& size, const math::vec2& uvStart, const math::vec2& uvEnd, const math::vec4& tint_color)
{
	KN_PROFILE_FUNC();

	math::mat4 transform = math::translate(math::mat4(1.0f), position)
		* math::scale(math::mat4(1.0f), { size.x, size.y, 1.0f });
	DrawQuad(transform, uvStart, uvEnd, tint_color);
}

inline void DrawQuad(const math::mat4& transform, const math::vec4& color)
{
	DrawQuad(transform, math::vec2(0.f), math::vec2(1.f), color);
}

inline void DrawQuad(const math::mat4& transform)
{
	KN_PROFILE_FUNC();

	DrawQuad(transform, math::vec4(1.0f));
}

} // Painter

} // Kinai
