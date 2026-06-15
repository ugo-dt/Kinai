#pragma once

#include "Kinai/Core/Parser.hpp"
#include "Kinai/Renderer/Shader.hpp"

namespace Kinai
{

class OpenGLShader : public Shader
{
public:
	OpenGLShader() = delete;

	OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	OpenGLShader(const ShaderConfig& config);
	~OpenGLShader();

	void Bind() const override;
	void Unbind() const override;

	void SetInt(const std::string& name, int value) override;
	void SetIntArray(const std::string& name, const int* values, uint32_t count) override;
	void SetUInt(const std::string& name, unsigned int value) override;
	void SetUIntArray(const std::string& name, const unsigned int* values, uint32_t count) override;
	void SetBool(const std::string& name, bool value) override;
	void SetBoolArray(const std::string& name, const bool* values, uint32_t count) override;
	void SetUByte(const std::string& name, unsigned char value) override;
	void SetUByteArray(const std::string& name, const unsigned char* values, uint32_t count) override;
	void SetUShort(const std::string& name, unsigned short value) override;
	void SetUShortArray(const std::string& name, const unsigned short* values, uint32_t count) override;
	void SetFloat(const std::string& name, float value) override;
	void SetFloat2(const std::string& name, const glm::vec2& value) override;
	void SetFloat3(const std::string& name, const glm::vec3& value) override;
	void SetFloat4(const std::string& name, const glm::vec4& value) override;
	void SetMat4(const std::string& name, const glm::mat4& value) override;

	const std::string&	GetName() const override { return _name; }

	void ApplyUniforms(const void* params, size_t size) override;

	void UploadUniformInt(const std::string& name, int value);
	void UploadUniformIntArray(const std::string& name, const int* values, uint32_t count);
	void UploadUniformUInt(const std::string& name, unsigned int value);
	void UploadUniformUIntArray(const std::string& name, const unsigned int* values, uint32_t count);
	void UploadUniformBool(const std::string& name, bool value);
	void UploadUniformBoolArray(const std::string& name, const bool* values, uint32_t count);
	void UploadUniformUByte(const std::string& name, unsigned char value);
	void UploadUniformUByteArray(const std::string& name, const unsigned char* values, uint32_t count);
	void UploadUniformUShort(const std::string& name, unsigned short value);
	void UploadUniformUShortArray(const std::string& name, const unsigned short* values, uint32_t count);
	void UploadUniformFloat(const std::string& name, float value);
	void UploadUniformFloatArray(const std::string& name, const float* values, uint32_t count);
	void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
	void UploadUniformFloat2Array(const std::string& name, const float* values, uint32_t count);
	void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
	void UploadUniformFloat3Array(const std::string& name, const float* values, uint32_t count);
	void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
	void UploadUniformFloat4Array(const std::string& name, const float* values, uint32_t count);

	void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
	void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

public:
	static void	GenerateHeaderFromShader(const std::string& filepath, const std::string& program_name, const std::string& vs, const std::string fs);
	static void	GenerateHeaderFromShader(const std::string& filepath, const std::string& program_name);

private:
	void	CreateProgram(const char *vertex, const char *fragment);

private:
	std::string	_name;
	uint32_t	_renderer_id;
	std::string	_filepath;

	struct OpenGLShaderUniform : public ShaderUniform
	{
		size_t offset;
	};
	std::vector<OpenGLShaderUniform> _uniforms;
};

} // Kinai
