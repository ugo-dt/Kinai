#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Pipeline.hpp"

namespace Kinai
{

class OpenGLPipeline : public Pipeline
{
public:
	OpenGLPipeline(const PipelineConfig& config);
	~OpenGLPipeline();
};

} // Kinai
