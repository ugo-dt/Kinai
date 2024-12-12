#include "Kinai/Core/Texture.hpp"
#include "Kinai/Renderer/Renderer.hpp"

#if defined(EG_HEADLESS)
#include "Kinai/Platform/Headless/HeadlessTexture.hpp"
#elif defined(EG_OPENGL)
#include "Kinai/Platform/OpenGL/OpenGLTexture.hpp"
#endif

namespace Kinai
{

std::shared_ptr<Texture2D> Texture2D::Create(const TextureConfig& config)
{
	EG_PRINT_FUNC();

#if defined(EG_HEADLESS)
	return std::make_shared<HeadlessTexture2D>(config);
#elif defined(EG_OPENGL)
	return std::make_shared<OpenGLTexture2D>(config);
#endif

	EG_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path, GLenum min_filter, GLenum max_filter)
{
	EG_PRINT_FUNC();

#if defined(EG_HEADLESS)
	return std::make_shared<HeadlessTexture2D>(path);
#elif defined(EG_OPENGL)
	return std::make_shared<OpenGLTexture2D>(path, min_filter, max_filter);
#endif

	EG_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

} // Kinai
