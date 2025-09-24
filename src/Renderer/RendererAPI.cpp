#include "Kinai/Renderer/RendererAPI.hpp"
#include "Kinai/Renderer/Pipeline.hpp"
#include "Kinai/Renderer/Bindings.hpp"

#include "Kinai/Platform/Headless/HeadlessRendererAPI.hpp"
#include "Kinai/Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Kinai
{

size_t	IndexTypeSize(IndexType type)
{
	switch (type)
	{
		case IndexType::None:   return 0;
		case IndexType::Uint16: return sizeof(uint16_t);
		case IndexType::Uint32: return sizeof(uint32_t);
	}

	Log::Critical("Unknown IndexType");
	return 0;
}

Scope<RendererAPI>	RendererAPI::Create()
{
	KN_PROFILE_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateScope<HeadlessRendererAPI>();
#elif defined(KINAI_OPENGL)
	return CreateScope<OpenGLRendererAPI>();
#endif

	Log::Critical("Unknown RendererAPI");
	return nullptr;
}

#if defined(KN_DEBUG_STATS)
RendererAPI::Stats	RendererAPI::_stats;
#endif

void	RendererAPI::ApplyUniforms(const void* params, size_t size)
{
	KN_PROFILE_FUNC();

	Log::Validate(_current_pipeline != nullptr, "can't apply uniforms: no current rendering pipeline!");
	Log::Validate(_current_pipeline->GetShader() != nullptr, "can't apply uniforms: no shader in current rendering pipeline!");

	const auto& shd = _current_pipeline->GetShader();
	shd->ApplyUniforms(params, size);
}

void	RendererAPI::Submit(uint32_t vertexCount)
{
	KN_PROFILE_FUNC();

	Ref<VertexArray> vao = _current_pipeline->GetVertexArray();
	if (_current_bindings->GetIndexBuffer())
	{
		Log::Validate(_current_bindings->GetVertexBuffer() != nullptr, "No vertex buffer set in bindings!");
		Log::Validate(_current_bindings->GetIndexBuffer()->GetCount() > 0, "Index buffer has no indices!");
		#ifdef KN_ENABLE_ASSERTS
			static bool warned = false;
			if (vertexCount && !warned)
			{
				warned = true;
				Log::Warn("Submit: vertexCount ({}) is unused because an index buffer was provided. This warning is only shown once.", vertexCount);
			}
		#endif

		_current_bindings->GetIndexBuffer()->Bind();
		DrawIndexed(
			_current_pipeline->GetVertexArray(),
			_current_pipeline->GetPrimitiveType(),
			_current_bindings->GetIndexBuffer()->GetIndexType(),
			_current_bindings->GetIndexBuffer()->GetCount()
		);
		#if defined(KN_DEBUG_STATS)
			_stats._vertexCount += _current_bindings->GetVertexBuffer()->GetSize();
			_stats._drawCalls++;
			_stats._totalDrawCalls++;
		#endif
	}
	else if (vertexCount > 0)
	{
		Draw(
			_current_pipeline->GetVertexArray(),
			_current_pipeline->GetPrimitiveType(),
			vertexCount
		);
		#if defined(KN_DEBUG_STATS)
			_stats._vertexCount += vertexCount;
			_stats._drawCalls++;
			_stats._totalDrawCalls++;
		#endif
	}
}

} // Kinai
