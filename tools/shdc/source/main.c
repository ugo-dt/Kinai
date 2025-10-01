#include "shdc.h"

struct State shdc;

static ShaderLang	match_slang(const char* slang)
{
	if (ft_strcmp(slang, "glsl410") == 0)
		return ShaderLang_GLSL410;
	if (ft_strcmp(slang, "glsl300es") == 0)
		return ShaderLang_GLSL300ES;
	return ShaderLang_Unknown;
}

static bool is_space(int c)
{
	if (c == '\t')
		return false;
	return ft_isspace(c);
}

static bool is_separator(int c)
{
	return c == ';' || c == '(' || c == ')' || c == '{' || c == '}';
}

static void	show_error_and_quit(ArgParse_State* arg_state, const char *error)
{
	ArgParse_ClearState(arg_state);
	fprintf(stderr, "shdc: %s\n", error);
	exit(EXIT_FAILURE);
}

static void	shdc_init(int argc, char **argv)
{
	const char* slang;

	ArgParse_State	arg_state = ArgParse_Parse(argc, argv, &(ArgParse_Desc){
		.program_name = "shdc",
		.opt_count = 3,
		.options = (ArgParse_OptionDesc[]){
			{
				.short_name = 'i',
				.long_name = "input",
				.type = ArgParse_OptionType_String,
				.default_value = NULL,
				.value = &shdc.input_file
			},
			{
				.short_name = 'o',
				.long_name = "output",
				.type = ArgParse_OptionType_String,
				.default_value = NULL,
				.value = &shdc.output_file
			},
			{
				.short_name = 's',
				.long_name = "slang",
				.type = ArgParse_OptionType_String,
				.value = &slang,
				.default_value = ARGPARSE_VALUE(const char*, "glsl410"),
			},
		},
	});

	if (!ArgParse_IsStateValid(&arg_state))
		show_error_and_quit(&arg_state, "unexpected error");
	if (!shdc.input_file)
		show_error_and_quit(&arg_state, "missing input file (-i)");
	if (!shdc.output_file)
		show_error_and_quit(&arg_state, "missing output file (-o)");

	// constants
	shdc.MaxVertexAttributes = 16;
	shdc.MaxUniformSlots = 8;

	shdc.ctypes = ft_vector_create(&(ft_vector_desc){
		.alloc.sizeof_type = sizeof(struct CType)
	});
	shdc.vs.params = ft_vector_create(&(ft_vector_desc){
		.alloc.sizeof_type = sizeof(struct Uniform)
	});
	shdc.fs.params = ft_vector_create(&(ft_vector_desc){
		.alloc.sizeof_type = sizeof(struct Uniform)
	});

	char** slangs = ft_split(slang, ':');
	for (int i = 0; slangs[i]; i++)
		shdc.slang_count++;

	shdc.slangs = malloc(sizeof(ShaderLang));
	if (!shdc.slangs)
		show_error_and_quit(&arg_state, strerror(errno));

	for (size_t i = 0; i < shdc.slang_count; i++)
		shdc.slangs[i] = match_slang(slangs[i]);

	ArgParse_ClearState(&arg_state);
}

static void	shdc_shutdown(void)
{
	free(shdc.slangs);
	ft_vector_destroy(&shdc.vs.params);
	ft_vector_destroy(&shdc.fs.params);
	ft_vector_destroy(&shdc.ctypes);
}

int	main(int argc, char** argv)
{
	shdc_init(argc, argv);
		
	FileParse_State	file_state = FileParse_Parse(shdc.input_file, &(FileParse_Desc){
		.isspace = is_space,
		.isseparator = is_separator,
		.skip_newlines = false,
		.token_count = TokenType_END - 1,
		.tokens = (FileParse_TokenDesc[]){
			{
				.type = TokenType_At,
				.value = "@",
			},
			{
				.type = TokenType_Tab,
				.value = "\t",
			},
			{
				.type = TokenType_Uniform,
				.value = "uniform",
			},
			{
				.type = TokenType_Semicolon,
				.value = ";",
			},
			{
				.type = TokenType_OpenParenthesis,
				.value = "(",
			},
			{
				.type = TokenType_CloseParenthesis,
				.value = ")",
			},
			{
				.type = TokenType_Std140,
				.value = "std140",
			},
			{
				.type = TokenType_OpenBracket,
				.value = "{",
			},
			{
				.type = TokenType_CloseBracket,
				.value = "}",
			}
		},
	});
	if (!FileParse_IsStateValid(&file_state))
	{
		fprintf(stderr, "shdc: can't open file %s\n", argv[1]);
		return EXIT_FAILURE;
	}
	parse_tokens(&file_state);

	FileParse_ClearState(&file_state);
	shdc_shutdown();
	return EXIT_SUCCESS;
}
