#include "Kinai/Renderer/Texture.hpp"

#if defined(KINAI_HEADLESS)
#include "Kinai/Platform/Headless/HeadlessTexture.hpp"
#elif defined(KINAI_OPENGL)
#include "Kinai/Platform/OpenGL/OpenGLTexture.hpp"
#endif

namespace Kinai
{

Ref<Texture2D> Texture2D::Create(const TextureConfig& config)
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateRef<HeadlessTexture2D>(config);
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLTexture2D>(config);
#endif

	KN_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

Ref<Texture2D> Texture2D::Create(const std::string& path, GLenum min_filter, GLenum max_filter)
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	KN_NOTUSED(min_filter);
	KN_NOTUSED(max_filter);
	return CreateRef<HeadlessTexture2D>(path);
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLTexture2D>(path, min_filter, max_filter);
#endif

	KN_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

} // Kinai
