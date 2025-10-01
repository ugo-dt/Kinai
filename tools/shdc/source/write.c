#include "shdc.h"

void	write_line_no_newline(const char* restrict fmt, ...)
{
	assert(shdc.f);

	va_list	args;
	va_start(args, fmt);
	vfprintf(shdc.f, fmt, args);
	va_end(args);
}

void	write_line(const char* restrict fmt, ...)
{
	assert(shdc.f);

	va_list	args;
	va_start(args, fmt);
	vfprintf(shdc.f, fmt, args);
	va_end(args);
	fprintf(shdc.f, "\n");
}

void	shdc_expect(bool condition, FileParse_Token* token, const char* restrict fmt, ...)
{
	if (!condition)
	{
		va_list	args;

		if (token)
		{
			fprintf(stderr, TEXT_BOLD COLOR_WHITE "%s:%d:%d: " COLOR_RED "error: " COLOR_WHITE, shdc.input_file, token->row, token->col + 1);
		}

		va_start(args, fmt);
		vfprintf(stderr, fmt, args);
		va_end(args);

		fprintf(stderr, COLOR_DEFAULT TEXT_RESET "\n");
		exit(EXIT_FAILURE);
	}
}

static inline bool	token_has_argument_count(const FileParse_State* state, size_t index, size_t count)
{
	return index + count < state->count && state->tokens[index].row == state->tokens[index + 1].row;
}

void	shdc_expect_arguments(const FileParse_State* state, FileParse_Token* token, size_t index, size_t count)
{
	const char* __count;
	if (count == 1)
		__count = "an";
	else if (count == 2)
		__count = "two";
	else if (count == 3)
		__count = "three";
	else
		__count = "";
	shdc_expect(token_has_argument_count(state, index, count), token, "'%s%s' expects %s argument%s",
		token->value[0] == '@' ? "" : "@", token->value, __count, count > 1 ? "s" : "");
}

void	shdc_warn_if(bool condition, FileParse_Token* token, const char* restrict fmt, ...)
{
	if (condition)
	{
		va_list	args;

		if (token)
		{
			fprintf(stderr, TEXT_BOLD COLOR_WHITE "%s:%d:%d: " COLOR_MAGENTA "warning: " COLOR_WHITE, shdc.input_file, token->row, token->col + 1);
		}

		va_start(args, fmt);
		vfprintf(stderr, fmt, args);
		va_end(args);

		fprintf(stderr, COLOR_DEFAULT TEXT_RESET "\n");
		exit(EXIT_FAILURE);
	}
}
