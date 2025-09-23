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

	#if defined(KN_DEBUG_STATS)
		class Stats
		{
		public:
			static void Reset() { _stats._drawCalls = 0; _stats._vertexCount = 0; }
			static uint64_t GetDrawCalls() { return _stats._drawCalls; }
			static uint64_t GetTotalDrawCalls() { return _stats._totalDrawCalls; }
			static uint64_t GetVertexCount() { return _stats._vertexCount; }
		private:
			friend class Renderer;
			uint64_t _drawCalls = 0;
			uint64_t _totalDrawCalls = 0;
			uint64_t _vertexCount = 0;
		};
	#endif
private:
	static Ref<Pipeline> _current_pipeline;
	static Ref<Bindings> _current_bindings;
	#if defined(KN_DEBUG_STATS)
		static Stats _stats;
	#endif
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
