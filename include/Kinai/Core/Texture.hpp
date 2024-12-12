#pragma once

#include "Kinai/Core/Core.hpp"

namespace Kinai
{

enum class ImageFormat
{
	None = 0,
	R8,
	RGB8,
	RGBA8,
	RGBA32F
};

struct TextureConfig
{
	uint32_t	width = 1;
	uint32_t	height = 1;
	ImageFormat	format = ImageFormat::RGBA8;
	bool		generate_mips = true;
	GLenum		min_filter = GL_LINEAR;
	GLenum		max_filter = GL_LINEAR;
};

class Texture
{
public:
	virtual ~Texture() = default;

	virtual const TextureConfig &GetConfig() const = 0;

	virtual uint32_t GetWidth() const = 0;
	virtual uint32_t GetHeight() const = 0;
	virtual uint32_t GetRendererID() const = 0;

	virtual const std::string &GetPath() const = 0;

	virtual void SetData(void *data, uint32_t size) = 0;

	virtual void Bind(uint32_t slot = 0) const = 0;

	virtual bool IsLoaded() const = 0;

	virtual bool operator==(const Texture &other) const = 0;
};

class Texture2D : public Texture
{
public:
	static std::shared_ptr<Texture2D>	Create(const TextureConfig &config);
	static std::shared_ptr<Texture2D>	Create(const std::string &path, GLenum min_filter, GLenum max_filter);
};

}
