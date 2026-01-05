#include "Kinai/Renderer/PerspectiveCamera.hpp"
#include "Kinai/Core/Input.hpp"
#include "Kinai/Core/Application.hpp"

namespace Kinai
{

PerspectiveCamera::PerspectiveCamera(float viewport_width, float viewport_height, float fov, float near_clip, float far_clip)
	: Camera(glm::perspective(glm::radians(fov), viewport_width / viewport_height, near_clip, far_clip)),
	  _fov(fov),
	  _aspect_ratio(viewport_width / viewport_height),
	  _near_clip(near_clip),
	  _far_clip(far_clip),
	  _view_matrix(),
	  _position(0.0f, 0.0f, 3.0f),
	  _focal_point(0.0f, 0.0f, 0.0f),
	  _inital_mouse_position(viewport_width / 2, viewport_height / 2),
	  _distance(10.f),
	  _pitch(0.0f),
	  _yaw(0.0f),
	  _viewport_width(viewport_width),
	  _viewport_height(viewport_height)
{
	UpdateView();
}

void	PerspectiveCamera::OnUpdate()
{
	UpdateView();
}

void	PerspectiveCamera::UpdateProjection()
{
	_aspect_ratio = _viewport_width / _viewport_height;
	_projection_matrix = glm::perspective(glm::radians(_fov), _viewport_width / _viewport_height, _near_clip, _far_clip);
}

void	PerspectiveCamera::UpdateView()
{
	// _position = CalculatePosition();

	glm::quat orientation = GetOrientation();
	_view_matrix = glm::translate(glm::mat4(1.0f), _position) * glm::toMat4(orientation);
	_view_matrix = glm::inverse(_view_matrix);
}

bool	PerspectiveCamera::OnMouseWheel(MouseWheelEvent& event)
{
	float delta = event.GetYOffset() * .1f;

	MouseZoom(delta);
	UpdateView();
	return false;
}

bool	PerspectiveCamera::OnMouseMotion(MouseMotionEvent& event)
{
	const glm::vec2 delta = glm::vec2(event.GetXRelative(), event.GetYRelative()) * .003f;

	MouseRotate(delta);
	UpdateView();
	return false;
}

void	PerspectiveCamera::MousePan(const glm::vec2& delta)
{
	glm::vec2 speed = PanSpeed();

	_focal_point += -GetRightDirection() * delta.x * speed.x * _distance;
	_focal_point += GetUpDirection() * delta.y * speed.y * _distance;
}

void	PerspectiveCamera::MouseRotate(const glm::vec2& delta)
{
	float yaw_sign = GetUpDirection().y < 0 ? -1.0f : 1.0f;

	_yaw += yaw_sign * delta.x * RotationSpeed();
	_pitch += delta.y * RotationSpeed();

	if (_pitch > glm::radians(89.f))
		_pitch =  glm::radians(89.f);
	if (_pitch < glm::radians(-89.f))
		_pitch = glm::radians(-89.f);
}

void	PerspectiveCamera::MouseZoom(const float delta)
{
	_distance -= delta * ZoomSpeed();
	if (_distance < 1.0f)
	{
		_focal_point += GetForwardDirection();
		_distance = 1.0f;
	}
}

glm::vec3	PerspectiveCamera::CalculatePosition() const
{
	return _focal_point - GetForwardDirection() * _distance;
}

glm::vec2	PerspectiveCamera::PanSpeed() const
{
	float x = std::min(_viewport_width / 1000.0f, 2.4f); // max = 2.4f
	float x_factor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

	float y = std::min(_viewport_height / 1000.0f, 2.4f); // max = 2.4f
	float y_factor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

	return glm::vec2(x_factor, y_factor);
}

float	PerspectiveCamera::RotationSpeed() const
{
	return 0.8f;
}

float	PerspectiveCamera::ZoomSpeed() const
{
	float distance = _distance * 0.2f;
	distance = std::max(distance, 0.0f);
	float speed = distance * distance;
	speed = std::min(speed, 100.0f); // max speed = 100
	return speed;
}

PerspectiveCameraController::PerspectiveCameraController(const PerspectiveCameraControllerConfig& config)
	: _camera(config.viewport_width, config.viewport_height, config.fov, config.near_clip, config.far_clip),
	  _config(config)
{
	SetRotationEnabled(!config.no_rotation);
	SetCursorLock(!config.no_lock_cursor);
	_camera.SetPosition(_config.position);
}

void	PerspectiveCameraController::OnUpdate(float delta)
{
	_camera.OnUpdate();

	const float	speed = _config.speed * delta;
	const glm::vec3	orientation_xz = glm::normalize(glm::vec3(_camera.GetForwardDirection().x, 0.f, _camera.GetForwardDirection().z));

	if (Input::IsKeyPressed(Key::W))
		_config.position += speed * orientation_xz;
	if (Input::IsKeyPressed(Key::S))
		_config.position -= speed * orientation_xz;
	if (Input::IsKeyPressed(Key::A))
		_config.position -= speed * glm::normalize(glm::cross(_camera.GetForwardDirection(), _camera.GetUpDirection()));
	if (Input::IsKeyPressed(Key::D))
		_config.position += speed * glm::normalize(glm::cross(_camera.GetForwardDirection(), _camera.GetUpDirection()));

	if (Input::IsKeyPressed(Key::Space))
		_config.position += speed * glm::vec3(0.0f, 1.0f, 0.0f);
	if (Input::IsKeyPressed(Key::LeftShift))
		_config.position -= speed * glm::vec3(0.0f, 1.0f, 0.0f);
	
	_camera.SetPosition(_config.position);

	Window& window = Application::Get().GetWindow();
	if (window.IsFocused() && window.GetRelativeMouseMode())
		window.WarpMouse(window.GetWidth() / 2, window.GetHeight() / 2);
}

void	PerspectiveCameraController::OnEvent(Event &e)
{
	EventDispatcher	dispatcher(e);

	dispatcher.Dispatch<MouseWheelEvent>(KN_BIND_EVENT_FN(PerspectiveCameraController::OnMouseWheel));
	dispatcher.Dispatch<MouseMotionEvent>(KN_BIND_EVENT_FN(PerspectiveCameraController::OnMouseMotion));
	dispatcher.Dispatch<WindowResizeEvent>(KN_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResize));
}

