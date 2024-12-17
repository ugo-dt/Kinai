#include <Kinai/Kinai.hpp>
#include <Kinai/EntryPoint.hpp>

class AppLayer : public Kinai::Layer
{
public:
	AppLayer(): Kinai::Layer("App Layer"), _camera(Kinai::OrthographicCameraControllerConfig{
		.enable_rotation = true
	}) {}
	~AppLayer() = default;

	void	OnUpdate(float delta)
	{
		KN_NOTUSED(delta);

		_camera.OnUpdate(delta);

		Kinai::RenderCommand::SetClearColor(0.12f, 0.12f, 0.12f, 1.0f);
		Kinai::RenderCommand::Clear();

		Kinai::Renderer2D::BeginFrame(_camera.GetCamera());
		Kinai::Renderer2D::DrawQuad(glm::vec2(.5f), glm::vec2(.3f), glm::vec4(1.f));
		Kinai::Renderer2D::EndFrame();
	}

	void	OnEvent(Kinai::Event& event)
	{
		Kinai::EventDispatcher dispatcher(event);

		dispatcher.Dispatch<Kinai::KeyPressedEvent>(KN_BIND_EVENT_FN(OnKeyPressed));
		_camera.OnEvent(event);
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

private:
	Kinai::OrthographicCameraController	_camera;
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
