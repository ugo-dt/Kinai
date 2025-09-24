#include "Kinai/Platform/Emscripten/Emscripten.hpp"
#include "Kinai/Core/Application.hpp"
#include "Kinai/Core/Core.hpp"

namespace Kinai
{

EmWindow*				EmWindow::_instance;
const char*				EmWindow::_canvas_name;
int						EmWindow::_sample_count;
double					EmWindow::_width;
double					EmWindow::_height;
GLint					EmWindow::_framebuffer;
Window::EventCallback	EmWindow::_eventCallback;
bool					EmWindow::_keys[Key::KeyCode_NUM];
EmWindow::EmMouse		EmWindow::_mouse;

EmWindow::EmWindow(const WindowProps& props, int flags)
{
	KN_PROFILE_FUNC();

	KN_ASSERT(!_instance, "EmWindow already exists!");
	_instance = this;

	_canvas_name = "#canvas";
	emscripten_set_window_title(props.title.c_str());
	emscripten_get_element_css_size(_canvas_name, &_width, &_height);
	emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, false, EmWindow::OnWindowResize);
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
	EmscriptenWebGLContextAttributes attrs;
	emscripten_webgl_init_context_attributes(&attrs);
	attrs.antialias = flags & EMSC_ANTIALIAS;
	attrs.majorVersion = 2;
	_sample_count = (flags & EMSC_ANTIALIAS) ? 4 : 1;
	ctx = emscripten_webgl_create_context(_canvas_name, &attrs);
	emscripten_webgl_make_context_current(ctx);
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint *)&_framebuffer);

	emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, true, EmWindow::OnKeyPressed);
	emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, true, EmWindow::OnKeyReleased);
	emscripten_set_keypress_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, this, true, EmWindow::OnChar);
	emscripten_set_mousedown_callback("canvas", this, true, EmWindow::OnMouseButtonDown);
	emscripten_set_mouseup_callback("canvas", this, true, EmWindow::OnMouseButtonUp);
	// emscripten_set_mouseenter_callback("canvas", this, true,
	// 	[](int, const EmscriptenMouseEvent*, void*)->EM_BOOL {
	// 		auto& io = ImGui::GetIO();
	// 		for (int i = 0; i < 3; i++) {
	// 			_button_down[i] = _button_up[i] = false;
	// 			io.MouseDown[i] = false;
	// 		}
	// 		return true;
	// 	});
	// emscripten_set_mouseleave_callback("canvas", this, true,
	// 	[](int, const EmscriptenMouseEvent*, void*)->EM_BOOL {
	// 		auto& io = ImGui::GetIO();
	// 		for (int i = 0; i < 3; i++) {
	// 			_button_down[i] = _button_up[i] = false;
	// 			io.MouseDown[i] = false;
	// 		}
	// 		return true;
	// 	});
	emscripten_set_mousemove_callback("canvas", this, true, EmWindow::OnMouseMotion);
	emscripten_set_wheel_callback("canvas", this, true, EmWindow::OnMouseWheel);
	emscripten_set_canvas_element_size(_canvas_name, _width, _height);
}

void	EmWindow::OnUpdate()
{
	KN_PROFILE_FUNC();
}

void*	EmWindow::GetNativeWindow() const
{
	return nullptr;
}

glm::ivec2		EmWindow::GetSize() const
{
	KN_PROFILE_FUNC();

	return glm::ivec2(GetWidth(), GetHeight());
}

uint32_t	EmWindow::GetWidth() const
{
	KN_PROFILE_FUNC();

	return _width;
}

uint32_t	EmWindow::GetHeight() const
{
	KN_PROFILE_FUNC();

	return _height;
}

#ifdef KINAI_SOKOL
sg_environment	EmWindow::GetSokolEnvironment() const
{
	KN_PROFILE_FUNC();

	sg_environment env = {};

	env.defaults.color_format = SG_PIXELFORMAT_RGBA8;
	env.defaults.depth_format = SG_PIXELFORMAT_DEPTH_STENCIL;
	env.defaults.sample_count = _sample_count;
	return env;
}

sg_swapchain	EmWindow::GetSokolSwapchain() const
{
	KN_PROFILE_FUNC();

	sg_swapchain swapchain = {};

	swapchain.width = (int)_width;
	swapchain.height = (int)_height;
	swapchain.sample_count = _sample_count;
	swapchain.color_format = SG_PIXELFORMAT_RGBA8;
	swapchain.depth_format = SG_PIXELFORMAT_DEPTH_STENCIL;
	swapchain.gl.framebuffer = (uint32_t)_framebuffer;
	return swapchain;
}
#endif

bool	EmWindow::IsVSync() const
{
	KN_PROFILE_FUNC();

	int mode;
	emscripten_get_main_loop_timing(&mode, nullptr);
	return mode == EM_TIMING_RAF;
}

void	EmWindow::SetVSync(bool enabled)
{
	KN_PROFILE_FUNC();

	if (enabled)
		emscripten_set_main_loop_timing(EM_TIMING_RAF, 1);
	else
		emscripten_set_main_loop_timing(EM_TIMING_SETTIMEOUT, 1);
}

