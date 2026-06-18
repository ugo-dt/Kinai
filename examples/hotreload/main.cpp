#include <Kinai/EntryPoint.hpp>
#include "hotreload.hpp"

ReloadLayer::ReloadLayer()
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
			// (void)system("make > /dev/null");

			const char *args[] = {
				"make",
				NULL
			};
			SDL_Process *process = NULL;
			char *buffer;
			int exit_code;
			// int i;
			size_t total_read = 0;

			process = SDL_CreateProcess(args, true);
			if (!process)
				Kinai::Log::Critical("SDL_CreateProcess() failed");
			exit_code = 0xdeadbeef;
			buffer = (char *)SDL_ReadProcess(process, &total_read, &exit_code);
			if (!buffer)
			{
				SDL_DestroyProcess(process);
				Kinai::Log::Critical("SDL_ReadProcess() failed");
			}

			constexpr std::chrono::milliseconds interval(500);
			std::this_thread::sleep_for(interval);
		}
	});
}

ReloadLayer::~ReloadLayer()
{
	_running = false;
	if (_thread.joinable())
		_thread.join();

	if (_app_layer)
		Unload();

	delete _state;
	_state = nullptr;
}

void ReloadLayer::Load()
{
	assert(_state);

	using CreateAppLayerFunc = AppLayer* (*)(AppState*);
	_lib_handle = SDL_LoadObject(LIBRARY_NAME);
	CreateAppLayerFunc CreateAppLayer_fn = (CreateAppLayerFunc)SDL_LoadFunction(_lib_handle, "CreateAppLayer");

	_app_layer = CreateAppLayer_fn(_state);
	Kinai::Application::Get().PushLayer(_app_layer);
	
	stat(LIBRARY_NAME, &_last_stat);
}

void ReloadLayer::Unload()
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

void ReloadLayer::OnUpdate(KN_UNUSED float delta)
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
	std::cout << "reloadlayer" << std::endl;
}

void ReloadLayer::OnRender()
{
	Kinai::Renderer::SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	Kinai::Renderer::Clear();
}

void ReloadLayer::OnEvent(Kinai::Event& event)
{
	Kinai::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Kinai::KeyPressedEvent>(KN_BIND_EVENT_FN(OnKeyPressed));
}

bool ReloadLayer::OnKeyPressed(Kinai::KeyPressedEvent &event)
{
	if (event.IsRepeat())
		return false;
	switch (event.GetKeyCode())
	{
		case Kinai::Key::Escape:
			Kinai::Quit();
			break;
		case Kinai::Key::Q:
			_state->current_layer = AppLayerType::AppLayer;
			Push<AppLayer>(_state);
			break;
		default:
			break;
	}
	return true;
}

App::App(): Kinai::Application(Kinai::ApplicationConfig{
	.name = "Kinai Cube Example",
	.enable_imgui = true,
})
{
	PushLayer<ReloadLayer>();
}

Kinai::Application*	Kinai::CreateApplication(int argc, char **argv)
{
	KN_NOTUSED(argc);
	KN_NOTUSED(argv);

	return new App();
}
