#pragma once

#include <Kinai/Kinai.hpp>

struct scope
{
	scope(const std::string& name): name(name)
	{
		printf("%s start\n", name.c_str());
	}
	~scope()
	{
		printf("%s end\n", name.c_str());
	}
	std::string name;
};

struct AppState
{
	bool first_load;
	Kinai::PerspectiveCameraController	camera;
	Kinai::Ref<Kinai::Pipeline>	pipeline;
	Kinai::Ref<Kinai::Bindings>	bindings;
	Kinai::PolygonMode mode = Kinai::PolygonMode::Fill;
	bool rotation;
	bool show_back_faces;
};

class AppLayer : public Kinai::Layer
{
public:
	AppLayer(AppState *state);
	~AppLayer();

	void OnUpdate(float delta);
	void OnRender();
	void OnImGuiRender();
	void OnEvent(Kinai::Event& event);
	bool OnKeyPressed(Kinai::KeyPressedEvent &event);

private:
	AppState *_state;
};

// extern "C" AppLayer* CreateAppLayer(AppState *state);
