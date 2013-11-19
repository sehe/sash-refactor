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

#ifndef SASH_MATH_LEXER_DEF_HPP
#define SASH_MATH_LEXER_DEF_HPP

#include "lexer.hpp"

namespace sash{
namespace math{

// Namespace shortcut.
namespace lex = boost::spirit::lex;

template <typename Lexer>
tokens<Lexer>::tokens()
{
	// Operators.
	add = "\\+";
	sub = "\\-";
	mul = "\\*";
	div = "\\\\";

	lparen = "\\(";
	rparen = "\\)";

	// Values.
	unsigned_digit = "[0-9]+";	

	// White spaces.
	ws = "[ \\t\\n]+";

	// The token must be added in priority order.
	this->self += mul | div | add | sub;
	this->self += unsigned_digit;
	this->self += lparen | rparen;
	this->self += ws 		[ lex::_pass = lex::pass_flags::pass_ignore ];
}

}} // namespace sash::math

#endif // SASH_MATH_LEXER_DEF_HPP
