#include "Kinai/Platform/Headless/HeadlessTexture.hpp"
#include "stb/stb_image.h"

namespace Kinai
{

HeadlessTexture2D::HeadlessTexture2D(const TextureConfig& config)
	: _config(config),
	  _is_loaded(false),
	  _width(_config.width),
	  _height(_config.height)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(_internal_format);
	KN_NOTUSED(_data_format);
}

HeadlessTexture2D::HeadlessTexture2D(const std::string& path, const TextureConfig& config)
	: _config(config),
	  _path(path),
	  _is_loaded(false)
{
	KN_PROFILE_FUNC();
}

HeadlessTexture2D::~HeadlessTexture2D()
{
	KN_PROFILE_FUNC();
}

void HeadlessTexture2D::SetData(void* data, uint32_t size)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(data);
	KN_NOTUSED(size);
}

void HeadlessTexture2D::Bind(uint32_t slot) const
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(slot);
}

HeadlessTextureCubeMap::HeadlessTextureCubeMap(const std::array<std::string, 6> &paths, const TextureConfig& config)
	: _config(config),
	  _paths(paths),
	  _is_loaded(false),
	  _width(0),
	  _height(0)
{
	KN_PROFILE_FUNC();
	KN_NOTUSED(_internal_format);
	KN_NOTUSED(_data_format);
}

HeadlessTextureCubeMap::~HeadlessTextureCubeMap()
{
	KN_PROFILE_FUNC();
}

void	HeadlessTextureCubeMap::SetData(void* data, uint32_t size)
{
	KN_PROFILE_FUNC();
	KN_NOTUSED(data);
	KN_NOTUSED(size);
}

void	HeadlessTextureCubeMap::Bind(uint32_t slot) const
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(slot);
}

} // Kinai
