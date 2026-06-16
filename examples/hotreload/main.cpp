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
				(void)system("make > /dev/null"); // TODO: fork and exec
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

		_lib_handle = dlopen(LIBRARY_NAME, RTLD_NOW);
		if (!_lib_handle)
		{
			Kinai::Log::Critical("Failed to load {}: {}", LIBRARY_NAME, dlerror());
			return;
		}

		using CreateAppLayerFunc = AppLayer* (*)(AppState*);
		auto CreateAppLayer_fn = (CreateAppLayerFunc)dlsym(_lib_handle, "CreateAppLayer");

		if (!CreateAppLayer_fn)
		{
			dlclose(_lib_handle);
			_lib_handle = nullptr;

			Kinai::Log::Critical("Failed to find CreateAppLayer symbol in {}", LIBRARY_NAME);
			return;
		}

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
			dlclose(_lib_handle);
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

	void* _lib_handle;
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
