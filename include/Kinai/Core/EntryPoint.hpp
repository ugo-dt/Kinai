#pragma once

#include "Kinai/Core/Application.hpp"
#include "Kinai/Core/Core.hpp"

#ifdef EG_PLATFORM_WEB
	#include "Kinai/Platform/Emscripten/Emscripten.hpp"
#endif

bool	g_KinaiApplicationRunning = true;

namespace Kinai
{
	
#if defined(EG_PLATFORM_DESKTOP)

int	Main(int argc, char **argv)
{
	EG_PRINT_FUNC();

	while (g_KinaiApplicationRunning)
	{
		Kinai::Application	*app = Kinai::CreateApplication(argc, argv);
		app->Run();
		delete app;
	}
	return EXIT_SUCCESS;
}

#elif defined(EG_PLATFORM_WEB)

int	Main(int argc, char **argv)
{
	EG_PRINT_FUNC();

    emscripten_request_animation_frame_loop(
		[](double, void*)
		{
			EG_PRINT_FUNC();
			Application::Get().Run();
			return g_KinaiApplicationRunning;
		}, 0);
	Kinai::CreateApplication(argc, argv);
	return EXIT_SUCCESS;
}

#endif // EG_PLATFORM_DESKTOP

} // Kinai

int	main(int argc, char **argv)
{
	EG_PRINT_FUNC();

	Kinai::Log::Init();
	return Kinai::Main(argc, argv);
}
