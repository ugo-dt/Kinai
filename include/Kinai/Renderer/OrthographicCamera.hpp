#pragma once

#include "Kinai/Renderer/Camera.hpp"
#include "Kinai/Core/Window.hpp"

namespace Kinai
{

class OrthographicCamera
{
public:
	OrthographicCamera(float left, float right, float bottom, float top);
	virtual ~OrthographicCamera() = default;
	
	void SetProjection(float left, float right, float bottom, float top);
	void SetProjection(float left, float right, float bottom, float top, float near, float far);
	void SetPosition(const math::vec3& position) { _position = position; UpdateView(); }
	void SetRotation(const math::vec3& rotation) { _rotation = rotation; }

	const math::vec3& GetPosition() const { return _position; }
	const math::vec3& GetRotation() const { return _rotation; }

	const math::mat4& GetProjectionMatrix() const { return _projection_matrix; }
	const math::mat4& GetViewMatrix() const { return _view_matrix; }
	const math::mat4& GetViewProjectionMatrix() const { return _view_projection_matrix; }

private:
	void UpdateView();

private:
	math::vec3 _position;
	math::vec3 _rotation;
	math::mat4 _projection_matrix;
	math::mat4 _view_matrix;
	math::mat4 _view_projection_matrix;
};

struct OrthographicCameraControllerConfig
{
	float aspect_ratio = KN_DEFAULT_WINDOW_WIDTH / (float)KN_DEFAULT_WINDOW_HEIGHT;
	bool enable_rotation = false;
	bool enable_zoom = false;
	float translation_speed = 5.0f;
	float rotation_speed = 180.0f;
	math::vec3 position = math::vec3(0.0f);
	math::vec3 rotation = math::vec3(0.0f);
	float zoom_level = 1.0f;
};

class OrthographicCameraController
{
public:
	OrthographicCameraController(const OrthographicCameraControllerConfig &config = OrthographicCameraControllerConfig());

	void OnUpdate(float delta);
	void OnEvent(Event& event);
	void OnResize(float width, float height);

	OrthographicCamera& GetCamera() { return _camera; }
	const OrthographicCamera& GetCamera() const { return _camera; }

	float GetZoomLevel() const { return _config.zoom_level; }

private:
	bool OnMouseWheel(MouseWheelEvent& event);
	bool OnWindowResize(WindowResizeEvent& event);

private:
	OrthographicCamera _camera;
	OrthographicCameraControllerConfig _config;
};

} // Kinai
