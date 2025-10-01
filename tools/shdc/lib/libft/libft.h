/** ************************************************************************** */
/**                                                                            */
/**                                                        :::      ::::::::   */
/**   libft.h                                            :+:      :+:    :+:   */
/**                                                    +:+ +:+         +:+     */
/**   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/**                                                +#+#+#+#+#+   +#+           */
/**   Created: 2022/03/26 12:51:19 by ugdaniel          #+#    #+#             */
/**   Updated: 2024/07/27 11:20:09 by ugdaniel         ###   ########.fr       */
/**                                                                            */
/** ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <assert.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

# ifndef INT32_MAX
#  define INT32_MAX INT_MAX
#  define INT32_MIN INT_MIN
# endif // INT32_MAX

# if defined(LIBFT_NO_FUNCTION_POINTERS)
#  define LIBFT_STRING_NO_FUNCTION_POINTERS
#  define LIBFT_VECTOR_NO_FUNCTION_POINTERS
# endif // defined(LIBFT_NO_FUNCTION_POINTERS)

# ifdef __cplusplus
extern "C" {
# endif

# if defined(__GNUC__) && !defined(LIBFT_NO_STATEMENT_EXPRESSIONS)
#  ifndef max
#   define max(a, b) ({\
	__typeof__(a) _a = (a); \
	__typeof__(b) _b = (b); \
	_a > _b ? _a : _b; })
#  endif // max
#  ifndef min
#   define min(a, b) ({\
	__typeof__(a) _a = (a); \
	__typeof__(b) _b = (b); \
	_a < _b ? _a : _b; })
#  endif // min
#  ifndef clamp
#   define clamp(x, mn, mx) ({\
	__typeof__(x) _x = (x); \
	__typeof__(mn) _mn = (mn); \
	__typeof__(mx) _mx = (mx); \
	max(_mn, min(_mx, _x)); })
#  endif // clamp
# else // !defined(__GNUC__) || defined(LIBFT_NO_STATEMENT_EXPRESSIONS)
#  define LIBFT_DECL_MIN_MAX_TYPE(T, ...) \
	static inline T _libft__min_##__VA_ARGS__(const T a, const T b) { return ((a) < (b)) ? (a) : (b); } \
	static inline T _libft__max_##__VA_ARGS__(const T a, const T b) { return ((a) > (b)) ? (a) : (b); }
LIBFT_DECL_MIN_MAX_TYPE(signed char, c) LIBFT_DECL_MIN_MAX_TYPE(unsigned char, uc)
LIBFT_DECL_MIN_MAX_TYPE(signed short, s) LIBFT_DECL_MIN_MAX_TYPE(unsigned short, us)
LIBFT_DECL_MIN_MAX_TYPE(signed int, i) LIBFT_DECL_MIN_MAX_TYPE(unsigned int, ui)
LIBFT_DECL_MIN_MAX_TYPE(signed long, l) LIBFT_DECL_MIN_MAX_TYPE(unsigned long, ul)
LIBFT_DECL_MIN_MAX_TYPE(signed long long, ll) LIBFT_DECL_MIN_MAX_TYPE(unsigned long long, ull)
LIBFT_DECL_MIN_MAX_TYPE(float, f) LIBFT_DECL_MIN_MAX_TYPE(double, d) LIBFT_DECL_MIN_MAX_TYPE(long double, ld)
#  define LIBFT_MIN_MAX_TYPE_GENERIC(a, b, _f) _Generic((b),	\
	signed char: _f##c,			unsigned char: _f##uc,			\
	signed short: _f##s,		unsigned short: _f##us,			\
	signed int: _f##i,			unsigned int: _f##ui,			\
	signed long: _f##l,			unsigned long: _f##ul,			\
	signed long long: _f##ll,	unsigned long long: _f##ull,	\
	float: _f##f,												\
	double: _f##d,												\
	long double: _f##ld											\
)((a), (b))
# ifndef min
#  define min(a, b) LIBFT_MIN_MAX_TYPE_GENERIC(a, b, _libft__min_)
# endif // min
# ifndef max
#  define max(a, b) LIBFT_MIN_MAX_TYPE_GENERIC(a, b, _libft__max_)
# endif // max
# endif // __GNUC__

# ifndef LIBFT_BUFFERSIZE
#  define LIBFT_BUFFERSIZE	42
# endif

// array

/** The ft_array_size() function returns the size of a NULL terminated
 * two-dimensional array. */
size_t	ft_array_size(void **arr);

/** The ft_free_array() function frees a each element from a two-dimensional
 * array, starting from index 0 up to the first NULL element encountered. */
void	ft_free_array(void **arr);

/** The ft_free_array_n() function frees up to n elements from a
 * two-dimensional array, then frees the void *to the array. */
void	ft_free_array_n(void **tab, size_t n);

/*
 * The ft_copy_array() function returns a copy of the NULL-terminated
 * two-dimensional array arr. The function only copies up to the first
 * NULL encountered.
 * 
 * The memory for the copy is obtained using malloc(3),
 * and can be freed with free(3);
 */
char	**ft_copy_array(char **arr);

/** 
 * The ft_split() function splits a string it into words, and returns them as
 * a NULL-terminated array of strings.
 * 
 * A "word" is defined as a part of a string delimited by the character c,
 * or by the start/end of the string.
 * 
 * The memory for the array is obtained using malloc(3),
 * and can be freed with free(3);
 */
char	**ft_split(const char *s, char c);

/*
 * Print every string in the array arr, followed by a newline,
 * on the file descriptor fd.
 * 
 * The function stops at the first NULL string encountered.
 */
void	ft_print_array_fd(const char **arr, int fd);

/** Sort an array of strings using ft_strcmp(). */
void	ft_sort_array(char **array);

// char

/** The ft_islower() function tests for any lower-case letters */
int		ft_islower(int c);

/** The ft_isupper() function tests for any upper-case letter. */
int		ft_isupper(int c);

/** The ft_tolower() function converts an upper-case letter to the corresponding
 * lower-case letter. The argument must be representable as an unsigned char.*/
int		ft_tolower(int c);

/** The ft_toupper() function converts an lower-case letter to the corresponding
 * upper-case letter. The argument must be representable as an unsigned char.*/
int		ft_toupper(int c);

/** The ft_isalpha() function tests for any character
 * for which isupper(3) or islower(3) is true.
 *
 * @return Zero if the character tests false and non-zero if the
 * character tests true.
 */
int		ft_isalpha(int c);

/** The ft_isdigit() function tests for a decimal digit character. 
 *
 * This includes the following characters only:
 * '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
 * 
 * @returns Zero if the character tests false and return non-zero if the
 * character tests true.
 */
int		ft_isdigit(int c);

/** The ft_isalnum() function tests for any character for which
 * ft_isalpha() or ft_isdigit() is true. */
int		ft_isalnum(int c);

/** The isascii() function tests for an ASCII character, which is any character
 * between 0 and decimal 127 inclusive. */
int		ft_isascii(int c);

/** The ft_isprint() function tests for any printing character,
 * including space (' '). */
int		ft_isprint(int c);

/** The ft_isspace() function tests for the white-space characters.
 * This includes the following standard characters:
 * '\\t'   '\\n'    '\\v'    '\\f'    '\\r'    ' ' */
int		ft_isspace(int c);

// list

/**
 * struct s_list
 * 
 * @param content Pointer to any type of data;
 * @param next The address of the next link of the list (NULL if last).
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

/** Adds a new element at the end of the list.
 * 
 * @param lst The first element of the list.
 * @param new_elem The new element to be added at the back of the list. Can be NULL.
 */
void	ft_lstadd_back(t_list **lst, t_list *new_elem);

/** Adds a new element at the start of the list.
 * 
 * @param lst The first element of the list. Can be NULL. 
 * @param new_elem The new element to be added at the front of the list. Can be NULL.
 */
void	ft_lstadd_front(t_list **lst, t_list *new_elem);

/** Clears a linked list.
 * 
 * @param lst The first element of the list. Can be NULL.
 * @param del The function to delete the contents of the element. Can be NULL.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/** Deletes an element, without relinking the list.
 *
 * @param lst The element to be deleted. Can be NULL.
 * @param del The function to delete the contents of the element. Can be NULL.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/** Applies the function f to each element in the list. 
 *
 * @param lst The first element of the list. Can be NULL.
 * @param f The function to apply to each element. Can be NULL.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/** 
 * @param lst The first element of the list. Can be NULL.
 *
 * @returns The address of the last element in a given list. */
t_list	*ft_lstlast(t_list *lst);

/** Creates a copy of the list with the function f applied to each element.
 * 
 * @param lst The first element of the list. Can be NULL.
 *
 * @returns A void *to the first element of the copy. 
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/** Creates a new t_list element.
 * 
 * @param content A void *to any type of data. Can be NULL.
 *
 * @returns A void *to the new element, or NULL if the allocation failed.
 */
t_list	*ft_lstnew(void *content);

/**
 * @param lst The first element of the list. Can be NULL.
 * 
 * @returns The numbers of elements in the list.
 */
int		ft_lstsize(t_list *lst);

// math

/** The ft_abs() function computes the absolute value of the integer i.
 *
 * @return The absolute value.
 */
int		ft_abs(int i);

/** The ft_labs() function computes the absolute value of a long number x.
 *
 * @return The absolute value.
 */
long		ft_labs(long i);
long long   ft_llabs(long long x);

/** The fabs() functions compute the absolute value of a floating-point
 * number x.
 * @return The absolute value.
 */
double		ft_fabs(double x);
float		ft_fabsf(float x);
long double	ft_fabsl(long double x);

// memory

/** The ft_bzero() function writes n zeroed bytes to the string s.
 * If n is zero, ft_bzero() does nothing. */
void	ft_bzero(void *s, size_t n);

/** The ft_calloc() function allocates enough space for count objects
 * that are size bytes of memory each and returns a void *to the allocated
 * memory.  The allocated memory is filled with bytes of value zero. */
void	*ft_calloc(size_t count, size_t size);

/** The ft_memccpy() function copies bytes from string src to string dst. 
 * If the character c (converted to an unsigned char) occurs in the string
 * src, the copy stops and a void *to the byte after the copy of c in the
 * string dst is returned. Otherwise, n bytes are copied, and a NULL void *is
 * returned.
 *
 * The source and destination strings should not overlap,
 * as the behavior is undefined. */
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);

/** The ft_memchr() function locates the first occurrence of c
 * (as converted to an unsigned char) in the string s. */
void	*ft_memchr(const void *s, int c, size_t n);

/** The ft_memcmp() function compares byte string s1 against byte string s2.
 * Both strings are assumed to be n bytes long. */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/** The memmove() function copies len bytes from string src to string dst.
 * The two strings may overlap; the copy is always done in a non-destructive
 * manner. */
void	*ft_memmove(void *dest, const void *src, size_t n);

/** The ft_memcpy() function copies n bytes from memory area src to memory
 * area dst. If dst and src overlap, behavior is undefined. Applications in
 * which dst and src might overlap should use ft_memmove instead. */
void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n);

/** The ft_memset() function writes len bytes of value c (converted to an
 * unsigned char) to the string s. */
void	*ft_memset(void *s, int c, size_t n);

// ft_printf

/** Maximum chars of output to write in MAXLEN.  */
int	ft_snprintf(char* str, size_t maxlen, const char *restrict format, ...)
	__attribute__ ((__format__ (__printf__, 3, 4)));

/** Maximum chars of output to write in MAXLEN.  */
int	ft_vsnprintf(char* str, size_t maxlen, const char *restrict format, va_list ap)
	__attribute__ ((__format__ (__printf__, 3, 0)));

/** Write formatted output to the file descriptor fd
 * from the format string FORMAT.
 * @returns The number of written characters. */
int	ft_dprintf(int fd, const char *restrict format, ...) \
	__attribute__((__format__ (__printf__, 2, 3)));

/** Write formatted output to stdout from the format string FORMAT.
 * @returns The number of written characters. */
int	ft_printf(const char *restrict format, ...) \
	__attribute__((__format__ (__printf__, 1, 2)));

// string

/** The ft_atoi() function converts the initial portion
 * of the string pointed by str to an int representation. */
int		ft_atoi(const char *str);

/** The ft_itoa() function converts an integer value to
 * a null-terminated string. */
char	*ft_itoa(int n);

/** Returns the length from s to the next character c
 * or the next '\\0' character. */
size_t	ft_len_to_char(const char *s, char c);

/** Returns the length from s to the next space character (using ft_isspace())
 * or the next '\\0' character. */
size_t	ft_len_to_space(const char *s);

/** The ft_str_tolower() function converts each uppercase letter to the 
 * corresponding lowercase letter in the null-terminated string s. */
