#include "shdc.h"

static inline Context	match_token(const FileParse_Token* token)
{
	if (ft_strcmp(token->value, "module") == 0)
		return Context_Module;
	if (ft_strcmp(token->value, "ctype") == 0)
		return Context_CType;
	if (ft_strcmp(token->value, "vs") == 0)
		return Context_VS;
	if (ft_strcmp(token->value, "fs") == 0)
		return Context_FS;
	if (ft_strcmp(token->value, "program") == 0)
		return Context_Program;
	return Context_None;
}

void	parse_context_module(const FileParse_State* state, size_t* index)
{
	shdc_expect_arguments(state, &state->tokens[*index], *index, 1);
	shdc.module_name = state->tokens[++(*index)].value;
}

void	parse_context_ctype(const FileParse_State* state, size_t* index)
{
	const char* name;
	const char* type;

	shdc_expect_arguments(state, &state->tokens[*index], *index, 2);
	name = state->tokens[++(*index)].value;
	type = state->tokens[++(*index)].value;
	ft_vector_push_back(&shdc.ctypes, &(struct CType){
		.name = name,
		.ctype = type,
	});
}

void	parse_context_shader(const FileParse_State* state, size_t* index, char shader_type)
{
	bool is_std140 = false;
	struct Shader* shader = shader_type == 'v' ? &shdc.vs : &shdc.fs;

	shdc_expect_arguments(state, &state->tokens[*index], *index, 1);
	if (shader_type == 'v')
	{
		shader->name = state->tokens[++(*index)].value;
		shader->start_index = ++(*index);
	}
	else
	{
		shader->name = state->tokens[++(*index)].value;
		shader->start_index = ++(*index);
	}
	while (*index < state->count)
	{
		if (state->tokens[*index].type == TokenType_Std140)
		{
			is_std140 = true;
			(*index)++;
			continue ;
		}
		if (state->tokens[*index].type == TokenType_At)
		{
			shdc_expect_arguments(state, &state->tokens[*index], *index, 1);
			(*index)++;
			shdc_expect(ft_strcmp(state->tokens[*index].value, "end") == 0,
				&state->tokens[*index], "unexpected token '@%s' in %s shader '%s', expected '@end'",
				state->tokens[*index].value,
				shader_type == 'v' ? "vertex" : "fragment",
				shader_type == 'v' ? shdc.vs.name : shdc.fs.name);
			shader->end_index = *index - 1;
			return ;
		}
		else if (state->tokens[*index].type == TokenType_Uniform)
		{
			if (is_std140)
			{
				shdc_expect_arguments(state, &state->tokens[*index], *index, 4);
				while (state->tokens[*index].type != TokenType_CloseBracket)
					(*index)++;
				is_std140 = false;
			}	
			else
			{
				const char* type;
				const char* name;
				
				shdc_expect_arguments(state, &state->tokens[*index], *index, 2);
				type = state->tokens[++(*index)].value;
				name = state->tokens[++(*index)].value;
				add_uniform(type, name, shader_type == 'v' ? ShaderStage_Vertex : ShaderStage_Fragment, &state->tokens[*index]);
			}
		}
		(*index)++;
	}
	shdc_expect(false, &state->tokens[*index - 1], "expected '@end' for %s shader '%s'",
		shader_type == 'v' ? "vertex" : "fragment",
		shader_type == 'v' ? "vs" : "fs"
	);
}

void	parse_context_program(const FileParse_State* state, size_t* index)
{
	shdc_warn_if(shdc.program.name != NULL, &state->tokens[*index],
		"duplicate program declaration");

	const char* program_name;
	const char* vs;
	const char* fs;
	shdc_expect_arguments(state, &state->tokens[*index], *index, 3);
	program_name = state->tokens[++(*index)].value;
	vs = state->tokens[++(*index)].value;
	fs = state->tokens[++(*index)].value;
	shdc.program.name = program_name;
	shdc.program.vs = vs;
	shdc.program.fs = fs;
}

void	parse_context_token(const FileParse_State* state, size_t* index)
{
	Context	context;

	shdc_expect_arguments(state, &state->tokens[*index], *index, 1);
	context = match_token(&state->tokens[*index + 1]);
	shdc_expect(context != Context_None,
		&state->tokens[*index + 1], "invalid context '@%s'", state->tokens[*index + 1].value);
	*index += 1;
	switch (context)
	{
		case Context_Module: parse_context_module(state, index); break;
		case Context_CType: parse_context_ctype(state, index); break;
		case Context_VS: parse_context_shader(state, index, 'v'); break;
		case Context_FS: parse_context_shader(state, index, 'f'); break;
		case Context_Program: parse_context_program(state, index); break;
		case Context_None:
		default:
			break;
	}
}

void	parse_tokens(const FileParse_State* state)
{
	shdc.f = fopen(shdc.output_file, "w");
	if (!shdc.f)
	{
		fprintf(stderr, "shdc: can't open output file %s\n", shdc.output_file);
		return ;
	}
	for (size_t i = 0; i < state->count; i++)
	{
		switch (state->tokens[i].type)
		{
			case TokenType_At:
				parse_context_token(state, &i);
				break;
			default:
				break;
		}
	}
	write_preprocessor();
	write_params(ShaderStage_Vertex);
	write_params(ShaderStage_Fragment);
	for (size_t i = 0; i < shdc.slang_count; i++)
	{
		write_shader(state, &shdc.vs, shdc.slangs[i]);
		write_shader(state, &shdc.fs, shdc.slangs[i]);
	}
	write_shader_config();
	fclose(shdc.f);
	printf("shdc: wrote %s successfully\n", shdc.output_file);
}
