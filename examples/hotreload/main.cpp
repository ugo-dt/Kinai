#include "AppLayer.hpp"
#include <Kinai/EntryPoint.hpp>
#include <dlfcn.h>

class ReloadLayer : public Kinai::Layer
{
public:
	ReloadLayer()
		: Kinai::Layer("Reload Layer"),
		  _state(nullptr),
		  _lib_handle(nullptr),
		  _app_layer(nullptr),
		  _attach(true)
	{
		_state = new AppState();
		_state->first_load = true;
	}
	~ReloadLayer()
	{
		delete _state;
		_state = nullptr;
	}

	void Load()
	{
		assert(_state);
		int result = system("make");
		_lib_handle = dlopen("libgame.so", RTLD_NOW);
		if (!_lib_handle)
			Kinai::Log::Critical("Failed to load libgame.so: {}", dlerror());
		(void)result;
		using CreateAppLayerFunc = AppLayer* (*)(AppState*);
		CreateAppLayerFunc CreateAppLayer_fn = (CreateAppLayerFunc)dlsym(_lib_handle, "CreateAppLayer");
		if (!CreateAppLayer_fn)
		{
			dlclose(_lib_handle);
			Kinai::Log::Critical("Failed to find CreateAppLayer symbol in libgame.so");
		}
		_app_layer = CreateAppLayer_fn(_state);
		Kinai::Application::Get().PushLayer(_app_layer);
		printf("load\n");
	}

	void Unload()
	{
		assert(_app_layer);
		Kinai::Application::Get().PopLayer();
		_app_layer = nullptr;
		dlclose(_lib_handle);
		_lib_handle = nullptr;
		printf("unload\n");
		usleep(50000);
	}

	void OnUpdate(KN_UNUSED float delta) override
	{
		if (_attach)
		{
			Load();
			_attach = false;
		}
	}

	void OnEvent(Kinai::Event& event) override
	{
		Kinai::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Kinai::KeyPressedEvent>(KN_BIND_EVENT_FN(OnKeyPressed));
	}

	bool OnKeyPressed(Kinai::KeyPressedEvent &event)
	{
		if (event.IsRepeat())
			return false;
		if (event.GetKeyCode() == Kinai::Key::R)
		{
			Unload();
			Load();
		}
		return true;
	}

private:
	AppState *_state;
	void* _lib_handle;
	AppLayer* _app_layer;
	bool _attach;
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
