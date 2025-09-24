#include "Kinai/Platform/OpenGL/OpenGLShader.hpp"

namespace Kinai
{

KN_INLINE bool	operator==(OpenGLShaderParser::const_iterator &it, const OpenGLShaderParser::token_type &t)
	{ return OpenGLShaderParser::iterator_equals(it, t); }
KN_INLINE bool	operator!=(OpenGLShaderParser::const_iterator &it, const OpenGLShaderParser::token_type &t)
	{ return !(it == t); }
KN_INLINE bool	operator==(OpenGLShaderParser::const_iterator &it, const std::string &s)
	{ return OpenGLShaderParser::iterator_equals(it, s); }
KN_INLINE bool	operator!=(OpenGLShaderParser::const_iterator &it, const std::string &s)
	{ return !(it == s); }

KN_INLINE bool	OpenGLShaderParser::_is_separator(const char& c)
	{ return strchr(separators, c); }

KN_INLINE void	OpenGLShaderParser::_throw_parser_with_context(
	const_iterator& error_it, const std::string &error,
	const std::string &note, std::string optional_declaration)
{
	KN_ASSERT((_context_token + 1) != _tokens.end(), "OpenGLShaderParser: unexpected end of file");
	_throw_parser_with_note(error_it, error, _context_token, note + " '" + WHITE("@", _context_token + 1, optional_declaration) + "'");
}

KN_INLINE void	OpenGLShaderParser::_print_warning_with_note(
	const_iterator& warning_it, const std::string &warning,
	const_iterator& note_it, const std::string &note,
	std::string optional_declaration)
{
	std::string _note;

	_note = note + " '" + WHITE("@", _context_token + 1, optional_declaration) + "'";
	std::cerr << _make_warning_string(warning_it, warning) << '\n';
	std::cerr << _make_note_string(note_it, _note) << '\n';
}

KN_INLINE void	OpenGLShaderParser::_print_warning_with_context_note(
	const_iterator& warning_it, const std::string &warning,
	const std::string &note, std::string optional_declaration)
{
	KN_ASSERT((_context_token + 1) != _tokens.end(), "OpenGLShaderParser: unexpected end of file");
	_print_warning_with_note(warning_it, warning, _context_token,
		note + " '" + WHITE("@", _context_token + 1, optional_declaration) + "'");
}

void	OpenGLShaderParser::_tokenize(const std::string &data)
{
	std::istringstream stream(data);

	std::string	line;
	uint32_t	row;
	size_t		i, j;
	bool		comment = false;

	row = 0;
	while (std::getline(stream, line))
	{
		row++;
		i = 0;
		while (i < line.length() && isspace(line[i]))
			i++;
		if (comment)
		{
			while (i < line.length())
			{
				if (i < line.length() - 1 && line[i] == '*' && line[i + 1] == '/')
				{
					comment = false;
					i += 2;
					break;
				}
				i++;
			}
		}
		while (i < line.length())
		{
			while (i < line.length() && isspace(line[i]))
				i++;
			/* Skip comments */
			if (line.length() >= 2 && line[0] == '/' && line[1] == '/')
				while (i < line.length())
					i++;
			if (line.length() >= 2 && line[0] == '/' && line[1] == '*')
			{
				comment = true;
				while (i < line.length())
				{
					if (i < line.length() - 1 && line[i] == '*' && line[i + 1] == '/')
					{
						comment = false;
						i += 2;
						break;
					}
					i++;
				}
				continue;
			}
			switch (line[i])
			{
			case SHADER_TOKEN_AT:
			case SHADER_TOKEN_QUOTE:
				_tokens.push_back(value_type(static_cast<ShaderParserTokenType>(line[i]), std::string(1, line[i]), row, i + 1));
				i++;
				break;
			default:
				j = i;
				while (i < line.length())
				{
					if (isspace(line[i]) || _is_separator(line[i]))
						break ;
					i++;
				}
				if (i - j > 0)
					_tokens.push_back(value_type(SHADER_TOKEN_TEXT, std::string(line, j, i - j), row, j + 1));
				break;
			}
		}
		_tokens.push_back(value_type(SHADER_TOKEN_NEWLINE, "\n", row, i + 1));
	}
}

void	OpenGLShaderParser::_import(size_t &current, std::string &contents)
{
	if (_make_iter(current) != SHADER_TOKEN_TEXT)
		_throw_parser_with_context(_make_iter(current), "expected import name", "as argument of");
	std::string	name = (*_make_iter(current)).text;
	current++;
	const auto c = std::find_if(_exports.begin(), _exports.end(), [name](const ExportContents& c){ return c.name == name; });
	if (c == _exports.end())
		_throw_parser(_make_iter(current) - 1, "no export named '" + WHITE(name) + "'");
	if ((*c).was_imported)
	{
		std::cerr << _make_warning_string(_make_iter(current), "duplicate import '" + WHITE(name) + "'") << '\n';
		return ;
	}
	(*c).was_imported = true;
	contents += (*c).contents;
}

void	OpenGLShaderParser::_parse_shader_context(size_t &current, const_iterator &end, Context &context)
{
	std::string name;
	std::string contents;
	bool use = true;

	if (_make_iter(current) != SHADER_TOKEN_TEXT)
		_throw_parser_with_context(_make_iter(current), "expected shader name", "as argument of");
	name = (*_make_iter(current)).text;
	current++;
	while (_make_iter(current) != end)// && _make_iterator(current) != SHADER_TOKEN_AT)
	{
		if (_make_iter(current) == SHADER_TOKEN_AT)
		{
			current++;

			if (_make_iter(current) == "end")
				break;
			else if (_make_iter(current) == "import")
			{
				_import(++current, contents);
				continue;
			}
			_throw_parser_with_context(_make_iter(current) - 1, "expected '" + WHITE("@end") + "' at end of shader", "to match this");
		}

		bool newline = (_make_iter(current) == SHADER_TOKEN_NEWLINE);
		contents += (*_make_iter(current)).text;
		current++;
		if (_make_iter(current) != end && _make_iter(current) != SHADER_TOKEN_NEWLINE && !newline)
			contents += " ";
	}
	if (_make_iter(current) == end)
		_throw_parser_with_context(_make_iter(current) - 1, "expected '" + WHITE("@end") + "' at end of shader", "to match this");

	current++;
	for (const auto &s : _shaders)
	{
		if (s.context == context && s.name == name)
		{
			_print_warning_with_note(_context_token, "conflicting declaration '"
				+ WHITE("@", _context_token + 1, name) + "', only the first declaration is used", s.token, "previous declaration as", s.name);
			use = false;
		}
	}
	if (use)
	{
		_shaders.push_back({name, contents, context, _context_token});
		// KN_INFO_LOG(context == CONTEXT_VERTEX_SHADER ? LOG_FOUND_VERT_SHADER : LOG_FOUND_FRAG_SHADER, name);
	}
}

void	OpenGLShaderParser::_include(size_t &current)
{
	bool	use = true;

	if (_make_iter(current) != SHADER_TOKEN_QUOTE)
		_throw_parser_with_context(_make_iter(current) - 1, "expected file path", "after");
	current++;
	if (_make_iter(current) != SHADER_TOKEN_TEXT)
		_throw_parser_with_context(_make_iter(current) - 1, "expected file path", "after");

	std::filesystem::path path = std::filesystem::path(_filepath).parent_path();
	path += "/" + (*_make_iter(current)).text;

	if (std::find(_included_files.begin(), _included_files.end(), path) != _included_files.end())
	{
		std::cerr << _make_warning_string(_make_iter(current), "ignored recursive include: " + (*_make_iter(current)).text) << '\n';
		use = false;
	}
	else
		_included_files.push_back(path.string());
	current++;

	if (_make_iter(current) != SHADER_TOKEN_QUOTE)
		_throw_parser_with_note(_make_iter(current), "expected '" + WHITE("\"") + "'", _make_iter(current) - 1, "to match this");
	current++;
	if (use)
	{
		std::ifstream file(path.string(), std::ios::binary);
		if (!file)
			_throw_parser("cannot open file: " + path.string());
		std::stringstream buffer;
		buffer << file.rdbuf();

		size_t first = _tokens.size();
		_tokenize(buffer.str());
		_parse_tokens(first, _tokens.size(), true);
	}
}

void	OpenGLShaderParser::_export(size_t &current, const_iterator &end)
{
	if (_make_iter(current) != SHADER_TOKEN_TEXT)
		_throw_parser_with_context(_make_iter(current) - 1, "expected file path", "after");
	std::string	name = (*_make_iter(current)).text;

	const auto c = std::find_if(_exports.begin(), _exports.end(), [name](const ExportContents& c){ return c.name == name; });
	if (c != _exports.end())
		_throw_parser(_make_iter(current), "duplicate export '" + WHITE(name) + "'");

	current++;
	std::string contents;
	while (_make_iter(current) != end && _make_iter(current) != SHADER_TOKEN_AT)
	{
		bool newline = (*_make_iter(current)).type == SHADER_TOKEN_NEWLINE;
		contents += (*_make_iter(current)).text;
		current++;
		if (_make_iter(current) != end && _make_iter(current) != SHADER_TOKEN_NEWLINE && !newline)
			contents += " ";
	}
	if (_make_iter(current) == end || _make_iter(current) != SHADER_TOKEN_AT || _make_iter(current) + 1 == end)
		_throw_parser_with_context(_make_iter(current) - 1, "expected '" + WHITE("@end") + "'", "to match this");
	current++;
	if (_make_iter(current) != "end")
		_throw_parser_with_context(_make_iter(current) - 1, "expected '" + WHITE("@end") + "'", "to match this");
	current++;

	_exports.push_back(ExportContents({name, contents, false}));
}

void	OpenGLShaderParser::_parse_program_context(size_t &current, const_iterator &end)
{
	Program		program;
	bool		use = true;

	program.context_token = _context_token;
	program.token = _make_iter(current);
	if (_make_iter(current) != SHADER_TOKEN_TEXT)
		_throw_parser_with_context(_make_iter(current), "expected program name", "as argument of");
	if (use)
		program.name = (*_make_iter(current)).text;
	for (const auto& prev : _programs)
	{
		if (prev.name == program.name)
		{
			_print_warning_with_note(_context_token, "conflicting declaration '"
				+ WHITE("@program ", _make_iter(current)) + "', only the first declaration is used", prev.context_token, "previous declaration as", prev.name);
			use = false;
		}
	}
	current++;
	if (_make_iter(current) == end || _make_iter(current) != SHADER_TOKEN_TEXT)
		_throw_parser_with_context(_make_iter(current), "expected vertex shader name", "as argument of");
	if (use)
	{
		program.vs = (*_make_iter(current)).text;
		program.vs_token = _make_iter(current);
	}
	current++;
	if (_make_iter(current) == end || _make_iter(current) != SHADER_TOKEN_TEXT)
		_throw_parser_with_context(_make_iter(current), "expected fragment shader name", "as argument of");
	if (use)
	{
		program.fs = (*_make_iter(current)).text;
		program.fs_token = _make_iter(current);
		_programs.push_back(program);
	}
	current++;
}

void	OpenGLShaderParser::_parse_tokens(size_t first, size_t last, bool included)
{
	Context	context = CONTEXT_NONE;

	while (first != last)
	{
		iterator end = _make_iter(last);

		while (first < last && _make_iter(first) == SHADER_TOKEN_NEWLINE)
			first++;
		if (first >= last)
			break ;
		if (!context)
		{
			if (_make_iter(first) != SHADER_TOKEN_AT)
				_throw_parser(_make_iter(first), "expected context token");
			_context_token = _make_iter(first);
			first++;
			if (first >= last)
				_throw_parser(_make_iter(first), "expected argument ");
			if (_make_iter(first) == SHADER_TOKEN_TEXT)
			{
				if (_make_iter(first) == "vs")
					context = CONTEXT_VERTEX_SHADER;
				else if (_make_iter(first) == "fs")
					context = CONTEXT_FRAGMENT_SHADER;
				else if (_make_iter(first) == "program")
					context = CONTEXT_PROGRAM;
				else if (_make_iter(first) == "include")
					context = CONTEXT_INCLUDE;
				else if (_make_iter(first) == "export")
					context = CONTEXT_EXPORT;
				else
					_throw_parser(_make_iter(first),
						// "expected one of '" + WHITE("@program") + "', '" + WHITE("@vs") + "', '" + WHITE("@fs") + "'", _make_iter(first) - 1,
						"unexpected token '" + WHITE("@", _make_iter(first)) + "'");
				first++;
			}
			else
				_throw_parser(_make_iter(first), "expected argument");
			if (context == CONTEXT_PROGRAM)
				_parse_program_context(first, end);
			else if (context == CONTEXT_INCLUDE)
				_include(first);
			else if (context == CONTEXT_EXPORT)
				_export(first, end);
			else
				_parse_shader_context(first, end, context);
			context = CONTEXT_NONE;
		}
	}
	if (!included && _programs.empty())
		_throw_parser(_tokens.begin(), "expected at least one '" + WHITE("@program") + "' declaration");
}

const std::string&	OpenGLShaderParser::_get_vertex_source(Program &program)
{
	for (const auto& s : _shaders)
		if (s.name == program.vs && s.context == CONTEXT_VERTEX_SHADER)
			return s.contents;
	_throw_parser(program.vs_token, program.name + ": unknown vertex shader: '" + WHITE(program.vs) + "'");
}

const std::string&	OpenGLShaderParser::_get_fragment_source(Program &program)
{
	for (const auto& s : _shaders)
		if (s.name == program.fs && s.context == CONTEXT_FRAGMENT_SHADER)
			return s.contents;
	_throw_parser(program.fs_token, program.name + ": unknown fragment shader: '" + WHITE(program.fs) + "'");
}

void	OpenGLShaderParser::MakeShader(const std::string& program_name, std::string &vertex_out, std::string &fragment_out)
{
	std::ifstream file(_filepath, std::ios::binary);
	if (!file)
	{
		Log::Critical("OpenGLShaderParser: Cannot open file '{}'", _filepath);
		return ;
	}

	_included_files.push_back(_filepath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	_tokenize(buffer.str());
	if (_tokens.empty())
		std::cerr << _make_warning_string("OpenGLShaderParser: empty file: " + _filepath) << '\n';
	else
		_parse_tokens(0, _tokens.size(), false);

	Program *p = nullptr;
	for (auto& program : _programs)
		if (program.name == program_name)
			p = &program;
	if (!p)
		_throw_parser("OpenGLShaderParser: unknown program name: '" + WHITE(program_name) + "'");

	vertex_out += _get_vertex_source(*p);
	fragment_out += _get_fragment_source(*p);
}

void	OpenGLShader::GenerateHeaderFromShader(
	const std::string& filepath,
	const std::string& program_name,
	const std::string& vs,
	const std::string fs)
{
	std::ofstream	header(filepath + ".hpp");
	KN_ASSERT(header, "Could not open file {}.hpp", filepath);

	auto Generate = [&header, &program_name](const std::string& shader, bool vertex)
	{
		if (vertex)
			header << "const char " << program_name << "_vs_source[] = {\n\t";
		else
			header << "const char " << program_name << "_fs_source[] = {\n\t";

		size_t i = 1;
		for (const auto c : shader)
		{
			header << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)c << ",";
			if (i++ % 16 == 0)
				header << "\n\t";
		}
		header << "0x00\n};\n";
	};
	
	header << "#pragma once\n\n";
	Generate(vs, true);
	header << "\n";
	Generate(fs, false);
}

void	OpenGLShader::GenerateHeaderFromShader(const std::string& filepath, const std::string& program_name)
{
	OpenGLShaderParser	parser(filepath);
	std::string			vs, fs;

	parser.MakeShader(program_name, vs, fs);
	GenerateHeaderFromShader(filepath, program_name, vs, fs);
}

OpenGLShader::OpenGLShader(const std::string& filepath, const std::string& program_name)
	: _name(program_name)
{
	OpenGLShaderParser	parser(filepath);
	std::string			vs, fs;

	parser.MakeShader(program_name, vs, fs);
	_name = program_name;

	// vs.insert(0, "#version 450 core\n\n");
	// fs.insert(0, "#version 450 core\n\n");

	CreateProgram(vs.c_str(), fs.c_str());
	Log::Trace("Created shader program '{}' (file: '{}')", _name, filepath);

	// TODO: make this into a real program
	// GenerateHeaderFromShader(filepath, program_name, vs, fs);
}

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
				SetFloat2(uniform.glsl_name, *static_cast<const glm::vec2 *>(ptr));
				break;
			case ShaderDataType::Float3:
				SetFloat3(uniform.glsl_name, *static_cast<const glm::vec3 *>(ptr));
				break;
			case ShaderDataType::Float4:
				SetFloat4(uniform.glsl_name, *static_cast<const glm::vec4 *>(ptr));
				break;
			case ShaderDataType::Mat4:
				SetMat4(uniform.glsl_name, *static_cast<const glm::mat4 *>(ptr));
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

void	OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
{
	KN_PROFILE_FUNC();

	UploadUniformFloat2(name, value);
}

void	OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
{
	KN_PROFILE_FUNC();

	UploadUniformFloat3(name, value);
}

void	OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
{
	KN_PROFILE_FUNC();

	UploadUniformFloat4(name, value);
}

void	OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
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

void	OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
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

void	OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
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

void	OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
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

void	OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
{
	GLint location = glGetUniformLocation(_renderer_id, name.c_str());
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	_KN_GL_CHECK_ERROR();
}

void	OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
{
	GLint location = glGetUniformLocation(_renderer_id, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	_KN_GL_CHECK_ERROR();
}

} // Kinai
