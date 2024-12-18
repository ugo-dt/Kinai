#include "Kinai/Renderer/OrthographicCamera.hpp"
#include "Kinai/Core/Input.hpp"

namespace Kinai
{

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	: _position(0.0f, 0.0f, 0.0f),
	  _rotation(0.0f),
	  _projection_matrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
	  _view_matrix(1.0f),
	  _view_projection_matrix(_projection_matrix * _view_matrix)
{
	KN_PRINT_FUNC();
}

void	OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
{
	KN_PRINT_FUNC();

	_projection_matrix = glm::ortho(left, right, bottom, top);
	_view_projection_matrix = _projection_matrix * _view_matrix;
}

void	OrthographicCamera::UpdateView()
{
	KN_PRINT_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	
	_view_matrix = glm::inverse(transform);
	_view_projection_matrix = _projection_matrix * _view_matrix;
}

OrthographicCameraController::OrthographicCameraController(const OrthographicCameraControllerConfig &config)
	: _camera(-config.aspect_ratio * config.zoom_level, config.aspect_ratio * config.zoom_level, -config.zoom_level, config.zoom_level),
	  _config(config)
{
	KN_PRINT_FUNC();

	_camera.SetPosition(_config.position);
	_camera.SetRotation(_config.rotation);
}

void	OrthographicCameraController::OnUpdate(float delta)
{
	KN_PRINT_FUNC();

	if (Input::IsKeyPressed(Key::W))
	{
		_config.position.x += -sin(glm::radians(_config.rotation)) * _config.translation_speed * delta;
		_config.position.y += cos(glm::radians(_config.rotation)) * _config.translation_speed * delta;
	}
	if (Input::IsKeyPressed(Key::S))
	{
		_config.position.x -= -sin(glm::radians(_config.rotation)) * _config.translation_speed * delta;
		_config.position.y -= cos(glm::radians(_config.rotation)) * _config.translation_speed * delta;
	}
	if (Input::IsKeyPressed(Key::A))
	{
		_config.position.x -= cos(glm::radians(_config.rotation)) * _config.translation_speed * delta;
		_config.position.y -= sin(glm::radians(_config.rotation)) * _config.translation_speed * delta;
	}
	if (Input::IsKeyPressed(Key::D))
	{
		_config.position.x += cos(glm::radians(_config.rotation)) * _config.translation_speed * delta;
		_config.position.y += sin(glm::radians(_config.rotation)) * _config.translation_speed * delta;
	}

	if (_config.enable_rotation)
	{
		if (Input::IsKeyPressed(Key::Q))
			_config.rotation += _config.rotation_speed * delta;
		if (Input::IsKeyPressed(Key::E))
			_config.rotation -= _config.rotation_speed * delta;
		
		if (_config.rotation > 180.0f)
			_config.rotation -= 360.0f;
		else if (_config.rotation <= -180.0f)
			_config.rotation += 360.0f;
		
		_camera.SetRotation(_config.rotation);
	}
	_camera.SetPosition(_config.position);

	_config.translation_speed = _config.zoom_level;
}

void	OrthographicCameraController::OnEvent(Event& event)
{
	KN_PRINT_FUNC();

	EventDispatcher	dispatcher(event);
	dispatcher.Dispatch<MouseWheelEvent>(KN_BIND_EVENT_FN(OrthographicCameraController::OnMouseWheel));
	dispatcher.Dispatch<WindowResizeEvent>(KN_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
}

void	OrthographicCameraController::OnResize(float width, float height)
{
	KN_PRINT_FUNC();

	_config.aspect_ratio = width / height;
	_camera.SetProjection(-_config.aspect_ratio * _config.zoom_level, _config.aspect_ratio * _config.zoom_level, -_config.zoom_level, _config.zoom_level);
}

bool	OrthographicCameraController::OnMouseWheel(MouseWheelEvent& event)
{
	KN_PRINT_FUNC();

	if (_config.enable_zoom)
	{
		_config.zoom_level -= event.GetYOffset() * 0.25f;
		_config.zoom_level = std::max(_config.zoom_level, 0.25f);
		_camera.SetProjection(-_config.aspect_ratio * _config.zoom_level, _config.aspect_ratio * _config.zoom_level, -_config.zoom_level, _config.zoom_level);
	}
	return false;
}

bool	OrthographicCameraController::OnWindowResize(WindowResizeEvent& event)
{
	KN_PRINT_FUNC();

	OnResize(event.GetWidth(), event.GetHeight());
	return false;
}

} // Kinai
