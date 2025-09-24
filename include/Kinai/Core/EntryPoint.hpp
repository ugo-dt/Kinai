#pragma once

#include "Kinai/Core/Application.hpp"
#include "Kinai/Core/Core.hpp"

#ifdef KN_PLATFORM_WEB
	#include "Kinai/Platform/Emscripten/Emscripten.hpp"
#endif

bool	g_KinaiApplicationRunning = true;

namespace Kinai
{
	
#if defined(KN_PLATFORM_DESKTOP)

int	Main(int argc, char **argv)
{
	KN_PROFILE_FUNC();

	Kinai::Log::Init();
	while (g_KinaiApplicationRunning)
	{
		Kinai::Application	*app = ::Kinai::CreateApplication(argc, argv);
		app->Run();
		delete app;
	}
	return EXIT_SUCCESS;
}

#elif defined(KN_PLATFORM_WEB)

int	Main(int argc, char **argv)
{
	KN_PROFILE_FUNC();

	Kinai::Log::Init();
    emscripten_request_animation_frame_loop(
		[](double, void*)
		{
			KN_PROFILE_FUNC();
			Application::Get().Run();
			return g_KinaiApplicationRunning;
		}, 0);
	Kinai::CreateApplication(argc, argv);
	return EXIT_SUCCESS;
}

#endif // KN_PLATFORM_DESKTOP

} // Kinai

int	main(int argc, char **argv)
{
	KN_PROFILE_FUNC();

	return Kinai::Main(argc, argv);
}
