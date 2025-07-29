#include <Kinai/Kinai.hpp>
#include <Kinai/EntryPoint.hpp>

float	cube_vertices[] = {
	-1.0, -1.0, -1.0,   1.0, 0.0, 0.0, 1.0,
	 1.0, -1.0, -1.0,   1.0, 0.0, 0.0, 1.0,
	 1.0,  1.0, -1.0,   1.0, 0.0, 0.0, 1.0,
	-1.0,  1.0, -1.0,   1.0, 0.0, 0.0, 1.0,

	-1.0, -1.0,  1.0,   0.0, 1.0, 0.0, 1.0,
	 1.0, -1.0,  1.0,   0.0, 1.0, 0.0, 1.0,
	 1.0,  1.0,  1.0,   0.0, 1.0, 0.0, 1.0,
	-1.0,  1.0,  1.0,   0.0, 1.0, 0.0, 1.0,

	-1.0, -1.0, -1.0,   0.0, 0.0, 1.0, 1.0,
	-1.0,  1.0, -1.0,   0.0, 0.0, 1.0, 1.0,
	-1.0,  1.0,  1.0,   0.0, 0.0, 1.0, 1.0,
	-1.0, -1.0,  1.0,   0.0, 0.0, 1.0, 1.0,

	 1.0, -1.0, -1.0,   1.0, 0.5, 0.0, 1.0,
	 1.0,  1.0, -1.0,   1.0, 0.5, 0.0, 1.0,
	 1.0,  1.0,  1.0,   1.0, 0.5, 0.0, 1.0,
	 1.0, -1.0,  1.0,   1.0, 0.5, 0.0, 1.0,

	-1.0, -1.0, -1.0,   0.0, 0.5, 1.0, 1.0,
	-1.0, -1.0,  1.0,   0.0, 0.5, 1.0, 1.0,
	 1.0, -1.0,  1.0,   0.0, 0.5, 1.0, 1.0,
	 1.0, -1.0, -1.0,   0.0, 0.5, 1.0, 1.0,

	-1.0,  1.0, -1.0,   1.0, 0.0, 0.5, 1.0,
	-1.0,  1.0,  1.0,   1.0, 0.0, 0.5, 1.0,
	 1.0,  1.0,  1.0,   1.0, 0.0, 0.5, 1.0,
	 1.0,  1.0, -1.0,   1.0, 0.0, 0.5, 1.0
};

uint32_t indices[] = {
	0, 1, 2,  0, 2, 3,
	6, 5, 4,  7, 6, 4,
	8, 9, 10,  8, 10, 11,
	14, 13, 12,  15, 14, 12,
	16, 17, 18,  16, 18, 19,
	22, 21, 20,  23, 22, 20
};

class AppLayer : public Kinai::Layer
{
private:
	Kinai::PerspectiveCameraController	_camera;
	Kinai::Ref<Kinai::VertexArray>		_vertex_array;
	Kinai::Ref<Kinai::Shader>			_shader;
	bool								_cube_rotation;
public:
	AppLayer()
		: Kinai::Layer("App Layer"),
		  _camera(Kinai::PerspectiveCameraControllerConfig{
			.position = {0.0f, 0.0f, 5.0f},
		  }),
		  _vertex_array(),
		  _shader(Kinai::Shader::Create("./assets/quad.glsl", "quad")),
		  _cube_rotation(true)
	{
		_vertex_array = Kinai::VertexArray::Create();
		auto vertex_buffer = Kinai::VertexBuffer::Create(cube_vertices, sizeof(cube_vertices));
		vertex_buffer->SetLayout({
			{ Kinai::ShaderDataType::Float3, "a_Position" },
			{ Kinai::ShaderDataType::Float4, "a_Color" }
		});
		_vertex_array->AddVertexBuffer(vertex_buffer);
		auto index_buffer = Kinai::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		_vertex_array->SetIndexBuffer(index_buffer);

		glFrontFace(GL_CW);
	}

	~AppLayer() = default;

	void	OnUpdate(float delta)
	{
		const float time = SDL_GetTicks() / 1000.0f;

		_camera.OnUpdate(delta);

		Kinai::RenderCommand::SetClearColor(0.25f, 0.5f, 0.75f, 1.0f);
		Kinai::RenderCommand::Clear();

		Kinai::Renderer::BeginFrame(_camera.GetCamera());
		glm::mat4 transform = glm::mat4(1.0f);
		if (_cube_rotation)
		{
			glm::mat4 rxm = glm::rotate(time, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rym = glm::rotate(2 * time, glm::vec3(0.0f, 1.0f, 0.0f));
			transform = rxm * rym;
		}
		Kinai::Renderer::Submit(_shader, _vertex_array, transform);
		Kinai::Renderer::EndFrame();
	}

	void	OnImGuiRender()
	{
		Kinai::Application& app = Kinai::Application::Get();

		ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize);
		ImGui::Text("Press F1 to toggle the mouse");
		ImGui::Text("Move with WASD keys");
		ImGui::Text("FPS: %zu", (size_t)app.GetFPS());
		if (ImGui::Button(("Cube Rotation: " + std::string(_cube_rotation ? "ON" : "OFF")).c_str()))
			_cube_rotation = !_cube_rotation;
		if (ImGui::Button(app.GetWindow().IsVSync() ? "VSync ON" : "VSync OFF"))
			app.GetWindow().SetVSync(!app.GetWindow().IsVSync());
		ImGui::End();
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
			case Kinai::Key::F1:
				_camera.SetRotationEnabled(!_camera.IsRotationEnabled());
				break;
			case Kinai::Key::F2:
				_camera.SetRotationEnabled(!_camera.IsRotationEnabled());
				break;
			default:
				break;
		}
		return true;
	}
};

class App : public Kinai::Application
{
public:
	App()
		: Kinai::Application(
			Kinai::ApplicationConfig{
				.enable_imgui = true,
				.no_vsync = false,
				.name = "Kinai Cube Example",
			}
		)
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