void	ft_str_tolower(char *s);

/** The ft_str_toupper() function converts each lowercase letter to the 
 * corresponding uppercase letter in the null-terminated string s. */
void	ft_str_toupper(char *s);

/** 
 * The ft_strcmp() and ft_strncmp() functions lexicographically compare the
 * null-terminated strings s1 and s2.
 * 
 * @returns 0 if the strings are identical.
 */
int		ft_strcmp(const char *s1, const char *s2);

/** 
 * The ft_strcmp() and ft_strncmp() functions lexicographically compare the
 * null-terminated strings s1 and s2.
 * 
 * The ft_strncmp() function compares not more than n characters.
 * Because ft_strncmp() is designed for comparing strings rather than binary
 * data, characters that appear after a '\\0' character are not compared.
 * 
 * @returns 0 if the strings are identical.
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/** 
 * The ft_strdup() function allocates sufficient memory for a copy of the string
 * s1, does the copy, and returns a void *to it. The void *may subsequently
 * be used as an argument tothe function free(3).
 * 
 * If insufficient memory is available, NULL is returned.
 */
char	*ft_strdup(const char *s);

/** 
 * The ft_strndup() function allocates sufficient memory for a copy of the string
 * s1, does the copy, and returns a void *to it. The void *may subsequently
 * be used as an argument tothe function free(3).
 * 
 * The function copies at most n characters from the string s1 and always
 * NULL-terminates the copied string.
 * 
 * If insufficient memory is available, NULL is returned.
 */
char	*ft_strndup(const char *s, size_t n);

/** 
 * The ft_strjoin() function appends the string s2 to the end of s1,
 * overwriting the terminating null character ('\\0') at the end of s1,
 * then adds a terminating null character.
 * 
 * If either of the strings is NULL, the function returns NULL.
 * 
 * Memory for the new string is obtained with malloc(3),
 * and can be freed with free(3);
 */
char	*ft_strjoin(const char *s1, const char *s2);

/** 
 * The ft_strjoin_3() function appends a copy of the null-terminated strings
 * s2 and s3 to the end of the null-terminated string s1, overwriting the
 * terminating null character ('\\0') at the end of s1, then adds a
 * terminating null character.
 * 
 * If one of the strings is NULL, the function returns NULL.
 * 
 * Memory for the new string is obtained with malloc(3),
 * and can be freed with free(3);
 */
char	*ft_strjoin_3(const char *s1, const char *s2, const char *s3);

/** 
 * The ft_strcat() and function append a copy of the null-terminated
 * string s2 to the end of the null-terminated string s1, then add a terminating
 * '\\0'. The string s1 must have sufficient space to hold the result.
 */
char	*ft_strcat(char *s1, const char *s2);

/** 
 * The ft_strcat() and function append a copy of the null-terminated
 * string s2 to the end of the null-terminated string s1, then add a terminating
 * '\\0'. The string s1 must have sufficient space to hold the result. 
 * 
 * The ft_strncat function appends not more than n characters from s2,
 * and then adds a terminating '\\0'.
 */
char	*ft_strncat(char *s1, const char *s2, size_t n);

/** 
 * The ft_strlcat() function appends the NUL-terminated
 * string src to the end of dst.
 * It will append at most size - ft_strlen(dst) - 1 bytes,
 * null-terminating the result.
 * 
 * The function returns the total length of the string it tried to create.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/**
 * The strcspn() function calculates the length of the initial segment of s
 * which consists entirely of bytes not in reject.
 */
size_t	ft_strcspn(const char *s1, const char *s2);

/** The ft_strcpy() function copy the string src to dst
 * (including the terminating '\\0' character.) */
char	*ft_strcpy(char *dest, const char *src);

/** 
 * The ft_strncpy() function copy the string src to dst
 * (including the terminating '\\0' character.)
 *
 * The function copy at most len characters from src into dst.
 * If src is less than n characters long, the remainder of dst is filled with
 * '\\0' characters. Otherwise, dst is not terminated.
 */
char	*ft_strncpy(char *s1, const char *s2, size_t n);

/** The ft_strlcpy() function copies up to size - 1 characters from
 * the NUL-terminated string src to dst, NUL-terminating the result. */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/** The ft_strlen() function computes the length of the string s. */
size_t	ft_strlen(const char *s);

/** The ft_strnlen() function attempts to compute the length of s,
 * but never scans beyond the first maxlen bytes of s. */
size_t	ft_strnlen(const char *s, size_t maxlen);

/** 
 * The ft_strnstr() function locates the first occurrence of the null-terminated
 * string needle in the string haystack, where not more than len characters are
 * searched. Characters that appear after a '\\0' character are not searched.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t n);

/** 
 * The ft_strchr() function locates the first occurrence of the char c in the
 * string pointed to by s. The terminating null character is considered to be
 * part of the string; therefore if c is '\\0', the function locates the
 * terminating '\\0'.
 * 
 * The function returns NULL if it cannot find the character c in the string s.
 */
char	*ft_strchr(const char *s, int c);

/** 
 * The ft_strchr() function locates the first occurrence of the char c in the
 * string pointed to by s. The terminating null character is considered to be
 * part of the string; therefore if c is '\\0', the function locates the
 * terminating '\\0'.
 * 
 * The function returns NULL if it cannot find the character c in the string s.
 *
 * The ft_strrchr() function is identical to ft_strchr(),
 * except it locates the last occurrence of c.
 */
char	*ft_strrchr(const char *s, int c);

/** 
 * The ft_strmapi() applies the given function f to each character of the
 * string s to create a new string (with malloc(3))
 * resulting from successive applications of f.
 */
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));

/** 
 * The ft_substr() function allocates memory with malloc(3) then returns a
 * string of len characters (or up to the first '\\0' encountered), and
 * starting from index start of s.
 */
char	*ft_substr(const char *s, unsigned int start, size_t len);

/*
 * The ft_strtrim() function allocates memory with malloc(3) then returns the
 * same string as s1, without the characters specified in set, at the start
 * and at the end of s1.
 */
char	*ft_strtrim(char *s1, char *set);

// write

/** Write a character on the standard output. */
void	ft_putchar(char c);

/** Write a character on the file descriptor fd. */
void	ft_putchar_fd(char c, int fd);

/** Print a number on the standard output. */
void	ft_putnbr(int n);

/** Print a number on the file descriptor fd. */
void	ft_putnbr_fd(int n, int fd);

/** Print the string s on the standard output. */
void	ft_putstr(const char *restrict s);

/** Print the string s on the file descriptor fd. */
void	ft_putstr_fd(const char *s, int fd);

/** Print the string s followed by a newline, on the standard output. */
void	ft_putendl(const char *restrict s);

/** Print a string followed by a newline, on the file descriptor fd. */
void	ft_putendl_fd(const char *s, int fd);

// get_next_line

int		ft_get_next_line(int fd, char **line);

// basic_string

typedef struct ft_string ft_string;

# ifndef LIBFT_STRING_DEFAULT_CAPACITY
#  define LIBFT_STRING_DEFAULT_CAPACITY	15
# endif // LIBFT_STRING_DEFAULT_CAPACITY

ft_string*	ft_string_create(void);
ft_string*	ft_string_create_from_str(const char *_x);
ft_string*	ft_string_create_from_str_count(const char *_x, size_t count);
ft_string*	ft_string_create_from_char(const char _x, size_t count);
ft_string*	ft_string_create_from_ft_string(const ft_string* s);
void		ft_string_destroy(ft_string* s);
bool		ft_string_equals(const ft_string* a, const ft_string* b);
bool		ft_string_equals_str(const ft_string* s, const char *_x);
const char*	ft_string_data(const ft_string* s);
size_t		ft_string_size(const ft_string* s);
size_t		ft_string_length(const ft_string* s);
char		ft_string_at(const ft_string* s, size_t pos);
bool		ft_string_empty(const ft_string* s);
size_t		ft_string_max_size(void);
void		ft_string_reserve(ft_string* s, size_t new_cap);
size_t		ft_string_capacity(const ft_string* s);
void		ft_string_shrink_to_fit(ft_string* s);
void		ft_string_append_str(ft_string* s, const char *_x);
void		ft_string_append_char(ft_string* s, const char _x, size_t n);
void		ft_string_append_ft_string(ft_string* s, const ft_string* x);
void		ft_string_assign(ft_string* s, const char *_x);
void		ft_string_assign_count(ft_string* s, const char *_x, size_t count);
void		ft_string_assign_char(ft_string* s, const char _x, size_t count);
void		ft_string_clear(ft_string* s);

#  define ft_string(...) _Generic((__VA_ARGS__),				\
	char *: ft_string_create_from_str,							\
	char: ft_string_create_from_char,							\
	int: ft_string_create_from_char,							\
	struct ft_string*: ft_string_create_from_ft_string,			\
	const struct ft_string*: ft_string_create_from_ft_string	\
)(__VA_ARGS__)

// ArgParse

#define ARGPARSE_INT_MIN			(INT32_MIN)
#define ARGPARSE_INT_MAX			(INT32_MAX)
#define ARGPARSE_VALUE(T_, value_)	(&(T_){value_})

typedef enum ArgParse_OptionType
{
	// options without arguments
	ArgParse_OptionType_Bool, // default

	// options with arguments
	// expect the address of the variable that will store the value
	ArgParse_OptionType_String,
	ArgParse_OptionType_Int,
	ArgParse_OptionType_Float,
} ArgParse_OptionType;

typedef void*	ArgParse_Value;

typedef struct ArgParse_OptionDesc
{
	ArgParse_OptionType	type;
	char				short_name;
	char*				long_name;
	void*				value; // pointer to the variable that will store the value
	ArgParse_Value		min;
	ArgParse_Value		max;
	ArgParse_Value		default_value;
} ArgParse_OptionDesc;

typedef struct ArgParse_Desc
{
	char*	program_name;
	char*	usage;

	// Options
	ArgParse_OptionDesc*	options;
	size_t					opt_count;
	bool					opt_ignore_unknown;
	bool					opt_allow_merge_short;
} ArgParse_Desc;

typedef struct ArgParse_Option
{
	bool	is_set;
} ArgParse_Option;

typedef enum ArgParse_Status
{
	ArgParse_Status_Success,
	ArgParse_Status_InvalidOption,
	ArgParse_Status_UnrecognizedOption,
	ArgParse_Status_OptionInvalidValue,
	ArgParse_Status_OptionRequiresAnArgument,
	ArgParse_Status_TooManyArguments,
	ArgParse_Status_AllocationError,
} ArgParse_Status;

typedef struct
{
	size_t				opt_count;
	ArgParse_Option*	options;
	char**				arguments;
	ArgParse_Status		_status;
} ArgParse_State;

ArgParse_State	ArgParse_Parse(int argc, char** argv, const ArgParse_Desc* state);
void			ArgParse_ClearState(ArgParse_State* state);
bool			ArgParse_IsStateValid(const ArgParse_State* state);

// FileParse

typedef struct
{
	int			type;
	const char*	value;
}FileParse_TokenDesc;

// todo: comments
typedef struct
{
	FileParse_TokenDesc*	tokens;
	size_t					token_count;
	bool					skip_newlines;
	bool					(*isspace)(int);
	bool					(*isseparator)(int);
}FileParse_Desc;

typedef struct
{
	int		type;
	char*	value;
	int		row, col;
}FileParse_Token;

typedef enum
{
	FileParse_Status_Success = 0,
	FileParse_Status_Error,
}FileParse_Status;

typedef struct
{
	FileParse_Status	_status;
	FileParse_Token*	tokens;
	size_t				count;
}FileParse_State;

FileParse_State	FileParse_Parse(const char *file, const FileParse_Desc* desc);
bool			FileParse_IsStateValid(const FileParse_State* state);
void			FileParse_ClearState(FileParse_State* state);

// vector

typedef struct ft_allocator
{
	size_t	sizeof_type;
	void*	(*allocate)(const struct ft_allocator*, size_t n);
	void	(*deallocate)(const struct ft_allocator*, void* p, size_t n);
	void	(*construct)(const struct ft_allocator*, void* p, const void *value_ptr);
	void	(*destroy)(const struct ft_allocator*, void* p);
	size_t	(*max_size)(const struct ft_allocator*);
}ft_allocator;

void*	ft_allocator_allocate(const ft_allocator* alloc, size_t n);
void	ft_allocator_deallocate(const ft_allocator* alloc, void *p, size_t n);
void	ft_allocator_construct(const ft_allocator* alloc, void *p, const void* value);
void	ft_allocator_destroy(const ft_allocator* alloc, void *p);
size_t	ft_allocator_max_size(const struct ft_allocator* alloc);

