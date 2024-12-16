#include <Kinai/Kinai.hpp>
#include <Kinai/EntryPoint.hpp>

class AppLayer : public Kinai::Layer
{
public:
	AppLayer(): Kinai::Layer("App Layer") {}
	~AppLayer() = default;

	void	OnAttach()
	{
		Kinai::Log::Info("AppLayer::OnAttach()");
	}

	void	OnDetach()
	{
		Kinai::Log::Info("AppLayer::OnDetach()");
	}

	void	OnUpdate(float delta)
	{
		(void)delta;

		// Close the window with the Escape key
		if (Kinai::Input::IsKeyPressed(Kinai::Key::Escape))
			Kinai::Application::Get().Close();

		float time = SDL_GetTicks() / 1000.f;
		float r = glm::sin(time) * 0.5f + 0.5f,
			g = glm::cos(time) * 0.5f + 0.5f;

		Kinai::RenderCommand::SetClearColor(r, g, 0.3f, 1.0f);
		Kinai::RenderCommand::Clear();
	}
};

class App : public Kinai::Application
{
public:
	App(): Kinai::Application(Kinai::ApplicationConfig())
	{
		// Push our app layer to the application.
		// It gets automatically deleted when the app closes.
		PushLayer(new AppLayer());
	}

	~App() = default;
};

Kinai::Application*	Kinai::CreateApplication(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	return new App();
}
