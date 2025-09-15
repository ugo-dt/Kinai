#pragma once

#include "Kinai/Core/Core.hpp"

namespace Kinai
{

class VertexArray
{
public:
	virtual ~VertexArray() = default;

	virtual void	Bind() const = 0;
	virtual void	Unbind() const = 0;

	static Ref<VertexArray>	Create();
};

} // Kinai