typedef enum
{
	IteratorType_Random = 1,
	IteratorType_Reverse = -1
}IteratorType;

typedef struct ft_iterator
{
	void*			_p;
	size_t			_sizeof_type;
	IteratorType	_type;
}ft_iterator;

typedef struct ft_vector
{
	ft_allocator	alloc;
	void*			begin;
	void*			end;
	void*			end_cap;
}ft_vector;

typedef struct
{
	ft_allocator	alloc;
	size_t			size;
	size_t			capacity;
	void*			default_value;
}ft_vector_desc;

ft_vector	ft_vector_create(const ft_vector_desc* desc);
void		ft_vector_destroy(ft_vector* vector);
ft_iterator	ft_vector_begin(const ft_vector* vector);
ft_iterator	ft_vector_end(const ft_vector* vector);
ft_iterator	ft_vector_rbegin(const ft_vector* vector);
ft_iterator	ft_vector_rend(const ft_vector* vector);
size_t		ft_vector_max_size(const ft_vector* vector);
size_t		ft_vector_size(const ft_vector* vector);
size_t		ft_vector_capacity(const ft_vector* vector);
size_t		ft_vector_empty(const ft_vector* vector);
void		ft_vector_clear(ft_vector* vector);
void		ft_vector_reserve(ft_vector* vector, size_t n);
void		ft_vector_assign(ft_vector* vector, ft_iterator first, ft_iterator last);
void		ft_vector_push_back(ft_vector* vector, const void* value);
void*		ft_vector_data(const ft_vector* vector);
void*		ft_vector_at(const ft_vector* vector, size_t n);

// Timer

# define FT_NS_PER_SECOND	(1000000000)
# define FT_NS_PER_MS		(1000000)

typedef struct ft_timer
{
	uint64_t	start; // ns
}ft_timer;

uint64_t	ft_timer_now(void);
void		ft_timer_reset(ft_timer* timer);
uint64_t	ft_timer_elapsed_ns(ft_timer* timer);
uint64_t	ft_timer_elapsed_ms(ft_timer* timer);
uint64_t	ft_timer_elapsed_seconds(ft_timer* timer);

# ifdef __cplusplus
}
# endif

#endif /** LIBFT_H */


#define _POINTER_ADD(__p, __size, __n) ((char*)(__p) + ((__n) * (__size)))
#define _POINTER_SUB(__p, __size, __n) ((char*)(__p) - ((__n) * (__size)))
#define _POINTER_INC(__p, __size) ((__p) = (_POINTER_ADD(__p, 1)))
#define _POINTER_DEC(__p, __size) ((__p) = (_POINTER_DEC(__p, 1)))

// type size is inferred. never use with void*
// #define _POINTER_POST_ADD(__p, __n) ({ __typeof__(__p) _old = (__p); (__p) = (__p) + __n; _old; })
// #define POINTER_POST_INC(__p) _POINTER_POST_ADD(__p, 1)
// #define POINTER_POST_DEC(__p) _POINTER_POST_ADD(__p, -1)

#define _ITER_ADD_SUB_TYPE(__p, __size, __n, __type) _POINTER_ADD((__p), (__size), ((__n) * (__type)))

#define _FT_ITER_ADD_P(__it, __n) _ITER_ADD_SUB_TYPE((__it)._p, (__it)._sizeof_type, (__n), (__it)._type)
#define _FT_ITER_SUB_P(__it, __n) _ITER_ADD_SUB_TYPE((__it)._p, (__it)._sizeof_type, (__n), ((__it)._type * -1))

#define _ITER_INC_DEC_TYPE(__p, __size, __type) _ITER_ADD_SUB_TYPE((__p), (__size), 1, (__type))
#define _FT_ITER_INC_P(__it) _ITER_INC_DEC_TYPE((__it)._p, (__it)._sizeof_type, (__it)._type)
#define _FT_ITER_DEC_P(__it) _ITER_INC_DEC_TYPE((__it)._p, (__it)._sizeof_type, ((__it)._type * -1))

// Modify the iterator in place
#define FT_ITER_ADD(__it, __n) ((__it) = (ft_iterator){ \
	._p = _FT_ITER_ADD_P(__it, __n), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )
#define FT_ITER_SUB(__it, __n) ((__it) = (ft_iterator){ \
	._p = _FT_ITER_SUB_P(__it, __n), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )
#define FT_ITER_INC(__it) ((__it) = (ft_iterator){ \
	._p = _FT_ITER_INC_P((__it)), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )
#define FT_ITER_DEC(__it) ((__it) = (ft_iterator){ \
	._p = _FT_ITER_DEC_P((__it)), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )

// Makes a new iterator
#define FT_ITER_ADD_NEW(__it, __n) ((ft_iterator){ \
	._p = _FT_ITER_ADD_P(__it, __n), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )
#define FT_ITER_SUB_NEW(__it, __n) ((ft_iterator){ \
	._p = _FT_ITER_SUB_P(__it, __n), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )
#define FT_ITER_INC_NEW(__it) ((ft_iterator){ \
	._p = _FT_ITER_INC_P((__it)), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )
#define FT_ITER_DEC_NEW(__it) ((ft_iterator){ \
	._p = _FT_ITER_DEC_P((__it)), ._sizeof_type = (__it)._sizeof_type, ._type = (__it)._type} )

#define FT_ITER_REF(__it) (( \
	(__it)._type) == IteratorType_Reverse ? _POINTER_SUB((__it)._p, (__it)._sizeof_type, 1) : ((__it)._p))
#define FT_ITER_VALUE(__it, __type) (*(__type *)(FT_ITER_REF(__it))) // dereference
 
#define FT_ITER_EQ(__it_a, __it_b) (((__it_a)._p) == ((__it_b)._p)) // equal
#define FT_ITER_LT(__it_a, __it_b) (((__it_a)._p) < ((__it_b)._p)) // less than
#define FT_ITER_NEQ(__it_a, __it_b) (!(FT_ITER_EQ((__it_a), (__it_b)))) // not equal
#define FT_ITER_GT(__it_a, __it_b) (FT_ITER_LT((__it_b), (__it_a)) && FT_ITER_NEQ((__it_a), (__it_b))) // greater than
#define FT_ITER_LE(__it_a, __it_b) (!FT_ITER_GT((__it_a), (__it_b))) // less than or equal
#define FT_ITER_GE(__it_a, __it_b) (!FT_ITER_LT((__it_a), (__it_b))) // greater than or equal

typedef enum
{
	TesterStatus_Success,
	TesterStatus_Failure,
	TesterStatus_Error,
	TesterStatus_ToDo,
}TesterStatus;

typedef void (*TestCallback)(void* param);

typedef struct
{
	const char*		name;
	TestCallback	callback;
	void*			param;
}TestIt;

typedef struct
{
	const char*	name;
	TestIt		*it;
	size_t		count;
}TesterContext;

typedef struct
{
	void			(*before)(void* param);
	void			(*before_each)(void* param);
	void			(*after)(void* param);
	void			(*after_each)(void* param);
	TesterContext*	contexts;
	size_t			count;
}TestDesc;

typedef enum
{
	Tester_ValueType_Int,
	Tester_ValueType_UInt,
	Tester_ValueType_Long,
	Tester_ValueType_ULong,
	Tester_ValueType_Float,
	Tester_ValueType_Double,
	Tester_ValueType_Pointer,
	Tester_ValueType_String,
}TesterValueType;

typedef struct TesterExpect
{
	void	(*ToBe)(const void* value, size_t sizeof_value, TesterValueType type);
	void	(*ToNotBe)(const void* value, size_t sizeof_value, TesterValueType type);
}TesterExpect;

void	Tester_Describe(const char* name, const TestDesc* desc);
void	Tester_SetStatus(TesterStatus status);

const TesterExpect*	_Tester_Expect(
	const char *value_name,
	const char* file,
	int line,
	const void* value,
	size_t sizeof_value
);
void	_TesterExpect_ToBe(const void* value, size_t sizeof_value, TesterValueType type);

// _Tester_Expect((&(__value)), sizeof((__value)))
#define Tester_Expect(__v)	({ _Tester_Expect(#__v, __FILE__, __LINE__, &(__typeof__((__v))){(__v)}, sizeof((__v))); })
#define _Tester_ValueType(__v) _Generic((__v), \
	int: Tester_ValueType_Int, \
	unsigned int: Tester_ValueType_UInt, \
	long: Tester_ValueType_Long, \
	unsigned long: Tester_ValueType_ULong, \
	float: Tester_ValueType_Float, \
	double: Tester_ValueType_Double, \
	char *: Tester_ValueType_String, \
	const char *: Tester_ValueType_String, \
	void *: Tester_ValueType_Pointer, \
	const void *: Tester_ValueType_Pointer, \
	default: Tester_ValueType_Pointer \
)

#if defined LIBFT_TESTER_MACROS
	#define ToBe(__v) ToBe(&(__typeof__((__v))){(__v)}, sizeof((__v)), _Tester_ValueType((__v)))
	#define ToNotBe(__v) ToNotBe(&(__typeof__((__v))){(__v)}, sizeof((__v)), _Tester_ValueType((__v)))
#endif // LIBFT_TESTER_MACROS

#ifdef LIBFT_IMPL
#ifndef LIBFT_IMPL_INCLUDED
#define LIBFT_IMPL_INCLUDED

#ifndef _LIBFT_PRINTF_H
# define _LIBFT_PRINTF_H

