#include "Kinai/Renderer/OrthographicCamera.hpp"
#include "Kinai/Core/Input.hpp"

namespace Kinai
{

static constexpr float ORTHO_NEAR_CLIP = -2048.0f;
static constexpr float ORTHO_FAR_CLIP = 2048.0f;

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	: _position(0.0f, 0.0f, 0.0f),
	  _rotation(0.0f),
	  _projection_matrix(math::ortho(left, right, bottom, top, ORTHO_NEAR_CLIP, ORTHO_FAR_CLIP)),
	  _view_matrix(1.0f),
	  _view_projection_matrix(_projection_matrix * _view_matrix)
{
	KN_PROFILE_FUNC();
}

void	OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
	KN_PROFILE_FUNC();

	_projection_matrix = math::ortho(left, right, bottom, top, ORTHO_NEAR_CLIP, ORTHO_FAR_CLIP);
	_view_projection_matrix = _projection_matrix * _view_matrix;
}

void	OrthographicCamera::SetProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
	KN_PROFILE_FUNC();

	_projection_matrix = math::ortho(left, right, bottom, top, nearPlane, farPlane);
	_view_projection_matrix = _projection_matrix * _view_matrix;
}

void	OrthographicCamera::UpdateView()
{
	KN_PROFILE_FUNC();

	math::mat4 transform = math::mat4(1.0f);

	transform = math::translate(transform, _position);
	transform = math::rotate(transform, math::radians(_rotation.x), math::vec3(1.0f, 0.0f, 0.0f));
	transform = math::rotate(transform, math::radians(_rotation.y), math::vec3(0.0f, 1.0f, 0.0f));
	transform = math::rotate(transform, math::radians(_rotation.z), math::vec3(0.0f, 0.0f, 1.0f));
	
	_view_matrix = math::inverse(transform);
	_view_projection_matrix = _projection_matrix * _view_matrix;
}

OrthographicCameraController::OrthographicCameraController(const OrthographicCameraControllerConfig &config)
	: _camera(-config.aspect_ratio * config.zoom_level, config.aspect_ratio * config.zoom_level, -config.zoom_level, config.zoom_level),
	  _config(config)
{
	KN_PROFILE_FUNC();

	_camera.SetPosition(_config.position);
	_camera.SetRotation(_config.rotation);
}

void	OrthographicCameraController::OnUpdate(float delta)
{
	KN_PROFILE_FUNC();

	if (Input::IsKeyPressed(Key::W))
	{
		_config.position.x += -sin(math::radians(_config.rotation.z)) * _config.translation_speed * delta;
		_config.position.y += cos(math::radians(_config.rotation.z)) * _config.translation_speed * delta;
	}
	if (Input::IsKeyPressed(Key::S))
	{
		_config.position.x -= -sin(math::radians(_config.rotation.z)) * _config.translation_speed * delta;
		_config.position.y -= cos(math::radians(_config.rotation.z)) * _config.translation_speed * delta;
	}
	if (Input::IsKeyPressed(Key::A))
	{
		_config.position.x -= cos(math::radians(_config.rotation.z)) * _config.translation_speed * delta;
		_config.position.y -= sin(math::radians(_config.rotation.z)) * _config.translation_speed * delta;
	}
	if (Input::IsKeyPressed(Key::D))
	{
		_config.position.x += cos(math::radians(_config.rotation.z)) * _config.translation_speed * delta;
		_config.position.y += sin(math::radians(_config.rotation.z)) * _config.translation_speed * delta;
	}

	if (_config.enable_rotation)
	{
		if (Input::IsKeyPressed(Key::Q))
			_config.rotation.z += _config.rotation_speed * delta;
		if (Input::IsKeyPressed(Key::E))
			_config.rotation.z -= _config.rotation_speed * delta;

		if (_config.rotation.z > 180.0f)
			_config.rotation.z -= 360.0f;
		else if (_config.rotation.z <= -180.0f)
			_config.rotation.z += 360.0f;
		
		_camera.SetRotation(_config.rotation);
	}
	_camera.SetPosition(_config.position);

	_config.translation_speed = _config.zoom_level;
}

void	OrthographicCameraController::OnEvent(Event& event)
{
	KN_PROFILE_FUNC();

	EventDispatcher	dispatcher(event);
	dispatcher.Dispatch<MouseWheelEvent>(KN_BIND_EVENT_FN(OnMouseWheel));
	dispatcher.Dispatch<WindowResizeEvent>(KN_BIND_EVENT_FN(OnWindowResize));
}

void	OrthographicCameraController::OnResize(float width, float height)
{
	KN_PROFILE_FUNC();

	_config.aspect_ratio = width / height;
	_camera.SetProjection(-_config.aspect_ratio * _config.zoom_level, _config.aspect_ratio * _config.zoom_level, -_config.zoom_level, _config.zoom_level);
}

bool	OrthographicCameraController::OnMouseWheel(MouseWheelEvent& event)
{
	KN_PROFILE_FUNC();

	if (_config.enable_zoom)
	{
		_config.zoom_level -= event.GetYOffset() * 0.1f;
		_config.zoom_level = std::max(_config.zoom_level, 0.25f);
		_camera.SetProjection(-_config.aspect_ratio * _config.zoom_level, _config.aspect_ratio * _config.zoom_level, -_config.zoom_level, _config.zoom_level);
	}
	return false;
}

bool	OrthographicCameraController::OnWindowResize(WindowResizeEvent& event)
{
	KN_PROFILE_FUNC();

	OnResize(event.GetWidth(), event.GetHeight());
	return false;
}

} // Kinai
