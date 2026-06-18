#pragma once

#include "AppLayer.hpp"

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
	ReloadLayer();

	~ReloadLayer();
	void Load();

	void Unload();

	void OnUpdate(KN_UNUSED float delta) override;
	void OnRender() override;
	void OnEvent(Kinai::Event& event) override;
	bool OnKeyPressed(Kinai::KeyPressedEvent &event);

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
	App();
	~App() = default;
};
