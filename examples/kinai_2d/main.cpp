#include <Kinai/Kinai.hpp>
#include <Kinai/EntryPoint.hpp>

namespace math = Kinai::math;

static int radio = 0;
static float slider = 0.0f;
static bool checkbox = false;

class AppLayer : public Kinai::Layer
{
// Private members are at the top for convenience
private:
	Kinai::OrthographicCameraController	_camera;
	Kinai::Ref<Kinai::Texture2D>		_cobblestone;
	// Kinai::Ref<Kinai::Texture2D>		_noise;
	// Kinai::Renderer2D::Shader2D			_shader;
	glm::vec2 _scroll1;
	glm::vec2 _scroll2;
	glm::vec1 _oscillation;
	glm::vec4 _tone_color;
	glm::vec4 _top_color;
	glm::vec1 _alpha;
public:
	AppLayer()
		: Kinai::Layer("App Layer"),
	  	  _camera(Kinai::OrthographicCameraControllerConfig{
		  	.enable_zoom = true,
	  	  }),
	  	  _cobblestone(Kinai::Texture2D::Create("assets/brick.bmp")),
	  	//   _noise(Kinai::Texture2D::Create("assets/seamless_noise.png")),
	  	//   _shader(Kinai::Renderer2D::MakeShader("customquad", custom_shader_vs, custom_shader_fs)),
		  _scroll1(0.05f),
		  _scroll2(-0.05f),
		  _oscillation(1.0f),
		  _tone_color(0.0f, 0.60f, 1.0f, 1.0f),
		  _top_color(1.0f),
		  _alpha(1.f)
	{
	}

	~AppLayer() = default;

	void	OnUpdate(float delta)
	{
		// Kinai::Renderer::BeginPass();

		// Kinai::Renderer2D::BeginFrame(_camera.GetCamera());
		// Kinai::Renderer2D::DrawQuad(glm::vec2(0.f), glm::vec2(1.f), _cobblestone);

		// Kinai::Renderer2D::SetQuadShader(_shader);
		// _shader.GetShader()->Bind();
		// _shader.GetShader()->SetFloat2("scroll1", glm::vec2(_scroll1.x));
		// _shader.GetShader()->SetFloat2("scroll2", glm::vec2(_scroll2.x));
		// _shader.GetShader()->SetFloat("oscillation_speed", _oscillation.x);
		// _shader.GetShader()->SetFloat4("tone_color", _tone_color);
		// _shader.GetShader()->SetFloat4("top_color", _top_color);
		// _shader.GetShader()->SetFloat("alpha", _alpha.x);
		// Kinai::Renderer2D::DrawQuad(glm::vec2(0.f), glm::vec2(2.f), _noise);
		// Kinai::Renderer2D::ResetQuadShader();

		KN_NOTUSED(delta);

		_camera.OnUpdate(delta);

		Kinai::Renderer::SetClearColor(0.12f, 0.12f, 0.12f, 1.0f);
		Kinai::Renderer::Clear();

		Kinai::DebugText::Home();
		Kinai::DebugText::SetOrigin(0.f, 0.f);
		Kinai::DebugText::SetColor(255, 255, 0, 255);
		Kinai::DebugText::Print("Radio button test value: {}\n", radio);
		Kinai::DebugText::Print("Slider test value: {}\n", slider);
		Kinai::DebugText::Print("Checkbox test value: {}\n", checkbox ? "true" : "false");

		Kinai::Painter::Begin();
		Kinai::Painter::SetImage(0, _cobblestone);
		Kinai::Painter::DrawQuad(glm::vec2(50.f), glm::vec2(500.f), glm::vec4(1.0f));
		Kinai::Painter::DrawQuad(50, 50, 100, 100, glm::vec4(1.0f));
		Kinai::Painter::ResetImage();
		
		Kinai::Renderer::BeginPass();
		Kinai::Painter::Flush();
		Kinai::Painter::End();
		Kinai::DebugText::Submit();
		Kinai::Renderer::EndPass();
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

	void	OnGUIRender()
	{
		Kinai::Application& app = Kinai::Application::Get();

		Kinai::GUI::Begin("Test window", nullptr, Kinai::GUI::WindowFlags_AlwaysAutoResize);
		Kinai::GUI::Text("FPS: {}", Kinai::Application::Get().GetFPS());
		if (Kinai::GUI::Button(app.GetWindow().IsVSync() ? "VSync ON" : "VSync OFF"))
			app.GetWindow().SetVSync(!app.GetWindow().IsVSync());

		Kinai::GUI::SliderFloat("Float Slider", &slider, -1.f, 1.f);
		Kinai::GUI::RadioButton("Option 0", (int*)&radio, 0, Kinai::GUI::ButtonFlags_Disabled);
		Kinai::GUI::RadioButton("Option 1", (int*)&radio, 1);
		Kinai::GUI::RadioButton("Option 2", (int*)&radio, 2);
		Kinai::GUI::RadioButton("Option 3", (int*)&radio, 3);

		Kinai::GUI::Checkbox("Checkbox", &checkbox);
		Kinai::GUI::Checkbox("Checkbox", &checkbox, Kinai::GUI::ButtonFlags_Disabled);
		Kinai::GUI::End();
		
		Kinai::GUI::Begin("Window", nullptr, Kinai::GUI::WindowFlags_AlwaysAutoResize);
		Kinai::GUI::Text("FPS: {}", Kinai::Application::Get().GetFPS());
		if (Kinai::GUI::Button(app.GetWindow().IsVSync() ? "VSync ON" : "VSync OFF"))
			app.GetWindow().SetVSync(!app.GetWindow().IsVSync());
		Kinai::GUI::End();
	}
};

class App : public Kinai::Application
{
public:
	App(): Kinai::Application(
		Kinai::ApplicationConfig{
			.name = "Kinai 2D",
			.enable_gui = true
		}
	)
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
