#include "Kinai/Sokol/Sokol.hpp"
#include "Kinai/Core/Application.hpp"
#include <utility>

namespace Kinai
{

sg_pass_action Sokol::_pass_action;

void	Sokol::Init()
{
	EG_PRINT_FUNC();

	sg_desc	desc = {};

	desc.environment = GetEnvironment(),
	desc.logger.func = slog_func,
	sg_setup(desc);

	Sokol::_pass_action = {};
	Sokol::_pass_action.colors[0].load_action = SG_LOADACTION_CLEAR;
	Sokol::_pass_action.colors[0].clear_value = {0.12f, 0.12f, 0.12f, 1.0f};
	EG_ASSERT(sg_isvalid());
}

void	Sokol::Shutdown()
{
	EG_PRINT_FUNC();

	sg_shutdown();
}

void	Sokol::BeginFrame()
{
	EG_PRINT_FUNC();
	sg_pass	pass = {};
	pass.action = Sokol::_pass_action;

	pass.swapchain = GetSwapchain(),
	sg_begin_pass(pass);
}

void	Sokol::EndFrame()
{
	EG_PRINT_FUNC();

	sg_end_pass();
	sg_commit();
}

sg_pass_action&	Sokol::GetPassAction()
{
	EG_PRINT_FUNC();

	return Sokol::_pass_action;
}

sg_environment	Sokol::GetEnvironment()
{
	EG_PRINT_FUNC();

	return Application::Get().GetWindow().GetSokolEnvironment();
}

sg_swapchain	Sokol::GetSwapchain()
{
	EG_PRINT_FUNC();

	return Application::Get().GetWindow().GetSokolSwapchain();
}

} // Kinai
