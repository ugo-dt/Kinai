// See also:
// sample-rectangle.c by edubart
// https://github.com/edubart/sokol_gp/blob/master/samples/sample-rectangle.c
// Make sure to compile Kinai with the Sokol backend

#ifndef KINAI_SOKOL
#define KINAI_SOKOL
#endif
#include <Kinai/EntryPoint.hpp>
#include <Kinai/Kinai.hpp>
#include "stb/stb_image.h"
#include "kinai_sokol_gp/quad.glsl.h"

static sg_pipeline pip;
static sg_shader shd;
static sg_image image;
static sg_sampler nearest_sampler;

static sg_image load_image(const char *filename)
{
    int width, height, channels;
    uint8_t* data = stbi_load(filename, &width, &height, &channels, 4);
    sg_image img = {SG_INVALID_ID};
    if (!data)
	{
        return img;
    }
    sg_image_desc image_desc = {};
    image_desc.width = width;
    image_desc.height = height;
    image_desc.data.subimage[0][0].ptr = data;
    image_desc.data.subimage[0][0].size = (size_t)(width * height * 4);
    img = sg_make_image(&image_desc);
    stbi_image_free(data);
    return img;
}

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
		sgp_desc sgpdesc = {};
		sgp_setup(&sgpdesc);
		if (!sgp_is_valid())
		{
			fprintf(stderr, "Failed to create Sokol GP context: %s\n", sgp_get_error_message(sgp_get_last_error()));
			exit(1);
		}

		image = load_image("./assets/cobblestone.png");
		if (sg_query_image_state(image) != SG_RESOURCESTATE_VALID)
		{
			Kinai::Log::Critical("Failed to load images");
			exit(1);
		}

		nearest_sampler = sg_make_sampler(sg_sampler_desc{
			.min_filter = SG_FILTER_NEAREST,
			.mag_filter = SG_FILTER_NEAREST,
			.wrap_u = SG_WRAP_REPEAT,
			.wrap_v = SG_WRAP_REPEAT,
		});
		if (sg_query_sampler_state(nearest_sampler) != SG_RESOURCESTATE_VALID)
		{
			Kinai::Log::Critical("failed to create linear sampler");
			exit(1);
		}

		shd = sg_make_shader(quad_program_shader_desc(sg_query_backend()));
		if (sg_query_shader_state(shd) != SG_RESOURCESTATE_VALID)
		{
			Kinai::Log::Critical("failed to make custom pipeline shader");
			exit(1);
		}
		pip = sgp_make_pipeline(sgp_pipeline_desc{
			.shader = shd,
			.has_vs_color = true
		});
		if (sg_query_pipeline_state(pip) != SG_RESOURCESTATE_VALID)
		{
			Kinai::Log::Critical("failed to make custom pipeline");
			exit(1);
		}
		glDisable(GL_CULL_FACE);
	}

	~Layer()
	{
		sg_destroy_sampler(nearest_sampler);
		sg_destroy_image(image);
		sg_destroy_pipeline(pip);
		sg_destroy_shader(shd);
		sgp_shutdown();
	}

	void	OnUpdate(float delta)
	{
		_camera.OnUpdate(delta);

		auto& app = Kinai::Application::Get();
		int width = app.GetWindow().GetWidth();
		int height = app.GetWindow().GetHeight();

		sgp_begin(width, height);
		sgp_viewport(0, 0, width, height);
		sgp_project(0, 1.f, 0.f, 1.f);

		sgp_set_color(0.1f, 0.1f, 0.1f, 1.0f);
		sgp_clear();

		float time = SDL_GetTicks() / 1000.f;
		float r = sinf(time)*0.5+0.5, g = cosf(time)*0.5+0.5;
		sgp_set_color(r, g, 0.3f, 1.0f);

		sgp_set_pipeline(pip);
		sgp_set_uniform(
			// vertex
			quad_vs_params_t{
				.view_proj = _camera.GetCamera().GetViewProjectionMatrix(),
				.rotate = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0.0f, 0.0f, 1.0f)),
			},
			sizeof(quad_vs_params_t),
			// fragment
			nullptr,
			0
		);
		sgp_set_image(IMG_quad_iTexChannel0, image);
		sgp_set_sampler(SMP_quad_iSmpChannel0, nearest_sampler);

		sgp_rect rect = {
			.x = 0.25f,
			.y = 0.25f,
			.w = 0.5f,
			.h = 0.5f,
		};
		sgp_draw_filled_rects(&rect, 1);

		sgp_reset_image(IMG_quad_iTexChannel0);

		sgp_rect rect2 = {
			.x = 0.75f,
			.y = 0.75f,
			.w = 0.5f,
			.h = 0.5f,
		};
		sgp_draw_filled_rects(&rect2, 1);

		sgp_reset_sampler(SMP_quad_iSmpChannel0);
		sgp_reset_pipeline();

		sg_pass pass = {.swapchain = Kinai::Sokol::GetSwapchain()};
		sg_begin_pass(&pass);
		sgp_flush();
		sgp_end();
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

class GameApplication : public Kinai::Application
{
public:
	GameApplication()
		: Kinai::Application(Kinai::ApplicationConfig{ .name = "Kinai Sokol GP", .enable_imgui = true })
	{
		PushLayer<Layer>();
	}

	~GameApplication() = default;
};

Kinai::Application*	Kinai::CreateApplication(int argc, char **argv)
{
	KN_NOTUSED(argc);
	KN_NOTUSED(argv);

	return new GameApplication();
}