# ifdef __cplusplus
extern "C" {
# endif

# if !defined(LIBFT_NO_STATEMENT_EXPRESSIONS)
#  if __GNUC__ && defined(__has_warning)
#   if __has_warning("-Wgnu-statement-expression")
#    pragma GCC diagnostic ignored	"-Wgnu-statement-expression"
#   endif
#  endif // __GNUC
# endif

# ifndef __extern_always_inline
#  define __extern_always_inline static inline
# endif

# ifndef LIBFT_PRINTF_NULL_STRING
#   define LIBFT_PRINTF_NULL_STRING	"(null)"
# endif // LIBFT_PRINTF_NULL_STRING

# ifndef LIBFT_PRINTF_NULL_PTR
#  if defined(__linux__)
#   define LIBFT_PRINTF_NULL_PTR	"(nil)"
#  elif defined(__APPLE__)
#   define LIBFT_PRINTF_NULL_PTR	"0x0"
#  else
#   define LIBFT_PRINTF_NULL_PTR	"0x0"
#  endif
# endif // LIBFT_PRINTF_NULL_PTR

struct _libft_printf_specs
{
	struct
	{
		bool	alt:1;
		bool	zero:1;
		bool	left:1;
		bool	space:1;
		bool	showsign:1;
	}flags;

	struct
	{
		int	width;
		int	precision;
	}info;
};

char *_ft_printf_create_c(char c, struct _libft_printf_specs *specs);
char *_ft_printf_create_s(const char *s, struct _libft_printf_specs *specs);
char *_ft_printf_create_p(size_t addr, struct _libft_printf_specs *specs);
char *_ft_printf_create_di(int nb, struct _libft_printf_specs *specs);
char *_ft_printf_create_u(unsigned int nb, struct _libft_printf_specs *specs);
char *_ft_printf_create_xX(char x, unsigned int nb, struct _libft_printf_specs *specs);
char *_ft_printf_create_l(long nb, struct _libft_printf_specs *specs);
char *_ft_printf_create_ll(long long nb, struct _libft_printf_specs *specs);
char *_ft_printf_create_ul(unsigned long nb, struct _libft_printf_specs *specs);
char *_ft_printf_create_ull(unsigned long long nb, struct _libft_printf_specs *specs);

__extern_always_inline const unsigned char *_ft_find_spec(const unsigned char *format)
{
	const unsigned char *c = (const unsigned char *)ft_strchr((const char *)format, '%');
	if (!c)
		return format + ft_strlen((const char *)format);
	return (c);
}

# define FIND_WIDTH(f_, specs_, ap_)						\
	do														\
	{														\
		specs_.info.width = 0;								\
		if (ft_isdigit(*f_))								\
		{													\
			specs_.info.width = ft_atoi((const char *)f_);	\
			while (ft_isdigit(*f_) && *f_)					\
				f_++;										\
		}													\
		else if (*f_ == '*')								\
		{													\
			int _w = va_arg(ap_, int);						\
			if (_w < 0)										\
			{												\
				specs_.flags.left = true;					\
				specs_.info.width = -_w;					\
			}												\
			else											\
				specs_.info.width = _w;						\
			f_++;											\
		}													\
		if (*f_ == '\0')									\
			return (-1);									\
	} while (0)

# define FIND_PRECISION(f_, specs_, ap_)							\
	do																\
	{																\
		specs_.info.precision = -1;									\
		while (*f_ == '*' || *f_ == '-' || ft_isdigit(*f_))			\
			f_++;													\
		if (*f_ == '.')												\
		{															\
			specs_.info.precision = 1;								\
			f_++;													\
			if (ft_isdigit(*f_))									\
				specs_.info.precision = ft_atoi((const char *)f);	\
			else if (*f_ == '*')									\
			{														\
				int _p = va_arg(ap_, int);							\
				specs_.info.precision = _p < 0 ? 0 : _p;			\
				f_++;												\
			}														\
		}															\
		while (*f_ == '*' || *f_ == '.' || ft_isdigit(*f_))			\
			f_++;													\
		if (specs_.info.precision > -1)								\
			specs_.flags.zero = false;								\
		if (*f_ == '\0')											\
			return (-1);											\
	} while (0)

# define FIND_FLAGS(f_, specs_)						\
	do												\
	{												\
		f_++;										\
		while (ft_strchr("#0- +", *f_) && *f_)		\
	{												\
			if (*f_ == '#')							\
			{										\
				specs_.flags.alt = true;			\
			}										\
			if (*f_ == '0')							\
			{										\
				specs_.flags.zero = true;			\
			}										\
			if (*f_ == '-')							\
			{										\
				specs_.flags.left = true;			\
				specs_.flags.zero = false;			\
			}										\
			if (*f_ == ' ')							\
			{										\
				specs_.flags.space = true;			\
			}										\
			if (*f_ == '+')							\
			{										\
				specs_.flags.showsign = true;		\
				specs_.flags.space = false;			\
			}										\
			f_++;									\
		}											\
	} while (0)

# define GET_NUMBER_LENGTH(len_ptr_, nb_, base_, precision_, type_)	\
	do																\
	{																\
		(*(len_ptr_)) = 1;											\
		type_ tmp_ = nb_;											\
		if (tmp_ < 0)												\
		{															\
			(*(len_ptr_))++;										\
			tmp_ = -tmp_;											\
		}															\
		while (tmp_ >= base_)										\
		{															\
			tmp_ /= base_;											\
			(*(len_ptr_))++;										\
		}															\
		if (nb_ < 0)												\
		{															\
			if (precision_ > -1 && (*(len_ptr_)) <= precision_)		\
				(*(len_ptr_)) = precision_ + 1;						\
		}															\
		else														\
		{															\
			if (precision_ > -1 && (*(len_ptr_)) < precision_)		\
				(*(len_ptr_)) = precision_;							\
		}															\
	} while (0)

# define GET_UNSIGNED_NUMBER_LENGTH(len_ptr_, nb_, base_, precision_, type_)	\
	do																			\
	{																			\
		(*(len_ptr_)) = 1;														\
		type_ tmp_ = nb_;														\
		while (tmp_ >= base_)													\
		{																		\
			tmp_ /= base_;														\
			(*(len_ptr_))++;													\
		}																		\
		if (precision_ > -1 && (*(len_ptr_)) < precision_)						\
			(*(len_ptr_)) = precision_;											\
	} while (0)

# define MAKE_UNSIGNED_NUMBER_STRING(s, n_, length_, type_)	\
	do														\
	{														\
		char *s_ = (s);										\
		int i_ = length_ - 1;								\
		type_ nb_ = n_;										\
		while (nb_ >= 10)									\
		{													\
			s_[i_] = nb_ % 10 + 48;							\
			nb_ /= 10;										\
			i_--;											\
		}													\
		s_[i_] = nb_ % 10 + 48;								\
		i_--;												\
		while (i_ >= 0)										\
			s_[i_--] = '0';									\
	} while (0)

# define MAKE_NUMBER_STRING(s, type_, abs_f_, n_, length_)	\
	do														\
	{														\
		char *s_ = (s);										\
		int i_;												\
		unsigned type_ nb_;									\
		if ((n_ < 0))										\
			s_[0] = '-';									\
		i_ = length_ - 1;									\
		nb_ = abs_f_(n_);									\
		while (nb_ >= 10)									\
		{													\
			s_[i_] = nb_ % 10 + 48;							\
			nb_ /= 10;										\
			i_--;											\
		}													\
		s_[i_] = nb_ % 10 + 48;								\
		i_--;												\
		while (i_ >= (n_ < 0))								\
			s_[i_--] = '0';									\
	} while (0)

static inline char *_ft_printf_create_string_helper(struct _libft_printf_specs *specs, int arg_length, int *arg_start)
{
	char *s;

	if (specs->info.width < arg_length)
		specs->info.width = arg_length;
	s = malloc(sizeof(char) * specs->info.width);
	if (!s)
		return (NULL);
	int padding_length = specs->info.width - arg_length;
	int padding_start;
	if (!specs->flags.left)
	{
		padding_start = 0;
		*arg_start = padding_length;
	}
	else
	{
		padding_start = arg_length;
		*arg_start = 0;
	}
	ft_memset(s + padding_start, specs->flags.zero ? '0' : ' ', padding_length);
	return (s);
}

# define DO_POSITIONAL(_f, _s, _specs, ap_)																\
	do																									\
	{																									\
		if (*_f == 'l')																					\
		{																								\
			int is_long_ = 0;																			\
			_f++;																						\
			if (*_f == 'l')																				\
			{																							\
				_f++;																					\
				is_long_ = 1;																			\
			}																							\
			if (*_f == 'u')																				\
			{																							\
				if (is_long_)																			\
					_s = _ft_printf_create_ull(va_arg(ap_, unsigned long long), &_specs);				\
				else																					\
					_s = _ft_printf_create_ul(va_arg(ap_, unsigned long), &_specs);						\
			}																							\
			else if (*_f == 'd' || *_f == 'i')															\
			{																							\
				if (is_long_)																			\
					_s = _ft_printf_create_ll(va_arg(ap_, long long), &_specs);							\
				else																					\
					_s = _ft_printf_create_l(va_arg(ap_, long), &_specs);								\
			}																							\
		}																								\
		else if (*_f == '%')																			\
			_s = _ft_printf_create_c('%', &_specs);														\
		else if (*_f == 'c')																			\
			_s = _ft_printf_create_c(va_arg(ap_, int), &_specs);										\
		else if (*_f == 's')																			\
			_s = _ft_printf_create_s(va_arg(ap_, char *), &_specs);										\
		else if (*_f == 'p')																			\
			_s = _ft_printf_create_p(va_arg(ap_, size_t), &_specs);										\
		else if (*_f == 'd' || *_f == 'i')																\
			_s = _ft_printf_create_di(va_arg(ap_, int), &_specs);										\
		else if (*_f == 'u')																			\
			_s = _ft_printf_create_u(va_arg(ap_, unsigned int), &_specs);								\
		else if (*_f == 'x' || *_f == 'X')																\
			_s = _ft_printf_create_xX(*_f, va_arg(ap_, int), &_specs);									\
		if (!_s)																						\
			return (-1);																				\
	} while (0)

# ifdef __cplusplus
}
# endif

#endif // _LIBFT_PRINTF_H

bool	_ArgParse_StringIsDigit(const char *str, const char **invalid)
{
	*invalid = str;
	if (!str || *str == '\0')
		return false;

	// Optional leading +/-
	if (*str == '+' || *str == '-')
		str++;

	*invalid = str;
	if (!*str) // string was just "+" or "-"
		return false;

	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return false;
		str++;
		*invalid = str;
	}
	return true;
}

bool	_ArgParse_StringIsFloat(const char *str, const char **invalid)
{
	*invalid = str;
	if (!str || *str == '\0')
		return false;

	// Optional leading +/-
	if (*str == '+' || *str == '-')
		str++;

	*invalid = str;
	if (!*str) // string was just "+" or "-"
		return false;

	bool seen_digit = false;
	bool seen_dot = false;
	bool seen_exp = false;

	while (*str)
	{
		if (ft_isdigit((unsigned char)*str))
		{
			seen_digit = true;
		}
		else if (*str == '.')
		{
			if (seen_dot || seen_exp) // no multiple dots, no dot after exponent
				return false;
			seen_dot = true;
		}
		else if (*str == 'e' || *str == 'E')
		{
			if (seen_exp || !seen_digit) // only one exponent, must follow digits
				return false;
			seen_exp = true;
			seen_digit = false; // require digits after 'e'
			if (*(str + 1) == '+' || *(str + 1) == '-') // allow sign after exponent
			{
				str++;
				*invalid = str;
			}
		}
		else
		{
			return false;
		}
		str++;
		*invalid = str;
	}
	return seen_digit; // must end with digit
}

void	_ArgParse_UnrecognizedOption(ArgParse_State* state, const ArgParse_Desc* desc, const char *long_name)
{
	state->_status = ArgParse_Status_UnrecognizedOption;
	ft_dprintf(STDERR_FILENO, "%s: unrecognized option '%s'\n", desc->program_name, long_name);
}

void	_ArgParse_InvalidOption(ArgParse_State* state, const ArgParse_Desc* desc, const char short_name)
{
	state->_status = ArgParse_Status_InvalidOption;
	ft_dprintf(STDERR_FILENO, "%s: invalid option -- '%c'\n", desc->program_name, short_name);
}

void	_ArgParse_OptionInvalidValue(ArgParse_State* state, const ArgParse_Desc* desc, const char *value, const char *invalid)
{
	state->_status = ArgParse_Status_OptionInvalidValue;
	ft_dprintf(STDERR_FILENO, "%s: invalid value (`%s' near '%s')\n", desc->program_name, value, invalid);
}

void	_ArgParse_OptionRequiresAnArgument(ArgParse_State* state, const ArgParse_Desc* desc, size_t j, bool short_option)
{
	state->_status = ArgParse_Status_OptionRequiresAnArgument;
	if (short_option)
		ft_dprintf(STDERR_FILENO, "%s: option requires an argument -- '%c'\n", desc->program_name, desc->options[j].short_name);
	else
		ft_dprintf(STDERR_FILENO, "%s: option '--%s' requires an argument\n", desc->program_name, desc->options[j].long_name);
}

void	_ArgParse_TooManyArguments(ArgParse_State* state, const ArgParse_Desc* desc)
{
	state->_status = ArgParse_Status_TooManyArguments;
	ft_dprintf(STDERR_FILENO, "%s: too many arguments\n", desc->program_name);
}

void	_ArgParse_GetValue(ArgParse_State* state, const ArgParse_Desc* desc, char **argv, int *i, size_t j, bool short_option)
{
	char* option_argument = NULL;
	const char* invalid = NULL;

	if (desc->options[j].type > ArgParse_OptionType_Bool)
	{
		if (short_option && !desc->opt_allow_merge_short)
		{
			option_argument = &argv[*i][2];
			if (!option_argument || *option_argument == '\0')
				option_argument = argv[++(*i)];
		}
		else 
			option_argument = argv[++(*i)];
		if (!option_argument || *option_argument == '\0')
		{
			_ArgParse_OptionRequiresAnArgument(state, desc, j, short_option);
			return ;
		}
		switch (desc->options[j].type)
		{
			case ArgParse_OptionType_String:
				*((char **)(desc->options[j].value)) = option_argument;
				break;
			case ArgParse_OptionType_Int:
				if (!_ArgParse_StringIsDigit(option_argument, &invalid))
				{
					_ArgParse_OptionInvalidValue(state, desc, option_argument, invalid);
					return ;
				}
				int* value = (int *)(desc->options[j].value);
				int min = desc->options[j].min ? *((int *)(desc->options[j].min)) : ARGPARSE_INT_MIN;
				int max = desc->options[j].max ? *((int *)(desc->options[j].max)) : ARGPARSE_INT_MAX;

				//FIXME: we rely on libc for strtol
				long _val = strtol(option_argument, NULL, 10);

				if (_val < min)
				{
					state->_status = ArgParse_Status_OptionInvalidValue;
					ft_dprintf(STDERR_FILENO, "%s: option value too small: %ld\n", desc->program_name, _val);
					return ;
				}
				if (_val > max)
				{
					state->_status = ArgParse_Status_OptionInvalidValue;
					ft_dprintf(STDERR_FILENO, "%s: option value too big: %ld\n", desc->program_name, _val);
					return ;
				}
				*value = _val;
				break;
			case ArgParse_OptionType_Float:
				if (!_ArgParse_StringIsFloat(option_argument, &invalid))
				{
					_ArgParse_OptionInvalidValue(state, desc, option_argument, invalid);
					return ;
				}
				//FIXME: we rely on libc for atof
				*((float *)(desc->options[j].value)) = atof(option_argument);
				break;
			default:
				break;
		}
	}
}

