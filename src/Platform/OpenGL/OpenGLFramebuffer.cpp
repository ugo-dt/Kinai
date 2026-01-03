#include "Kinai/Platform/OpenGL/OpenGLFramebuffer.hpp"
#include "Kinai/Platform/OpenGL/OpenGLTexture.hpp"

namespace Kinai
{

constexpr int MAX_FRAME_BUFFER_SIZE = 8192;

static GLenum	TextureTarget(bool multisampled)
{
#if KINAI_OPENGL_VERSION_MAJOR >= 4
	return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
#else
	KN_NOTUSED(multisampled);
	return GL_TEXTURE_2D;
#endif
}

static void	CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
{
#if KINAI_OPENGL_VERSION_MAJOR >= 4
	glCreateTextures(TextureTarget(multisampled), count, outID);
#else
	KN_NOTUSED(multisampled);
	glGenTextures(count, outID);
#endif
	_KN_GL_CHECK_ERROR();
}

static void	BindTexture(bool multisampled, uint32_t id)
{
	glBindTexture(TextureTarget(multisampled), id);
	_KN_GL_CHECK_ERROR();
}

static void	AttachColorTexture(
	uint32_t id,
	int samples,
	GLenum internalFormat,
	GLenum format,
	GLenum min_filter,
	GLenum mag_filter,
	GLenum wrap_s,
	GLenum wrap_t,
	GLenum wrap_r,
	int width,
	int height,
	int index
)
{
	bool multisampled = samples > 1;
#if KINAI_OPENGL_VERSION_MAJOR >= 4
	if (multisampled)
	{
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
	}
	else
#endif
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrap_r);
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
	_KN_GL_CHECK_ERROR();
}

static void	AttachDepthTexture(
	uint32_t id,
	int samples,
	GLenum format,
	GLenum attachmentType,
	GLenum min_filter,
	GLenum mag_filter,
	GLenum wrap_s,
	GLenum wrap_t,
	GLenum wrap_r,
	int width,
	int height
)
{
	bool multisampled = samples > 1;
#if KINAI_OPENGL_VERSION_MAJOR >= 4
	if (multisampled)
	{
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
	}
	else
#endif
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
		_KN_GL_CHECK_ERROR();
		glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrap_r);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
	_KN_GL_CHECK_ERROR();
}

static bool	IsDepthFormat(FramebufferTextureFormat format)
{
	switch (format)
	{
		case FramebufferTextureFormat::DEPTH24STENCIL8:  return true;
		default: break;
	}

	return false;
}

static GLenum	FBTextureFormatToGL(FramebufferTextureFormat format)
{
	switch (format)
	{
		case FramebufferTextureFormat::RGBA8:       return GL_RGBA8;
		case FramebufferTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
		default: break;
	}

	KN_ASSERT(false);
	return 0;
}

OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferConfig& spec)
	: _config(spec)
{
	for (auto spec : _config.attachments.attachments)
	{
		if (!IsDepthFormat(spec.TextureFormat))
			_color_attachment_configs.emplace_back(spec);
		else
			_depth_attachment_config = spec;
	}

	Invalidate();
}

