#include "Kinai/Renderer/RenderCommand.hpp"

namespace Kinai
{

std::unique_ptr<RendererAPI>	RenderCommand::_renderer_api = RendererAPI::Create();

} // Kinai
