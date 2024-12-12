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
	EG_PRINT_FUNC();
}

HeadlessTexture2D::HeadlessTexture2D(const std::string& path)
	: _path(path),
	  _is_loaded(false)
{
	EG_PRINT_FUNC();

	(void)path;
}

HeadlessTexture2D::~HeadlessTexture2D()
{
	EG_PRINT_FUNC();
}

void HeadlessTexture2D::SetData(void* data, uint32_t size)
{
	EG_PRINT_FUNC();

	(void)data;
	(void)size;
}

void HeadlessTexture2D::Bind(uint32_t slot) const
{
	EG_PRINT_FUNC();

	(void)slot;
}

} // Kinai