void	_ArgParse_ParseLongOption(ArgParse_State* state, char **argv, const ArgParse_Desc* desc, int *i)
{
	bool	found = false;
	const char *arg = argv[*i];

	for (size_t j = 0; j < desc->opt_count; j++)
	{
		const char *long_name = &arg[2];

		if (ft_strcmp(long_name, desc->options[j].long_name) == 0)
		{
			state->options[j].is_set = true;
			_ArgParse_GetValue(state, desc, argv, i, j, false);
			found = true;
			break;
		}
		if (found)
			break;
	}
	if (!desc->opt_ignore_unknown && !found)
	{
		_ArgParse_UnrecognizedOption(state, desc, arg);
		return ;
	}
}

void	_ArgParse_ParseShortOption(ArgParse_State* state, char **argv, const ArgParse_Desc* desc, int *i)
{
	bool	found = false;
	const char *arg = argv[*i];

	for (int k = 1; arg[k]; k++)
	{
		found = false;
		for (size_t j = 0; j < desc->opt_count; j++)
		{
			if (arg[k] == desc->options[j].short_name)
			{
				state->options[j].is_set = true;
				_ArgParse_GetValue(state, desc, argv, i, j, true);
				found = true;
			}
		}
		if (!desc->opt_ignore_unknown && !found)
		{
			_ArgParse_InvalidOption(state, desc, arg[k]);
			return ;
		}
		if (!desc->opt_allow_merge_short && found) // everything after the option is treated as the value of the option
			break ;
	}
}

void	_ArgParse_SetOptionsDefaultValues(const ArgParse_Desc* desc)
{
	for (size_t i = 0; i < desc->opt_count; i++)
	{
		assert(desc->options[i].type == ArgParse_OptionType_Bool || desc->options[i].value != NULL);
		if (!desc->options[i].default_value)
			continue;
		switch (desc->options[i].type)
		{
			case ArgParse_OptionType_String:
				assert(desc->options[i].value != NULL);
				*((char **)((desc->options[i].value))) = *(char **)(desc->options[i].default_value);
				break;
			case ArgParse_OptionType_Int:
				assert(desc->options[i].value != NULL);
				*((int *)(desc->options[i].value)) = *(int *)desc->options[i].default_value;
			break;
			case ArgParse_OptionType_Float:
				assert(desc->options[i].value != NULL);
				*((float *)(desc->options[i].value)) = *(float *)desc->options[i].default_value;
				break;
			default:
				break;
		}
	}
}

bool	_ArgParse_OptionTakesArgument(const ArgParse_Desc* desc, const char *option)
{
	for (size_t i = 0; i < desc->opt_count; i++)
		if (desc->options[i].short_name == option[1] || ft_strcmp(desc->options[i].long_name, &option[2]) == 0)
			return desc->options[i].type > ArgParse_OptionType_Bool;
	return false;
}

bool	ArgParse_IsStateValid(const ArgParse_State* state)
{
	return state->_status == ArgParse_Status_Success;
}

ArgParse_State	ArgParse_Parse(int argc, char** argv, const ArgParse_Desc* desc)
{
	assert(desc != NULL);
	assert(desc->options != NULL || desc->opt_count == 0);

	ArgParse_State state = {
		.opt_count = desc->opt_count,
		.options = NULL,
		.arguments = NULL,
		._status = ArgParse_Status_Success,
	};

	if (state.opt_count > 0)
	{
		state.options = ft_calloc(desc->opt_count, sizeof(ArgParse_Option));
		if (!state.options)
			return (ArgParse_State){ ._status = ArgParse_Status_AllocationError };
		state._status = ArgParse_Status_Success;
		_ArgParse_SetOptionsDefaultValues(desc);
	}

	bool parse_options = true;
	size_t arg_count = 0;
	for (int i = 1; i < argc; i++)
	{
		if (parse_options && argv[i][0] == '-')
		{
			if (ft_strcmp(argv[i], "--") == 0)
			{
				parse_options = false;
				continue;
			}
			if (argv[i][1] == '-')
				_ArgParse_ParseLongOption(&state, argv, desc, &i);
			else
				_ArgParse_ParseShortOption(&state, argv, desc, &i);
		}
		else
			arg_count++;
		if (state._status != ArgParse_Status_Success)
			return state;
	}

	if (arg_count > 0)
	{
		state.arguments = ft_calloc(arg_count + 1, sizeof(char *));
		if (!state.arguments)
		{
			free(state.options);
			state.options = NULL;
			return (ArgParse_State){ ._status = ArgParse_Status_AllocationError };
		}
		parse_options = true;
		int j = 0;
		for (int i = 1; i < argc; i++)
		{
			if (parse_options && argv[i][0] == '-')
			{
				if (_ArgParse_OptionTakesArgument(desc, argv[i]))
				{
					// if we allow merging short options, we need to skip the next argument
					// otherwise, we skip if the option and its argument are separated.
					// for long options, we always skip the next argument as the '=' sign is not yet supported
					if (desc->opt_allow_merge_short || argv[i][2] == '\0' || argv[i][1] == '-')
						i++;
				}
				if (ft_strcmp(argv[i], "--") == 0)
				{
					parse_options = false;
					continue;
				}
			}
			else
			{
				state.arguments[j++] = argv[i];
			}
		}
		state.arguments[j++] = NULL;
	}
	return state;
}

void	ArgParse_ClearState(ArgParse_State* state)
{
	free(state->options);
	free(state->arguments);
}

