/*
	Copyright (C) 2013 by Pierre Talbot <ptalbot@hyc.io>
	Part of the Battle for Wesnoth Project http://www.wesnoth.org/

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY.

	See the COPYING file for more details.
*/

#ifndef SASH_MATH_LEXER_HPP
#define SASH_MATH_LEXER_HPP

#include <boost/spirit/include/lex_lexertl.hpp>

namespace sash{
namespace math{

// Namespace shortcut.
namespace lex = boost::spirit::lex;

// Token definition base, defines all tokens for the base grammar below
template <typename Lexer>
struct tokens : lex::lexer<Lexer>
{
public:
	// Tokens with no attributes.
	lex::token_def<lex::omit> add, sub, mul, div;
	lex::token_def<lex::omit> lparen, rparen, ws;

	// Attributed tokens. (If you add a new type, don't forget to add it 
	// to the lex::lexertl::token definition too below).
	lex::token_def<std::size_t> unsigned_digit;

	tokens();
};

namespace detail{
// Some typedef for the use of the lexertl engine.
template <class BaseIterator>
struct lexer_helper
{
	typedef BaseIterator base_iterator_type;

	typedef lex::lexertl::token<
		base_iterator_type, boost::mpl::vector<lex::omit, std::size_t> 
	> token_type;

	typedef lex::lexertl::actor_lexer<token_type> type;
};

// iterator type used to expose the underlying input stream
typedef std::string::const_iterator lexer_base_iterator_type;

// We use the default lexer engine.
typedef lexer_helper<lexer_base_iterator_type>::type lexer_type;

} // namespace detail

typedef tokens<detail::lexer_type> tokens_type;

}} // namespace sash::math

#endif // SASH_MATH_LEXER_HPP