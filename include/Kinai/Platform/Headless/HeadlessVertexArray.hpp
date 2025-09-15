#pragma once

#include "Kinai/Renderer/VertexArray.hpp"

namespace Kinai
{

class HeadlessVertexArray : public VertexArray
{
public:
	HeadlessVertexArray();
	~HeadlessVertexArray();

	void	Bind() const override;
	void	Unbind() const override;
};

} // Kinai
