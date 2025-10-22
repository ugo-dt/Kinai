#include "Kinai/Sokol/Sokol.hpp"
#include "Kinai/Core/Application.hpp"

#ifdef KINAI_SOKOL

namespace Kinai
{

void	Sokol::Init()
{
	KN_PROFILE_FUNC();

	sg_setup(sg_desc{
		.logger.func = slog_func,
		.environment = GetEnvironment()
	});
	KN_ASSERT(sg_isvalid());
}

void	Sokol::Shutdown()
{
	KN_PROFILE_FUNC();

	sg_shutdown();
}

sg_environment	Sokol::GetEnvironment()
{
	KN_PROFILE_FUNC();

	return Application::Get().GetWindow().GetSokolEnvironment();
}

sg_swapchain	Sokol::GetSwapchain()
{
	KN_PROFILE_FUNC();

	return Application::Get().GetWindow().GetSokolSwapchain();
}

} // Kinai

#endif // KINAI_SOKOL
