#include "shdc.h"

static void	shader_add_char(int c, int *line)
{
	if (*line == 0)
		write_line_no_newline("\t");
	write_line_no_newline("0x%02x,", c);
	(*line)++;
	if (*line >= 16)
	{
		*line = 0;
		write_line_no_newline("\n");
	}
}

void	write_shader(const FileParse_State* state, const struct Shader* shader, ShaderLang slang)
{
	const char* shader_version;
	const char* gl_version;
	const char* precision = "precision mediump float;\n";

	switch (slang)
	{
		case ShaderLang_GLSL410:
			shader_version = "#version 410\n";
			gl_version = "glsl410";
			break;
		case ShaderLang_GLSL300ES:
			shader_version = "#version 300 es\n";
			gl_version = "glsl300es";
			break;
		default:
			fprintf(stderr, "invalid shader lang");
			exit(EXIT_FAILURE);
	}
	size_t array_length = ft_strlen(shader_version) + 1;

	int row = state->tokens[shader->start_index].row;
	write_line("/*");
	write_line_no_newline("\t%s", shader_version);
	if (slang == ShaderLang_GLSL300ES)
	{
		write_line_no_newline("%s", precision);
		array_length += ft_strlen(precision);
	}
	for (int i = shader->start_index; i < shader->end_index; i++)
	{
		if (state->tokens[i].type == TokenType_Tab)
			array_length += 4;
		else
		{
			array_length += ft_strlen(state->tokens[i].value);
			if (state->tokens[i].value[0] != '\n' && (i < shader->end_index - 1 && state->tokens[i + 1].value[0] != '\n'))
				array_length += 1;
		}

		write_line_no_newline("%s", state->tokens[i].value);
		if (i + 1 < shader->end_index &&
			state->tokens[i].value[0] != '\n' && state->tokens[i + 1].value[0] != '\n' &&
			state->tokens[i].value[0] != '\t' && state->tokens[i + 1].value[0] != '\t' &&
			state->tokens[i].value[0] != ';' && state->tokens[i + 1].value[0] != ';' &&
			state->tokens[i].value[0] != '{' && state->tokens[i + 1].value[0] != '{' &&
			state->tokens[i].value[0] != '}' && state->tokens[i + 1].value[0] != '}' &&
			state->tokens[i].value[0] != '(' && state->tokens[i + 1].value[0] != '(' &&
			state->tokens[i + 1].value[0] != ')' &&
			state->tokens[i + 1].value[0] != ','
		)
			write_line_no_newline(" ");
		if (i + 1 < shader->end_index && state->tokens[i + 1].row > row)
		{
			row = state->tokens[i + 1].row;
			write_line_no_newline("\t");
		}
	}

	write_line("*/");
	write_line("static const char %s_%s_source_%s[%zu] = {",
		shdc.program.name, shader->name, gl_version, array_length);
	int line = 0;
	for (const char *c = shader_version; *c; c++)
		shader_add_char(*c, &line);
	if (slang == ShaderLang_GLSL300ES)
		for (const char *c = precision; *c; c++)
			shader_add_char(*c, &line);

	for (int i = shader->start_index; i < shader->end_index; i++)
	{
		if (state->tokens[i].type == TokenType_Tab)
		{
			for (int j = 0; j < 4; j++)
				shader_add_char(' ', &line);
		}
		else
		{
			for (size_t j = 0; j < ft_strlen(state->tokens[i].value); j++)
				shader_add_char(state->tokens[i].value[j], &line);
		}
		if (state->tokens[i].value[0] != '\n' && state->tokens[i].value[0] != '\t' &&
			(i < shader->end_index - 1 && state->tokens[i + 1].value[0] != '\n') &&
			(i < shader->end_index - 1 && state->tokens[i + 1].value[0] != '\t'))
		{
			shader_add_char(' ', &line);
		}
	}
	shader_add_char(0, &line);
	write_line("\n};");
}

