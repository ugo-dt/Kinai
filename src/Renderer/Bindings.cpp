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
	KN_PRINT_FUNC();
	
#if defined(KINAI_HEADLESS)
	return CreateRef<HeadlessBindings>();
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLBindings>();
#endif

	KN_ASSERT(false, "Unknown RendererAPI");
	return nullptr;
}

} // Kinai