size_t	ft_array_size(void **arr)
{
	size_t	i;

	if (!arr || !(*arr))
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	ft_free_array(void **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	ft_free_array_n(void **tab, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		free(tab[i++]);
	free(tab);
}

void	ft_print_array_fd(const char **arr, int fd)
{
	int		i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		ft_putendl_fd(arr[i++], fd);
}

void	ft_sort_array(char **array)
{
	int		i;
	char	*temp;

	i = 0;
	while (array[i + 1])
	{
		if (ft_strcmp(array[i], array[i + 1]) > 0)
		{
			temp = ft_strdup(array[i]);
			free(array[i]);
			array[i] = ft_strdup(array[i + 1]);
			free(array[i + 1]);
			array[i + 1] = ft_strdup(temp);
			free(temp);
			i = 0;
		}
		else
			i++;
	}
}

char	**ft_copy_array(char **arr)
{
	size_t	i;
	size_t	size;
	char	**copy;

	size = ft_array_size((void **)arr);
	copy = malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (arr[i] && i < size)
	{
		copy[i] = ft_strdup(arr[i]);
		if (!copy[i])
		{
			ft_free_array_n((void **)copy, i);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

typedef struct ft_string
{
	char*	_data;
	size_t	_capacity;
}ft_string;

static size_t	_ft_string_recommend(size_t capacity, size_t new_size)
{
	assert(new_size < SIZE_MAX);
    if (capacity >= SIZE_MAX / 2)
        return SIZE_MAX;
    return max(2 * capacity, new_size);
}

ft_string*	_ft_string_alloc_impl(void)
{
	ft_string*	s = malloc(sizeof(struct ft_string));
	return s;
}

ft_string*	ft_string_create(void)
{
	ft_string*	string;
	
	string = _ft_string_alloc_impl();
	assert(string);
	string->_capacity = LIBFT_STRING_DEFAULT_CAPACITY;
	string->_data = malloc(string->_capacity * sizeof(*string->_data));
	assert(string->_data);
	string->_data[0] = '\0';
	return string;
}

ft_string*	ft_string_create_from_str(const char *_x)
{
	ft_string*	string;
	
	string = _ft_string_alloc_impl();
	assert(string);
	string->_capacity = 0;
	string->_data = NULL;
	ft_string_assign(string, _x);
	return string;
}

ft_string*	ft_string_create_from_str_count(const char *_x, size_t count)
{
	ft_string* string;
	
	string = _ft_string_alloc_impl();
	string->_capacity = 0;
	string->_data = NULL;
	ft_string_assign_count(string, _x, count);
	return string;
}

ft_string*	ft_string_create_from_char(const char _x, size_t count)
{
	ft_string* string;
	
	string = _ft_string_alloc_impl();
	string->_capacity = 0;
	string->_data = NULL;
	ft_string_assign_char(string, _x, count);
	return string;
}

ft_string*	ft_string_create_from_ft_string(const ft_string* x)
{
	ft_string*	string;
	ft_string*	_x;
	
	string = _ft_string_alloc_impl();
	string->_capacity = 0;
	string->_data = NULL;
	_x = (ft_string*)x;
	if (_x->_data)
		ft_string_assign(string, _x->_data);
	return string;
}

void	ft_string_destroy(ft_string* s)
{
	if (!s)
		return ;
	if (s->_data)
	{
		free(s->_data);
		s->_capacity = 0;
	}
	free(s);
}

bool	ft_string_equals(const ft_string* a, const ft_string* b)
{
	return ft_strcmp(a->_data, b->_data) == 0;
}

bool	ft_string_equals_str(const ft_string* s, const char *_x)
{
	return ft_strcmp(s->_data, _x) == 0;
}

const char*	ft_string_data(const ft_string* s)
{
	return s->_data;
}

size_t	ft_string_size(const ft_string* s)
{
	if (!s->_data)
		return 0;
	return ft_strlen(s->_data);
}

size_t	ft_string_length(const ft_string* s)
{
	return ft_strlen(s->_data);
}

char	ft_string_at(const ft_string* s, size_t pos)
{
	assert(pos < s->_capacity);
	return s->_data[pos];
}

bool	ft_string_empty(const ft_string* s)
{
	return s->_capacity == 0 || s->_data[0] == '\0';
}

size_t	ft_string_max_size(void)
{
	return (SIZE_MAX);
}

void	ft_string_reserve(ft_string *s, size_t new_cap)
{
	if (s->_capacity < new_cap)
	{
		char *new_data = ft_calloc(new_cap, sizeof(char));
		assert(new_data);
		s->_capacity = new_cap;

		ft_strcpy(new_data, s->_data);

		if (s->_data)
			free(s->_data);
		s->_data = new_data;
	}
}

size_t	ft_string_capacity(const ft_string* s)
{
	return s->_capacity;
}

void	ft_string_shrink_to_fit(ft_string *s)
{
	size_t	len = ft_strlen(s->_data) + 1;

	if (s->_capacity > len)
	{
		char *new_data = malloc(sizeof(char) * len);
		assert(new_data);
		ft_memcpy(new_data, s->_data, len);
		if (s->_data)
			free(s->_data);
		s->_data = new_data;
		s->_capacity = len;
	}
}

void	_ft_string_print_debug(const ft_string* s, const char *_info, const char *param, size_t param_size)
{
	int	_cap;

	if (!s)
		return ;
	_cap = s->_capacity;
	ft_printf("--- FT_STRING");
	if (_info)
	{
		ft_printf(" %s", _info);
		if (param)
		{
			ft_putstr(" '");
			for (size_t i = 0; i < param_size; i++)
			{
				if (param[i] == '\0')
					ft_putstr("\\0");
				else if (param[i] == '\n')
					ft_putstr("\\n");
				else if (param[i] == '\t')
					ft_putstr("\\t");
				else if (ft_isascii(param[i]))
					ft_putchar(param[i]);
				else
					ft_putchar('.');
			}
			ft_putchar('\'');
		}
	}
	ft_printf(" ---\n");
	ft_printf("DATA START\n%s\nDATA END\n", s->_data);
	ft_printf("-----\n");
	ft_printf("CAP : %d\n", _cap);

	ft_printf("MEM : |");
	for (int i = 0; i <= _cap; i++)
	{
		if (s->_data[i] == '\0')
			ft_printf("\\0|");
		else if (s->_data[i] == '\n')
			ft_printf("\\n|");
		else if (s->_data[i] == '\t')
			ft_printf("\\t|");
		else if (ft_isascii(s->_data[i]))
			ft_printf("%2c|", s->_data[i]);
		else
			ft_printf("%2c|", '.');
	}
	ft_printf("\n");
	ft_printf("      |");
	for (int i = 0; i <= _cap; i++)
		ft_printf("%2d|", i);
	ft_printf("\n");
	ft_printf("--- END ---\n");
}

void	ft_string_append_str(ft_string *s, const char *_x)
{
	size_t _size, _newsize;
	size_t len = ft_strlen(_x);

	_size = ft_strlen(s->_data);
	_newsize = _size + len + 1;
	if (s->_capacity < _newsize)
	{
		size_t _newcap = _ft_string_recommend(s->_capacity, _newsize);
		char *new_data = ft_calloc(_newcap, sizeof(char));
		assert(new_data);
		s->_capacity = _newcap;

		if (s->_data)
		{
			ft_strcat(new_data, s->_data);
			free(s->_data);
		}
		ft_strcat(new_data, _x);
		s->_data = new_data;
	}
	else
	{
		ft_strcat(s->_data, _x);
	}
	// _ft_string_print_debug(s, "append_string()", _x, ft_strlen(_x));
}

void	ft_string_append_char(ft_string* s, const char _x, size_t n)
{
	size_t _size, _newsize;

	_size = ft_strlen(s->_data);
	_newsize = _size + n + 1;
	if (s->_capacity < _newsize)
	{
		size_t _newcap = _ft_string_recommend(s->_capacity, _newsize);
		char *new_data = ft_calloc(_newcap, sizeof(char));
		assert(new_data);
		s->_capacity = _newcap;

		if (s->_data)
		{
			ft_strcpy(new_data, s->_data);
			free(s->_data);
		}
		ft_memset(new_data + _size, _x, n);
		s->_data = new_data;
	}
	else
	{
		ft_memset(s->_data + _size, _x, n);
	}
	// _ft_string_print_debug(s, "append_char()", &_x, 1);
}

void	ft_string_append_ft_string(ft_string* s, const ft_string* x)
{
	if (x->_capacity && x->_data)
		ft_string_append_str(s, x->_data);
}

void	ft_string_assign(ft_string* s, const char *_x)
{
	size_t _xsize;

	_xsize = ft_strlen(_x) + 1;
	if (s->_capacity < _xsize)
	{
		char *new_data = ft_strdup(_x);
		assert(new_data);
		assert(new_data);
		s->_capacity = _xsize;

		if (s->_data)
			free(s->_data);
		s->_data = new_data;
	}
	else
	{
		ft_strcpy(s->_data, _x);
		ft_memset(s->_data + _xsize, '\0', s->_capacity - _xsize);
	}
}

void	ft_string_assign_count(ft_string* s, const char *_x, size_t count)
{
	size_t _xsize;

	_xsize = ft_strnlen(_x, count) + 1;
	if (s->_capacity < _xsize)
	{
		char *new_data = ft_strndup(_x, count);
		assert(new_data);
		s->_capacity = _xsize;

		if (s->_data)
			free(s->_data);
		s->_data = new_data;
	}
	else
	{
		ft_strcpy(s->_data, _x);
		ft_memset(s->_data + _xsize, '\0', s->_capacity - _xsize);
	}
}

void	ft_string_assign_char(ft_string* s, const char _x, size_t count)
{
	size_t	_newcap;

	_newcap = count + 1;
	if (s->_capacity < count)
	{
		char *new_data = ft_calloc(_newcap, sizeof(char));
		assert(new_data);
		s->_capacity = _newcap;

		ft_memset(new_data, _x, count);
		ft_memset(new_data + count, '\0', s->_capacity - count);

		if (s->_data)
			free(s->_data);
		s->_data = new_data;
	}
	else
	{
		ft_memset(s->_data, _x, count);
		ft_memset(s->_data + count, '\0', s->_capacity - count);
	}
}

void	ft_string_clear(ft_string *s)
{
	if (s->_data)
		ft_bzero(s->_data, s->_capacity);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

int	ft_toupper(int c)
{
	if (ft_islower(c))
		return (c - 'a' + 'A');
	return (c);
}

int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}

int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c - 'A' + 'a');
	return (c);
}

typedef struct
{
	FileParse_Token	t;
	size_t			length;
}FileParse_TokenListItem;

typedef struct
{
	FileParse_TokenListItem*	begin;
	FileParse_TokenListItem*	end;
	FileParse_TokenListItem*	end_cap;
}FileParse_TokenList;

bool	FileParse_IsSpace(const FileParse_Desc* desc, int c)
{
	if (desc->isspace)
		return desc->isspace(c);
	return ft_isspace(c);
}

bool	FileParse_IsSeparator(const FileParse_Desc* desc, int c)
{
	if (desc->isseparator)
		return desc->isseparator(c);
	return false;
}

size_t	FileParse_TokenList_RecommendNewSize(FileParse_TokenList *list)
{
	size_t size = (size_t)(list->end - list->begin);
	size_t capacity = (size_t)(list->end_cap - list->begin);
	return max(2 * capacity, size + 1);
}

bool	FileParse_TokenList_Push(FileParse_TokenList *list, const FileParse_TokenListItem* token)
{
	assert(list != NULL);
	assert(token != NULL);

	if (list->end < list->end_cap)
		ft_memcpy(list->end++, token, sizeof(FileParse_TokenListItem));
	else
	{
		FileParse_TokenList new_list = { 0 };

		// alloc
		size_t	new_cap = FileParse_TokenList_RecommendNewSize(list);
		new_list.begin = ft_calloc(new_cap, sizeof(FileParse_TokenListItem));
		if (!new_list.begin)
			return false;
		new_list.end_cap = new_list.begin + new_cap;

		// copy old data
		size_t old_size = (size_t)(list->end - list->begin);
		if (old_size)
			ft_memcpy(new_list.begin, list->begin, old_size * sizeof(FileParse_TokenListItem));
		new_list.end = new_list.begin + old_size;

		// copy new token
		ft_memcpy(new_list.end, token, sizeof(FileParse_TokenListItem));
		new_list.end++;

		// swap
		free(list->begin);
		*list = new_list;
	}
	return true;
}

bool	FileParse_IsStateValid(const FileParse_State* state)
{
	return state->_status == FileParse_Status_Success;
}

FileParse_State	FileParse_Parse(const char *file, const FileParse_Desc* desc)
{
	assert(file != NULL);
	assert(desc != NULL);
	
	FileParse_State 	state = { 0 };
	char				*line = NULL;
	int					fd;
	size_t				i, length, row;
	FileParse_TokenList	list = { 0 };

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (FileParse_State){ ._status = FileParse_Status_Error };
	row = 0;
	while (ft_get_next_line(fd, &line))
	{
		row++;
		i = 0;
		length = ft_strlen(line);
		while (i < length && FileParse_IsSpace(desc, line[i]))
			i++;
		// todo: comments
		while (i < length)
		{
			bool found = false;
		
			while (i < length && FileParse_IsSpace(desc, line[i]))
				i++;
			for (size_t j = 0; j < desc->token_count; j++)
			{
				size_t token_length = ft_strlen(desc->tokens[j].value);
				if (ft_strncmp(&line[i], desc->tokens[j].value, token_length) == 0)
				{
					if (!FileParse_TokenList_Push(&list, &(FileParse_TokenListItem){
						.t = {
							.type = desc->tokens[j].type,
							.value = (char*)desc->tokens[j].value,
							.row = row,
							.col = i,
						},
						.length = token_length,
					}))
					{
						free(list.begin);
						state._status = FileParse_Status_Error;
						close(fd);
						return state;
					}
					found = true;
					i += token_length;
					break ;
				}
			}
			if (!found)
			{
				size_t j = i;
				while (i < length && !FileParse_IsSpace(desc, line[i]) && !FileParse_IsSeparator(desc, line[i]))
					i++;
				if (j < i)
				{
					if (!FileParse_TokenList_Push(&list, &(FileParse_TokenListItem){
						.t = {
							.type = -1,
							.value = &line[j],
							.row = row,
							.col = j + 1,
						},
						.length = i - j,
					}))
					{
						free(list.begin);
						state._status = FileParse_Status_Error;
						close(fd);
						return state;
					}
				}
				// break;
			}
		}
		if (!desc->skip_newlines)
		{
			if (!FileParse_TokenList_Push(&list, &(FileParse_TokenListItem){
				.t = {
					.type = -1,
					.value = "\n",
					.row = row,
					.col = i + 1,
				},
				.length = 1,
			}))
			{
				free(list.begin);
				state._status = FileParse_Status_Error;
				close(fd);
				return state;
			}
		}
	}
	close(fd);
	
	state.count = (size_t)(list.end - list.begin);
	state.tokens = ft_calloc(state.count, sizeof(FileParse_Token));
	if (!state.tokens)
	{
		free(list.begin);
		state._status = FileParse_Status_Error;
		return state;
	}
	for (size_t i = 0; i < state.count; i++)
	{
		state.tokens[i].type = list.begin[i].t.type;
		state.tokens[i].row = list.begin[i].t.row;
		state.tokens[i].col = list.begin[i].t.col;
		state.tokens[i].value = ft_strndup(list.begin[i].t.value, list.begin[i].length);
	}
	return state;
}

void	FileParse_ClearState(FileParse_State* state)
{
	for (size_t i = 0; i < state->count; i++)
		free(state->tokens[i].value);
	free(state->tokens);
}

void	_ft_printf_create_hex_internal(char *s, char x, unsigned int nb, int alt, int length)
{
	int	caps = x == 'X' ? 55 : 87;

	if (alt)
	{
		s[0] = '0';
		s[1] = x;
	}
	int i = length - 1;
	while (nb > 0)
	{
		int digit = nb % 16;
        if (digit < 10)
			s[i] = digit + 48;
		else
			s[i] = digit + caps;
		i--;
		nb /= 16;
	}
	while (i >= (alt ? 2 : 0))
		s[i--] = '0';
}

/** The function _ft_printf_create_xX() writes the number fd in hexadecimal to the
 * file descriptor fd.
 * 
 * @returns The number of characters written. */
char	*_ft_printf_create_xX(char x, unsigned int nb, struct _libft_printf_specs *specs)
{
	int arg_length;
	int arg_start;
	char *s;

	GET_UNSIGNED_NUMBER_LENGTH(&arg_length, nb, 16, specs->info.precision, int);
	if (specs->flags.alt)
		arg_length += 2;
	s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
	if (!s)
		return (NULL);
	_ft_printf_create_hex_internal(s + arg_start, x, nb, specs->flags.alt, arg_length);
	return (s);
}

int	_ft_vsnprintf_internal(char* string, size_t maxlen, const char *format, va_list ap)
{
	unsigned char	*f;
	unsigned char	*lead_str_end;
	size_t			curlen;
	long			len;

	ft_memset(string, 0, maxlen);
	curlen = 0;
	f = lead_str_end = (unsigned char *)_ft_find_spec((const unsigned char *)format);
	len = min((const unsigned char *)lead_str_end - (const unsigned char *)format, (long)maxlen - 1);
	ft_strncat(string, format, len);
	curlen += len;
	while (*f != '\0' && curlen < maxlen)
	{
		if (*f != '%')
		{
			ft_strncat(string, (const char *)f++, 1);
			curlen++;
		}
		else
		{
			struct _libft_printf_specs specs = { 0 };

			FIND_FLAGS(f, specs);
			FIND_WIDTH(f, specs, ap);
			FIND_PRECISION(f, specs, ap);

			char	*s = NULL;
			DO_POSITIONAL(f, s, specs, ap);

			len = min(maxlen - 1 - curlen, (size_t)specs.info.width);
			ft_strncat(string, s, len);
			free(s);
			curlen += len;

			f++;
		}
	}
	return (curlen);
}

char	*_ft_printf_create_c(char c, struct _libft_printf_specs *specs)
{
	int		arg_length;
	int		arg_start;
	char	*s;
	
	arg_length = 1;
	s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
	if (!s)
		return (NULL);
	ft_memset(s + arg_start, c, arg_length);
	return (s);
}

void	_ft_printf_create_hex_internal(char *s, char x, unsigned int nb, int alt, int length);

/** The function _ft_printf_create_p() writes the address addr in hexadecimal
 * to the file descriptor fd.
 * @returns The number of characters written. */
char	*_ft_printf_create_p(size_t addr, struct _libft_printf_specs *specs)
{
	int		arg_length;
	int		arg_start;
	char	*s;

	if (addr)
	{
		GET_UNSIGNED_NUMBER_LENGTH(&arg_length, addr, 16, specs->info.precision, size_t);
		arg_length += 2;
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
		if (!s)
			return (NULL);
		_ft_printf_create_hex_internal(s + arg_start,  'x', addr, 1, arg_length);
	}
	else
	{
		arg_length = (sizeof(LIBFT_PRINTF_NULL_PTR) - 1); // Remove null character
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
		if (!s)
			return (NULL);
		ft_memcpy(s + arg_start, LIBFT_PRINTF_NULL_PTR, arg_length);
	}
	return (s);
}

#define _ft_printf__abs(x)	_Generic((x),	\
	int:       ft_abs,						\
	long:      ft_labs,						\
	long long: ft_llabs						\
	)(x)

#define _SIGNED_CONVERSION_DEF(_name, _type)										\
	char	*_ft_printf_create_##_name(_type nb, struct _libft_printf_specs *specs)	\
	{																				\
		int arg_length;																\
		int arg_start;																\
		char *s;																	\
		GET_NUMBER_LENGTH(&arg_length, nb, 10, specs->info.precision, _type);		\
		int	showfront = (nb >= 0 && (specs->flags.space || specs->flags.showsign));	\
		arg_length += showfront;													\
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);			\
		if (!s)																		\
			return (NULL);															\
		MAKE_NUMBER_STRING(s + arg_start, _type, _ft_printf__abs, nb, arg_length);	\
		if (showfront)																\
		{																			\
			if (specs->flags.space)													\
				s[0] = ' ';															\
			else if (specs->flags.showsign)											\
				s[0] = '+';															\
		}																			\
		return (s);																	\
	}

_SIGNED_CONVERSION_DEF(di, int)
_SIGNED_CONVERSION_DEF(l, long)
_SIGNED_CONVERSION_DEF(ll, long long)

/** The function _ft_printf_create_s() writes the string pointed to by str to the file
 * descriptor fd.
 * @returns The number of characters written. */
char	*_ft_printf_create_s(const char *str, struct _libft_printf_specs *specs)
{
	int arg_length;
	int arg_start;
	char *s;

	if (str)
	{
		if (specs->info.precision > -1)
			arg_length = min((int)ft_strlen(str), specs->info.precision);
		else
			arg_length = ft_strlen(str);
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
		if (!s)
			return (NULL);
		ft_memcpy(s + arg_start, str, arg_length);
	}
	else
	{
		arg_length = sizeof(LIBFT_PRINTF_NULL_STRING) - 1; // Remove the null character
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);
		if (!s)
			return (NULL);
		ft_memcpy(s + arg_start, LIBFT_PRINTF_NULL_STRING, arg_length);
	}
	return (s);
}

