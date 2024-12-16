#include "Kinai/Platform/Headless/HeadlessWindow.hpp"
#include "Kinai/Core/Application.hpp"

namespace Kinai
{

void	SigIntHandler(int signum)
{
	(void)signum;
	std::cout << "[Kinai] Caught signal interrupt. Stopping." << std::endl;
	Application::Get().Close();
}

HeadlessWindow::HeadlessWindow(const WindowProps& props)
	: _eventCallback(nullptr)
{
	std::cout << "[Kinai] Running '" << props.title << "'." << std::endl;
}

HeadlessWindow::~HeadlessWindow()
{
}

void	HeadlessWindow::OnUpdate()
{
}

void*	HeadlessWindow::GetNativeWindow() const
{
	return nullptr;
}

glm::ivec2	HeadlessWindow::GetSize() const
{
	return glm::ivec2(0, 0);
}

uint32_t	HeadlessWindow::GetWidth() const
{
	return 0;
}

uint32_t	HeadlessWindow::GetHeight() const
{
	return 0;
}

bool	HeadlessWindow::GetRelativeMouseMode() const
{
	return false;
}

bool	HeadlessWindow::IsVSync() const
{
	return false;
}

bool	HeadlessWindow::IsFocused() const
{
	return false;
}

bool	HeadlessWindow::IsHovered() const
{
	return false;
}

sg_environment	HeadlessWindow::GetSokolEnvironment() const
{
	return {};
}

sg_swapchain	HeadlessWindow::GetSokolSwapchain() const
{
	return {};
}

void	HeadlessWindow::SetVSync(bool enabled)
{
	(void)enabled;
}

void	HeadlessWindow::SetEventCallback(const EventCallback &callback)
{
	_eventCallback = callback;
}

void	HeadlessWindow::SetTitle(const std::string &title)
{
	(void)title;
}

void	HeadlessWindow::SetRelativeMouseMode(bool enabled)
{
	(void)enabled;
}

void	HeadlessWindow::WarpMouse(float x, float y)
{
	(void)x;
	(void)y;
}

} // Kinai
