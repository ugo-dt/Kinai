#include <Kinai/Kinai.hpp>
#include <Kinai/EntryPoint.hpp>

class AppLayer : public Kinai::Layer
{
public:
	AppLayer(): Kinai::Layer("App Layer") {}
	~AppLayer() = default;

	void	OnAttach()
	{
	}

	void	OnDetach()
	{
	}

	void	OnUpdate(float delta)
	{
		KN_NOTUSED(delta);

		Kinai::RenderCommand::SetClearColor(0.12f, 0.12f, 0.12f, 1.0f);
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
		PushLayer(new AppLayer());
	}

	~App() = default;
};

Kinai::Application*	Kinai::CreateApplication(int argc, char **argv)
{
	KN_NOTUSED(argc);
	KN_NOTUSED(argv);

	return new App();
}
