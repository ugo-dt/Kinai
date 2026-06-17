#include "AppLayer.hpp"
#include "quad.glsl.hpp"

static AppState *g_state = nullptr;

class EventsLayer : public Kinai::Layer
{
public:
	EventsLayer(): Kinai::Layer("App Layer") {}
	~EventsLayer() = default;

	void	OnUpdate(float delta)
	{
		KN_NOTUSED(delta);
	}

	void	OnRender()
	{
		float time = std::chrono::duration<float>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
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
				Kinai::Quit();
				break;
			case Kinai::Key::Q:
				g_state->current_layer = AppLayerType::AppLayer;
				TransitionTo<AppLayer>(g_state);
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

AppLayer::AppLayer(AppState *state)
	: Kinai::Layer("App Layer"),
	  _state(state),
	  _pipeline(Kinai::Pipeline::Create(Kinai::PipelineConfig{
	  	.vao = Kinai::VertexArray::Create(),
	  	.shader = Kinai::Shader::Create(quadProgramShaderConfig()),
	  	.layout = Kinai::BufferLayout{
	  		{ Kinai::ShaderDataType::Float3, "a_Position" },
	  		{ Kinai::ShaderDataType::Float4, "a_Color" }
	  	},
	  	.label = "Cube pipeline",
	  })),
	  _bindings(Kinai::Bindings::Create())
{
	g_state = state; // Store the state in a global variable for the EventsLayer
	assert(state);
	if (state->first_load)
	{
		*_state = AppState{
			.first_load = false,
			.camera = Kinai::PerspectiveCameraController(Kinai::PerspectiveCameraControllerConfig{
				.position = {0.0f, 0.0f, 5.0f},
			}),
			.mode = Kinai::PolygonMode::Fill,
			.rotation = 0.0f,
			.rotate = true,
			.show_back_faces = false,
		};
	}
	_bindings->AddVertexBuffer(Kinai::VertexBuffer::Create(cube_vertices, sizeof(cube_vertices)));
	_bindings->SetIndexBuffer(Kinai::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
}

AppLayer::~AppLayer()
{
}

void AppLayer::OnUpdate(float delta)
{
	if (_state->current_layer == AppLayerType::EventsLayer)
		TransitionTo<EventsLayer>();
	_state->camera.OnUpdate(delta);
	_state->rotation += delta;
}

void AppLayer::OnRender()
{
	if (_state->current_layer != AppLayerType::AppLayer)
		return;
	Kinai::Renderer::BeginPass();
	{
		Kinai::Renderer::SetClearColor(0.25f, 0.5f, 0.75f, 1.0f);
		Kinai::Renderer::Clear();

		Kinai::Renderer::ApplyPipeline(_pipeline);
		Kinai::Renderer::ApplyBindings(_bindings);

		glm::mat4 transform = glm::mat4(1.0f);
		if (_state->rotate)
		{
			glm::mat4 rxm = glm::rotate(_state->rotation, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rym = glm::rotate(2 * _state->rotation, glm::vec3(0.0f, 1.0f, 0.0f));
			transform = rxm * rym;
		}

		Kinai::Renderer::ApplyUniforms<quad_vs_params_t>({
			.u_ViewProjection = _state->camera.GetCamera().GetViewProjectionMatrix(),
			.u_Transform = transform,
		});

		if (_state->show_back_faces)
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

void AppLayer::OnImGuiRender()
{
	Kinai::Application& app = Kinai::Application::Get();

	ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize);
	ImGui::Text("Move around with WASD keys");
	ImGui::Text("FPS: %zu", (size_t)app.GetFPS());
	if (ImGui::Button(_state->camera.IsRotationEnabled() ? "(F1) Mouse Grab ON" : "(F1) Mouse Grab OFF"))
		_state->camera.SetRotationEnabled(!_state->camera.IsRotationEnabled());
	if (ImGui::Button(("(F2) Cube Rotation: " + std::string(_state->rotation ? "ON" : "OFF")).c_str()))
		_state->rotation = !_state->rotation;
	if (ImGui::Button(app.GetWindow().IsVSync() ? "(F3) VSync ON" : "(F3) VSync OFF"))
		app.GetWindow().SetVSync(!app.GetWindow().IsVSync());
	if (ImGui::Button(_pipeline->GetFaceWinding() == Kinai::FaceWinding::CCW
		? "(F4) glFrontFace(GL_CCW)"
		: "(F4) glFrontFace(GL_CW)")
	)
	{
		_pipeline->SetFaceWinding(
			_pipeline->GetFaceWinding() == Kinai::FaceWinding::CCW
			? Kinai::FaceWinding::CW : Kinai::FaceWinding::CCW
		);
	}
	if (ImGui::Button(_state->show_back_faces ? "(F5) Hide back faces" : "(F5) Show back faces"))
	{
		_state->show_back_faces = !_state->show_back_faces;
		Kinai::Renderer::SetPolygonMode(_state->mode);
	}
	if (ImGui::Button(_state->mode == Kinai::PolygonMode::Line ? "Wireframe ON" : "Wireframe OFF"))
	{
		_state->mode = _state->mode == Kinai::PolygonMode::Fill ? Kinai::PolygonMode::Line : Kinai::PolygonMode::Fill;
		Kinai::Renderer::SetPolygonMode(_state->mode);
	}
	if (ImGui::Button(_pipeline->GetCullMode() == Kinai::CullMode::Back ? "glCullFace(GL_BACK)" : "glCullFace(GL_FRONT)"))
	{
		_pipeline->SetCullMode(
			_pipeline->GetCullMode() == Kinai::CullMode::Back
			? Kinai::CullMode::Front : Kinai::CullMode::Back
		);
	}
	ImGui::End();
}

void AppLayer::OnEvent(Kinai::Event& event)
{
	Kinai::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<Kinai::KeyPressedEvent>(KN_BIND_EVENT_FN(OnKeyPressed));
	_state->camera.OnEvent(event);
}

bool AppLayer::OnKeyPressed(Kinai::KeyPressedEvent &event)
{
	switch (event.GetKeyCode())
	{
		case Kinai::Key::Escape:
			Kinai::Quit();
			break;
		case Kinai::Key::R:
			return false; // forward the event
		case Kinai::Key::F1:
			_state->camera.SetRotationEnabled(!_state->camera.IsRotationEnabled());
			break;
		case Kinai::Key::F2:
			_state->rotate = !_state->rotate;
			break;
		case Kinai::Key::F3:
			Kinai::Application::Get().GetWindow().SetVSync(!Kinai::Application::Get().GetWindow().IsVSync());
			break;
		case Kinai::Key::F4:
			_pipeline->SetFaceWinding(
				_pipeline->GetFaceWinding() == Kinai::FaceWinding::CCW
				? Kinai::FaceWinding::CW : Kinai::FaceWinding::CCW
			);
			break;
		case Kinai::Key::F5:
			_state->show_back_faces = !_state->show_back_faces;
			Kinai::Renderer::SetPolygonMode(_state->mode);
			break;
		case Kinai::Key::Q:
			_state->current_layer = AppLayerType::EventsLayer;
			TransitionTo<EventsLayer>();
			break;
		default:
			break;
	}
	return true;
}

extern "C" AppLayer* CreateAppLayer(AppState *state)
{
	return new AppLayer(state);
}
