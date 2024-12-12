#include "Kinai/Platform/Headless/HeadlessShader.hpp"

namespace Kinai
{

HeadlessShader::HeadlessShader(const std::string& filepath, const std::string& program_name)
	: _name(program_name)
{
	EG_PRINT_FUNC();
	
	(void)filepath;
}

HeadlessShader::HeadlessShader(const std::string& name, const std::string& vs, const std::string& fs)
	: _name(name)
{
	EG_PRINT_FUNC();

	std::cout << "--- Vertex Shader ---\n" << vs << "\n--- Fragment Shader ---\n" << fs << std::endl;
}

HeadlessShader::~HeadlessShader()
{
	EG_PRINT_FUNC();
}

void	HeadlessShader::CreateProgram(const char *vertex, const char *fragment)
{
	EG_PRINT_FUNC();

	(void)vertex;
	(void)fragment;
}

void	HeadlessShader::Bind() const
{
	EG_PRINT_FUNC();
}

void	HeadlessShader::Unbind() const
{
	EG_PRINT_FUNC();
}

void	HeadlessShader::SetInt(const std::string& name, int value)
{
	EG_PRINT_FUNC();

	(void)name;
	(void)value;
}

void	HeadlessShader::SetIntArray(const std::string& name, int* values, uint32_t count)
{
	EG_PRINT_FUNC();
	
	(void)name;
	(void)values;
	(void)count;
}

void	HeadlessShader::SetFloat(const std::string& name, float value)
{
	EG_PRINT_FUNC();
	
	(void)name;
	(void)value;
}

void	HeadlessShader::SetFloat2(const std::string& name, const glm::vec2& value)
{
	EG_PRINT_FUNC();
	
	(void)name;
	(void)value;
}

void	HeadlessShader::SetFloat3(const std::string& name, const glm::vec3& value)
{
	EG_PRINT_FUNC();
	
	(void)name;
	(void)value;
}

void	HeadlessShader::SetFloat4(const std::string& name, const glm::vec4& value)
{
	EG_PRINT_FUNC();
	
	(void)name;
	(void)value;
}

void	HeadlessShader::SetMat4(const std::string& name, const glm::mat4& value)
{
	EG_PRINT_FUNC();
	
	(void)name;
	(void)value;
}

void	HeadlessShader::UploadUniformInt(const std::string& name, int value)
{
	EG_PRINT_FUNC();
	
	(void)name;
	(void)value;
}

void	HeadlessShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
{
	EG_PRINT_FUNC();
	
	(void)name;
	(void)values;
	(void)count;
}

void	HeadlessShader::UploadUniformFloat(const std::string& name, float value)
{
	EG_PRINT_FUNC();
	
	(void)name;
	(void)value;
}

void	HeadlessShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
{
	EG_PRINT_FUNC();
	
	(void)name;
	(void)value;
}

void	HeadlessShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
{
	EG_PRINT_FUNC();
	
	(void)name;
	(void)value;
}

void	HeadlessShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
{
	EG_PRINT_FUNC();
	
	(void)name;
	(void)value;
}

void	HeadlessShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
{
	EG_PRINT_FUNC();
	
	(void)name;
	(void)matrix;
}

void	HeadlessShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	EG_PRINT_FUNC();
	
	(void)name;
	(void)matrix;
}

} // Kinai
