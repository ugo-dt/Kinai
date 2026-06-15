#pragma once

#include "Kinai/Renderer/Texture.hpp"

namespace Kinai
{

GLenum FilterToGLFilter(Filter filter);
GLenum WrapToGLWrap(Wrap wrap);

class OpenGLTexture2D : public Texture2D
{
public:
	OpenGLTexture2D(const TextureConfig& config);
	OpenGLTexture2D(const std::string& path, const TextureConfig& config, bool flip_vertically = true);
	~OpenGLTexture2D();

	const TextureConfig& GetConfig() const override { return _config; }

	int GetWidth() const override { return _width;  }
	int GetHeight() const override { return _height; }
	uint32_t GetRendererID() const override { return _renderer_id; }
	const std::string& GetPath() const override { return _path; }
	bool IsLoaded() const override { return _is_loaded; }
	
	void SetData(void* data, uint32_t size) override;
	void Bind(uint32_t slot = 0) const override;

	bool operator==(const Texture& other) const override
	{
		return _renderer_id == other.GetRendererID();
	}

private:
	TextureConfig _config;
	std::string _path;
	bool _is_loaded;
	int _width, _height;
	uint32_t _renderer_id;
	GLenum _internal_format, _data_format;
};

class OpenGLTextureCubeMap : public TextureCubeMap
{
public:
	OpenGLTextureCubeMap(const std::array<std::string, 6> &paths, const TextureConfig& config);
	~OpenGLTextureCubeMap();

	const TextureConfig& GetConfig() const override { return _config; }
	int GetWidth() const override { return _width;  }
	int GetHeight() const override { return _height; }
	uint32_t GetRendererID() const override { return _renderer_id; }
	const std::string& GetPath() const override { return _paths[0]; } // return first path as representative
	const std::array<std::string, 6>& GetPaths() const { return _paths; }
	bool IsLoaded() const override { return _is_loaded; }

	void SetData(void* data, uint32_t size) override;
	void Bind(uint32_t slot = 0) const override;

	bool operator==(const Texture& other) const override
	{
		return _renderer_id == other.GetRendererID();
	}

private:
	TextureConfig _config;
	std::array<std::string, 6> _paths;
	bool _is_loaded;
	int _width, _height;
	uint32_t _renderer_id;
	GLenum _internal_format, _data_format;
};

} // Kinai
