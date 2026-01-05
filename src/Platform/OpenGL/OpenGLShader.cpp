#include "Kinai/Platform/OpenGL/OpenGLShader.hpp"

namespace Kinai
{

OpenGLShader::OpenGLShader(const std::string& name, const std::string& vs, const std::string& fs)
	: _name(name)
{
	CreateProgram(vs.c_str(), fs.c_str());
	Log::Trace("Created shader program '{}'", _name);
}

OpenGLShader::OpenGLShader(const ShaderConfig& config)
	: _name(config.name)
{
	CreateProgram(config.vs_source, config.fs_source);

	_uniforms.reserve(ShaderConstants::MaxUniformSlots);
	size_t offset = 0;
	for (int i = 0; i < ShaderConstants::MaxUniformSlots; i++)
	{
		OpenGLShaderUniform u;
		u.glsl_name = config.uniforms[i].glsl_name,
		u.stage = config.uniforms[i].stage,
		u.type = config.uniforms[i].type,
		u.array_count = config.uniforms[i].array_count,
		u.offset = offset;
		_uniforms.push_back(u);
		offset += ShaderDataTypeSize(config.uniforms[i].type);
	}

	Log::Trace("Created shader program '{}'", _name);
}

OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(_renderer_id);
	_KN_GL_CHECK_ERROR();
	Log::Trace("Deleted shader program '{}'", _name);
}

void	OpenGLShader::ApplyUniforms(const void* params, size_t size)
{
#ifndef KINAI_DEBUG
	KN_NOTUSED(size);
#endif
	Bind();
	for (const auto& uniform : _uniforms)
	{
		if (uniform.glsl_name == nullptr || uniform.type == ShaderDataType::None)
			continue ;

		KN_ASSERT(uniform.offset < size,
			"Invalid offset {} for uniform {}. Got 'params' of size {}", uniform.offset, uniform.glsl_name, size);

		const void* ptr = (const uint8_t*)params + uniform.offset;
		switch (uniform.type)
		{
			case ShaderDataType::Float:
				SetFloat(uniform.glsl_name, *static_cast<const float *>(ptr));
				break;
			case ShaderDataType::Float2:
				SetFloat2(uniform.glsl_name, *static_cast<const math::vec2 *>(ptr));
				break;
			case ShaderDataType::Float3:
				SetFloat3(uniform.glsl_name, *static_cast<const math::vec3 *>(ptr));
				break;
			case ShaderDataType::Float4:
				SetFloat4(uniform.glsl_name, *static_cast<const math::vec4 *>(ptr));
				break;
			case ShaderDataType::Mat4:
				SetMat4(uniform.glsl_name, *static_cast<const math::mat4 *>(ptr));
				break;
			case ShaderDataType::Int:
				SetInt(uniform.glsl_name, *static_cast<const int *>(ptr));
				break;
			case ShaderDataType::Int2:
				SetIntArray(uniform.glsl_name, static_cast<const int *>(ptr), 2);
				break;
			case ShaderDataType::Int3:
				SetIntArray(uniform.glsl_name, static_cast<const int *>(ptr), 3);
				break;
			case ShaderDataType::Int4:
				SetIntArray(uniform.glsl_name, static_cast<const int *>(ptr), 4);
				break;
			default:
				Log::Critical("OpenGLShader::ApplyUniforms(): unknown uniform type");
				break;
		}
	}
}

static KN_INLINE std::string	get_shader_info_log(GLuint shader, void (*f)(GLuint, GLsizei, GLsizei *, GLchar *))
{
	char info[1024];
	f(shader, 1024, nullptr, info);
	std::string s(info);
	if (!s.empty())
		s.pop_back();
	return s;
}

