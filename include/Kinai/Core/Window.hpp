#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Events/Event.hpp"
#include "Kinai/Sokol/Sokol.hpp"

static constexpr uint32_t KN_DEFAULT_WINDOW_WIDTH = 1280;
static constexpr uint32_t KN_DEFAULT_WINDOW_HEIGHT = 720;

namespace Kinai
{

struct WindowProps
{
	std::string	title;
	uint32_t	width;
	uint32_t	height;
	bool		fullscreen;
	bool		vsync;

	WindowProps(
		const std::string& title = "Kinai",
		uint32_t width = KN_DEFAULT_WINDOW_WIDTH,
		uint32_t height = KN_DEFAULT_WINDOW_HEIGHT,
		bool fullscreen = false,
		bool vsync = true
	)
		: title(title), width(width), height(height), fullscreen(fullscreen), vsync(vsync)
	{
	}
};

class Window
{
public:
	using EventCallback = std::function<void(Event &event)>;

protected:
	Window() = default;

public:
	virtual ~Window() = default;

	virtual void			OnUpdate() = 0;

	virtual void*			GetNativeWindow() const = 0;
	virtual glm::ivec2		GetSize() const = 0;
	virtual uint32_t		GetWidth() const = 0;
	virtual uint32_t		GetHeight() const = 0;
	virtual bool			GetRelativeMouseMode() const = 0;
	virtual bool			IsFocused() const = 0;
	virtual bool			IsHovered() const = 0;
	
	virtual sg_environment	GetSokolEnvironment() const = 0;
	virtual sg_swapchain	GetSokolSwapchain() const = 0;

	virtual bool			IsVSync() const = 0;
	virtual void			SetVSync(bool enabled) = 0;
	virtual void			SetEventCallback(const EventCallback &callback) = 0;
	virtual void			SetTitle(const std::string &title) = 0;
	virtual void			SetRelativeMouseMode(bool enabled) = 0;
	virtual void			WarpMouse(float x, float y) = 0;

	static std::unique_ptr<Window>	Create(const WindowProps &props);
};

}
