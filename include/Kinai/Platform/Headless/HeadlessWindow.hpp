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

	void OnUpdate() override;
	void* GetNativeWindow() const override;
	glm::ivec2 GetSize() const override;
	glm::ivec2 GetSizeInPixels() const override;
	uint32_t GetWidth() const override;
	uint32_t GetHeight() const override;
	bool GetRelativeMouseMode() const override;
	bool IsVSync() const override;
	bool IsFocused() const override;
	bool IsHovered() const override;
	bool SetVSync(bool enabled) override;
	bool SetEventCallback(const EventCallback &callback) override;
	bool SetTitle(const std::string &title) override;
	bool SetRelativeMouseMode(bool enabled) override;
	bool WarpMouse(float x, float y) override;
	bool ToggleFullscreen() override;

private:
	EventCallback _eventCallback;
	std::string _title;
	bool _relativeMouseMode;
	glm::vec2 _mousePosition;
	bool _vsync;
	bool _focused;
	bool _hovered;
	bool _fullscreen;
	glm::ivec2 _size;
};

} // Kinai
