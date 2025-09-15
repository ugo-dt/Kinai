#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Bindings.hpp"
#include "Kinai/Renderer/PerspectiveCamera.hpp"
#include "Kinai/Renderer/Pipeline.hpp"
#include "Kinai/Renderer/RendererAPI.hpp"
#include "Kinai/Renderer/Shader.hpp"

namespace Kinai
{

class Renderer
{
public:
	static void Init();
	static void Shutdown();

	static void BeginPass();
	static void EndPass();

	static void ApplyPipeline(const Ref<Pipeline>& pipeline);
	static void ApplyBindings(const Ref<Bindings>& bindings);
	template <class Tp>
	static void ApplyUniforms(const Tp& params);

	static void OnWindowResize(uint32_t width, uint32_t height);

	static void Submit(uint32_t vertexCount = 0);

private:
	static Ref<Pipeline> _current_pipeline;
	static Ref<Bindings> _current_bindings;
};

template <class Tp>
void
Renderer::ApplyUniforms(const Tp& params)
{
	KN_PRINT_FUNC();

	Log::Validate(_current_pipeline != nullptr, "Renderer::ApplyUniforms(): no current rendering pipeline!");
	Log::Validate(_current_pipeline->GetShader() != nullptr, "Renderer::ApplyUniforms(): no shader in current rendering pipeline!");

	const auto& shd = _current_pipeline->GetShader();
	shd->ApplyUniforms(&params, sizeof(params));
}

} // Kinai
