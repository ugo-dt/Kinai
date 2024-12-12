#pragma once

#include "Kinai/Core/Core.hpp"
#include "BufferElement.hpp"

namespace Kinai
{

class BufferLayout
{
public:
	BufferLayout() {}
	BufferLayout(std::initializer_list<BufferElement> elements)
		: _elements(elements)
	{
		CalculateOffsetsAndStride();
	}

	uint32_t							GetStride()   const { return stride; }
	const std::vector<BufferElement>&	GetElements() const { return _elements; }

	std::vector<BufferElement>::iterator		begin()       { return _elements.begin(); }
	std::vector<BufferElement>::iterator		end()         { return _elements.end(); }
	std::vector<BufferElement>::const_iterator	begin() const { return _elements.begin(); }
	std::vector<BufferElement>::const_iterator	end()   const { return _elements.end(); }
private:
	void CalculateOffsetsAndStride()
	{
		size_t offset = 0;
		stride = 0;
		for (auto& element : _elements)
		{
			element.offset = offset;
			offset += element.size;
			stride += element.size;
		}
	}
private:
	std::vector<BufferElement> _elements;
	uint32_t stride = 0;
};

} // Kinai
