#include "Kinai/Core/Texture.hpp"
#include "Kinai/Renderer/Renderer.hpp"

#if defined(KINAI_HEADLESS)
#include "Kinai/Platform/Headless/HeadlessTexture.hpp"
#elif defined(KINAI_OPENGL)
#include "Kinai/Platform/OpenGL/OpenGLTexture.hpp"
#endif

namespace Kinai
{

std::shared_ptr<Texture2D> Texture2D::Create(const TextureConfig& config)
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	return std::make_shared<HeadlessTexture2D>(config);
#elif defined(KINAI_OPENGL)
	return std::make_shared<OpenGLTexture2D>(config);
#endif

	KN_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path, GLenum min_filter, GLenum max_filter)
{
	KN_PRINT_FUNC();

#if defined(KINAI_HEADLESS)
	(void)min_filter;
	(void)max_filter;
	return std::make_shared<HeadlessTexture2D>(path);
#elif defined(KINAI_OPENGL)
	return std::make_shared<OpenGLTexture2D>(path, min_filter, max_filter);
#endif

	KN_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

} // Kinai
