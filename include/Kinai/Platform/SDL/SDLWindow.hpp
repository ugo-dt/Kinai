#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Core/Window.hpp"
#include "Kinai/Events/ApplicationEvent.hpp"
#include "Kinai/Events/MouseEvent.hpp"
#include "Kinai/Events/KeyEvent.hpp"

namespace Kinai
{

class SDLWindow final : public Window
{
public:
	SDLWindow(const WindowProps &props);
	~SDLWindow();

	void OnUpdate() override;

	void* GetNativeWindow() const override;
	math::ivec2 GetSize() const override;
	math::ivec2 GetSizeInPixels() const override;
	uint32_t GetWidth() const override;
	uint32_t GetHeight() const override;
	bool GetRelativeMouseMode() const override;
	
	bool IsVSync() const override;
	bool IsFocused() const override;
	bool IsHovered() const override;

#ifdef KINAI_SOKOL
	sg_environment GetSokolEnvironment() const override;
	sg_swapchain GetSokolSwapchain() const override;
#endif

	void SetVSync(bool enabled) override;
	void SetEventCallback(const EventCallback &callback) override;
	void SetTitle(const std::string &title) override;
	void SetRelativeMouseMode(bool enabled) override;
	void WarpMouse(float x, float y) override;
	void ToggleFullscreen() override;

private:
	void _handle_window_events(SDL_WindowEvent *_window_event);
	void _handle_event(SDL_Event &event);

private:
	SDL_Window *_handle;
	SDL_GLContext _gl_context;

	void (*_window_size_callback)(SDLWindow &window, uint32_t width, uint32_t height);
	void (*_window_close_callback)(SDLWindow &window);
	void (*_key_callback)(SDLWindow &window, SDL_KeyboardEvent &event);
	void (*_mouse_button_callback)(SDLWindow &window, SDL_MouseButtonEvent &event);
	void (*_mouse_wheel_callback)(SDLWindow &window, float wheel_x, float wheel_y);
	void (*_cursor_pos_callback)(SDLWindow &window, float mouse_x, float mouse_y, float rel_x, float rel_y);

	struct Data
	{
		std::string title;
		EventCallback eventCallback;
		uint32_t width, height;
		int sample_count;
		bool no_depth_buffer;
	};

	Data	_data;
};

} // Kinai
