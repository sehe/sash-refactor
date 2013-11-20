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

#ifndef SASH_MATH_PARSER_HPP
#define SASH_MATH_PARSER_HPP

#include "ast.hpp"
#include "lexer.hpp"

#include <boost/spirit/include/qi.hpp>

namespace sash{
namespace math{

namespace bs = boost::spirit;
namespace qi = boost::spirit::qi;

// Grammar definition, define a little part of the SQL language.
template <typename Iterator>
struct grammar 
	: qi::grammar<Iterator, ast::expression()>
{
	typedef Iterator iterator_type;

	template <typename TokenDef>
	grammar(TokenDef const& tok);

private:
	ast::expression arithmetic_expr;

    template <typename Arg> using rule = qi::rule<iterator_type, Arg()>;
	rule<ast::expression> expression;
	rule<ast::add_op>     add_expr;
	rule<ast::sub_op>     sub_expr;
	rule<ast::mul_op>     mul_expr;
	rule<ast::div_op>     div_expr;
	rule<ast::usub_op>    neg_expr;
	rule<ast::expression> term;
	rule<ast::expression> factor;
};

// this is the iterator type exposed by the lexer 
typedef tokens_type::iterator_type token_iterator_type;

// this is the type of the grammar to parse
typedef grammar<token_iterator_type> grammar_type;

}} // namespace sash::math
#endif // SASH_MATH_PARSER_HPP
