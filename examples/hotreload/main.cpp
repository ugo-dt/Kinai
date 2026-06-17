#include "AppLayer.hpp"
#include <Kinai/EntryPoint.hpp>
#include <dlfcn.h>
#include <sys/stat.h>

#ifndef LIBRARY_NAME
#ifdef __APPLE__
#define LIBRARY_NAME "libgame.dylib"
#elif defined(_WIN32)
#define LIBRARY_NAME "libgame.dll"
#else
#define LIBRARY_NAME "libgame.so"
#endif
#endif

class ReloadLayer : public Kinai::Layer
{
public:
	ReloadLayer()
		: Kinai::Layer("Reload Layer"),
		  _state(nullptr),
		  _lib_handle(nullptr),
		  _app_layer(nullptr),
		  _attach(true),
		  _running(true)
	{
		_state = new AppState();
		_state->first_load = true;

		_thread = std::thread([this]()
		{
			while (_running)
			{
				// TODO: fork and exec
				(void)system("make > /dev/null");
				constexpr std::chrono::milliseconds interval(500);
				std::this_thread::sleep_for(interval);
			}
		});
	}

	~ReloadLayer()
	{
		_running = false;
		if (_thread.joinable())
			_thread.join();

		if (_app_layer)
			Unload();

		delete _state;
		_state = nullptr;
	}

	void Load()
	{
		assert(_state);

		using CreateAppLayerFunc = AppLayer* (*)(AppState*);
		_lib_handle = SDL_LoadObject(LIBRARY_NAME);
		CreateAppLayerFunc CreateAppLayer_fn = (CreateAppLayerFunc)SDL_LoadFunction(_lib_handle, "CreateAppLayer");

		_app_layer = CreateAppLayer_fn(_state);
		Kinai::Application::Get().PushLayer(_app_layer);
		
		stat(LIBRARY_NAME, &_last_stat);
	}

	void Unload()
	{
		if (!_app_layer)
			return;

		Kinai::Application::Get().PopLayer();
		_app_layer = nullptr;

		if (_lib_handle)
		{
			// dlclose(_lib_handle);
			SDL_UnloadObject((SDL_SharedObject*)_lib_handle);
			_lib_handle = nullptr;
		}
	}

	void OnUpdate(KN_UNUSED float delta) override
	{
		if (_attach)
		{
			Load();
			_attach = false;
		}

		struct stat current_stat;
		if (stat(LIBRARY_NAME, &current_stat) == 0)
		{
			if (current_stat.st_mtime != _last_stat.st_mtime)
			{
				Unload();
				Load();
			}
		}
	}

private:
	AppState* _state;

	SDL_SharedObject *_lib_handle;
	AppLayer* _app_layer;

	bool _attach;

	std::thread _thread;
	std::atomic<bool> _running;

	struct stat _last_stat;
};

class App : public Kinai::Application
{
public:
	App()
		: Kinai::Application(
			Kinai::ApplicationConfig{
				.name = "Kinai Cube Example",
				.enable_imgui = true,
			}
		)
	{
		PushLayer<ReloadLayer>();
	}

	~App() = default;
};

Kinai::Application*	Kinai::CreateApplication(int argc, char **argv)
{
	KN_NOTUSED(argc);
	KN_NOTUSED(argv);

	return new App();
}
