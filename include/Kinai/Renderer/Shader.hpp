#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Buffer/BufferLayout.hpp"

namespace Kinai
{

enum ShaderConstants : int
{
	MaxVertexAttributes = 16,
	MaxUniformSlots = 8,
};

enum ShaderStage : int
{
	None = 0,
	Vertex,
	Fragment,
};

struct ShaderUniform
{
	const char* glsl_name;
	ShaderStage stage;
	ShaderDataType type;
	uint16_t array_count;
};

struct ShaderConfig
{
	const char* name;
	const char* vs_source;
	const char* fs_source;
	BufferLayout layout;
	ShaderUniform uniforms[ShaderConstants::MaxUniformSlots];
};

class Shader
{
public:
	virtual ~Shader() = default;

	virtual void	Bind() const = 0;
	virtual void	Unbind() const = 0;

	virtual void	SetInt(const std::string& name, int value) = 0;
	virtual void	SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
	virtual void	SetFloat(const std::string& name, float value) = 0;
	virtual void	SetFloat2(const std::string& name, const glm::vec2& value) = 0;
	virtual void	SetFloat3(const std::string& name, const glm::vec3& value) = 0;
	virtual void	SetFloat4(const std::string& name, const glm::vec4& value) = 0;
	virtual void	SetMat4(const std::string& name, const glm::mat4& value) = 0;

	virtual const std::string&	GetName() const = 0;
	virtual void SetLayout(const BufferLayout& layout) = 0; 
	virtual const BufferLayout& GetLayout() const = 0;
	
	virtual void ApplyUniforms(const void* params, size_t size) = 0;

	static Ref<Shader>	Create(const std::string& filepath, const std::string& program_name);
	static Ref<Shader>	Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	static Ref<Shader>	Create(const ShaderConfig& config);

protected:
	BufferLayout _layout;
};

class ShaderLibrary
{
public:
	void		Add(const std::string& name, const Ref<Shader>& shader);
	void		Add(const Ref<Shader>& shader);
	Ref<Shader>	Load(const std::string& filepath, const std::string& name);
	Ref<Shader>	Load(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);

	Ref<Shader>	Get(const std::string& name);

	bool		Exists(const std::string& name) const;

private:
	std::unordered_map<std::string, Ref<Shader>> _shaders;

};

} // Kinai
