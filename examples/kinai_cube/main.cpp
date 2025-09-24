#include <Kinai/Kinai.hpp>
#include <Kinai/EntryPoint.hpp>
#include "quad.glsl.hpp"

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

static struct
{
	bool rotation = true;
	Kinai::PolygonMode mode = Kinai::PolygonMode::Fill;
	bool show_back_faces = false;
	Kinai::Ref<Kinai::Pipeline>	pipeline;
	Kinai::Ref<Kinai::Bindings>	bindings;
}cube;

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
		cube.bindings = Kinai::Bindings::Create();
		cube.bindings->AddVertexBuffer(Kinai::VertexBuffer::Create(cube_vertices, sizeof(cube_vertices)));
		cube.bindings->SetIndexBuffer(Kinai::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		cube.pipeline = Kinai::Pipeline::Create(Kinai::PipelineConfig{
			.vao = Kinai::VertexArray::Create(),
			.shader = Kinai::Shader::Create(quadProgramShaderConfig()),
			.layout = Kinai::BufferLayout{
				{ Kinai::ShaderDataType::Float3, "a_Position" },
				{ Kinai::ShaderDataType::Float4, "a_Color" }
			},
			.label = "Cube pipeline",
		});
	}

	void	OnUpdate(float delta)
	{
		_camera.OnUpdate(delta);
	}

	void	OnRender()
	{
		Kinai::Renderer::BeginPass();
		{
			Kinai::Renderer::SetClearColor(0.25f, 0.5f, 0.75f, 1.0f);
			Kinai::Renderer::Clear();

			Kinai::Renderer::ApplyPipeline(cube.pipeline);
			Kinai::Renderer::ApplyBindings(cube.bindings);

			glm::mat4 transform = glm::mat4(1.0f);
			if (cube.rotation)
			{
				const float time = SDL_GetTicks() / 1000.0f;
				glm::mat4 rxm = glm::rotate(time, glm::vec3(1.0f, 0.0f, 0.0f));
				glm::mat4 rym = glm::rotate(2 * time, glm::vec3(0.0f, 1.0f, 0.0f));
				transform = rxm * rym;
			}

			Kinai::Renderer::ApplyUniforms<quad_vs_params_t>({
				.u_ViewProjection = _camera.GetCamera().GetViewProjectionMatrix(),
				.u_Transform = transform,
			});

			if (cube.show_back_faces)
			{
				glCullFace(GL_FRONT);
				Kinai::Renderer::SetPolygonMode(Kinai::PolygonMode::Line);
				Kinai::Renderer::Submit();
				
				glCullFace(GL_BACK);
				Kinai::Renderer::SetPolygonMode(Kinai::PolygonMode::Fill);
			}
			Kinai::Renderer::Submit();
		}
		Kinai::Renderer::EndPass();
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
		if (ImGui::Button(cube.pipeline->GetFaceWinding() == Kinai::FaceWinding::CCW
			? "(F4) glFrontFace(GL_CCW)"
			: "(F4) glFrontFace(GL_CW)")
		)
		{
			cube.pipeline->SetFaceWinding(
				cube.pipeline->GetFaceWinding() == Kinai::FaceWinding::CCW
				? Kinai::FaceWinding::CW : Kinai::FaceWinding::CCW
			);
		}
		if (ImGui::Button(cube.show_back_faces ? "(F5) Hide back faces" : "(F5) Show back faces"))
		{
			cube.show_back_faces = !cube.show_back_faces;
			Kinai::Renderer::SetPolygonMode(cube.mode);
		}
		if (!cube.show_back_faces)
		{
			if (ImGui::Button(cube.mode == Kinai::PolygonMode::Line ? "Wireframe ON" : "Wireframe OFF"))
			{
				cube.mode = cube.mode == Kinai::PolygonMode::Fill ? Kinai::PolygonMode::Line : Kinai::PolygonMode::Fill;
				Kinai::Renderer::SetPolygonMode(cube.mode);
			}
			if (ImGui::Button(cube.pipeline->GetCullMode() == Kinai::CullMode::Back ? "glCullFace(GL_BACK)" : "glCullFace(GL_FRONT)"))
			{
				cube.pipeline->SetCullMode(
					cube.pipeline->GetCullMode() == Kinai::CullMode::Back
					? Kinai::CullMode::Front : Kinai::CullMode::Back
				);
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
		PushLayer(Kinai::CreateRef<AppLayer>());
	}

	~App() = default;
};

Kinai::Application*	Kinai::CreateApplication(int argc, char **argv)
{
	KN_NOTUSED(argc);
	KN_NOTUSED(argv);

	return new App();
}
