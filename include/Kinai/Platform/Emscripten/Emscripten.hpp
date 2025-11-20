#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Core/Window.hpp"
#include "Kinai/Events/ApplicationEvent.hpp"
#include "Kinai/Events/KeyEvent.hpp"
#include "Kinai/Events/MouseEvent.hpp"
#include "Kinai/ImGui/ImGuiLayer.hpp"
#include "Kinai/Core/KeyCode.hpp"
#include "Kinai/Core/MouseButton.hpp"

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>

enum
{
	EMSC_NONE = 0,
	EMSC_ANTIALIAS = (1 << 1)
};

namespace Kinai
{

class EmWindow : public Window
{
public:
	EmWindow(const WindowProps& props, int flags);
	~EmWindow() = default;
	
	void OnUpdate() override;

	void* GetNativeWindow() const override;
	glm::ivec2 GetSize() const override;
	glm::ivec2 GetSizeInPixels() const override;
	uint32_t GetWidth() const override;
	uint32_t GetHeight() const override;

	#ifdef KINAI_SOKOL
		sg_environment GetSokolEnvironment() const override;
		sg_swapchain GetSokolSwapchain() const override;
	#endif

	bool IsVSync() const override;
	void SetVSync(bool enabled) override;
	void SetEventCallback(const EventCallback &callback) override;
	void SetTitle(const std::string &title) override;

	bool GetRelativeMouseMode() const override { return true; }
	bool IsFocused() const override { return true; }
	bool IsHovered() const override { return true; }
	
	void SetRelativeMouseMode(bool enabled) override;
	void WarpMouse(float x, float y) override;

	void ToggleFullscreen() override;

	static bool IsKeyPressed(KeyCode key) { return _keys[key]; }
	static bool IsMouseButtonPressed(MouseButton button) { return _mouse.buttons[button]; }
	static glm::vec2 GetMousePosition() { return _mouse.pos; }

public:
	static EmWindow& Get() { return *_instance; }

private:
	static bool OnWindowResize(int type, const EmscriptenUiEvent *event, void *data);
	static bool OnKeyPressed(int type, const EmscriptenKeyboardEvent *event, void *data);
	static bool OnKeyReleased(int type, const EmscriptenKeyboardEvent *event, void *data);
	static bool OnChar(int type, const EmscriptenKeyboardEvent *event, void *data);
	static bool OnMouseButtonDown(int type, const EmscriptenMouseEvent *event, void *data);
	static bool OnMouseButtonUp(int type, const EmscriptenMouseEvent *event, void *data);
	static bool OnMouseMotion(int type, const EmscriptenMouseEvent *event, void *data);
	static bool OnMouseWheel(int type, const EmscriptenWheelEvent *event, void *data);
	static bool OnFullscreenChange(int type, const EmscriptenFullscreenChangeEvent *event, void *data);

private:
	static EmWindow* _instance;
	static const char* _canvas_name;
	static int _sample_count;
	static double _width;
	static double _height;
	static GLint _framebuffer;
	static EventCallback _eventCallback;
	static bool _keys[Key::KeyCode_NUM];
	static struct EmMouse
	{
		bool buttons[Mouse::MouseButton_NUM];
		glm::vec2 pos;
	}_mouse;
};

ImGuiKey	Em_KeyEventToImGuiKey(const EmscriptenKeyboardEvent* e);
KeyCode		Em_KeyEventToKeyCode(const EmscriptenKeyboardEvent* e);

} // Kinai
