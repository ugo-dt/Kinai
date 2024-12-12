/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugdaniel <ugdaniel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 12:54:59 by ugdaniel          #+#    #+#             */
/*   Updated: 2024/12/12 17:18:17 by ugdaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Kinai/Core/Core.hpp"

namespace Kinai
{

template <class Tp> struct is_token_type : std::false_type {};

template <class Tp, typename std::enable_if<is_token_type<Tp>::value, bool>::type = 0>
struct TokenBase
{
	typedef Tp						token_type;
	typedef typename std::size_t	size_type;
	typedef typename std::ptrdiff_t	difference_type;
	typedef typename std::string	string_type;

	TokenBase(Tp t, string_type w, uint32_t r, uint32_t c)
		: type(t), text(w), row(r), col(c) {}
	
	token_type	type;
	string_type	text;
	uint32_t	row, col;
};

template <class Token>
class Parser
{
public:
	typedef Token													value_type;
    typedef value_type&												reference;
    typedef const value_type&										const_reference;
	typedef value_type*												pointer;
    typedef const value_type*										const_pointer;
	typedef typename Token::token_type								token_type;
	typedef typename Token::size_type								size_type;
	typedef typename Token::difference_type							difference_type;
	typedef typename Token::string_type								string_type;
	typedef typename std::vector<value_type>::iterator				iterator;
	typedef const typename std::vector<value_type>::const_iterator	const_iterator;

public:
	Parser(const std::string& filepath);
	
	static KN_INLINE string_type	YELLOW(const string_type &s);
	static KN_INLINE string_type	CYAN(const string_type &s);
	static KN_INLINE string_type	MAGENTA(const string_type &s);
	static KN_INLINE string_type	RED(const string_type &s);
	static KN_INLINE string_type	WHITE(const string_type &s);

	static constexpr KN_INLINE bool	iterator_equals(const_iterator &it, const token_type &t)
		{ return (*it).type == t; }
	static constexpr KN_INLINE bool	iterator_equals(const_iterator &it, const string_type &s)
		{ return (*it).text == s; }

protected:
	string_type				_filepath;
	std::vector<value_type>	_tokens;

protected:
	KN_INLINE iterator			_make_iter(pointer p);
	KN_INLINE const_iterator	_make_iter(pointer p) const;
	KN_INLINE iterator			_make_iter(size_t pos);
	KN_INLINE const_iterator	_make_iter(size_t pos) const;
	KN_INLINE bool				_is_token(size_t pos, const token_type &t);

	KN_INLINE string_type	_make_error_string(const string_type &error);
	KN_INLINE string_type	_make_error_string(const_iterator& error_it, const string_type &error);
	KN_INLINE string_type	_make_warning_string(const string_type &warning);
	KN_INLINE string_type	_make_warning_string(const_iterator& warning_it, const string_type &warning);
	KN_INLINE string_type	_make_note_string(const_iterator& note_it, const string_type &note);

	KN_INLINE void	_throw_invalid_argument(const char *) KN_NORETURN;
	KN_INLINE void	_throw_parser(const string_type &error) KN_NORETURN;
	KN_INLINE void	_throw_parser(const_iterator& it, const string_type &error) KN_NORETURN;
	KN_INLINE void	_throw_parser_with_note(const_iterator& it, const string_type &error, const_iterator& note_it, const string_type &note) KN_NORETURN;

	static KN_INLINE string_type	WHITE(const_iterator& it);
	static KN_INLINE string_type	WHITE(const string_type &s, const_iterator& it);
	static KN_INLINE string_type	WHITE(const string_type &s, const_iterator& it, const string_type &name);

private:
	KN_INLINE string_type	_make_log_string_impl(const string_type &log_name, const string_type &log);
	KN_INLINE string_type	_make_log_string_impl(const_iterator& it, const string_type &log_name, const string_type &log);
};

template <class Token>
KN_NORETURN KN_INLINE void
Parser<Token>::_throw_invalid_argument(const char *arg)
{
	throw std::invalid_argument(arg);
}

template <class Token>
Parser<Token>::Parser(const std::string& filepath)
	: _filepath(filepath)
{
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::YELLOW(const string_type &s)
{
	return "\033[93m" + string_type(s) + "\033[39m";
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::CYAN(const string_type &s)
{
	return "\033[96m" + string_type(s) + "\033[39m";
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::MAGENTA(const string_type &s)
{
	return "\033[95m" + string_type(s) + "\033[39m";
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::RED(const string_type &s)
{
	return "\033[91m" + string_type(s) + "\033[39m";
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::WHITE(const string_type &s)
{
	return "\033[97m" + string_type(s) + "\033[39m";
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::WHITE(const_iterator& it)
{
	return "\033[97m" + (*it).text + "\033[39m";
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::WHITE(const string_type &s, const_iterator& it)
{
	return "\033[97m" + string_type(s) + (*it).text + "\033[39m";
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::WHITE(const string_type &s, const_iterator& it, const string_type &name)
{
	return "\033[97m" + string_type(s) + (*it).text + (name.empty() ? "" : " ") + name + "\033[39m";
}

template <class Tp>
KN_NODISCARD KN_INLINE typename Parser<Tp>::iterator
Parser<Tp>::_make_iter(pointer p)
{
	return iterator(p);
}

template <class Tp>
KN_NODISCARD KN_INLINE typename Parser<Tp>::const_iterator
Parser<Tp>::_make_iter(pointer p) const
{
	return const_iterator(p);
}

template <class Tp>
KN_NODISCARD KN_INLINE typename Parser<Tp>::iterator
Parser<Tp>::_make_iter(size_t pos)
{
	return _tokens.begin() + pos;
}

template <class Tp>
KN_NODISCARD KN_INLINE typename Parser<Tp>::const_iterator
Parser<Tp>::_make_iter(size_t pos) const
{
	return _tokens.cbegin() + pos;
}

template <class Tp>
KN_INLINE bool
Parser<Tp>::_is_token(size_t pos, const token_type &t)
{
	return (_make_iter(pos)) == t;
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::_make_log_string_impl(const_iterator& it, const string_type &log_type, const string_type &arg)
{
	return string_type(_filepath + ":" +
		std::to_string((*it).row) + ":" +
		std::to_string((*it).col) + ": " +
		log_type + "\033[39m " + arg
	);
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::_make_log_string_impl(const string_type &log_type, const string_type &arg)
{
	return string_type(_filepath + ": " + log_type + "\033[39m " + arg);
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::_make_error_string(const_iterator& error_it, const string_type &error)
{
	return _make_log_string_impl(error_it, RED("error:"), error);
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::_make_error_string(const string_type &error)
{
	return _make_log_string_impl(RED("error:"), error);
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::_make_warning_string(const_iterator& warning_it, const string_type &warning)
{
	return _make_log_string_impl(warning_it, MAGENTA("warning:"), warning);
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::_make_warning_string(const string_type &warning)
{
	return _make_log_string_impl(MAGENTA("warning:"), warning);
}

template <class Token>
KN_NODISCARD KN_INLINE typename Parser<Token>::string_type
Parser<Token>::_make_note_string(const_iterator& note_it, const string_type &note)
{
	return _make_log_string_impl(note_it, CYAN("note:"), note);
}

template <class Token>
KN_NORETURN KN_INLINE void
Parser<Token>::_throw_parser(const_iterator& it, const string_type &error)
{
	_throw_invalid_argument(_make_error_string(it, error).c_str());
}

template <class Token>
KN_NORETURN KN_INLINE void
Parser<Token>::_throw_parser(const string_type &error)
{
	_throw_invalid_argument(_make_error_string(error).c_str());
}

template <class Token>
KN_NORETURN KN_INLINE void
Parser<Token>::_throw_parser_with_note(
	const_iterator& it, const string_type &error,
	const_iterator& note_it, const string_type &note)
{
	_throw_invalid_argument(string_type(_make_error_string(it, error) + '\n' + _make_note_string(note_it, note)).c_str());
}

// trim from start (in place)
static KN_INLINE void	ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
}

// trim from end (in place)
static KN_INLINE void	rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

// trim from both ends (in place)
static KN_INLINE void	trim(std::string &s)
{
    rtrim(s);
    ltrim(s);
}

static KN_INLINE std::string	str_toupper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::toupper(c); });
    return s;
}

} // Kinai
