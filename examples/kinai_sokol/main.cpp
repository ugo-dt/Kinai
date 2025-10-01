// Make sure to compile Kinai with the Sokol backend

#ifndef KINAI_SOKOL
#define KINAI_SOKOL
#endif
#include <Kinai/Kinai.hpp>
#include <Kinai/EntryPoint.hpp>

sg_pass_action pass_action;
sg_pipeline pip;
sg_bindings bind;

class Layer : public Kinai::Layer
{
private:
	Kinai::OrthographicCameraController	_camera;

public:

	Layer()
		: _camera(Kinai::OrthographicCameraControllerConfig{
			.enable_zoom = true, // Enable zoom with mouse wheel
		})
	{
		// a vertex buffer
		const float vertices[] = {
			// positions            // colors
			0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f
		};

		sg_buffer vbuf = sg_make_buffer(sg_buffer_desc{
			.data = SG_RANGE(vertices)
		});

		// a shader
		sg_shader shd = sg_make_shader(sg_shader_desc{
			.vertex_func.source =
				"#version 410\n"
				"layout(location=0) in vec4 position;\n"
				"layout(location=1) in vec4 color0;\n"
				"uniform mat4 mvp;"
				"out vec4 color;\n"
				"void main() {\n"
				"  gl_Position = mvp * position;\n"
				"  color = color0;\n"
				"}\n",
			.fragment_func.source =
				"#version 410\n"
				"in vec4 color;\n"
				"out vec4 frag_color;\n"
				"void main() {\n"
				"  frag_color = color;\n"
				"}\n",
			.uniform_blocks[0] = {
				.stage = SG_SHADERSTAGE_VERTEX,
				.size = sizeof(glm::mat4),
				.glsl_uniforms = {
					[0] = { .type = SG_UNIFORMTYPE_MAT4, .glsl_name = "mvp" },
				}
			},
		});

		// a pipeline state object (default render states are fine for triangle)
		pip = sg_make_pipeline(sg_pipeline_desc{
			.shader = shd,
			.layout = {
				.attrs = {
						[0].format=SG_VERTEXFORMAT_FLOAT3,
						[1].format=SG_VERTEXFORMAT_FLOAT4
					}
				}
		});

		// resource bindings
		bind = {
			.vertex_buffers[0] = vbuf
		};

		pass_action = {
			.colors[0] = { .load_action = SG_LOADACTION_CLEAR, .clear_value = { .12f, 0.12f, 0.12f, 1.0f } }
		};
	}

	void	OnUpdate(float delta)
	{
		_camera.OnUpdate(delta);

		sg_pass pass = {
			.action = pass_action,
			.swapchain = Kinai::Sokol::GetSwapchain()
		};
		sg_begin_pass(&pass);
		sg_apply_pipeline(pip);
		sg_apply_bindings(&bind);

		const glm::mat4 &mvp = _camera.GetCamera().GetViewProjectionMatrix();
		const sg_range r = SG_RANGE(mvp);
		sg_apply_uniforms(0, &r);
		sg_draw(0, 3, 1);
		sg_end_pass();
		sg_commit();
	}

	void	OnImGuiRender()
	{
		Kinai::Application& app = Kinai::Application::Get();

		ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize);
		ImGui::Text("Move with WASD keys");
		ImGui::Text("FPS: %zu", (size_t)app.GetFPS());
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
		: Kinai::Application(Kinai::ApplicationConfig{ .name = "Kinai Sokol", .enable_imgui = true })
	{
		PushLayer<Layer>();
	}

	~App() = default;
};

Kinai::Application*	Kinai::CreateApplication(int argc, char **argv)
{
	KN_NOTUSED(argc);
	KN_NOTUSED(argv);

	return new App();
}
