#include "Kinai/Platform/Headless/HeadlessShader.hpp"

namespace Kinai
{

HeadlessShader::HeadlessShader(const std::string& filepath, const std::string& program_name)
	: _name(program_name)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(filepath);
}

HeadlessShader::HeadlessShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	: _name(name)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(vertexSrc);
	KN_NOTUSED(fragmentSrc);
}

HeadlessShader::HeadlessShader(const ShaderConfig& config)
	: _name(config.name)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(config);
}

HeadlessShader::~HeadlessShader()
{
	KN_PROFILE_FUNC();
}

void	HeadlessShader::ApplyUniforms(const void* params, size_t size)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(params);
	KN_NOTUSED(size);
}

void	HeadlessShader::CreateProgram(const char *vertex, const char *fragment)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(vertex);
	KN_NOTUSED(fragment);
}

void	HeadlessShader::Bind() const
{
	KN_PROFILE_FUNC();
}

void	HeadlessShader::Unbind() const
{
	KN_PROFILE_FUNC();
}

void	HeadlessShader::SetInt(const std::string& name, int value)
{
	KN_PROFILE_FUNC();

	KN_NOTUSED(name);
	KN_NOTUSED(value);
}

void	HeadlessShader::SetIntArray(const std::string& name, const int* values, uint32_t count)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(name);
	KN_NOTUSED(values);
	KN_NOTUSED(count);
}

void	HeadlessShader::SetFloat(const std::string& name, float value)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(name);
	KN_NOTUSED(value);
}

void	HeadlessShader::SetFloat2(const std::string& name, const math::vec2& value)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(name);
	KN_NOTUSED(value);
}

void	HeadlessShader::SetFloat3(const std::string& name, const math::vec3& value)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(name);
	KN_NOTUSED(value);
}

void	HeadlessShader::SetFloat4(const std::string& name, const math::vec4& value)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(name);
	KN_NOTUSED(value);
}

void	HeadlessShader::SetMat4(const std::string& name, const math::mat4& value)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(name);
	KN_NOTUSED(value);
}

void	HeadlessShader::UploadUniformInt(const std::string& name, int value)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(name);
	KN_NOTUSED(value);
}

void	HeadlessShader::UploadUniformIntArray(const std::string& name, const int* values, uint32_t count)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(name);
	KN_NOTUSED(values);
	KN_NOTUSED(count);
}

void	HeadlessShader::UploadUniformFloat(const std::string& name, float value)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(name);
	KN_NOTUSED(value);
}

void	HeadlessShader::UploadUniformFloat2(const std::string& name, const math::vec2& value)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(name);
	KN_NOTUSED(value);
}

void	HeadlessShader::UploadUniformFloat3(const std::string& name, const math::vec3& value)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(name);
	KN_NOTUSED(value);
}

void	HeadlessShader::UploadUniformFloat4(const std::string& name, const math::vec4& value)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(name);
	KN_NOTUSED(value);
}

void	HeadlessShader::UploadUniformMat3(const std::string& name, const math::mat3& matrix)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(name);
	KN_NOTUSED(matrix);
}

void	HeadlessShader::UploadUniformMat4(const std::string& name, const math::mat4& matrix)
{
	KN_PROFILE_FUNC();
	
	KN_NOTUSED(name);
	KN_NOTUSED(matrix);
}

} // Kinai
