#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Core/Input.hpp"
#include "Kinai/Core/Time.hpp"
#include "Kinai/Core/Window.hpp"
#include "Kinai/Core/Layer.hpp"
#include "Kinai/Core/LayerStack.hpp"
#include "Kinai/Events/Event.hpp"
#include "Kinai/Events/ApplicationEvent.hpp"
#include "Kinai/Events/KeyEvent.hpp"
#include "Kinai/Events/MouseEvent.hpp"
#include "Kinai/ImGui/ImGuiLayer.hpp"
#include "Kinai/Renderer/Renderer.hpp"

extern bool	g_KinaiApplicationRunning;

namespace Kinai
{

struct ApplicationConfig
{
	std::string	name = "Kinai Application";
	uint32_t	window_width = KN_DEFAULT_WINDOW_WIDTH;
	uint32_t	window_height = KN_DEFAULT_WINDOW_HEIGHT;
	bool		fullscreen = false;
	bool		no_vsync = true;
	bool		enable_imgui = false;
};

class Application
{
public:
	Application(const ApplicationConfig &config);
	virtual ~Application();
	
	void		OnEvent(Event& event);

	Layer*		PushLayer(Layer* layer);
	Layer*		PushOverlay(Layer* layer);
	
	void		Close();

	Window&		GetWindow()     { return *_window; }

	uint64_t	GetFPS()        const { return _time.fps; }
	float		GetDeltaTime()  const { return _time.delta; }
	ImGuiLayer*	GetImGuiLayer() const { return _imgui_layer; }

	void		Run();
public:
	static Application& Get() { return *_instance; }

private:
	bool	OnWindowClose(WindowCloseEvent &event);
	bool	OnWindowResize(WindowResizeEvent &event);

private:
	Scope<Window>	_window;
	ApplicationConfig		_config;
	ImGuiLayer*				_imgui_layer;
	Time					_time;
	LayerStack				_layerstack;
	bool					_minimized;

private:
	static Application	*_instance;

private:
	friend int	Main(int argc, char **argv);
};

extern Application	*CreateApplication(int argc, char **argv);

} // Kinai