void	OpenGLShader::CreateProgram(const char *vertex, const char *fragment)
{
	GLint	status;

	int vertex_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_id, 1, &vertex, NULL);
	glCompileShader(vertex_id);
	glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &status);
	Log::Validate(status == GL_TRUE, "{}: vertex shader: {}", _name, get_shader_info_log(vertex_id, glGetShaderInfoLog));
	_KN_GL_CHECK_ERROR();

	int fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_id, 1, &fragment, NULL);
	glCompileShader(fragment_id);
	glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &status);
	Log::Validate(status == GL_TRUE, "{}: fragment shader: {}", _name, get_shader_info_log(fragment_id, glGetShaderInfoLog));
	_KN_GL_CHECK_ERROR();

	int id = glCreateProgram();
	glAttachShader(id, vertex_id);
	glAttachShader(id, fragment_id);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &status);
	Log::Validate(status == GL_TRUE, "glLinkProgram(): {}", get_shader_info_log(id, glGetProgramInfoLog));
	_KN_GL_CHECK_ERROR();

	glDeleteShader(vertex_id);
	glDeleteShader(fragment_id);

	_renderer_id = id;
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::Bind() const
{
	KN_PROFILE_FUNC();

	glUseProgram(_renderer_id);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::Unbind() const
{
	KN_PROFILE_FUNC();

	glUseProgram(0);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::SetInt(const std::string& name, int value)
{
	KN_PROFILE_FUNC();

	UploadUniformInt(name, value);
}

void	OpenGLShader::SetIntArray(const std::string& name, const int* values, uint32_t count)
{
	UploadUniformIntArray(name, values, count);
}

void	OpenGLShader::SetFloat(const std::string& name, float value)
{
	KN_PROFILE_FUNC();

	UploadUniformFloat(name, value);
}

void	OpenGLShader::SetFloat2(const std::string& name, const math::vec2& value)
{
	KN_PROFILE_FUNC();

	UploadUniformFloat2(name, value);
}

void	OpenGLShader::SetFloat3(const std::string& name, const math::vec3& value)
{
	KN_PROFILE_FUNC();

	UploadUniformFloat3(name, value);
}

void	OpenGLShader::SetFloat4(const std::string& name, const math::vec4& value)
{
	KN_PROFILE_FUNC();

	UploadUniformFloat4(name, value);
}

void	OpenGLShader::SetMat4(const std::string& name, const math::mat4& value)
{
	KN_PROFILE_FUNC();

	UploadUniformMat4(name, value);
}

void	OpenGLShader::UploadUniformInt(const std::string& name, int value)
{
	GLint location = glGetUniformLocation(_renderer_id, name.c_str());
	glUniform1i(location, value);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::UploadUniformIntArray(const std::string& name, const int* values, uint32_t count)
{
	GLint location = glGetUniformLocation(_renderer_id, name.c_str());
	glUniform1iv(location, count, values);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::UploadUniformFloat(const std::string& name, float value)
{
	GLint location = glGetUniformLocation(_renderer_id, name.c_str());
	glUniform1f(location, value);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::UploadUniformFloatArray(const std::string& name, const float* values, uint32_t count)
{
	GLint location = glGetUniformLocation(_renderer_id, name.c_str());
	glUniform1fv(location, count, values);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::UploadUniformFloat2(const std::string& name, const math::vec2& value)
{
	GLint location = glGetUniformLocation(_renderer_id, name.c_str());
	glUniform2f(location, value.x, value.y);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::UploadUniformFloat2Array(const std::string& name, const float* values, uint32_t count)
{
	GLint location = glGetUniformLocation(_renderer_id, name.c_str());
	glUniform2fv(location, count, values);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::UploadUniformFloat3(const std::string& name, const math::vec3& value)
{
	GLint location = glGetUniformLocation(_renderer_id, name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::UploadUniformFloat3Array(const std::string& name, const float* values, uint32_t count)
{
	GLint location = glGetUniformLocation(_renderer_id, name.c_str());
	glUniform3fv(location, count, values);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::UploadUniformFloat4(const std::string& name, const math::vec4& value)
{
	GLint location = glGetUniformLocation(_renderer_id, name.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::UploadUniformFloat4Array(const std::string& name, const float* values, uint32_t count)
{
	GLint location = glGetUniformLocation(_renderer_id, name.c_str());
	glUniform4fv(location, count, values);
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::UploadUniformMat3(const std::string& name, const math::mat3& matrix)
{
	GLint location = glGetUniformLocation(_renderer_id, name.c_str());
	glUniformMatrix3fv(location, 1, GL_FALSE, math::value_ptr(matrix));
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::UploadUniformMat4(const std::string& name, const math::mat4& matrix)
{
	GLint location = glGetUniformLocation(_renderer_id, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, math::value_ptr(matrix));
	_KN_GL_CHECK_ERROR();
}

} // Kinai
