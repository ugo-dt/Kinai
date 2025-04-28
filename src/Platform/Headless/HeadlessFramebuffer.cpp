#include "Kinai/Platform/Headless/HeadlessFramebuffer.hpp"

namespace Kinai
{

constexpr uint32_t MAX_FRAME_BUFFER_SIZE = 8192;

// static GLenum	TextureTarget(bool multisampled)
// {
// 	KN_PRINT_FUNC();

// 	KN_NOTUSED(multisampled);
// 	return 0;
// }

// static void	CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
// {
// 	KN_PRINT_FUNC();

// 	KN_NOTUSED(multisampled);
// 	KN_NOTUSED(outID);
// 	KN_NOTUSED(count);
// }

// static void	BindTexture(bool multisampled, uint32_t id)
// {
// 	KN_PRINT_FUNC();

// 	KN_NOTUSED(multisampled);
// 	KN_NOTUSED(id);
// }

// static void	AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index)
// {
// 	KN_PRINT_FUNC();

// 	KN_NOTUSED(id);
// 	KN_NOTUSED(samples);
// 	KN_NOTUSED(internalFormat);
// 	KN_NOTUSED(format);
// 	KN_NOTUSED(width);
// 	KN_NOTUSED(height);
// 	KN_NOTUSED(index);
// }

// static void	AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
// {
// 	KN_PRINT_FUNC();

// 	KN_NOTUSED(id);
// 	KN_NOTUSED(samples);
// 	KN_NOTUSED(format);
// 	KN_NOTUSED(attachmentType);
// 	KN_NOTUSED(width);
// 	KN_NOTUSED(height);
// }

// static bool	IsDepthFormat(FramebufferTextureFormat format)
// {
// 	KN_PRINT_FUNC();

// 	switch (format)
// 	{
// 		case FramebufferTextureFormat::DEPTH24STENCIL8:  return true;
// 		default:
// 			break;
// 	}

// 	return false;
// }

HeadlessFramebuffer::HeadlessFramebuffer(const FramebufferConfig& spec)
	: _config(spec)
{
	KN_PRINT_FUNC();

	KN_NOTUSED(spec);
}

HeadlessFramebuffer::~HeadlessFramebuffer()
{
	KN_PRINT_FUNC();
}

void	HeadlessFramebuffer::Invalidate()
{
	KN_PRINT_FUNC();
}

void	HeadlessFramebuffer::Bind()
{
	KN_PRINT_FUNC();
}

void	HeadlessFramebuffer::Unbind()
{
	KN_PRINT_FUNC();
}

void	HeadlessFramebuffer::Resize(uint32_t width, uint32_t height)
{
	KN_PRINT_FUNC();

	KN_NOTUSED(width);
	KN_NOTUSED(height);
}

int	HeadlessFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
{
	KN_PRINT_FUNC();

	KN_NOTUSED(attachmentIndex);
	KN_NOTUSED(x);
	KN_NOTUSED(y);
	
	return 0;
}

void	HeadlessFramebuffer::ClearAttachment(uint32_t attachmentIndex, int value)
{
	KN_PRINT_FUNC();

	KN_NOTUSED(attachmentIndex);
	KN_NOTUSED(value);
}

} // Kinai
