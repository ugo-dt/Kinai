#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Buffer/BufferLayout.hpp"
#include "Kinai/Renderer/Shader.hpp"
#include "Kinai/Renderer/VertexArray.hpp"

namespace Kinai
{

enum class PrimitiveType
{
	Points,
	Lines,
	LineStrip,
	Triangles,
	TriangleStrip,
};

enum class CullMode
{
	None,
	Front,
	Back,
	FrontAndBack,
};

enum class FaceWinding
{
	CCW,
	CW,
};

enum class DepthState
{
	None = 0,
	Less,
	LessEqual,
	Equal,
	Greater,
	GreaterEqual,
	Always,
};

enum class BlendFactor
{
	Zero,
	One,
	SrcColor,
	OneMinusSrcColor,
	DstColor,
	OneMinusDstColor,
	SrcAlpha,
	OneMinusSrcAlpha,
	DstAlpha,
	OneMinusDstAlpha,
	SrcAlphaSaturated,
};

enum class BlendOp
{
	Add,
	Subtract,
	ReverseSubtract,
	Min,
	Max,
};

struct BlendState
{
	bool enabled;
    BlendFactor src_factor_rgb = BlendFactor::One;
    BlendFactor dst_factor_rgb = BlendFactor::Zero;
    BlendOp op_rgb = BlendOp::Add;
    BlendFactor src_factor_alpha = BlendFactor::One;
    BlendFactor dst_factor_alpha = BlendFactor::Zero;
    BlendOp op_alpha = BlendOp::Add;
};

struct PipelineConfig
{
	Ref<VertexArray> vao;
	Ref<Shader> shader;
	BufferLayout layout;
	PrimitiveType primitive_type = PrimitiveType::Triangles;
	CullMode cull_mode = CullMode::Back;
	FaceWinding face_winding = FaceWinding::CCW;
	DepthState depth_state = DepthState::Less;
	BlendState blend_state = BlendState();
	std::string label = "Rendering pipeline";
};

class Pipeline
{
public:
	virtual ~Pipeline() = default;

	void SetVertexArray(const Ref<VertexArray>& vao) { _vao = vao; }
	void SetShader(const Ref<Shader>& shader) { _shader = shader; }
	void SetLayout(const BufferLayout& layout) { _layout = layout; }
	void SetPrimitiveType(const PrimitiveType& primitive_type) { _primitive_type = primitive_type; }
	void SetCullMode(const CullMode& cull_mode) { _cull_mode = cull_mode; }
	void SetFaceWinding(const FaceWinding& face_winding) { _face_winding = face_winding; }
	void SetLabel(const std::string& label) { _label = label; }

	Ref<VertexArray> GetVertexArray() const { return _vao; }
	Ref<Shader> GetShader() const { return _shader; }
	BufferLayout GetLayout() const { return _layout; }
	PrimitiveType GetPrimitiveType() const { return _primitive_type; }
	CullMode GetCullMode() const { return _cull_mode; }
	FaceWinding GetFaceWinding() const { return _face_winding; }
	DepthState GetDepthState() const { return _depth_state; }
	BlendState GetBlendState() const { return _blend_state; }
	const std::string& GetLabel() const { return _label; }

	static Ref<Pipeline> Create(const PipelineConfig& config);

protected:
	Ref<VertexArray> _vao;
	Ref<Shader> _shader;
	BufferLayout _layout;
	PrimitiveType _primitive_type;
	CullMode _cull_mode;
	FaceWinding _face_winding;
	DepthState _depth_state;
	BlendState _blend_state;
	std::string _label;
};

} // Kinai
