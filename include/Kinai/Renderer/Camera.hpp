#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Events/ApplicationEvent.hpp"
#include "Kinai/Events/MouseEvent.hpp"
#include "Kinai/Events/KeyEvent.hpp"

namespace Kinai
{

class Camera
{
public:
	Camera() = default;
	Camera(const math::mat4& projection_matrix)
		: _projection_matrix(projection_matrix) {}

	virtual ~Camera() = default;

	const math::mat4&	GetProjectionMatrix() const { return _projection_matrix; }

protected:
	math::mat4	_projection_matrix = math::mat4(1.0f);
};

} // Kinai
