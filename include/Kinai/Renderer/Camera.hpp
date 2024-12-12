#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Events/ApplicationEvent.hpp"
#include "Kinai/Events/MouseEvent.hpp"
#include "Kinai/Events/KeyEvent.hpp"

namespace Kinai
{

class Camera
{
protected:
	Camera() = default;
	Camera(const glm::mat4& projection)
		: _projection(projection) {}

	virtual ~Camera() = default;

	const glm::mat4&	GetProjectionMatrix() { return _projection; }

protected:
	glm::mat4	_projection = glm::mat4(1.0f);
};

} // Kinai
