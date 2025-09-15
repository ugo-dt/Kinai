#include <Kinai/Kinai.hpp>
#include <Kinai/EntryPoint.hpp>
#include "quad.glsl.h"

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
    // front face (z = -1)
    0, 2, 1,  0, 3, 2,

    // back face (z = +1)
    6, 4, 5,  7, 4, 6,

    // left face (x = -1)
    8, 10, 9,  8, 11, 10,

    // right face (x = +1)
    14, 12, 13,  15, 12, 14,

    // bottom face (y = -1)
    16, 18, 17,  16, 19, 18,

    // top face (y = +1)
    22, 20, 21,  23, 20, 22
};

float quad_vertices[] = {
    // positions  // texture coords
    -1.0f, -1.0f, 0.0f, 0.0f,  // bottom-left
     1.0f, -1.0f, 1.0f, 0.0f,  // bottom-right
     1.0f,  1.0f, 1.0f, 1.0f,  // top-right
    -1.0f,  1.0f, 0.0f, 1.0f   // top-left
};

unsigned int quad_indices[] = {
    0, 1, 2,
    2, 3, 0
};

struct Mesh
{
	Kinai::Ref<Kinai::VertexArray> vao;
	Kinai::Ref<Kinai::Shader> shader;
	Kinai::Ref<Kinai::VertexBuffer> vbo;
	Kinai::Ref<Kinai::IndexBuffer> ibo;
};

static struct : Mesh
{
	bool rotation = true;
	Kinai::PolygonMode mode = Kinai::PolygonMode::Fill;
	GLenum front_face = GL_CCW;
	GLenum cull_face = GL_BACK;
	bool show_back_faces = false;
} cube;

class AppLayer : public Kinai::Layer
{
private:
	Kinai::PerspectiveCameraController	_camera;

public:
	AppLayer()
		: Kinai::Layer("App Layer"),
			_camera(Kinai::PerspectiveCameraControllerConfig{
				.position = {0.0f, 0.0f, 5.0f},
			})
	{
		cube.vao = Kinai::VertexArray::Create();
		cube.shader = Kinai::Shader::Create("quad", quad_vs_source_glsl410, quad_fs_source_glsl410);
		cube.vbo = Kinai::VertexBuffer::Create(cube_vertices, sizeof(cube_vertices));
		cube.vbo->SetLayout({
			{ Kinai::ShaderDataType::Float3, "a_Position" },
			{ Kinai::ShaderDataType::Float4, "a_Color" }
		});
		cube.vao->AddVertexBuffer(cube.vbo);
		cube.ibo = Kinai::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		cube.vao->SetIndexBuffer(cube.ibo);
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}

	void	OnUpdate(float delta)
	{
		_camera.OnUpdate(delta);

		Kinai::Renderer::BeginFrame(_camera.GetCamera());
		{
			Kinai::RenderCommand::SetClearColor(0.25f, 0.5f, 0.75f, 1.0f);
			Kinai::RenderCommand::Clear();
			cube.vao->SetIndexBuffer(cube.ibo);
			glm::mat4 transform = glm::mat4(1.0f);
			if (cube.rotation)
			{
				const float time = SDL_GetTicks() / 1000.0f;		
				glm::mat4 rxm = glm::rotate(time, glm::vec3(1.0f, 0.0f, 0.0f));
				glm::mat4 rym = glm::rotate(2 * time, glm::vec3(0.0f, 1.0f, 0.0f));
				transform = rxm * rym;
			}

			if (cube.show_back_faces)
			{
				glCullFace(GL_FRONT);
				Kinai::RenderCommand::SetPolygonMode(Kinai::PolygonMode::Line);
				Kinai::Renderer::Submit(cube.shader, cube.vao, transform);
				
				glCullFace(GL_BACK);
				Kinai::RenderCommand::SetPolygonMode(Kinai::PolygonMode::Fill);
			}
			Kinai::Renderer::Submit(cube.shader, cube.vao, transform);
		}
		Kinai::Renderer::EndFrame();
	}

	void	OnImGuiRender()
	{
		Kinai::Application& app = Kinai::Application::Get();

		ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize);
		ImGui::Text("Move around with WASD keys");
		ImGui::Text("FPS: %zu", (size_t)app.GetFPS());
		if (ImGui::Button(_camera.IsRotationEnabled() ? "(F1) Mouse Grab ON" : "(F1) Mouse Grab OFF"))
			_camera.SetRotationEnabled(!_camera.IsRotationEnabled());
		if (ImGui::Button(("(F2) Cube Rotation: " + std::string(cube.rotation ? "ON" : "OFF")).c_str()))
			cube.rotation = !cube.rotation;
		if (ImGui::Button(app.GetWindow().IsVSync() ? "(F3) VSync ON" : "(F3) VSync OFF"))
			app.GetWindow().SetVSync(!app.GetWindow().IsVSync());
		if (ImGui::Button(cube.front_face == GL_CCW ? "(F4) glFrontFace(GL_CCW)" : "(F4) glFrontFace(GL_CW)"))
		{
			cube.front_face = cube.front_face == GL_CCW ? GL_CW : GL_CCW;
			glFrontFace(cube.front_face);
		}
		if (ImGui::Button(cube.show_back_faces ? "(F5) Hide back faces" : "(F4) Show back faces"))
		{
			cube.show_back_faces = !cube.show_back_faces;
			Kinai::RenderCommand::SetPolygonMode(cube.mode);
			glFrontFace(cube.front_face);
			glCullFace(cube.cull_face);
		}
		if (!cube.show_back_faces)
		{
			if (ImGui::Button(cube.mode == Kinai::PolygonMode::Line ? "Wireframe ON" : "Wireframe OFF"))
			{
				cube.mode = cube.mode == Kinai::PolygonMode::Fill ? Kinai::PolygonMode::Line : Kinai::PolygonMode::Fill;
				Kinai::RenderCommand::SetPolygonMode(cube.mode);
			}
			if (ImGui::Button(cube.cull_face == GL_BACK ? "glCullFace(GL_BACK)" : "glCullFace(GL_FRONT)"))
			{
				cube.cull_face = cube.cull_face == GL_BACK ? GL_FRONT : GL_BACK;
				glCullFace(cube.cull_face);
			}
		}
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
				.name = "Kinai Cube Example",
				.enable_imgui = true,
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
