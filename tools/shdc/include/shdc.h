#pragma once

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <libft/libft.h>

#define TEXT_RESET		"\033[0m"
#define TEXT_BOLD		"\033[1m"
#define COLOR_DEFAULT	"\033[39m"
#define COLOR_DARK_RED	"\033[31m"
#define COLOR_GREY		"\033[90m"
#define COLOR_RED		"\033[91m"
#define COLOR_GREEN		"\033[92m"
#define COLOR_YELLOW	"\033[93m"
#define COLOR_MAGENTA	"\033[95m"
#define COLOR_WHITE		"\033[97m"

typedef enum
{
	TokenType_Unknown = 0,
	TokenType_At,
	TokenType_Tab,
	TokenType_Uniform,
	TokenType_Semicolon,
	TokenType_OpenParenthesis,
	TokenType_CloseParenthesis,
	TokenType_OpenBracket,
	TokenType_CloseBracket,
	TokenType_Std140,
	TokenType_END,
}TokenType;

typedef enum
{
	Context_None = 0,
	Context_Module,
	Context_CType,
	Context_VS,
	Context_FS,
	Context_Program,
}Context;

typedef enum
{
	ShaderLang_Unknown = 0,
	ShaderLang_GLSL410,
	ShaderLang_GLSL300ES,
}ShaderLang;

typedef enum
{
	ShaderStage_None = 0,
	ShaderStage_Vertex,
	ShaderStage_Fragment,
}ShaderStage;

typedef enum
{
	ImageType_Unknown = 0,
	ImageType_2D,
	ImageType_Cube,
	ImageType_3D,
	ImageType_Array,
}ImageType;

typedef enum
{
	ImageSampleType_Unknown = 0,
	ImageSampleType_Float,
	ImageSampleType_Depth,
	ImageSampleType_SINT,
	ImageSampleType_UINT,
	ImageSampleType_UnfilterableFloat,
}ImageSampleType;

struct Image
{
	ShaderStage stage;
	ImageType type;
	ImageSampleType sample_type;
	bool multisampled;
};

typedef enum
{
	SamplerType_Unknown = 0,
	SamplerType_Filtering,
	SamplerType_NonFiltering,
	SamplerType_Comparison,
}SamplerType;

struct Sampler
{
	ShaderStage stage;
	SamplerType type;
};

struct ImageSamplerair
{
	ShaderStage stage;
	uint16_t image_slot;
	uint16_t sampler_slot;
	const char* glsl_name;
};

struct CType
{
	const char*	name;
	const char*	ctype;
};

struct Uniform
{
	const char* glsl_name;
	const char* original_type;
	const char* ctype;
	int array_count; // 0 or 1 for scalars, >1 if array
	FileParse_Token* token_used;
};

struct ShaderAttribute
{
	const char* name;
	const char* glsl_name;
};

struct Shader
{
	const char* name;
	int	start_index;
	int	end_index;
	ft_vector params;
};

struct State
{
	ShaderLang*	slangs;
	size_t		slang_count;

	const char* input_file;
	const char* output_file;

	FILE*		f;

	const char*	module_name;
	ft_vector	ctypes; // vector<struct CType>

	struct Shader vs;
	struct Shader fs;

	struct {
		const char*	name;
		const char*	vs;
		const char*	fs;
	} program;

	ft_vector	attrs; // vector<struct ShaderAttribute>

	uint16_t MaxVertexAttributes;
	uint16_t MaxUniformSlots;
};

extern struct State shdc;

void	shdc_expect(bool condition, FileParse_Token* token, const char* restrict fmt, ...);
void	shdc_expect_arguments(const FileParse_State* state, FileParse_Token* token, size_t index, size_t count);
void	shdc_warn_if(bool condition, FileParse_Token* token, const char* restrict fmt, ...);

// parse
void	parse_context_module(const FileParse_State* state, size_t* index);
void	parse_context_ctype(const FileParse_State* state, size_t* index);
void	parse_context_shader(const FileParse_State* state, size_t* index, char shader_type);
void	parse_context_program(const FileParse_State* state, size_t* index);
void	parse_context_token(const FileParse_State* state, size_t* index);
void	parse_tokens(const FileParse_State* state);

// pp
void	write_preprocessor(void);

// uniform
void	add_uniform(const char* type, const char* name, ShaderStage stage, FileParse_Token* token);
void	write_params(ShaderStage stage);

// shader
void	write_shader(const FileParse_State* state, const struct Shader* shader, ShaderLang slang);
void	write_shader_config(void);

// write
void	write_line_no_newline(const char* restrict fmt, ...);
void	write_line(const char* restrict fmt, ...);

