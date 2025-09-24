#include "Kinai/Sokol/Sokol.hpp"
#include "Kinai/Core/Application.hpp"

#ifdef KINAI_SOKOL

namespace Kinai
{

void	Sokol::Init()
{
	KN_PROFILE_FUNC();

	sg_desc	desc = {};

	desc.environment = GetEnvironment(),
	desc.logger.func = slog_func,
	sg_setup(desc);
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

#endif // KINAI_SOKOL

} // Kinai