int _ft_vdprintf_internal(int fd, const char *format, va_list ap)
{
	int				done;
	unsigned char	*f;
	unsigned char	*lead_str_end;

	done = 0;
	f = lead_str_end = (unsigned char *)_ft_find_spec((const unsigned char *)format);
	if ((done = write(fd, format, (const unsigned char *)lead_str_end - (const unsigned char *)format)) < 0)
		return -1;
	while (*f != '\0')
	{
		if (*f != '%')
			done += write(fd, f++, 1);
		else
		{
			struct _libft_printf_specs specs = { 0 };

			FIND_FLAGS(f, specs);
			FIND_WIDTH(f, specs, ap);
			FIND_PRECISION(f, specs, ap);

			char	*s = NULL;
			DO_POSITIONAL(f, s, specs, ap);
			write(fd, s, specs.info.width);
			free(s);
			done += specs.info.width;
			f++;
		}
	}
	return (done);
}

#define _UNSIGNED_CONVERSION_DEF(_name, _type)											\
	char	*_ft_printf_create_##_name(_type nb, struct _libft_printf_specs *specs)		\
	{																					\
		int arg_length;																	\
		int arg_start;																	\
		char *s;																		\
																						\
		GET_UNSIGNED_NUMBER_LENGTH(&arg_length, nb, 10, specs->info.precision, _type);	\
		s = _ft_printf_create_string_helper(specs, arg_length, &arg_start);				\
		if (!s)																			\
			return (NULL);																\
		MAKE_UNSIGNED_NUMBER_STRING(s + arg_start, nb, arg_length, _type);				\
		return (s);																		\
	}

_UNSIGNED_CONVERSION_DEF(u, unsigned int)
_UNSIGNED_CONVERSION_DEF(ul, unsigned long)
_UNSIGNED_CONVERSION_DEF(ull, unsigned long long)

int	_ft_vdprintf_internal(int fd, const char *format, va_list ap);

int	ft_dprintf(int fd, const char *restrict format, ...)
{
	int		done;
	va_list	ap;

	va_start(ap, format);
	done = _ft_vdprintf_internal(fd, format, ap);
	va_end(ap);
	return (done);
}

int	_ft_vsnprintf_internal(char *s, size_t maxlen, const char *f, va_list ap);

int	ft_vsnprintf(char* str, size_t size, const char* restrict format, va_list ap)
{
	int		done;
	va_list	ap_copy;

	va_copy(ap_copy, ap);
	done = _ft_vsnprintf_internal(str, size, format, ap_copy);
	va_end(ap_copy);
	return (done);
}

int	_ft_vdprintf_internal(int fd, const char *format, va_list ap);

int	ft_printf(const char *restrict format, ...)
{
	int		done;
	va_list	ap;

	va_start(ap, format);
	done = _ft_vdprintf_internal(STDOUT_FILENO, format, ap);
	va_end(ap);
	return (done);
}

int	_ft_vsnprintf_internal(char *s, size_t maxlen, const char *f, va_list ap);

int	ft_snprintf(char* str, size_t maxlen, const char *restrict format, ...)
{
	int		done;
	va_list	ap;

	va_start(ap, format);
	done = _ft_vsnprintf_internal(str, maxlen, format, ap);
	va_end(ap);
	return (done);
}

static char	*_ft_gnl_join(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	int		len;
	char	*s;

	if (!s1 && !s2)
		return (0);
	s1_len = s1 ? ft_strlen(s1) : 0;
	s2_len = s2 ? ft_strlen(s2) : 0;
	len = s1_len + s2_len;
	s = malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	ft_memmove(s, s1, s1_len);
	ft_memmove(s + s1_len, s2, s2_len);
	s[len] = '\0';
	free((char *)s1);
	return (s);
}

static int	_ft_gnl_find_endl(char *s)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		if (s[i++] == '\n')
			return (1);
	return (0);
}

static char	*_ft_gnl_save_string(char *str)
{
	char	*dest;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	if (!(dest = malloc(sizeof(char) * (ft_strlen(str) - i) + 1)))
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		dest[j++] = str[i++];
	dest[j] = '\0';
	free(str);
	return (dest);
}

static char	*_ft_gnl_create_line(char *str)
{
	char	*line;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!(line = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	ft_get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*str[256];
	int			nb_read;

	if (fd < 0 || !line || LIBFT_BUFFERSIZE <= 0)
		return (-1);
	if (!(buffer = malloc(sizeof(char) * LIBFT_BUFFERSIZE + 1)))
		return (-1);
	nb_read = 1;
	while (!_ft_gnl_find_endl(str[fd]) && nb_read != 0)
	{
		if ((nb_read = read(fd, buffer, LIBFT_BUFFERSIZE)) == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[nb_read] = '\0';
		str[fd] = _ft_gnl_join(str[fd], buffer);
	}
	free(buffer);
	*line = _ft_gnl_create_line(str[fd]);
	str[fd] = _ft_gnl_save_string(str[fd]);
	return (nb_read || **line);
}

void	ft_lstadd_back(t_list **lst, t_list *new_elem)
{
	t_list	*temp;

	temp = *lst;
	if (temp == NULL)
		*lst = new_elem;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_elem;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = malloc(sizeof(*elem));
	if (!elem)
		return (NULL);
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	if (!temp)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !(*lst))
		return ;
	while (*lst != NULL)
	{
		if (del)
			del((*lst)->content);
		temp = (*lst);
		(*lst) = (*lst)->next;
		free(temp);
	}
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	temp = lst;
	while (temp != NULL)
	{
		if (f)
			f(temp->content);
		temp = temp->next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*temp;

	new_list = NULL;
	while (lst != NULL)
	{
		temp = ft_lstnew(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&new_list, del);
			break ;
		}
		ft_lstadd_back(&new_list, temp);
		lst = lst->next;
	}
	return (new_list);
}

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*temp;

	size = 0;
	temp = lst;
	while (temp != NULL)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst != NULL && new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}

double	ft_fabs(double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	ft_abs(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

long	ft_labs(long x)
{
	if (x < 0)
		return (-x);
	return (x);
}

long long	ft_llabs(long long i)
{
	if (i < 0)
		return (-i);
	return (i);
}

long double	ft_fabsl(long double x)
{
	if (x < 0)
		return (-x);
	return (x);
}

float	ft_fabsf(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (n--)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	char	*d;
	char	*s;

	if (!src && !dst)
		return (NULL);
	d = (char *)dst;
	s = (char *)src;
	while (n-- > 0)
		*d++ = *s++;
	return (dst);
}

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n-- > 0)
	{
		*d++ = *s;
		if (*s++ == (unsigned char)c)
			return (d);
	}
	return (NULL);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
	{
		if (*str == (unsigned char)c)
			return (str);
		str++;
	}
	return (NULL);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
		*ptr++ = c;
	return (s);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (!dest && !src)
		return (NULL);
	d = (char *)dest;
	s = (char *)src;
	i = 0;
	if (d < s)
		while (n-- > 0)
			*d++ = *s++;
	else
		while (++i <= n)
			d[n - i] = s[n - i];
	return (dest);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	char	*s;
	size_t	ss;

	s = s1;
	s1 += ft_strlen(s1);
	ss = ft_strnlen(s2, n);
	s1[ss] = '\0';
	ft_memcpy(s1, s2, ss);
	return (s);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0' || needle == NULL)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < n)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && i + j < n)
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

size_t	ft_strcspn(const char *s1, const char *s2)
{
	const char	*s;
	const char	*c;

	s = s1;
	while (*s1)
	{
		c = s2;
		while (*c)
		{
			if (*s1 == *c)
				break ;
			c++;
		}
		if (*c)
			break ;
		s1++;
	}
	return (s1 - s);
}

char	*ft_strjoin_3(const char *s1, const char *s2, const char *s3)
{
	char			*dst;

	if (!s1 || !s2 || !s3)
		return (NULL);
	dst = malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3)) + 1);
	if (!dst)
		return (NULL);
	return (ft_strcat(ft_strcat(ft_strcpy(dst, s1), s2), s3));
}

size_t	ft_len_to_char(const char *s, char c)
{
	int	n;

	n = 0;
	while (s[n] && s[n] != c)
		n++;
	return (n);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	if (!dst || !src)
		return (0);
	i = 0;
	if (size > 0)
	{
		while (--size && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static int	ft_wordslen(const char *s, char c, int i)
{
	int	n;

	n = 0;
	while (s[i++] != c && s[i] != '\0')
		n++;
	return (n);
}

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	words;
	int	j;

	i = 0;
	words = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == c && j > 0) || (s[i] != c && s[i + 1] == '\0'))
		{
			words++;
			j = 0;
		}
		else if (s[i] != c)
			j++;
		i++;
	}
	return (words);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**split;
	int		n;
	int		i[2];

	i[1] = 0;
	i[0] = 0;
	n = 0;
	split = malloc(8 * (ft_countwords(s, c) + 1));
	if (!s || !c || !split)
		return (NULL);
	while (ft_countwords(s, c) > n)
	{
		i[1] = 0;
		while (s[i[0]] == c)
			i[0]++;
		split[n] = malloc(ft_wordslen(s, c, i[0]) + 2);
		if (!split[n])
			return (NULL);
		while (s[i[0]] != c && s[i[0]] != '\0')
			split[n][i[1]++] = s[i[0]++];
		split[n++][i[1]] = '\0';
	}
	split[n] = NULL;
	return (split);
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (i < maxlen && s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char			*d;

	if (!s1 || !s2)
		return (NULL);
	d = malloc(sizeof(*d) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!d)
		return (NULL);
	return (ft_strcat(ft_strcpy(d, s1), s2));
}

char	*ft_strcat(char *restrict s1, const char *restrict s2)
{
	ft_strcpy(s1 + ft_strlen(s1), s2);
	return (s1);
}

size_t	ft_len_to_space(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n] && !ft_isspace(s[n]))
		n++;
	return (n);
}

static unsigned int	words(const char *s, char c)
{
	int		i;
	int		words;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	words = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			words++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (words);
}

static int	len_to_sep(const char *s, char c, unsigned int i)
{
	int		len;

	len = 0;
	while (s[i + len] && s[i + len] != c)
		len++;
	return (len);
}

static char	**free_tab(void **tab, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	**init_split(const char *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	return (malloc(sizeof(*tab) * (words(s, c) + 1)));
}

char	**ft_split(const char *s, char c)
{
	char			**tab;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	tab = init_split(s, c);
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (i < words(s, c))
	{
		while (s[j] == c && s[j])
			j++;
		tab[i] = malloc(sizeof(*tab[i]) * len_to_sep(s, c, j) + 1);
		if (!tab[i])
			return (free_tab((void **)tab, i));
		k = 0;
		while (s[j] && s[j] != c)
			if (s[j] != c)
				tab[i][k++] = s[j++];
		tab[i++][k] = '\0';
	}
	tab[i] = NULL;
	return (tab);
}

char	*ft_strrchr(const char *s, int c)
{
	int		len;

	len = ft_strlen((char *)s);
	while (len && s[len] != (char)c)
		len--;
	if (s[len] == (char)c)
		return ((char *)&s[len]);
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s)
		return (NULL);
	str = malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_str_toupper(char *s)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (ft_islower(s[i]))
			s[i] = (char)ft_toupper(s[i]);
		i++;
	}
}

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*d;
	unsigned int	i;

	if (!s)
		return (NULL);
	d = malloc(sizeof(*d) * ft_strlen(s) + 1);
	if (!d)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		d[i] = f(i, s[i]);
		i++;
	}
	d[i] = '\0';
	return (d);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	size_s;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size_s = ft_strlen(s1);
	while (size_s && ft_strchr(set, s1[size_s]))
		size_s--;
	dest = ft_substr(s1, 0, size_s + 1);
	return (dest);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*d;

	len = ft_strnlen(s, n);
	d = malloc(sizeof(*d) * len + 1);
	if (!d)
		return (NULL);
	ft_memcpy(d, s, len);
	d[len] = '\0';
	return d;
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = 0;
	while (dst[i])
		i++;
	while (src[len])
		len++;
	if (size <= i)
		return (size + len);
	while (src[j] != '\0' && j + i < size - 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (len + i);
}

