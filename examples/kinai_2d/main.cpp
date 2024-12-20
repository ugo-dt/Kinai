#include <Kinai/Kinai.hpp>
#include <Kinai/EntryPoint.hpp>

const char *custom_shader_vs = R"(
	void	vertex()
	{
		VERTEX = (CANVAS_MATRIX * vec4(VERTEX, 0.0, 1.0)).xy;
	}
)";

const char *custom_shader_fs = R"(
	uniform vec2 scroll = vec2(0.05, 0.05);
	uniform float distortion_strength = 0.2;

	void	fragment()
	{
		vec4 screen_col = texture(TEXTURE, UV + scroll * TIME);
		COLOR = screen_col;
	}
)";

class AppLayer : public Kinai::Layer
{
public:
	AppLayer()
		: Kinai::Layer("App Layer"),
	  	  _camera(Kinai::OrthographicCameraControllerConfig{
		  	.enable_zoom = true,
	  	  }),
	  	  _texture(Kinai::Texture2D::Create("./examples/assets/cobblestone.png", GL_NEAREST, GL_NEAREST)),
	  	  _shader(Kinai::Renderer2D::MakeShader("customquad", custom_shader_vs, custom_shader_fs))
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glDisable(GL_DEPTH_TEST);

		_texture->Bind();
	}
	~AppLayer() = default;

	void	OnUpdate(float delta)
	{
		KN_NOTUSED(delta);

		_camera.OnUpdate(delta);

		Kinai::RenderCommand::SetClearColor(0.12f, 0.12f, 0.12f, 1.0f);
		Kinai::RenderCommand::Clear();

		Kinai::Renderer2D::BeginFrame(_camera.GetCamera());
		Kinai::Renderer2D::SetQuadShader(_shader);
		Kinai::Renderer2D::DrawQuad(glm::vec2(0), glm::vec2(.3f), _texture);
		Kinai::Renderer2D::ResetQuadShader();
		Kinai::Renderer2D::DrawQuad(glm::vec2(0.1f), glm::vec2(.3f), _texture);

		Kinai::Renderer2D::SetQuadShader(_shader);
		Kinai::Renderer2D::DrawQuad(glm::vec2(.2f, .2f), glm::vec2(.3f), _texture);
		Kinai::Renderer2D::EndFrame();
	}

	void	OnImGuiRender()
	{
		Kinai::Application& app = Kinai::Application::Get();

		static uint32_t total_draw_calls = 0;	

		ImGui::Begin("Stats");

		auto& stats = Kinai::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Current Draw Calls: %d", stats.GetDrawCalls());
		ImGui::Text("Total Draw Calls: %d", total_draw_calls);
		total_draw_calls += stats.GetDrawCalls();

		ImGui::Text("Quads: %d", stats.GetQuadCount());
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
		ImGui::Text("FPS: %zu", app.GetFPS());
		ImGui::SameLine();
		if (ImGui::Button(app.GetWindow().IsVSync() ? "VSync ON" : "VSync OFF"))
			app.GetWindow().SetVSync(!app.GetWindow().IsVSync());
		ImGui::End();
		stats.Reset();
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
	Kinai::Ref<Kinai::Texture2D>		_texture;
	Kinai::Renderer2D::Shader2D			_shader;
};

class App : public Kinai::Application
{
public:
	App(): Kinai::Application(Kinai::ApplicationConfig{ .enable_imgui = true })
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
