#include "AppLayer.hpp"
#include <Kinai/EntryPoint.hpp>
#include <dlfcn.h>

class ReloadLayer : public Kinai::Layer
{
public:
	ReloadLayer()
		: Kinai::Layer("Reload Layer"),
		  _state(nullptr),
		  _attach(true)
	{
		scope("ReloadLayer::ReloadLayer");
		_state = new AppState();
		_state->first_load = true;
	}
	~ReloadLayer()
	{
		scope("ReloadLayer::~ReloadLayer");
		delete _state;
	}

	void Load()
	{
		scope("ReloadLayer::Load");
		assert(_state);
		using CreateAppLayerFunc = AppLayer* (*)(AppState*);
		void *handle = dlopen("libgame.dylib", RTLD_NOW);
		if (!handle)
			Kinai::Log::Critical("Failed to load libgame.dylib: {}", dlerror());
		CreateAppLayerFunc CreateAppLayer_fn = (CreateAppLayerFunc)dlsym(handle, "CreateAppLayer");
		if (!CreateAppLayer_fn)
		{
			dlclose(handle);
			Kinai::Log::Critical("Failed to find CreateAppLayer symbol in libgame.dylib");
		}
		Kinai::Application::Get().PushLayer(CreateAppLayer_fn(_state));
		dlclose(handle);
	}

	void Unload()
	{
		scope("ReloadLayer::Unload");
		Kinai::Application::Get().PopLayer();
	}

	void OnUpdate(KN_UNUSED float delta) override
	{
		scope("ReloadLayer::OnUpdate");
		if (_attach)
		{
			Load();
			_attach = false;
		}
	}

	void OnEvent(Kinai::Event& event) override
	{
		scope("ReloadLayer::OnEvent");
		Kinai::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Kinai::KeyPressedEvent>(KN_BIND_EVENT_FN(OnKeyPressed));
	}

	bool OnKeyPressed(Kinai::KeyPressedEvent &event)
	{
		scope("ReloadLayer::OnKeyPressed");
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
