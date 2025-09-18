#include "Kinai/Platform/OpenGL/OpenGLTexture.hpp"
#include "stb/stb_image.h"

namespace Kinai
{

static GLenum ImageFormatToGLDataFormat(ImageFormat format)
{
	switch (format)
	{
		case ImageFormat::R8:		return GL_RED;
		case ImageFormat::RGB8:		return GL_RGB;
		case ImageFormat::RGBA8:	return GL_RGBA;
		case ImageFormat::RGBA32F:	return GL_RGBA;
		default: break;
	}

	KN_ASSERT(false, "ImageFormatToGLDataFormat");
	return 0;
}

static GLenum ImageFormatToGLInternalFormat(ImageFormat format)
{
	switch (format)
	{
		case ImageFormat::R8:		return GL_R8;
		case ImageFormat::RGB8:		return GL_RGB8;
		case ImageFormat::RGBA8:	return GL_RGBA8;
		case ImageFormat::RGBA32F:	return GL_RGBA32F;
		default: break;
	}

	KN_ASSERT(false, "invalid image format");
	return 0;
}

GLenum OpenGLTexture2D::FilterToGLFilter(Filter filter)
{
	switch (filter)
	{
		case Filter::Nearest: return GL_NEAREST;
		case Filter::Linear: return GL_LINEAR;
		default: break;
	}

	KN_ASSERT(false, "invalid texture filter");
	return 0;
}

GLenum OpenGLTexture2D::WrapToGLWrap(Wrap wrap)
{
	switch (wrap)
	{
		case Wrap::Repeat:			return GL_REPEAT;
		case Wrap::ClampToEdge:		return GL_CLAMP_TO_EDGE;
		case Wrap::MirroredRepeat:	return GL_MIRRORED_REPEAT;
		default: break;
	}

	KN_ASSERT(false, "invalid texture wrap");
	return 0;
}

OpenGLTexture2D::OpenGLTexture2D(const TextureConfig& config)
	: _config(config),
	  _is_loaded(false),
	  _width(_config.width),
	  _height(_config.height)
{
	KN_PRINT_FUNC();

	_internal_format = ImageFormatToGLInternalFormat(_config.format);
	_data_format = ImageFormatToGLDataFormat(_config.format);

#if defined(KN_PLATFORM_DESKTOP) && !defined(KN_PLATFORM_MACOS)
	glCreateTextures(GL_TEXTURE_2D, 1, &_renderer_id);
	glTextureStorage2D(_renderer_id, 1, _internal_format, _width, _height);

	glTextureParameteri(_renderer_id, GL_TEXTURE_MIN_FILTER, config.min_filter);
	glTextureParameteri(_renderer_id, GL_TEXTURE_MAG_FILTER, config.max_filter);

	glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_R, GL_REPEAT);
#else
	glGenTextures(1, &_renderer_id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _renderer_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterToGLFilter(config.sampler_config.min_filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterToGLFilter(config.sampler_config.mag_filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
#endif
	_KN_GL_CHECK_ERROR();
}

OpenGLTexture2D::OpenGLTexture2D(const std::string& path, const TextureConfig& config)
	: _config(config),
	  _path(path),
	  _is_loaded(false)
{
	KN_PRINT_FUNC();

	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = nullptr;
	{
		Log::Trace("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
		data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	}
		
	if (data)
	{
		_is_loaded = true;

		_width = width;
		_height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		_internal_format = internalFormat;
		_data_format = dataFormat;

		KN_ASSERT(internalFormat & dataFormat, "format not supported!");

	#if KINAI_OPENGL_VERSION_MAJOR >= 4
		glCreateTextures(GL_TEXTURE_2D, 1, &_renderer_id);
		glTextureStorage2D(_renderer_id, 1, internalFormat, _width, _height);

		glTextureParameteri(_renderer_id, GL_TEXTURE_MIN_FILTER, FilterToGLFilter(_config.sampler_config.min_filter));
		glTextureParameteri(_renderer_id, GL_TEXTURE_MAG_FILTER, FilterToGLFilter(_config.sampler_config.mag_filter));
		glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_S, WrapToGLWrap(_config.sampler_config.wrap_s));
		glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_T, WrapToGLWrap(_config.sampler_config.wrap_t));
		glTextureParameteri(_renderer_id, GL_TEXTURE_WRAP_R, WrapToGLWrap(_config.sampler_config.wrap_r));
		glTextureSubImage2D(_renderer_id, 0, 0, 0, _width, _height, dataFormat, GL_UNSIGNED_BYTE, data);
	#else
		glGenTextures(1, &_renderer_id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _renderer_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterToGLFilter(_config.sampler_config.min_filter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterToGLFilter(_config.sampler_config.mag_filter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapToGLWrap(_config.sampler_config.wrap_s));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapToGLWrap(_config.sampler_config.wrap_t));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, WrapToGLWrap(_config.sampler_config.wrap_r));
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _width, _height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	#endif
		stbi_image_free(data);
	}
	_KN_GL_CHECK_ERROR();
}

OpenGLTexture2D::~OpenGLTexture2D()
{
	KN_PRINT_FUNC();

	glDeleteTextures(1, &_renderer_id);
	_KN_GL_CHECK_ERROR();
}

void OpenGLTexture2D::SetData(void* data, uint32_t size)
{
	KN_PRINT_FUNC();

#ifdef KN_ENABLE_ASSERTS
	uint32_t bpp = _data_format == GL_RGBA ? 4 : 3;
	KN_ASSERT(size == _width * _height * bpp, "Data must be entire texture!");
#endif

#if KINAI_OPENGL_VERSION_MAJOR >= 4
	glTextureSubImage2D(_renderer_id, 0, 0, 0, _width, _height, _data_format, GL_UNSIGNED_BYTE, data);
#else
	glBindTexture(GL_TEXTURE_2D, _renderer_id);
	glTexImage2D(GL_TEXTURE_2D, 0, _internal_format, _width, _height, 0, _data_format, GL_UNSIGNED_BYTE, data);
#endif
	_KN_GL_CHECK_ERROR();
}

void OpenGLTexture2D::Bind(uint32_t slot) const
{
	KN_PRINT_FUNC();

#if KINAI_OPENGL_VERSION_MAJOR >= 4
	glBindTextureUnit(slot, _renderer_id);
#else
	KN_NOTUSED(slot);
	glBindTexture(GL_TEXTURE_2D, _renderer_id);
#endif
	_KN_GL_CHECK_ERROR();
}

} // Kinai
