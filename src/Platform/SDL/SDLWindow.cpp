#include "Kinai/Platform/SDL/SDLWindow.hpp"
#include "Kinai/ImGui/ImGuiLayer.hpp"
#include "Kinai/Core/Application.hpp"

namespace Kinai
{

#define SDL_DEF(val, def) (((val) == 0) ? (def) : (val))

struct Kinai_Sokol_SDL_Desc {
	uint32_t		width, height;
	int				sample_count;
	bool			no_depth_buffer;
    int				version_major;
    int				version_minor;
	const char*		title;
	bool			fullscreen;
	bool			vsync;
};

SDLWindow::SDLWindow(const WindowProps &props)
{
	KN_PRINT_FUNC();

	Kinai_Sokol_SDL_Desc	desc = {
		.width = props.width,
		.height = props.height,
		.sample_count = 1,
		.no_depth_buffer = false,
		.version_major = 4,
		.version_minor = 1,
		.title = props.title.c_str(),
		.fullscreen = props.fullscreen,
		.vsync = props.vsync,
	};

    int				status;
	SDL_WindowFlags flags;

	Kinai_Sokol_SDL_Desc desc_def = desc;
	desc_def.sample_count = SDL_DEF(desc_def.sample_count, 1);
    desc_def.version_major = SDL_DEF(desc_def.version_major, 4);
    desc_def.version_minor = SDL_DEF(desc_def.version_minor, 1);

	#ifdef __APPLE__
		desc_def.version_major = 3;
		desc_def.version_minor = 3;
	#endif

	_data.sample_count = desc_def.sample_count;
	_data.no_depth_buffer = desc_def.no_depth_buffer;

	(void)status;
	status = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	KN_ASSERT(status == true && "Failed to init SDL");

	Log::Info("CORE - Initialized SDL.");

	if (desc_def.no_depth_buffer)
	{
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	}

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, (desc_def.sample_count == 1) ? 0 : desc_def.sample_count);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, desc_def.version_major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, desc_def.version_major);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	#ifdef KN_DEV
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	#endif

	flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_FOCUS;
	if (desc_def.fullscreen)
		flags |= SDL_WINDOW_FULLSCREEN;
	_handle = SDL_CreateWindow(desc_def.title, desc_def.width, desc_def.height, flags);
	KN_ASSERT(_handle);
	_gl_context = SDL_GL_CreateContext(_handle);
	KN_ASSERT(_gl_context);

	SDL_GL_MakeCurrent(_handle, _gl_context);
	SDL_GL_SetSwapInterval(desc_def.vsync);

	#ifdef KN_PLATFORM_DESKTOP
		status = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
		KN_ASSERT(status != 0);
	#endif

	Log::Info("CORE - OpenGL info:");
	Log::Info("  Vendor: {}", glGetString(GL_VENDOR));
	Log::Info("  Renderer: {}", glGetString(GL_RENDERER));
	Log::Info("  Version: {}", glGetString(GL_VERSION));

	_data.title = props.title;
	SDL_WarpMouseInWindow(_handle, (props.width / 2), (props.height / 2));

	_window_size_callback = [](SDLWindow &window, uint32_t width, uint32_t height)
	{
		window._data.width = width;
		window._data.height = height;

		WindowResizeEvent event(width, height);
		window._data.eventCallback(event);
	};

	_window_close_callback = [](SDLWindow &window)
	{
		WindowCloseEvent event;
		window._data.eventCallback(event);
	};

	_key_callback = [](SDLWindow &window, SDL_KeyboardEvent &keyboard_event)
	{
		if (keyboard_event.down)
		{
			KeyPressedEvent event(keyboard_event.scancode, keyboard_event.repeat);
			window._data.eventCallback(event);
		}
		else
		{
			KeyReleasedEvent event(keyboard_event.scancode);
			window._data.eventCallback(event);
		}
	};
	_mouse_button_callback = [](SDLWindow &window, SDL_MouseButtonEvent &button_event)
	{
		if (button_event.down)
		{
			MouseButtonPressedEvent event(button_event.button);
			window._data.eventCallback(event);
		}
		else
		{
			MouseButtonReleasedEvent event(button_event.button);
			window._data.eventCallback(event);
		}
	};
	_mouse_wheel_callback = [](SDLWindow &window, float wheel_x, float wheel_y)
	{
		MouseWheelEvent event(wheel_x, wheel_y);
		window._data.eventCallback(event);
	};

	_cursor_pos_callback = [](SDLWindow &window, float mouse_x, float mouse_y, float rel_x, float rel_y)
	{
		MouseMotionEvent event(mouse_x, mouse_y, rel_x, rel_y);
		window._data.eventCallback(event);
	};
	Log::Info("CORE - Created SDLWindow '{}' ({}, {}).", props.title, props.width, props.height);
}

