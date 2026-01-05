#pragma once

#include "Kinai/Core/Core.hpp"

namespace Kinai
{

enum class Filter
{
	None = 0,
	Nearest,
	Linear,
};

enum class Wrap
{
	None = 0,
	Repeat,
	ClampToEdge,
	MirroredRepeat,
};

enum class ImageFormat
{
	None = 0,
	R8,
	RGB8,
	RGBA8,
	RGBA32F,
	SRGB_ALPHA,
	BGR,
	BGRA,
};

struct SamplerConfig
{
	Filter min_filter = Filter::Nearest;
	Filter mag_filter = Filter::Nearest;
	Wrap wrap_s = Wrap::Repeat;
	Wrap wrap_t = Wrap::Repeat;
	Wrap wrap_r = Wrap::Repeat;
};

struct TextureConfig
{
	int width = 1;
	int height = 1;
	ImageFormat format = ImageFormat::RGBA8;
	// If true, image rows are flipped vertically when loading from a file.
	bool flip_y_on_load = false;
	// bool generate_mips = true;
	SamplerConfig sampler_config = SamplerConfig();
	std::string label = "Texture";
};

class Texture
{
public:
	virtual ~Texture() = default;

	virtual const TextureConfig &GetConfig() const = 0;

	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
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
	static Ref<Texture2D>	Create(const TextureConfig &config);
	static Ref<Texture2D>	Create(const std::string &path, const TextureConfig& config = TextureConfig());
};

class TextureCubeMap : public Texture
{
public:
	static Ref<TextureCubeMap>	Create(const std::array<std::string, 6> &paths, const TextureConfig& config = TextureConfig());
};

}