void	EmWindow::SetEventCallback(const EventCallback &callback)
{
	KN_PROFILE_FUNC();

	_eventCallback = callback;
}

void	EmWindow::SetTitle(const std::string &title)
{
	KN_PROFILE_FUNC();

	emscripten_set_window_title(title.c_str());
}

void	EmWindow::SetRelativeMouseMode(bool enabled)
{
	KN_PROFILE_FUNC();

	if (enabled)
		emscripten_request_pointerlock("canvas", true);
	else
		emscripten_exit_pointerlock();
}

void	EmWindow::WarpMouse(float x, float y)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(x);
	KN_NOTUSED(y);
}

bool	EmWindow::OnWindowResize(int, const EmscriptenUiEvent *, void *)
{
	KN_PROFILE_FUNC();

	emscripten_get_element_css_size(_canvas_name, &_width, &_height);
	emscripten_set_canvas_element_size(_canvas_name, _width, _height);
	return true;
}

bool	EmWindow::OnKeyPressed(int, const EmscriptenKeyboardEvent *e, void *)
{
	if (e->keyCode < 512)
	{
		ImGuiKey imguiKey = Em_KeyEventToImGuiKey(e);
		ImGui::GetIO().AddKeyEvent(imguiKey, true);

		KeyCode key = Em_KeyEventToKeyCode(e);
		KeyPressedEvent event(key);
		_eventCallback(event);
		_keys[key] = true;
	}

	// Only forward alpha-numeric keys to browser
	return e->keyCode < 32;
}

bool	EmWindow::OnKeyReleased(int, const EmscriptenKeyboardEvent *e, void *)
{
	if (e->keyCode < 512)
	{
		ImGuiKey imguiKey = Em_KeyEventToImGuiKey(e);
		ImGui::GetIO().AddKeyEvent(imguiKey, false);

		KeyCode key = Em_KeyEventToKeyCode(e);
		KeyReleasedEvent event(key);
		_eventCallback(event);
		_keys[key] = false;
	}
	// Only forward alpha-numeric keys to browser
	return e->keyCode < 32;
}

bool	EmWindow::OnChar(int, const EmscriptenKeyboardEvent *e, void *)
{
	ImGui::GetIO().AddInputCharacter((ImWchar)e->charCode);
	return true;
}

bool	EmWindow::OnMouseButtonDown(int, const EmscriptenMouseEvent *e, void *)
{
	/** Emscripten mouse buttons: Left: 0, Middle: 1, Right: 2
	 * ImGui mouse buttons:      Left: 0, Middle: 2, Right: 1 */
	switch (e->button)
	{
		case 0:
		{
			ImGui::GetIO().AddMouseButtonEvent(0, true);
			MouseButtonPressedEvent event(Mouse::ButtonLeft);
			_eventCallback(event);
			break;
		}
		case 1:
		{
			ImGui::GetIO().AddMouseButtonEvent(2, true);
			MouseButtonPressedEvent event(Mouse::ButtonMiddle);
			_eventCallback(event);
			break;
		}
		case 2:
		{
			ImGui::GetIO().AddMouseButtonEvent(1, true);
			MouseButtonPressedEvent event(Mouse::ButtonRight);
			_eventCallback(event);
			break;
		}
		default:
		{
			ImGui::GetIO().AddMouseButtonEvent(e->button, true);
			MouseButtonPressedEvent event(e->button);
			_eventCallback(event);
			break;
		}
	}
	return true;
}

bool	EmWindow::OnMouseButtonUp(int, const EmscriptenMouseEvent *e, void *)
{
	switch (e->button)
	{
		case 0:
		{
			ImGui::GetIO().AddMouseButtonEvent(0, false);
			MouseButtonPressedEvent event(Mouse::ButtonLeft);
			_eventCallback(event);
			break;
		}
		case 1:
		{
			ImGui::GetIO().AddMouseButtonEvent(2, false);
			MouseButtonPressedEvent event(Mouse::ButtonMiddle);
			_eventCallback(event);
			break;
		}
		case 2:
		{
			ImGui::GetIO().AddMouseButtonEvent(1, false);
			MouseButtonPressedEvent event(Mouse::ButtonRight);
			_eventCallback(event);
			break;
		}
		default:
		{
			ImGui::GetIO().AddMouseButtonEvent(e->button, false);
			MouseButtonPressedEvent event(e->button);
			_eventCallback(event);
			break;
		}
	}
	return true;
}

bool	EmWindow::OnMouseMotion(int, const EmscriptenMouseEvent *e, void *)
{
	ImGui::GetIO().AddMousePosEvent(e->targetX, e->targetY);

	MouseMotionEvent event(e->targetX, e->targetY, e->movementX, e->movementY);
	_eventCallback(event);
	_mouse.pos = glm::vec2(e->targetX, e->targetY);
	return true;
}

bool	EmWindow::OnMouseWheel(int, const EmscriptenWheelEvent *e, void *)
{
	ImGui::GetIO().AddMouseWheelEvent(e->deltaX, e->deltaY);

	MouseWheelEvent event(e->deltaX, e->deltaY);
	_eventCallback(event);
	return true;
}

} // Kinai
