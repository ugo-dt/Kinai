#pragma once

#include <Kinai/Kinai.hpp>

enum class AppLayerType
{
	AppLayer,
	EventsLayer,
};

struct AppState
{
	bool first_load;
	Kinai::PerspectiveCameraController	camera;
	Kinai::PolygonMode mode = Kinai::PolygonMode::Fill;
	float rotation;
	bool rotate;
	bool show_back_faces;
	AppLayerType current_layer = AppLayerType::AppLayer;
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
	Kinai::Ref<Kinai::Pipeline>	_pipeline;
	Kinai::Ref<Kinai::Bindings>	_bindings;
};
