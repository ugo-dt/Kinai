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

	void	OnUpdate();
	void	OnEvent(Event& event);

	void				SetViewportSize(float width, float height) { _viewport_width = width; _viewport_height = height; UpdateProjection();}
	inline void			SetDistance(float distance)	{ _distance = distance; }
	void				SetPosition(const glm::vec3& position) { _position = position; UpdateView(); }

	inline float		GetDistance()             const { return _distance; }

	const glm::mat4&	GetViewMatrix()           const { return _view_matrix; }
	glm::mat4			GetViewProjectionMatrix() const { return _projection * _view_matrix; }

	glm::vec3			GetUpDirection()          const { return glm::rotate(GetOrientation(), glm::vec3(0.f, 1.f, 0.f)); }
	glm::vec3			GetRightDirection()       const { return glm::rotate(GetOrientation(), glm::vec3(1.f, 0.f, 0.f)); }
	glm::vec3			GetForwardDirection()     const { return glm::rotate(GetOrientation(), glm::vec3(0.f, 0.f, -1.f)); }
	glm::quat			GetOrientation()          const { return glm::quat(glm::vec3(-_pitch, -_yaw, 0.f)); }

	const glm::vec3&	GetPosition()             const { return _position; }
	float				GetPitch()                const { return _pitch; }
	float				GetYaw()                  const { return _yaw; }
	
	bool	OnMouseWheel(MouseWheelEvent& e);
	bool	OnMouseMotion(MouseMotionEvent& event);

private:
	void	UpdateProjection();
	void	UpdateView();

	void	MousePan(const glm::vec2& delta);
	void	MouseRotate(const glm::vec2& delta);
	void	MouseZoom(const float delta);

	glm::vec3	CalculatePosition() const;

	glm::vec2	PanSpeed() const;
	float		RotationSpeed() const;
	float		ZoomSpeed() const;

private:
	float		_fov, _aspect_ratio, _near_clip, _far_clip;
	glm::mat4	_view_matrix;
	glm::vec3	_position;
	glm::vec3	_focal_point;
	glm::vec2	_inital_mouse_position;
	float		_distance;
	float		_pitch, _yaw;
	float		_viewport_width;
	float		_viewport_height;
};

struct CameraControllerConfig
{
	float		viewport_width = EG_DEFAULT_WINDOW_WIDTH;
	float		viewport_height = EG_DEFAULT_WINDOW_HEIGHT;
	float		fov = 45.0f;
	float		near_clip = 0.1f;
	float		far_clip = 1000.0f;
	float		speed = 5.0f;
	glm::vec3	position = {0.0f, 0.0f, 2.0f};
	bool		enable_rotation = true;
	bool		lock_cursor = true;
	bool		lock_rotation = true; // When true, lock the cursor when rotation is enabled. Unlock it when disabled.
};

class PerspectiveCameraController
{
public:
	PerspectiveCameraController(const CameraControllerConfig& config = CameraControllerConfig());

	void	OnUpdate(float delta);
	void	OnEvent(Event &e);

	void	OnResize(float width, float height);

	PerspectiveCamera&			GetCamera()       { return _camera; }
	const PerspectiveCamera&	GetCamera() const { return _camera; }

	bool	IsCursorLocked() const;
	void	SetCursorLock(bool enabled);

	bool	IsRotationEnabled() const;
	void	SetRotationEnabled(bool enabled);

private:
	bool	OnMouseWheel(MouseWheelEvent& event);
	bool	OnMouseMotion(MouseMotionEvent& event);
	bool	OnWindowResize(WindowResizeEvent& event);

private:
	PerspectiveCamera		_camera;
	CameraControllerConfig	_config;
};

} // Kinai
