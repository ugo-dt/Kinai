#pragma once

#include "Kinai/Renderer/Camera.hpp"
#include "Kinai/Core/Window.hpp"

namespace Kinai
{

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera() = default;
	PerspectiveCamera(float viewport_width, float viewport_height, float fov, float near_clip, float far_clip);
	~PerspectiveCamera() = default;

	void OnUpdate();

	void SetViewportSize(float width, float height) { _viewport_width = width; _viewport_height = height; UpdateProjection();}
	inline void SetDistance(float distance)	{ _distance = distance; }
	void SetPosition(const math::vec3& position) { _position = position; UpdateView(); }
	void SetFarClip(float far_clip) { _far_clip = far_clip; UpdateProjection(); }

	inline float GetDistance()          const { return _distance; }
	const math::mat4& GetViewMatrix()    const { return _view_matrix; }
	math::mat4 GetViewProjectionMatrix() const { return _projection_matrix * _view_matrix; }
	math::vec3 GetUpDirection()          const { return math::rotate(GetOrientation(), math::vec3(0.f, 1.f, 0.f)); }
	math::vec3 GetRightDirection()       const { return math::rotate(GetOrientation(), math::vec3(1.f, 0.f, 0.f)); }
	math::vec3 GetForwardDirection()     const { return math::rotate(GetOrientation(), math::vec3(0.f, 0.f, -1.f)); }
	math::quat GetOrientation()          const { return math::quat(math::vec3(-_pitch, -_yaw, 0.f)); }
	const math::vec3& GetPosition()      const { return _position; }
	float GetPitch()                    const { return _pitch; }
	float GetYaw()                      const { return _yaw; }

	bool	OnMouseWheel(MouseWheelEvent& e);
	bool	OnMouseMotion(MouseMotionEvent& event);

	math::mat4 GetOrthographicProjectionMatrix(float aspect_ratio, float zoom_level = 1.0f) const
	{
		float left = -aspect_ratio * zoom_level;
		float right = aspect_ratio * zoom_level;
		float bottom = -zoom_level;
		float top = zoom_level;
		return math::ortho(left, right, bottom, top, _near_clip, _far_clip);
	}

	math::mat4 GetOrthographicViewProjectionMatrix(float aspect_ratio, float zoom_level = 1.0f) const
	{
		return GetOrthographicProjectionMatrix(aspect_ratio, zoom_level) * _view_matrix;
	}

private:
	void	UpdateProjection();
	void	UpdateView();

	void	MousePan(const math::vec2& delta);
	void	MouseRotate(const math::vec2& delta);
	void	MouseZoom(const float delta);

	math::vec3	CalculatePosition() const;

	math::vec2	PanSpeed() const;
	float		RotationSpeed() const;
	float		ZoomSpeed() const;

private:
	float		_fov, _aspect_ratio, _near_clip, _far_clip;
	math::mat4	_view_matrix;
	math::vec3	_position;
	math::vec3	_focal_point;
	math::vec2	_inital_mouse_position;
	float		_distance;
	float		_pitch, _yaw;
	float		_viewport_width;
	float		_viewport_height;
};

struct PerspectiveCameraControllerConfig
{
	float		viewport_width = KN_DEFAULT_WINDOW_WIDTH;
	float		viewport_height = KN_DEFAULT_WINDOW_HEIGHT;
	float		fov = 45.0f;
	float		near_clip = 0.1f;
	float		far_clip = 100.0f;
	float		speed = 5.0f;
	math::vec3	position = {0.0f, 0.0f, 2.0f};
	bool		no_rotation = false;
	bool		no_lock_cursor = false;
	bool		no_lock_rotation = false; // When true, lock the cursor when rotation is enabled. Unlock it when disabled.
};

class PerspectiveCameraController
{
public:
	PerspectiveCameraController(const PerspectiveCameraControllerConfig& config = PerspectiveCameraControllerConfig());

	void OnUpdate(float delta);
	void OnEvent(Event &e);

	void OnResize(float width, float height);

	PerspectiveCamera& GetCamera()       { return _camera; }
	const PerspectiveCamera& GetCamera() const { return _camera; }

	bool IsCursorLocked() const;
	void SetCursorLock(bool enabled);

	bool IsRotationEnabled() const;
	void SetRotationEnabled(bool enabled);

	void SetSpeed(float speed) { _config.speed = speed; }
	void SetFarClip(float far_clip) { _camera.SetFarClip(far_clip); _config.far_clip = far_clip; }

private:
	bool	OnMouseWheel(MouseWheelEvent& event);
	bool	OnMouseMotion(MouseMotionEvent& event);
	bool	OnWindowResize(WindowResizeEvent& event);

private:
	PerspectiveCamera					_camera;
	PerspectiveCameraControllerConfig	_config;
};

} // Kinai
