/* Copyright (c) 2013 by Pierre Talbot
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#include "evaluator.hpp"
#include "lexer.hpp"
#include "parser.hpp"

namespace sash{
namespace math{

divide_by_zero::divide_by_zero()
: std::logic_error("Division by zero detected.")
{}

int evaluator::operator()(ast::arithmetic_type value) const
{
  return value;
}

int evaluator::operator()(const ast::add_op& binary) const
{
  return boost::apply_visitor(evaluator(), binary.left)
       + boost::apply_visitor(evaluator(), binary.right);
}

int evaluator::operator()(const ast::sub_op& binary) const
{
  return boost::apply_visitor(evaluator(), binary.left)
       - boost::apply_visitor(evaluator(), binary.right);
}

int evaluator::operator()(const ast::mul_op& binary) const
{
  return boost::apply_visitor(evaluator(), binary.left)
       * boost::apply_visitor(evaluator(), binary.right);
}

int evaluator::operator()(const ast::div_op& binary) const
{
  ast::arithmetic_type right_value = boost::apply_visitor(evaluator(), binary.right);
  if(right_value == 0)
    throw divide_by_zero();
  return boost::apply_visitor(evaluator(), binary.left)
       / right_value;
}

int evaluator::operator()(const ast::usub_op& usub) const
{
  return -boost::apply_visitor(evaluator(), usub.expr);
}

int eval_expression(const std::string& expr)
{
  // now we use the types defined above to create the lexer and grammar
  // object instances needed to invoke the parsing process.
  tokens_type tokens;        // Our lexer
  grammar_type parser(tokens);  // Our parser

  // At this point we generate the iterator pair used to expose the
  // tokenized input stream.
  std::string::const_iterator it = expr.begin();
  token_iterator_type iter = tokens.begin(it, expr.end());
  token_iterator_type end = tokens.end();

  // Parsing is done based on the the token stream, not the character 
  // stream read from the input.
  ast::expression arith_ast;
  bool r = boost::spirit::qi::parse(iter, end, parser, arith_ast);
  if (r && iter == end)
  {
    return boost::apply_visitor(evaluator(), arith_ast);
  }
  else
  {
    throw std::invalid_argument("The arithmetic expression is malformed.\n");
  }
}

}} // namespace sash::math
