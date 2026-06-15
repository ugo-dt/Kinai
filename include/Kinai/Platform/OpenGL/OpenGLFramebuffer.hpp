#pragma once

#include "Kinai/Renderer/Framebuffer.hpp"
#include "Kinai/Renderer/Texture.hpp"

namespace Kinai
{

class OpenGLFramebuffer : public Framebuffer
{
public:
	OpenGLFramebuffer(const FramebufferConfig &spec);
	~OpenGLFramebuffer();

	void Invalidate();

	void Bind() override;
	void Unbind() override;

	void Resize(int width, int height) override;
	int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

	void BindAttachment(uint32_t attachmentIndex, uint32_t slot = 0) override;
	void ClearAttachment(uint32_t attachmentIndex, int value) override;

	uint32_t	GetColorAttachmentRendererID(uint32_t index = 0) const override
	{
		KN_ASSERT(index < _color_attachments.size());
		return _color_attachments[index];
	}
	uint32_t GetRendererID() const override { return _renderer_id; }
	int GetWidth() const { return _config.width; }
	int GetHeight() const { return _config.height; }
	uint32_t GetDepthAttachmentRendererID() const override { return _depth_attachment; }

	const FramebufferConfig& GetConfig() const override { return _config; }

	void CopyTextureData(Ref<Texture2D>& dest);

private:
	uint32_t _renderer_id = 0;
	FramebufferConfig _config;

	std::vector<FramebufferTextureConfig> _color_attachment_configs;
	FramebufferTextureConfig _depth_attachment_config;

	std::vector<uint32_t> _color_attachments;
	uint32_t _depth_attachment = 0;
};

}
