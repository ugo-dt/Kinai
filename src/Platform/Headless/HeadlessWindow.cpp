#include "Kinai/Platform/Headless/HeadlessWindow.hpp"
#include "Kinai/Core/Application.hpp"

namespace Kinai
{

void	SigIntHandler(int signum)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(signum);
	Log::Info("[Kinai] Caught signal interrupt. Stopping.");
	Application::Get().Close();
}

HeadlessWindow::HeadlessWindow(const WindowProps& props)
	: _eventCallback(nullptr)
{
	KN_PROFILE_FUNC();

	Log::Info("[Kinai] Headless --- {}", props.title);
	_fullscreen = props.fullscreen;
	_title = props.title;
	_size = { (int)props.width, (int)props.height };
	_vsync = !props.no_vsync;
	_relativeMouseMode = false;
	_mousePosition = { 0.f, 0.f };
}

HeadlessWindow::~HeadlessWindow()
{
	KN_PROFILE_FUNC();
}

void	HeadlessWindow::OnUpdate()
{
	KN_PROFILE_FUNC();
}

void*	HeadlessWindow::GetNativeWindow() const
{
	KN_PROFILE_FUNC();

	return nullptr;
}

glm::ivec2	HeadlessWindow::GetSize() const
{
	KN_PROFILE_FUNC();

	return _size;
}

glm::ivec2	HeadlessWindow::GetSizeInPixels() const
{
	KN_PROFILE_FUNC();

	return GetSize();
}

uint32_t	HeadlessWindow::GetWidth() const
{
	KN_PROFILE_FUNC();

	return _size.x;
}

uint32_t	HeadlessWindow::GetHeight() const
{
	KN_PROFILE_FUNC();

	return _size.y;
}

bool	HeadlessWindow::GetRelativeMouseMode() const
{
	KN_PROFILE_FUNC();

	return _relativeMouseMode;
}

bool	HeadlessWindow::IsVSync() const
{
	KN_PROFILE_FUNC();

	return _vsync;
}

bool	HeadlessWindow::IsFocused() const
{
	KN_PROFILE_FUNC();

	return _focused;
}

bool	HeadlessWindow::IsHovered() const
{
	KN_PROFILE_FUNC();

	return _hovered;
}

#ifdef KINAI_SOKOL
sg_environment	HeadlessWindow::GetSokolEnvironment() const
{
	KN_PROFILE_FUNC();

	return {};
}

sg_swapchain	HeadlessWindow::GetSokolSwapchain() const
{
	KN_PROFILE_FUNC();

	return {};
}
#endif

void	HeadlessWindow::SetVSync(bool enabled)
{
	KN_PROFILE_FUNC();

	_vsync = enabled;
}

void	HeadlessWindow::SetEventCallback(const EventCallback &callback)
{
	KN_PROFILE_FUNC();

	_eventCallback = callback;
}

void	HeadlessWindow::SetTitle(const std::string &title)
{
	KN_PROFILE_FUNC();

	_title = title;
}

void	HeadlessWindow::SetRelativeMouseMode(bool enabled)
{
	KN_PROFILE_FUNC();

	_relativeMouseMode = enabled;
}

void	HeadlessWindow::WarpMouse(float x, float y)
{
	KN_PROFILE_FUNC();

	_mousePosition.x = x;
	_mousePosition.y = y;
}

void	HeadlessWindow::ToggleFullscreen()
{
	KN_PROFILE_FUNC();
	_fullscreen = !_fullscreen;
}

} // Kinai