void	PerspectiveCameraController::OnResize(float width, float height)
{
	_camera.SetViewportSize(width, height);
}

bool	PerspectiveCameraController::OnMouseWheel(MouseWheelEvent& event)
{
	_camera.OnMouseWheel(event);
	return false;
}

bool	PerspectiveCameraController::OnMouseMotion(MouseMotionEvent& event)
{
	if (!_config.no_rotation)
		_camera.OnMouseMotion(event);
	return false;
}

bool	PerspectiveCameraController::OnWindowResize(WindowResizeEvent& event)
{
	OnResize(event.GetWidth(), event.GetHeight());
	return false;
}

bool	PerspectiveCameraController::IsCursorLocked() const
{
	// return Application::Get().GetWindow().GetRelativeMouseMode();
	return !_config.no_lock_cursor;
}

void	PerspectiveCameraController::SetCursorLock(bool lock)
{
	_config.no_lock_cursor = !lock;
	Application::Get().GetWindow().SetRelativeMouseMode(lock);
}

bool	PerspectiveCameraController::IsRotationEnabled() const
{
	return !_config.no_rotation;
}

void	PerspectiveCameraController::SetRotationEnabled(bool enabled)
{
	_config.no_rotation = !enabled;

	if (enabled)
	{
		Window& window = Application::Get().GetWindow();

		if (!_config.no_lock_rotation || IsCursorLocked())
			window.SetRelativeMouseMode(true);
		window.WarpMouse(window.GetWidth() / 2, window.GetHeight() / 2);
	}
	else if (!_config.no_lock_rotation || !IsCursorLocked())
		Application::Get().GetWindow().SetRelativeMouseMode(false);
}

} // Kinai
