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

#ifndef SASH_MATH_PARSER_DEF_HPP
#define SASH_MATH_PARSER_DEF_HPP

#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_QI_DEBUG
#include "parser.hpp"

namespace sash{
namespace math{

namespace bs = boost::spirit;
namespace qi = boost::spirit::qi;
namespace phx = boost::phoenix;

template <typename Iterator>
template <typename TokenDef>
grammar<Iterator>::grammar(TokenDef const& tok)
  : grammar::base_type(expression, "arithmetic expression")
{
  RULE_DEF(expression,
    %=  add_expr
     |  sub_expr
     |  term
    );

  RULE_DEF(term,
    %=  mul_expr
     |  div_expr
     |  factor
    );

  RULE_DEF(factor,
    %=  tok.unsigned_digit
     | (tok.lparen >> expression >> tok.rparen)
     | usub_expr
     | (tok.add >> factor)
    );

  /**
  * These rules permit the automatic generation of semantic rules (AST creation) because they are typed.
  * (see the parser.hpp to look at the type.)
  */
  RULE_DEF(add_expr, 
    %= (term >> tok.add >> expression)
    );

  RULE_DEF(sub_expr, 
    %= (term >> tok.sub >> expression)
    );  

  RULE_DEF(mul_expr, 
    %= (factor >> tok.mul >> term)
    );  

  RULE_DEF(div_expr, 
    %= (factor >> tok.div >> term)
    );

  RULE_DEF(usub_expr,
    %= (tok.sub >> factor)
    );

  using namespace qi::labels;
  qi::on_error<qi::fail>
  (
    expression,
    std::cout
      << phx::val("Error! Expecting ")
      << bs::_4                               // what failed?
      << phx::val(" here: \"")
      << phx::construct<std::string>(bs::_3, bs::_2)   // iterators to error-pos, end
      << phx::val("\"")
      << std::endl
  );
}

}} // namespace sash::math

#endif // SASH_MATH_PARSER_DEF_HPP