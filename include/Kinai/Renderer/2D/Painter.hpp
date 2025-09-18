#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Texture.hpp"

namespace Kinai::Painter
{

enum Constants
{
	BatchOptimizerDepth = 8,
	UniformContentSlots = 8,
	TextureSlots = 4,
	MaxVertices = 65536,
	MaxCommands = 16384,
	MaxMoveVertices = 96,
	MaxStackDepth = 64,
};

enum BlendMode
{
	None = 0,
	Blend,
	BlendPremultiplied,
	Add,
	AddPremultiplied,
	Mod,
	Mul,
};

enum VertexAttributeLocation
{
	AttrCoord = 0,
	AttrColor = 1
};

enum UniformSlot
{
	Vertex = 0,
	Fragment = 1
};

struct Size
{
	int w, h;
};

struct Rect
{
	float x, y, w, h;
};

struct IRect
{
	int x, y, w, h;
};

struct TexturedRect
{
	Rect dst, src;
};

using Point = glm::vec2;

struct Line
{
	Point a, b;
};

struct Triangle
{
	Point a, b, c;
};

using Color = glm::vec4;
using ColorUB4 = glm::u8vec4;

struct Vertex
{
	Point position;
	Point texcoord;
	ColorUB4 color;
};

struct UniformData
{
	float floats[UniformContentSlots];
	uint8_t bytes[UniformContentSlots * sizeof(float)];
};

struct Uniform
{
	uint32_t vs_size;
	uint32_t fs_size;
	UniformData data;
};

struct TexturesUniform
{
	uint32_t count;
	Ref<Texture> images[TextureSlots];
};

void	Init();
void	Shutdown();

} // Kinai::Painter