SDLWindow::~SDLWindow()
{
	SDL_GL_DestroyContext(_gl_context);
	_gl_context = NULL;
	SDL_DestroyWindow(_handle);
	_handle = NULL;
	SDL_Quit();
	Log::Info("CORE - Destroyed SDLWindow '{}'.", _data.title);
}

void	SDLWindow::_handle_window_events(SDL_WindowEvent *_window_event)
{
	switch (_window_event->type)
	{
	case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
		_window_close_callback(*this);
		break;
	case SDL_EVENT_WINDOW_RESIZED:
		_window_size_callback(*this, _window_event->data1, _window_event->data2);
		break;
	default:
		break;
	}
}

void	SDLWindow::_handle_event(SDL_Event &event)
{
	switch (event.type)
	{
	case SDL_EVENT_QUIT:
		Application::Get().Close();
		break;
	case SDL_EVENT_KEY_DOWN:
	case SDL_EVENT_KEY_UP:
		_key_callback(*this, event.key);
		break;
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
	case SDL_EVENT_MOUSE_BUTTON_UP:
		_mouse_button_callback(*this, event.button);
		break;
	case SDL_EVENT_MOUSE_WHEEL:
		_mouse_wheel_callback(*this, event.wheel.x, event.wheel.y);
		break;
	case SDL_EVENT_MOUSE_MOTION:
		_cursor_pos_callback(*this, event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
		break;
	default:
		if (event.type >= SDL_EVENT_WINDOW_FIRST && event.type <= SDL_EVENT_WINDOW_LAST)
			_handle_window_events(&event.window);
		break;
	}
}

void	SDLWindow::OnUpdate()
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (Application::Get().GetImGuiLayer())
			ImGui_ImplSDL3_ProcessEvent(&event);
		_handle_event(event);
	}
	SDL_GL_SwapWindow(_handle);
}

void	*SDLWindow::GetNativeWindow() const
{
	return _handle;
}

glm::ivec2	SDLWindow::GetSize() const
{
	int w, h;

	SDL_GetWindowSizeInPixels(_handle, &w, &h);
	return glm::ivec2(w, h);
}

uint32_t	SDLWindow::GetWidth() const
{
	return GetSize().x;
}

uint32_t	SDLWindow::GetHeight() const
{
	return GetSize().y;
}

sg_environment	SDLWindow::GetSokolEnvironment() const
{
	sg_environment env = {};
	env.defaults.color_format = SG_PIXELFORMAT_RGBA8,
	env.defaults.depth_format = _data.no_depth_buffer ? SG_PIXELFORMAT_NONE : SG_PIXELFORMAT_DEPTH_STENCIL,
	env.defaults.sample_count = _data.sample_count;
	return env;
}

sg_swapchain	SDLWindow::GetSokolSwapchain() const
{
	int width, height;
	SDL_GetWindowSizeInPixels(_handle, &width, &height);

	sg_swapchain swapchain = {};
	swapchain.width = width,
	swapchain.height = height,
	swapchain.sample_count = _data.sample_count,
	swapchain.color_format = SG_PIXELFORMAT_RGBA8,
	swapchain.depth_format = _data.no_depth_buffer ? SG_PIXELFORMAT_NONE : SG_PIXELFORMAT_DEPTH_STENCIL,
	// we just assume here that the GL framebuffer is always 0
	swapchain.gl.framebuffer = 0;
	return swapchain;
}

bool	SDLWindow::IsVSync() const
{
	int	interval;
	SDL_GL_GetSwapInterval(&interval);
	return interval;
}

void	SDLWindow::SetVSync(bool enabled)
{
	if (enabled)
		SDL_GL_SetSwapInterval(1);
	else
		SDL_GL_SetSwapInterval(0);
}

void	SDLWindow::SetEventCallback(const EventCallback &callback)
{
	_data.eventCallback = callback;
}

void	SDLWindow::SetTitle(const std::string &title)
{
	SDL_SetWindowTitle(_handle, title.c_str());
}

bool	SDLWindow::GetRelativeMouseMode() const
{
	return SDL_GetWindowRelativeMouseMode(_handle);
}

void	SDLWindow::SetRelativeMouseMode(bool enabled)
{
	SDL_SetWindowRelativeMouseMode(_handle, enabled);
}

void	SDLWindow::WarpMouse(float x, float y)
{
	SDL_WarpMouseInWindow(_handle, x, y);
}

bool	SDLWindow::IsFocused() const
{
	return SDL_GetWindowFlags(_handle) & SDL_WINDOW_INPUT_FOCUS;
}

bool	SDLWindow::IsHovered() const
{
	return SDL_GetWindowFlags(_handle) & SDL_WINDOW_MOUSE_FOCUS;
}

}
