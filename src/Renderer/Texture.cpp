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
	KN_PROFILE_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateRef<HeadlessTexture2D>(config);
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLTexture2D>(config);
#endif

	Log::Critical("Unknown RendererAPI!");
	return nullptr;
}

Ref<Texture2D> Texture2D::Create(const std::string& path, const TextureConfig& config)
{
	KN_PROFILE_FUNC();

#if defined(KINAI_HEADLESS)
	KN_NOTUSED(min_filter);
	KN_NOTUSED(max_filter);
	return CreateRef<HeadlessTexture2D>(path, config);
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLTexture2D>(path, config);
#endif

	Log::Critical("Unknown RendererAPI!");
	return nullptr;
}

Ref<TextureCubeMap> TextureCubeMap::Create(const std::array<std::string, 6> &paths, const TextureConfig& config)
{
	KN_PROFILE_FUNC();

#if defined(KINAI_HEADLESS)
	return CreateRef<HeadlessTextureCubeMap>(paths, config);
#elif defined(KINAI_OPENGL)
	return CreateRef<OpenGLTextureCubeMap>(paths, config);
#endif

	Log::Critical("Unknown RendererAPI!");
	return nullptr;
}

} // Kinai