void	ft_str_tolower(char *s)
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (ft_isupper(s[i]))
			s[i] = (char)ft_tolower(s[i]);
		i++;
	}
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*d;

	len = ft_strlen(s) + 1;
	d = malloc(sizeof(*d) * len);
	if (!d)
		return (NULL);
	return (ft_memcpy(d, s, len));
}

/*
int	ft_atoi(const char *nptr)
{
	int		sign;
	int		result;

	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	sign = 1;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	result = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + *nptr - 48;
		nptr++;
	}
	return (result * sign);
}
*/

int	ft_atoi(const char *s)
{
	int		digit;
	int		sign;
	int		result;

	if (!s)
		return (0);
	while (*s == ' ')
		s++;
	sign = 1;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	result = 0;
	while (*s >= '0' && *s <= '9')
	{
		digit = *s++ - 48;
		if (result * sign > INT32_MAX / 10
			|| ((sign == 1 && result >= 214748364 && digit >= 7)))
			return (INT32_MAX);
		if (result * sign < INT32_MIN / 10
			|| ((sign == -1 && result >= 214748364 && digit >= 8)))
			return (INT32_MIN);
		result = result * 10 + digit;
	}
	return (result * sign);
}

static int	_ft_itoa_digits(unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

static int	_ft_itoa_get_nb(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static char	*_ft_itoa_create_string(int len, int nb, int n)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(*dest) * len + 1 + (nb < 0));
	if (dest)
	{
		if (n < 0)
		{
			dest[i] = '-';
			len++;
		}
		i = len - 1;
		while (nb >= 10)
		{
			dest[i] = nb % 10 + 48;
			nb /= 10;
			i--;
		}
		dest[i] = nb % 10 + 48;
		dest[len] = '\0';
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	unsigned int	len;
	unsigned int	nb;

	nb = _ft_itoa_get_nb(n);
	len = _ft_itoa_digits(nb);
	return (_ft_itoa_create_string(len, nb, n));
}

char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	size_t	size;

	size = ft_strnlen(s2, n);
	if (size != n)
		ft_memset(s1 + size, '\0', n - size);
	return (ft_memcpy(s1, s2, size));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

uint64_t	ft_timer_now(void)
{
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);

	return ts.tv_sec * FT_NS_PER_SECOND + ts.tv_nsec;
}

void	ft_timer_reset(ft_timer* timer)
{
	timer->start = ft_timer_now();
}

uint64_t	ft_timer_elapsed_ns(ft_timer* timer)
{
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);

	const uint64_t now = ts.tv_sec * FT_NS_PER_SECOND + ts.tv_nsec;
	return now - timer->start;
}

uint64_t	ft_timer_elapsed_ms(ft_timer* timer)
{
	return ft_timer_elapsed_ns(timer) / FT_NS_PER_MS;
}

uint64_t	ft_timer_elapsed_seconds(ft_timer* timer)
{
	return ft_timer_elapsed_ns(timer) / FT_NS_PER_SECOND;
}

void*	ft_allocator_allocate(const ft_allocator* alloc, size_t n)
{
	return malloc(n * alloc->sizeof_type);
}

void	ft_allocator_deallocate(const ft_allocator* alloc, void *p, size_t n)
{
	(void)alloc;
	(void)n;
	free(p);
}

void	ft_allocator_construct(const ft_allocator* alloc, void *p, const void* value)
{
	ft_memcpy(p, value, alloc->sizeof_type);
}

void	ft_allocator_destroy(const ft_allocator* alloc, void *p)
{
	(void)alloc;
	(void)p;
}

size_t	ft_allocator_max_size(const struct ft_allocator* alloc)
{
	return SIZE_MAX / alloc->sizeof_type;
}

#define ft_def(__a, __b) (((__a) == 0) ? (__b) : (__a))

#define POINTER_ADD(__v, __p, __n) _POINTER_ADD((__p), ((__v)->alloc.sizeof_type), (__n))
#define POINTER_SUB(__v, __p, __n) _POINTER_SUB((__p), ((__v)->alloc.sizeof_type), (__n))
#define POINTER_INC(__v, __p) ((__p) = (POINTER_ADD(__v, __p, 1)))
#define POINTER_DEC(__v, __p) ((__p) = (POINTER_SUB(__v, __p, 1)))

static inline ft_iterator	_make_iter(size_t sizeof_type, void* p, IteratorType type)
{
	return (ft_iterator){
		._p = p,
		._sizeof_type = sizeof_type,
		._type = type,
	};
}

static void	_swap(void **a, void **b)
{
	void* tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

ft_allocator	_ft_allocator_defaults(const ft_allocator* alloc)
{
	assert(alloc->sizeof_type != 0);

	ft_allocator	def = *alloc;

	def.max_size = ft_def(def.max_size, ft_allocator_max_size);
	def.allocate = ft_def(def.allocate, ft_allocator_allocate);
	def.deallocate = ft_def(def.deallocate, ft_allocator_deallocate);
	def.construct = ft_def(def.construct, ft_allocator_construct);
	def.destroy = ft_def(def.destroy, ft_allocator_destroy);
	return def;
}

void	_construct_at_end(ft_vector* vector, size_t n, const void* value)
{
	assert(ft_vector_size(vector) + n <= ft_vector_capacity(vector));
	while (n-- > 0)
	{
		vector->alloc.construct(&vector->alloc, vector->end, value);
		POINTER_INC(vector, vector->end);
	}
}

void	_construct_at_end_iter(ft_vector* vector, ft_iterator first, ft_iterator last, size_t n)
{
	assert(ft_vector_size(vector) + n <= ft_vector_capacity(vector));

	if (n == 0)
		return ;
	for (; !FT_ITER_EQ(first, last); FT_ITER_INC(first))
	{
		vector->alloc.construct(&vector->alloc, vector->end, FT_ITER_REF(first));
		POINTER_INC(vector, vector->end);
	}
}

void	_destruct_at_end(ft_vector* vector, void* new_last)
{
	void* soon_to_be_end = vector->end;
	while (new_last != soon_to_be_end)
	{
		POINTER_DEC(vector, soon_to_be_end);
		vector->alloc.destroy(&vector->alloc, soon_to_be_end);
	}
	vector->end = new_last;
}

void	_vallocate(ft_vector* vector, size_t n)
{
	assert(n <= vector->alloc.max_size(&vector->alloc));

	vector->begin = vector->end = vector->alloc.allocate(&vector->alloc, n);
	vector->end_cap = POINTER_ADD(vector, vector->begin, n);
}

void	_ft_vector_swap(ft_vector *_v, ft_vector *_x)
{
	ft_allocator tmp = _v->alloc;
	_v->alloc = _x->alloc;
	_x->alloc = tmp;

	_swap(&_v->begin, &_x->begin);
	_swap(&_v->end, &_x->end);
	_swap(&_v->end_cap, &_x->end_cap);
}

size_t	_ft_vector_recommend(const ft_vector *vector, size_t new_size)
{
	size_t max_size = vector->alloc.max_size(&vector->alloc);
	
	assert(new_size < vector->alloc.max_size(&vector->alloc));
    const size_t cap = ft_vector_capacity(vector);
    if (cap >= max_size / 2)
        return max_size;
    return max(2 * cap, new_size);
}

ft_vector	ft_vector_create(const ft_vector_desc* desc)
{
	return (ft_vector){
		.alloc = _ft_allocator_defaults(&desc->alloc),
		.begin = NULL,
		.end = NULL,
		.end_cap = NULL,
	};
}

void	ft_vector_destroy(ft_vector* vector)
{
	if (vector->begin)
	{
		ft_vector_clear(vector);
		vector->alloc.deallocate(&vector->alloc, vector->begin, ft_vector_capacity(vector));
		vector->begin = vector->end = vector->end_cap = NULL;
	}
}

void*	ft_vector_data(const ft_vector* vector)
{
	return vector->begin;
}

void*	ft_vector_at(const ft_vector* vector, size_t n)
{
	assert(n < ft_vector_size(vector));
	return POINTER_ADD(vector, vector->begin, n);
}

ft_iterator	ft_vector_begin(const ft_vector* vector)
{
	return _make_iter(vector->alloc.sizeof_type, vector->begin, IteratorType_Random);
}

ft_iterator	ft_vector_end(const ft_vector* vector)
{
	return _make_iter(vector->alloc.sizeof_type, vector->end, IteratorType_Random);
}

ft_iterator	ft_vector_rbegin(const ft_vector* vector)
{
	return _make_iter(vector->alloc.sizeof_type, vector->end, IteratorType_Reverse);
}

ft_iterator	ft_vector_rend(const ft_vector* vector)
{
	return _make_iter(vector->alloc.sizeof_type, vector->begin, IteratorType_Reverse);
}

size_t	ft_vector_max_size(const ft_vector* vector)
{
	return vector->alloc.max_size(&vector->alloc);
}

size_t	ft_vector_size(const ft_vector* vector)
{
	return ((char*)vector->end - (char*)vector->begin) / vector->alloc.sizeof_type;
}

size_t	ft_vector_capacity(const ft_vector* vector)
{
	return ((char*)vector->end_cap - (char*)vector->begin) / vector->alloc.sizeof_type;
}

size_t	ft_vector_empty(const ft_vector* vector)
{
	return vector->begin == vector->end;
}

void	ft_vector_reserve(ft_vector* vector, size_t n)
{
	if (n > ft_vector_capacity(vector))
	{
		size_t size = ft_vector_size(vector);
		ft_vector v = ft_vector_create(&(ft_vector_desc){
			.alloc = vector->alloc,
		});
		_vallocate(&v, n);

		ft_iterator begin = ft_vector_begin(vector);
		ft_iterator up_to = FT_ITER_ADD_NEW(begin, size);

		_construct_at_end_iter(&v, begin, up_to, size);

		_ft_vector_swap(vector, &v);
		ft_vector_destroy(&v);
	}
}

void	ft_vector_assign(ft_vector* vector, ft_iterator first, ft_iterator last)
{
	ft_vector_clear(vector);
	for (; !FT_ITER_EQ(first, last); FT_ITER_INC(first))
		ft_vector_push_back(vector, FT_ITER_REF(first));
}

void	ft_vector_push_back(ft_vector* vector, const void* value)
{
	if (vector->end != vector->end_cap)
		_construct_at_end(vector, 1, value);
	else
	{
		ft_vector v = ft_vector_create(&(ft_vector_desc){
			.alloc = vector->alloc,
		});

		ft_vector_reserve(&v, _ft_vector_recommend(vector, ft_vector_size(vector) + 1));
		ft_vector_assign(&v, ft_vector_begin(vector), ft_vector_end(vector));
		v.alloc.construct(&v.alloc, v.end, value);
		POINTER_INC(vector, v.end);
		_ft_vector_swap(vector, &v);

		ft_vector_destroy(&v);
	}
}

void	ft_vector_clear(ft_vector* vector)
{
	_destruct_at_end(vector, vector->begin);
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (s)
		while (*s)
			ft_putchar_fd(*s++, fd);
}

void	ft_putnbr(int n)
{
	ft_putnbr_fd(n, STDOUT_FILENO);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT32_MIN)
	{
		ft_putnbr_fd(-214748364, fd);
		ft_putchar_fd('8', fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n < 10)
		ft_putchar_fd(n + 48, fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

void	ft_putendl(const char *restrict s)
{
	ft_putendl_fd(s, STDOUT_FILENO);
}

void	ft_putendl_fd(const char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_putchar(char c)
{
	ft_putchar_fd(c, STDOUT_FILENO);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr(const char *restrict s)
{
	ft_putstr_fd(s, STDOUT_FILENO);
}

#endif // LIBFT_IMPL_INCLUDED
#endif // LIBFT_IMPL
