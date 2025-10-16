#include <Kinai/Kinai.hpp>
#include <Kinai/EntryPoint.hpp>

const char *custom_shader_vs = R"(
	#version 410 core

	uniform float TIME;
	uniform float PI;
	uniform float TAU;
	uniform float E;

	uniform mat4 CANVAS_MATRIX;

	layout (location = 0) in  vec2 a_VERTEX;
	layout (location = 1) in  vec2 a_UV;
	layout (location = 2) in  vec4 a_COLOR;
	layout (location = 3) in  int a_TEX_INDEX;

	int VERTEX_ID; // gl_VertexID
	float POINT_SIZE; // gl_PointSize
	vec2 VERTEX;
	vec2 UV;
	vec4 COLOR;
	int  TEX_INDEX;

	out vec2 v_VERTEX;
	out vec2 v_UV;
	out vec4 v_COLOR;
	out float v_TEX_INDEX;

	void	vertex()
	{
		VERTEX = (CANVAS_MATRIX * vec4(VERTEX, 0.0, 1.0)).xy;
	}

	void main()
	{
		VERTEX_ID = gl_VertexID;
		// POINT_SIZE = gl_PointSize;
		VERTEX = a_VERTEX;
		UV = a_UV;
		COLOR = a_COLOR;
		TEX_INDEX = a_TEX_INDEX;

		// Custom shader code
		vertex();

		gl_Position = vec4(VERTEX, 0.0, 1.0);
		// gl_PointSize = POINT_SIZE;

		v_VERTEX = VERTEX;
		v_UV = UV;
		v_COLOR = COLOR;
		v_TEX_INDEX = TEX_INDEX;
	}
)";

const char *custom_shader_fs = R"(
	#version 410 core

	uniform float TIME;
	uniform float PI;
	uniform float TAU;
	uniform float E;

	in vec2 v_VERTEX;
	in vec2 v_UV;
	in vec4 v_COLOR;
	in float  v_TEX_INDEX;

	vec2 VERTEX;
	vec2 UV;
	vec4 COLOR;
	float  TEX_INDEX;
	vec2 SCREEN_UV;

	uniform sampler2D TEXTURE_SLOTS[16];
	#define TEXTURE             (TEXTURE_SLOTS[int(TEX_INDEX)])
	#define SCREEN_TEXTURE      (TEXTURE_SLOTS[1])

	uniform vec2 VIEWPORT;

	vec4 FRAGCOORD; // gl_FragCoord
	vec2 SCREEN_PIXEL_SIZE; // TODO

	layout (location = 0) out vec4 out_COLOR;

	uniform vec2 scroll1;
	uniform vec2 scroll2;
	uniform float oscillation_speed;
	uniform float light_start = 0.275;
	uniform float light_end = 0.4;

	uniform vec4 top_color;
	uniform vec4 tone_color;
	uniform float alpha;

	void	fragment()
	{
		float oscillation = sin(TIME * oscillation_speed);
		float distortion_strength = mix(-0.05, 0.05, (oscillation + 1.0) / 2.0);

		float depth = texture(TEXTURE, UV + scroll1 * TIME).r * texture(TEXTURE, UV + scroll2 * TIME).r;
		vec4 screen_col = texture(SCREEN_TEXTURE, SCREEN_UV + distortion_strength * vec2(depth));
		vec4 top_light = smoothstep(light_start, light_end, depth) * top_color;
		COLOR = screen_col * tone_color + top_light;
		COLOR.a = alpha;
	}

	void main()
	{
		VERTEX = v_VERTEX;
		UV = v_UV;
		COLOR = v_COLOR;
		TEX_INDEX = v_TEX_INDEX;
		FRAGCOORD = gl_FragCoord;
		// SCREEN_PIXEL_SIZE =
		SCREEN_UV = gl_FragCoord.xy / VIEWPORT;

		// Custom shader code
		fragment();

		out_COLOR = COLOR;
	}
)";

class AppLayer : public Kinai::Layer
{
// Private members are at the top for convenience
private:
	Kinai::OrthographicCameraController	_camera;
	Kinai::Ref<Kinai::Texture2D>		_cobblestone;
	Kinai::Ref<Kinai::Texture2D>		_noise;
	// Kinai::Renderer2D::Shader2D			_shader;
	glm::vec2							_scroll1;
	glm::vec2							_scroll2;
	glm::vec1							_oscillation;
	glm::vec4							_tone_color;
	glm::vec4							_top_color;
	glm::vec1							_alpha;
public:
	AppLayer()
		: Kinai::Layer("App Layer"),
	  	  _camera(Kinai::OrthographicCameraControllerConfig{
		  	.enable_zoom = true,
	  	  }),
	  	  _cobblestone(Kinai::Texture2D::Create("assets/cobblestone.png")),
	  	  _noise(Kinai::Texture2D::Create("assets/seamless_noise.png")),
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
		KN_NOTUSED(delta);

		_camera.OnUpdate(delta);

		Kinai::Renderer::SetClearColor(0.12f, 0.12f, 0.12f, 1.0f);
		Kinai::Renderer::Clear();

		Kinai::Renderer::BeginPass();
		Kinai::Painter::BeginPass();

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

		Kinai::Painter::SetImage(0, _cobblestone);
		Kinai::Painter::DrawQuad(glm::vec2(0.5f), glm::vec2(0.5f), glm::vec4(1.0f));
		Kinai::Painter::ResetImage();
		// Kinai::Painter::DrawQuad(glm::vec2(-0.25f, 0.25f), glm::vec2(0.5f), glm::vec4(1.0f));
		Kinai::Painter::EndPass();
		Kinai::Renderer::EndPass();
	}

	void	OnImGuiRender()
	{
		Kinai::Application& app = Kinai::Application::Get();

		ImGui::Begin("Debug");

		// static uint32_t total_draw_calls = 0;

		// auto& stats = Kinai::Painter::GetStats();
		// ImGui::Text("Renderer2D Stats:");
		// ImGui::Text("Current Draw Calls: %d", stats.GetDrawCalls());
		// ImGui::Text("Total Draw Calls: %d", total_draw_calls);
		// total_draw_calls += stats.GetDrawCalls();

		// ImGui::Text("Quads: %d", stats.GetQuadCount());
		// ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		// ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
		// ImGui::Text("FPS: %zu", (size_t)app.GetFPS());
		// stats.Reset();

		ImGui::SameLine();
		if (ImGui::Button(app.GetWindow().IsVSync() ? "VSync ON" : "VSync OFF"))
			app.GetWindow().SetVSync(!app.GetWindow().IsVSync());
		ImGui::SliderFloat("Scroll1", (float*)&_scroll1, -1.f, 1.f, nullptr);
		ImGui::SliderFloat("Scroll2", (float*)&_scroll2, -1.f, 1.f, nullptr);
		ImGui::SliderFloat("Oscillation", (float*)&_oscillation, 0.f, 4.f, nullptr);
		ImGui::ColorEdit4("Tone color", (float*)&_tone_color);
		ImGui::ColorEdit4("Top color", (float*)&_top_color);
		ImGui::SliderFloat("Alpha cap", (float*)&_alpha, 0.0, 1.f, nullptr);
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
	App(): Kinai::Application(Kinai::ApplicationConfig{ .enable_imgui = true })
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
