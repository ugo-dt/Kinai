#pragma once

#include "Kinai/Core/Core.hpp"

namespace Kinai
{

enum class FramebufferTextureFormat
{
	None = 0,

	// Color
	RGBA8,
	RED_INTEGER,

	// Depth/stencil
	DEPTH24STENCIL8,

	// Defaults
	Depth = DEPTH24STENCIL8
};

struct FramebufferTextureConfig
{
	FramebufferTextureConfig() = default;
	FramebufferTextureConfig(FramebufferTextureFormat format)
		: TextureFormat(format) {}

	FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
	// TODO: filtering/wrap
};

struct FramebufferAttachmentConfig
{
	FramebufferAttachmentConfig() = default;
	FramebufferAttachmentConfig(std::initializer_list<FramebufferTextureConfig> attachments)
		: attachments(attachments) {}

	std::vector<FramebufferTextureConfig> attachments;
};

struct FramebufferConfig
{
	uint32_t	width = 0, height = 0;
	FramebufferAttachmentConfig	attachments;
	uint32_t	samples = 1;
	bool		swapChainTarget = false;
};

class Framebuffer
{
public:
	virtual ~Framebuffer() = default;

	virtual void	Bind() = 0;
	virtual void	Unbind() = 0;

	virtual void	Resize(uint32_t width, uint32_t height) = 0;
	virtual int		ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

	virtual void	ClearAttachment(uint32_t attachmentIndex, int value) = 0;

	virtual uint32_t	GetColorAttachmentRendererID(uint32_t index = 0) const = 0;
	virtual uint32_t	GetDepthAttachmentRendererID() const = 0;

	virtual const FramebufferConfig&	GetConfig() const = 0;
	virtual uint32_t	GetRendererID() const = 0;

	static Ref<Framebuffer> Create(const FramebufferConfig& config);

};

} // Kinai
