#pragma once

#include "Kinai/Renderer/Texture.hpp"

namespace Kinai
{

class OpenGLTexture2D : public Texture2D
{
public:
	OpenGLTexture2D(const TextureConfig& specification);
	OpenGLTexture2D(const std::string& path, GLenum min_filter, GLenum max_filter);
	~OpenGLTexture2D();

	const TextureConfig& GetConfig() const override { return _config; }

	uint32_t	GetWidth() const override { return _width;  }
	uint32_t	GetHeight() const override { return _height; }
	uint32_t	GetRendererID() const override { return _renderer_id; }

	const std::string& GetPath() const override { return _path; }
	
	void SetData(void* data, uint32_t size) override;

	void Bind(uint32_t slot = 0) const override;

	bool IsLoaded() const override { return _is_loaded; }

	bool operator==(const Texture& other) const override
	{
		return _renderer_id == other.GetRendererID();
	}

private:
	TextureConfig	_config;
	std::string		_path;
	bool			_is_loaded;
	uint32_t		_width, _height;
	uint32_t		_renderer_id;
	GLenum			_internal_format, _data_format;
};

} // Kinai
