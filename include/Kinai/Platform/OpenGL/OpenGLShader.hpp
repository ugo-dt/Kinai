#pragma once

#include "Kinai/Core/Parser.hpp"
#include "Kinai/Renderer/Shader.hpp"

namespace Kinai
{

enum ShaderParserTokenType : char
{
	SHADER_TOKEN_AT			= '@',
	SHADER_TOKEN_NEWLINE	= '\n',
	SHADER_TOKEN_QUOTE		= '"',
	SHADER_TOKEN_TEXT		= '\0',
};

template <> struct is_token_type<ShaderParserTokenType>	: std::true_type {};

struct ShaderParserToken : TokenBase<ShaderParserTokenType>
{
	ShaderParserToken(ShaderParserTokenType t, std::string w, uint32_t r, uint32_t c)
		: TokenBase<ShaderParserTokenType>(t, w, r, c) {}
};

class OpenGLShaderParser : public Parser<ShaderParserToken>
{
public:
	OpenGLShaderParser(const std::string& filepath): Parser(filepath) {}

	void	MakeShader(const std::string& program_name, std::string &vertex_out, std::string &fragment_out);

private:
	static inline constexpr const char *separators = "@\"";

	enum Context { CONTEXT_NONE, CONTEXT_VERTEX_SHADER, CONTEXT_FRAGMENT_SHADER, CONTEXT_PROGRAM, CONTEXT_INCLUDE, CONTEXT_EXPORT };

	struct ShaderContents
	{
		std::string	name;
		std::string	contents;
		Context		context;
		iterator	token;
	};

	struct ExportContents
	{
		std::string	name;
		std::string	contents;
		bool		was_imported;
	};

	struct Program
	{
		std::string	name;
		std::string	vs;
		std::string	fs;
		iterator	token;
		iterator	context_token;
		iterator 	vs_token;
		iterator 	fs_token;
	};

private:
	std::vector<ShaderContents>	_shaders;
	std::vector<Program>		_programs;
	iterator 					_context_token;
	std::vector<std::string>	_included_files;
	std::vector<ExportContents>	_exports;

private:
	bool				_is_separator(const char& c);
	void				_throw_parser_with_context(const_iterator& error_it, const std::string &error, const std::string &note, std::string optional_declaration = std::string());
	void				_print_warning_with_note(const_iterator& warning_it, const std::string &warning, const_iterator& note_it, const std::string &note, std::string optional_declaration = std::string());
	void				_print_warning_with_context_note(const_iterator& warning_it, const std::string &warning, const std::string &note, std::string optional_declaration = std::string());
	void 				_import(size_t &pos, std::string &contents);
	void				_parse_shader_context(size_t &pos, const_iterator &end, Context &context);
	void				_parse_program_context(size_t &pos, const_iterator &end);
	void 				_include(size_t &pos);
	void 				_export(size_t &pos, const_iterator &end);
	void 				_tokenize(const std::string& data);
	void				_parse_tokens(size_t first, size_t last, bool included);
	const std::string&	_get_vertex_source(Program &program);
	const std::string&	_get_fragment_source(Program &program);
};

class OpenGLShader : public Shader
{
public:
	OpenGLShader() = delete;

	OpenGLShader(const std::string& filepath, const std::string& program_name);
	OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	OpenGLShader(const ShaderConfig& config);
	~OpenGLShader();

	void Bind() const override;
	void Unbind() const override;

	void SetInt(const std::string& name, int value) override;
	void SetIntArray(const std::string& name, const int* values, uint32_t count) override;
	void SetFloat(const std::string& name, float value) override;
	void SetFloat2(const std::string& name, const math::vec2& value) override;
	void SetFloat3(const std::string& name, const math::vec3& value) override;
	void SetFloat4(const std::string& name, const math::vec4& value) override;
	void SetMat4(const std::string& name, const math::mat4& value) override;

	const std::string&	GetName() const override { return _name; }

	void ApplyUniforms(const void* params, size_t size) override;

	void UploadUniformInt(const std::string& name, int value);
	void UploadUniformIntArray(const std::string& name, const int* values, uint32_t count);

	void UploadUniformFloat(const std::string& name, float value);
	void UploadUniformFloatArray(const std::string& name, const float* values, uint32_t count);
	void UploadUniformFloat2(const std::string& name, const math::vec2& value);
	void UploadUniformFloat2Array(const std::string& name, const float* values, uint32_t count);
	void UploadUniformFloat3(const std::string& name, const math::vec3& value);
	void UploadUniformFloat3Array(const std::string& name, const float* values, uint32_t count);
	void UploadUniformFloat4(const std::string& name, const math::vec4& value);
	void UploadUniformFloat4Array(const std::string& name, const float* values, uint32_t count);

	void UploadUniformMat3(const std::string& name, const math::mat3& matrix);
	void UploadUniformMat4(const std::string& name, const math::mat4& matrix);

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
