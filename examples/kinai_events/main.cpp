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

		float time = SDL_GetTicks() / 1000.f;
		float r = glm::sin(time) * 0.5f + 0.5f,
			g = glm::cos(time) * 0.5f + 0.5f;

		Kinai::RenderCommand::SetClearColor(r, g, 0.3f, 1.0f);
		Kinai::RenderCommand::Clear();
	}

	void	OnEvent(Kinai::Event& event)
	{
		Kinai::EventDispatcher dispatcher(event);

		// Send specific events to the appropriate function
		dispatcher.Dispatch<Kinai::KeyPressedEvent>(KN_BIND_EVENT_FN(OnKeyPressed));
		dispatcher.Dispatch<Kinai::MouseButtonPressedEvent>(KN_BIND_EVENT_FN(OnMouseButtonPressed));
	}

	bool	OnKeyPressed(Kinai::KeyPressedEvent &event)
	{
		Kinai::Log::Info("Pressed key {}", event.GetKeyCode());
		switch (event.GetKeyCode())
		{
			// Close the window with the Escape key
			case Kinai::Key::Escape:
				Kinai::Application::Get().Close();
				break;
			default:
				break;
		}
		return true;
	}

	bool	OnMouseButtonPressed(Kinai::MouseButtonPressedEvent &event)
	{
		Kinai::Log::Info("Pressed mouse button {}", event.GetButton());
		return true;
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
