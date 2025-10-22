#include "Kinai/Core/Application.hpp"
#include "Kinai/Debug/Profiler.hpp"
#include "Kinai/Renderer/Renderer.hpp"
#include "Kinai/Renderer/2D/Painter.hpp"
#include "Kinai/Debug/Text/Text.hpp"

namespace Kinai
{

Application*	Application::_instance;

Application::Application(const ApplicationConfig &config)
	: _window(nullptr),
	  _config(config),
	  _gui_layer(nullptr),
	  _layerStack(),
	  _minimized(false)
{
	KN_PROFILE_FUNC();

	#ifdef KINAI_PROFILER
		Kinai::Profiler::Start(config.name);
	#endif

	Log::Validate(!_instance, "Application already exists!");
	_instance = this;

	#ifdef KINAI_HEADLESS
		void SigIntHandler(int signum);
		std::signal(SIGINT, SigIntHandler);
	#endif

	_window = Window::Create(
		WindowProps(
			config.name,
			config.window_width, config.window_height,
			config.fullscreen, config.no_vsync
		)
	);
	
	#if defined(KINAI_OPENGL) || defined(KINAI_SOKOL)
		SDL_RegisterEvents(KN_CUSTOM_EVENT_TYPE_COUNT);
	#endif
	
	_window->SetEventCallback(KN_BIND_EVENT_FN(Application::OnEvent));
	std::memset(&_time, 0, sizeof(Time));

	#if defined(KINAI_SOKOL)
		Sokol::Init();
	#else
		Renderer::Init();
		Painter::Init();
		Kinai::DebugText::Init();
	#endif

	if (config.enable_gui)
	{
		PushLayer<GUILayer>();
		_gui_layer = GetLayer<GUILayer>();
	}
}

Application::~Application()
{
	KN_PROFILE_FUNC();

	_layerStack.clear();

#ifdef KINAI_SOKOL
	Sokol::Shutdown();
#else
	Kinai::DebugText::Shutdown();
	Painter::Shutdown();
#endif
	_instance = nullptr;

	#ifdef KINAI_PROFILER
		Kinai::Profiler::End();
	#endif
}

void	Application::Close()
{
	KN_PROFILE_FUNC();

#if defined(KN_PLATFORM_DESKTOP)
	g_KinaiApplicationRunning = false;
#elif defined(KN_PLATFORM_WEB)
	emscripten_cancel_main_loop();
#endif
}

void	Application::Run()
{
	KN_PROFILE_FUNC();

#ifdef KN_PLATFORM_DESKTOP
	while (g_KinaiApplicationRunning)
#endif
	{
	#ifndef KINAI_HEADLESS
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
	#endif

		if (!_minimized)
		{
			for (auto& layer : _layerStack)
				layer->OnUpdate(_time.delta);
			for (auto& layer : _layerStack)
				layer->OnRender();
			_time.frames++;
		}

		if (_config.enable_gui)
		{
			_gui_layer->Begin();
			for (auto& layer : _layerStack)
				layer->OnGUIRender();
			_gui_layer->End();
		}

		_window->OnUpdate();

		// Handle layer transitions
		for (auto& pending : Layer::_pendingTransitions)
		{
			auto& [from, layer] = pending;
			from->DoTransition(std::move(layer));
		}
		Layer::_pendingTransitions.clear();
	}
}

bool	Application::OnWindowClose(WindowCloseEvent &event)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(event);
	Close();
	return true;
}

bool	Application::OnWindowResize(WindowResizeEvent &event)
{
	KN_PROFILE_FUNC();

	if (event.GetWidth() == 0 || event.GetHeight() == 0)
	{
		_minimized = true;
		return false;
	}

	_minimized = false;
	math::ivec2 size = _window->GetSize();
	Renderer::SetViewport(0, 0, size.x, size.y);
	// Painter::UpdateViewport(size.x, size.y);

	// Forward the event
	return false;
}

} // Kinai
