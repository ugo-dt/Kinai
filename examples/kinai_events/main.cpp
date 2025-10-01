#include <Kinai/Kinai.hpp>
#include <Kinai/EntryPoint.hpp>

class AppLayer : public Kinai::Layer
{
public:
	AppLayer(): Kinai::Layer("App Layer") {}
	~AppLayer() = default;

	void	OnUpdate(float delta)
	{
		KN_NOTUSED(delta);
	}

	void	OnRender()
	{
		float time = SDL_GetTicks() / 1000.f;
		float r = glm::sin(time) * 0.5f + 0.5f,
			g = glm::cos(time) * 0.5f + 0.5f;

		Kinai::Renderer::SetClearColor(r, g, 0.3f, 1.0f);
		Kinai::Renderer::Clear();
	}

	void	OnEvent(Kinai::Event& event)
	{
		Kinai::EventDispatcher dispatcher(event);

		std::cout << event.ToString() << std::endl;

		// Send specific events to the appropriate function
		dispatcher.Dispatch<Kinai::KeyPressedEvent>(KN_BIND_EVENT_FN(OnKeyPressed));
		dispatcher.Dispatch<Kinai::MouseButtonPressedEvent>(KN_BIND_EVENT_FN(OnMouseButtonPressed));
	}

	bool	OnKeyPressed(Kinai::KeyPressedEvent &event)
	{
		switch (event.GetKeyCode())
		{
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
		std::cout << event.ToString() << std::endl;
		return true;
	}
};

class App : public Kinai::Application
{
public:
	App(): Kinai::Application(Kinai::ApplicationConfig())
	{
		PushLayer<AppLayer>();
	}

	~App() = default;
};

Kinai::Application*	Kinai::CreateApplication(int argc, char **argv)
{
	KN_NOTUSED(argc);
	KN_NOTUSED(argv);

	return new App();
}
