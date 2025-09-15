#pragma once

#include "Kinai/Core/Core.hpp"
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

enum class IndexType
{
	None = 0,
	Uint16,
	Uint32,
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

struct PipelineConfig
{
	Ref<VertexArray> vao = nullptr;
	Ref<Shader> shader = nullptr;
	PrimitiveType primitive_type = PrimitiveType::Triangles;
	IndexType index_type = IndexType::None;
	CullMode cull_mode = CullMode::Back;
	FaceWinding face_winding = FaceWinding::CCW;
	std::string label = "Rendering pipeline";
};

class Pipeline
{
public:
	virtual ~Pipeline() = default;

	void SetVertexArray(const Ref<VertexArray>& vao) { _vao = vao; }
	void SetShader(const Ref<Shader>& shader) { _shader = shader; }
	void SetPrimitiveType(const PrimitiveType& primitive_type) { _primitive_type = primitive_type; }
	void SetIndexType(const IndexType& index_type) { _index_type = index_type; }
	void SetCullMode(const CullMode& cull_mode) { _cull_mode = cull_mode; }
	void SetFaceWinding(const FaceWinding& face_winding) { _face_winding = face_winding; }
	void SetLabel(const std::string& label) { _label = label; }

	Ref<VertexArray> GetVertexArray() const { return _vao; }
	Ref<Shader> GetShader() const { return _shader; }
	PrimitiveType GetPrimitiveType() const { return _primitive_type; }
	IndexType GetIndexType() const { return _index_type; }
	CullMode GetCullMode() const { return _cull_mode; }
	FaceWinding GetFaceWinding() const { return _face_winding; }
	const std::string& GetLabel() const { return _label; }

	static Ref<Pipeline> Create(const PipelineConfig& config);

protected:
	Ref<VertexArray> _vao;
	Ref<Shader> _shader;
	PrimitiveType _primitive_type;
	IndexType _index_type;
	CullMode _cull_mode;
	FaceWinding _face_winding;
	std::string _label;
};

} // Kinai