// None = 0,
// Float, Float2, Float3, Float4,
// Mat3, Mat4,
// Int, Int2, Int3, Int4,
// Bool,
// UByte, UByte2, UByte3, UByte4,
// UInt, UInt2, UInt3, UInt4,
static inline const char* match_kinai_shader_data_type(const struct Uniform* uniform)
{
	if (ft_strcmp(uniform->original_type, "float") == 0)
	{
		if (uniform->array_count > 1)
		{
			if (uniform->array_count == 2)
				return "Float2";
			if (uniform->array_count == 3)
				return "Float3";
			if (uniform->array_count == 4)
				return "Float4";
		}
		return "Float";
	}
	if (ft_strcmp(uniform->original_type, "vec2") == 0)
		return "Float2";
	if (ft_strcmp(uniform->original_type, "vec3") == 0)
		return "Float3";
	if (ft_strcmp(uniform->original_type, "vec4") == 0)
		return "Float4";
	if (ft_strcmp(uniform->original_type, "mat3") == 0)
		return "Mat3";
	if (ft_strcmp(uniform->original_type, "mat4") == 0)
		return "Mat4";
	if (ft_strcmp(uniform->original_type, "int") == 0)
	{
		if (uniform->array_count > 1)
		{
			if (uniform->array_count == 2)	
				return "Int2";
			if (uniform->array_count == 3)
				return "Int3";
			if (uniform->array_count == 4)
				return "Int4";
		}
		return "Int";
	}
	if (ft_strcmp(uniform->original_type, "ivec2") == 0)
		return "Int2";
	if (ft_strcmp(uniform->original_type, "ivec3") == 0)
		return "Int3";
	if (ft_strcmp(uniform->original_type, "ivec4") == 0)
		return "Int4";
	if (ft_strcmp(uniform->original_type, "bool") == 0)
		return "Bool";
	if (ft_strcmp(uniform->original_type, "uint") == 0)
	{
		if (uniform->array_count > 1)
		{
			if (uniform->array_count == 2)
				return "UInt2";
			if (uniform->array_count == 3)	
				return "UInt3";
			if (uniform->array_count == 4)
				return "UInt4";
		}
		return "UInt";
	}
	if (ft_strcmp(uniform->original_type, "uvec2") == 0)
		return "UInt2";
	if (ft_strcmp(uniform->original_type, "uvec3") == 0)
		return "UInt3";
	if (ft_strcmp(uniform->original_type, "uvec4") == 0)
		return "UInt4";
	if (ft_strcmp(uniform->original_type, "sampler2D") == 0)
		return "UInt"; // we use uint to represent texture slots
	shdc_warn_if(true, uniform->token_used, "unknown uniform type '%s' for uniform '%s'",
		uniform->original_type, uniform->glsl_name);
	return "None";
}

void	write_shader_config(void)
{
	write_line("static inline const Kinai::ShaderConfig& %sProgramShaderConfig()", shdc.program.name);
	write_line("{");
	write_line("\tstatic Kinai::ShaderConfig config;");
	write_line("\tstatic bool valid = false;");
	write_line("\tif (!valid)");
	write_line("\t{");
	write_line("\t\tvalid = true;");
	write_line("\t\tconfig.name = \"%s\";", shdc.program.name);
	write_line("\t\tconfig.vs_source = KINAI_SHADER_SOURCE_VERSION(%s_vs_source);", shdc.program.name);
	write_line("\t\tconfig.fs_source = KINAI_SHADER_SOURCE_VERSION(%s_fs_source);", shdc.program.name);
	for (size_t i = 0; i < ft_vector_size(&shdc.vs.params); i++)
	{
		struct Uniform* uniform = ft_vector_at(&shdc.vs.params, i);
		write_line("\t\tconfig.uniforms[%zu].glsl_name = \"%s\";", i, uniform->glsl_name);
		write_line("\t\tconfig.uniforms[%zu].stage = Kinai::ShaderStage::Vertex;", i);
		write_line("\t\tconfig.uniforms[%zu].type = Kinai::ShaderDataType::%s;", i, match_kinai_shader_data_type(uniform));
	}
	for (size_t i = 0; i < ft_vector_size(&shdc.fs.params); i++)
	{
		struct Uniform* uniform = ft_vector_at(&shdc.fs.params, i);
		write_line("\t\tconfig.uniforms[%zu + %zu].glsl_name = \"%s\";", i, ft_vector_size(&shdc.vs.params), uniform->glsl_name);
		write_line("\t\tconfig.uniforms[%zu + %zu].stage = Kinai::ShaderStage::Fragment;", i, ft_vector_size(&shdc.vs.params));
		write_line("\t\tconfig.uniforms[%zu + %zu].type = Kinai::ShaderDataType::%s;", i, ft_vector_size(&shdc.vs.params), match_kinai_shader_data_type(uniform));
	}
	write_line("\t}");
	write_line("\treturn config;");
	write_line("}");
}