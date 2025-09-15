#include "Kinai/Renderer/Pipeline.hpp"

#if defined(KINAI_HEADLESS)
	#include "Kinai/Platform/Headless/HeadlessPipeline.hpp"
#elif defined(KINAI_OPENGL)
	#include "Kinai/Platform/OpenGL/OpenGLPipeline.hpp"
#endif

namespace Kinai
{

Ref<Pipeline>	Pipeline::Create(const PipelineConfig& config)
{
	KN_PRINT_FUNC();

	Log::Validate(config.vao != nullptr, "Pipeline requires a valid VertexArray");
	Log::Validate(config.shader != nullptr, "Pipeline requires a valid Shader");

#if defined(KINAI_HEADLESS)
	return CreateRef<HeadlessPipeline>(config);
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLPipeline>(config);
#endif

	KN_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

} // Kinai
