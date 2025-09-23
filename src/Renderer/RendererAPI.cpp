#include "Kinai/Renderer/RendererAPI.hpp"

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
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateScope<HeadlessRendererAPI>();
#elif defined(KINAI_OPENGL)
	return CreateScope<OpenGLRendererAPI>();
#endif

	Log::Critical("Unknown RendererAPI");
	return nullptr;
}

} // Kinai
