#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Core/Input.hpp"
#include "Kinai/Core/Layer.hpp"
#include "Kinai/Core/LayerStack.hpp"
#include "Kinai/Core/Window.hpp"
#include "Kinai/Events/Event.hpp"
#include "Kinai/Events/ApplicationEvent.hpp"
#include "Kinai/Events/KeyEvent.hpp"
#include "Kinai/Events/MouseEvent.hpp"
#include "Kinai/ImGui/ImGuiLayer.hpp"

extern bool	g_KinaiApplicationRunning;

namespace Kinai
{

struct ApplicationConfig
{
	std::string name = "Kinai Application";
	uint32_t window_width = KN_DEFAULT_WINDOW_WIDTH;
	uint32_t window_height = KN_DEFAULT_WINDOW_HEIGHT;
	bool fullscreen = false;
	bool no_vsync = false;
	bool enable_imgui = false;
};

struct Time
{
	uint64_t fps;
	uint64_t frames;
	uint64_t last;
	uint64_t last_second;
	float frame_time;
	float delta;
};

class Application
{
public:
	Application(const ApplicationConfig &config);
	virtual ~Application();

	Ref<Layer> PushLayer(Ref<Layer> layer);
	void PopLayer();
	void RemoveLayer(Ref<Layer> layer);

	void Close();

	Window& GetWindow() { return *_window; }
	const Window& GetWindow() const { return *_window; }
	uint64_t GetFPS() const { return _time.fps; }
	float GetDeltaTime() const { return _time.delta; }
	Ref<ImGuiLayer> GetImGuiLayer() const { return _imgui_layer; }

public:
	static Application& Get() { return *_instance; }

private:
	void Run();

	template <class EventType>
	requires(std::is_base_of_v<Event, EventType>)
	void OnEvent(EventType& event);

	bool OnWindowClose(WindowCloseEvent &event);
	bool OnWindowResize(WindowResizeEvent &event);

private:
	Scope<Window> _window;
	ApplicationConfig _config;
	Ref<ImGuiLayer> _imgui_layer;
	Time _time;
	LayerStack _layerstack;
	bool _minimized;

private:
	static Application	*_instance;

private:
	friend int Main(int argc, char **argv);
};

template <class EventType>
requires(std::is_base_of_v<Event, EventType>)
void	Application::OnEvent(EventType& event)
{
	KN_PROFILE_FUNC();
	EventDispatcher	dispatcher(event);

	dispatcher.Dispatch<WindowCloseEvent>(KN_BIND_EVENT_FN(Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(KN_BIND_EVENT_FN(Application::OnWindowResize));
	for (auto it = _layerstack.rbegin(); it != _layerstack.rend(); it++)
	{
		(*it)->OnEvent(event);
		if (event.handled)
			break;
	}
}

extern Application	*CreateApplication(int argc, char **argv);

} // Kinai