OpenGLFramebuffer::~OpenGLFramebuffer()
{
	glDeleteFramebuffers(1, &_renderer_id);
	glDeleteTextures(_color_attachments.size(), _color_attachments.data());
	glDeleteTextures(1, &_depth_attachment);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLFramebuffer::Invalidate()
{
	if (_renderer_id)
	{
		glDeleteFramebuffers(1, &_renderer_id);
		glDeleteTextures(_color_attachments.size(), _color_attachments.data());
		glDeleteTextures(1, &_depth_attachment);
		
		_color_attachments.clear();
		_depth_attachment = 0;
	}

#if KINAI_OPENGL_VERSION_MAJOR >= 4
	glCreateFramebuffers(1, &_renderer_id);
#else
	glGenFramebuffers(1, &_renderer_id);
#endif
	glBindFramebuffer(GL_FRAMEBUFFER, _renderer_id);
	_KN_GL_CHECK_ERROR();

	bool multisample = _config.samples > 1;

	// Attachments
	if (_color_attachment_configs.size())
	{
		_color_attachments.resize(_color_attachment_configs.size());
		CreateTextures(multisample, _color_attachments.data(), _color_attachments.size());

		for (size_t i = 0; i < _color_attachments.size(); i++)
		{
			BindTexture(multisample, _color_attachments[i]);
			switch (_color_attachment_configs[i].TextureFormat)
			{
				case FramebufferTextureFormat::RGBA8:
					AttachColorTexture(
						_color_attachments[i],
						_config.samples,
						GL_RGBA8,
						GL_RGBA,
						FilterToGLFilter(_color_attachment_configs[i].sampler_config.min_filter),
						FilterToGLFilter(_color_attachment_configs[i].sampler_config.mag_filter),
						WrapToGLWrap(_color_attachment_configs[i].sampler_config.wrap_s),
						WrapToGLWrap(_color_attachment_configs[i].sampler_config.wrap_t),
						WrapToGLWrap(_color_attachment_configs[i].sampler_config.wrap_r),
						_config.width,
						_config.height,
						i
					);
					break;
				case FramebufferTextureFormat::RED_INTEGER:
					AttachColorTexture(
						_color_attachments[i],
						_config.samples,
						GL_R32I,
						GL_RED_INTEGER,
						FilterToGLFilter(_color_attachment_configs[i].sampler_config.min_filter),
						FilterToGLFilter(_color_attachment_configs[i].sampler_config.mag_filter),
						WrapToGLWrap(_color_attachment_configs[i].sampler_config.wrap_s),
						WrapToGLWrap(_color_attachment_configs[i].sampler_config.wrap_t),
						WrapToGLWrap(_color_attachment_configs[i].sampler_config.wrap_r),
						_config.width,
						_config.height,
						i
					);
					break;
				default:
					break;
			}
		}
	}

	if (_depth_attachment_config.TextureFormat != FramebufferTextureFormat::None)
	{
		CreateTextures(multisample, &_depth_attachment, 1);
		BindTexture(multisample, _depth_attachment);
		switch (_depth_attachment_config.TextureFormat)
		{
			case FramebufferTextureFormat::DEPTH24STENCIL8:
				AttachDepthTexture(
					_depth_attachment,
					_config.samples,
					GL_DEPTH24_STENCIL8,
					GL_DEPTH_STENCIL_ATTACHMENT,
					FilterToGLFilter(_depth_attachment_config.sampler_config.min_filter),
					FilterToGLFilter(_depth_attachment_config.sampler_config.mag_filter),
					WrapToGLWrap(_depth_attachment_config.sampler_config.wrap_s),
					WrapToGLWrap(_depth_attachment_config.sampler_config.wrap_t),
					WrapToGLWrap(_depth_attachment_config.sampler_config.wrap_r),
					_config.width, _config.height);
				break;
			default:
				break;
		}
	}

	if (_color_attachments.size() > 1)
	{
		KN_ASSERT(_color_attachments.size() <= 4);
		GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers(_color_attachments.size(), buffers);
	}
	else if (_color_attachments.empty())
	{
		// Only depth-pass
	#ifdef KN_PLATFORM_WEB
		glDrawBuffers(1, (GLenum[]){ GL_NONE });
	#else
		glDrawBuffer(GL_NONE);
	#endif
	}

	KN_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLFramebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _renderer_id);
	glViewport(0, 0, _config.width, _config.height);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLFramebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLFramebuffer::Resize(int width, int height)
{
	if (width == 0 || height == 0 || width > MAX_FRAME_BUFFER_SIZE || height > MAX_FRAME_BUFFER_SIZE)
	{
		Log::Warn("Attempted to rezize framebuffer to {0}, {1}", width, height);
		return;
	}
	_config.width = width;
	_config.height = height;
	
	Invalidate();
	_KN_GL_CHECK_ERROR();
}

int OpenGLFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
{
	KN_ASSERT(attachmentIndex < _color_attachments.size());

	glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
	int pixelData;
	glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
	_KN_GL_CHECK_ERROR();
	return pixelData;
}

void	OpenGLFramebuffer::CopyTextureData(Ref<Texture2D>& dest)
{
	GLubyte *data = new GLubyte[_config.width * _config.height * 4]; // RGBA;
	glReadPixels(0, 0, _config.width,  _config.height, GL_RGBA8, GL_UNSIGNED_BYTE, data);

	dest->SetData(data, _config.width * _config.height * 4);
	delete[] data;
	_KN_GL_CHECK_ERROR();
}

void	OpenGLFramebuffer::ClearAttachment(uint32_t attachmentIndex, int value)
{
#if KINAI_OPENGL_VERSION_MAJOR >= 4
	KN_ASSERT(attachmentIndex < _color_attachments.size());

	auto& spec = _color_attachment_configs[attachmentIndex];
	glClearTexImage(_color_attachments[attachmentIndex], 0,
		FBTextureFormatToGL(spec.TextureFormat), GL_INT, &value);
#else
	KN_NOTUSED(attachmentIndex);
	KN_NOTUSED(value);
	KN_NOTUSED(FBTextureFormatToGL);
	Log::Warn("glClearTexImage was introduced in OpenGL 4.4, current version is {}.{}",
		KINAI_OPENGL_VERSION_MAJOR, KINAI_OPENGL_VERSION_MINOR);
#endif
	_KN_GL_CHECK_ERROR();
}

} // Kinai
