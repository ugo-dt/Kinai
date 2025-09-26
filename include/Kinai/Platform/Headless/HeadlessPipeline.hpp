#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Pipeline.hpp"

namespace Kinai
{

class HeadlessPipeline : public Pipeline
{
public:
	HeadlessPipeline(const PipelineConfig& config);
	~HeadlessPipeline() = default;
};

} // Kinai
