#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Core/Window.hpp"

namespace Kinai
{

class HeadlessWindow : public Window
{
public:
	HeadlessWindow(const WindowProps& props);
	~HeadlessWindow();

	// Unused

	void			OnUpdate() override KN_UNUSED;
	void*			GetNativeWindow() const override KN_UNUSED;
	glm::ivec2		GetSize() const override KN_UNUSED;
	uint32_t		GetWidth() const override KN_UNUSED;
	uint32_t		GetHeight() const override KN_UNUSED;
	bool			GetRelativeMouseMode() const override KN_UNUSED;
	bool			IsVSync() const override KN_UNUSED;
	bool			IsFocused() const override KN_UNUSED;
	bool			IsHovered() const override KN_UNUSED;
	sg_environment	GetSokolEnvironment() const override KN_UNUSED;
	sg_swapchain	GetSokolSwapchain() const override KN_UNUSED;
	void			SetVSync(bool enabled) override KN_UNUSED;
	void			SetEventCallback(const EventCallback &callback) override KN_UNUSED;
	void			SetTitle(const std::string &title) override KN_UNUSED;
	void			SetRelativeMouseMode(bool enabled) override KN_UNUSED;
	void			WarpMouse(float x, float y) override KN_UNUSED;

private:
	EventCallback	_eventCallback;
};

} // Kinai
