#include "Kinai/Renderer/Bindings.hpp"

#if defined(KINAI_HEADLESS)
	#include "Kinai/Platform/Headless/HeadlessBindings.hpp"
#elif defined(KINAI_OPENGL)
	#include "Kinai/Platform/OpenGL/OpenGLBindings.hpp"
#endif

namespace Kinai
{

Ref<Bindings> Bindings::Create()
{
	KN_PROFILE_FUNC();
	
#if defined(KINAI_HEADLESS)
	return CreateRef<HeadlessBindings>();
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLBindings>();
#endif

	Log::Critical("Unknown RendererAPI");
	return nullptr;
}

} // Kinai
