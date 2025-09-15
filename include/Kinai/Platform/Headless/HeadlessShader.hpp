#pragma once

#include "Kinai/Core/Parser.hpp"
#include "Kinai/Renderer/Shader.hpp"

namespace Kinai
{

class HeadlessShader : public Shader
{
public:
	HeadlessShader() = delete;

	HeadlessShader(const std::string& filepath, const std::string& program_name);
	HeadlessShader(const ShaderConfig& config);
	~HeadlessShader();

	void	Bind() const override;
	void	Unbind() const override;

	void	SetInt(const std::string& name, int value) override;
	void	SetIntArray(const std::string& name, int* values, uint32_t count) override;
	void	SetFloat(const std::string& name, float value) override;
	void	SetFloat2(const std::string& name, const glm::vec2& value) override;
	void	SetFloat3(const std::string& name, const glm::vec3& value) override;
	void	SetFloat4(const std::string& name, const glm::vec4& value) override;
	void	SetMat4(const std::string& name, const glm::mat4& value) override;

	const std::string&	GetName() const override { return _name; }

	void	UploadUniformInt(const std::string& name, int value);
	void	UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

	void	UploadUniformFloat(const std::string& name, float value);
	void	UploadUniformFloat2(const std::string& name, const glm::vec2& value);
	void	UploadUniformFloat3(const std::string& name, const glm::vec3& value);
	void	UploadUniformFloat4(const std::string& name, const glm::vec4& value);

	void	UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
	void	UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

private:
	void	CreateProgram(const char *vertex, const char *fragment);

private:
	std::string	_name;
	std::string	_filepath;
};

} // Kinai
