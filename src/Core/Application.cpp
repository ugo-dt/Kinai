#include "Kinai/Core/Application.hpp"

namespace Kinai
{

Application*	Application::_instance;

Application::Application(const ApplicationConfig &config)
	: _window(nullptr),
	  _config(config),
	  _imgui_layer(nullptr),
	  _layerstack(),
	  _minimized(false)
{
	EG_PRINT_FUNC();

	EG_ASSERT(!_instance, "Application already exists!");
	_instance = this;

	_window = Window::Create(
		WindowProps(
			config.name,
			config.window_width, config.window_height,
			config.fullscreen, config.vsync
		)
	);
	
	SDL_RegisterEvents(EG_CUSTOM_EVENT_TYPE_COUNT);

	_window->SetEventCallback(EG_BIND_EVENT_FN(Application::OnEvent));
	std::memset(&_time, 0, sizeof(Time));

	Renderer::Init();

	if (_config.enable_imgui)
	{
		// This gets deleted by LayerStack's destructor
		_imgui_layer = static_cast<ImGuiLayer *>(PushOverlay(new ImGuiLayer()));
	}

#ifdef EG_HEADLESS
	void SigIntHandler(int signum);
	std::signal(SIGINT, SigIntHandler);
#endif
}

Application::~Application()
{
	EG_PRINT_FUNC();

	_layerstack.Clear();
	Renderer::Shutdown();
}

void	Application::OnEvent(Event& event)
{
	EG_PRINT_FUNC();
	EventDispatcher	dispatcher(event);

	dispatcher.Dispatch<WindowCloseEvent>(EG_BIND_EVENT_FN(Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(EG_BIND_EVENT_FN(Application::OnWindowResize));
	for (auto it = _layerstack.rbegin(); it != _layerstack.rend(); it++)
	{
		(*it)->OnEvent(event);
		if (event.handled)
			break;
	}
}

Layer	*Application::PushLayer(Layer* layer)
{
	EG_PRINT_FUNC();

	_layerstack.PushLayer(layer);
	layer->OnAttach();
	return layer;
}

Layer	*Application::PushOverlay(Layer* layer)
{
	EG_PRINT_FUNC();

	_layerstack.PushOverlay(layer);
	layer->OnAttach();
	return layer;
}

void	Application::Close()
{
	EG_PRINT_FUNC();

#if defined(EG_PLATFORM_DESKTOP)
	g_KinaiApplicationRunning = false;
#elif defined(EG_PLATFORM_WEB)
	emscripten_cancel_main_loop();
#endif
}

void	Application::Run()
{
	EG_PRINT_FUNC();

#ifdef EG_PLATFORM_DESKTOP
	while (g_KinaiApplicationRunning)
#endif
	{
		const uint64_t	perf_counter = SDL_GetPerformanceCounter();

		_time.delta = (double)(perf_counter - _time.last) / (double)SDL_GetPerformanceFrequency();
		_time.last = perf_counter;

		_time.frame_time = (perf_counter - _time.last_second) * 1000.0 / SDL_GetPerformanceFrequency();
		if (_time.frame_time > 1000)
		{
			_time.fps = _time.frames;
			_time.frames = 0;
			_time.last_second = perf_counter;
		}

		if (!_minimized)
		{
			for (Layer* layer : _layerstack)
				layer->OnUpdate(_time.delta);
			_time.frames++;

			if (_config.enable_imgui)
			{
				_imgui_layer->Begin();
				for (Layer* layer : _layerstack)
					layer->OnImGuiRender();
				_imgui_layer->End();
			}
		}

		_window->OnUpdate();
	}
}

bool	Application::OnWindowClose(WindowCloseEvent &event)
{
	EG_PRINT_FUNC();

	(void)event;
	Close();
	return true;
}

bool	Application::OnWindowResize(WindowResizeEvent &event)
{
	EG_PRINT_FUNC();

	(void)event;

	if (event.GetWidth() == 0 || event.GetHeight() == 0)
	{
		_minimized = true;
		return false;
	}

	_minimized = false;
	glm::ivec2 size = _window->GetSize();
	Renderer::OnWindowResize(size.x, size.y);

	// Forward the event
	return false;
}

} // Kinai
