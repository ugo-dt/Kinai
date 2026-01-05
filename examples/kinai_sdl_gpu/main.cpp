#include <Kinai/Kinai.hpp>
#include <Kinai/EntryPoint.hpp>

class AppLayer : public Kinai::Layer
{
public:
	AppLayer() = default;
	~AppLayer() = default;

	void	OnAttach();
	void	OnDetach();
	void	OnUpdate(float delta);
private:
	SDL_GPUDevice*	_device;
	SDL_Window*		_window;
};

void	AppLayer::OnAttach()
{
	bool status;

	_device = SDL_CreateGPUDevice(
		SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL, true, nullptr);
	KN_ASSERT(_device, "Could not create GPU device: {}", SDL_GetError());

	_window = static_cast<SDL_Window *>(Kinai::Application::Get().GetWindow().GetNativeWindow());

	status = SDL_ClaimWindowForGPUDevice(_device, _window);
	KN_ASSERT(status, "SDL_ClaimWindowForGPUDevice(): {}", SDL_GetError());
}

void	AppLayer::OnDetach()
{
	SDL_ReleaseWindowFromGPUDevice(_device, _window);
	SDL_DestroyGPUDevice(_device);
}

void	AppLayer::OnUpdate(KN_UNUSED float delta)
{
	bool status;

	// Close the window with the Escape key
	if (Kinai::Input::IsKeyPressed(Kinai::Key::Escape))
		Kinai::Application::Get().Close();

	SDL_GPUCommandBuffer *cmdbuf = SDL_AcquireGPUCommandBuffer(_device);
	KN_ASSERT(cmdbuf, "SDL_AcquireGPUCommandBuffer(): {}", SDL_GetError());

	SDL_GPUTexture *swapchain_texture;
	status = SDL_AcquireGPUSwapchainTexture(cmdbuf, _window, &swapchain_texture, nullptr, nullptr);
	KN_ASSERT(status, "SDL_AcquireGPUSwapchainTexture(): {}", SDL_GetError());

	SDL_GPUColorTargetInfo info = {};
	float time = SDL_GetTicks() / 1000.f;
	float r = glm::sin(time) * 0.5f + 0.5f, g = glm::cos(time) * 0.5f + 0.5f;
	info.clear_color = SDL_FColor{ r, g, 0.3f, 1.0f };
	info.texture = swapchain_texture;
	info.load_op = SDL_GPU_LOADOP_CLEAR;
	info.store_op = SDL_GPU_STOREOP_STORE;

	SDL_GPURenderPass *render_pass = SDL_BeginGPURenderPass(cmdbuf, &info, 1, nullptr);
	SDL_EndGPURenderPass(render_pass);
	SDL_SubmitGPUCommandBuffer(cmdbuf);
}

Kinai::Application*	Kinai::CreateApplication(KN_UNUSED int argc, KN_UNUSED char **argv)
{
	struct App : public Kinai::Application
	{
		App(): Kinai::Application({ .name = "Kinai SDL_gpu", })
		{
			PushLayer<AppLayer>();
		}
		~App() = default;
	};
	return new App();
}
