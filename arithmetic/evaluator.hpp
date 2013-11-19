/* Copyright (c) 2013 by Pierre Talbot
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#ifndef SASH_MATH_EVALUATOR_HPP
#define SASH_MATH_EVALUATOR_HPP
 
#include "ast.hpp"

#include <stdexcept>
#include <string>

namespace sash{
namespace math{

class divide_by_zero : std::logic_error
{
public:
  divide_by_zero();
};


class evaluator : public boost::static_visitor<ast::arithmetic_type>
{
public:
  int operator()(ast::arithmetic_type value) const;
  int operator()(const ast::add_op& binary) const;
  int operator()(const ast::sub_op& binary) const;
  int operator()(const ast::mul_op& binary) const;
  int operator()(const ast::div_op& binary) const;
  int operator()(const ast::usub_op& usub) const;
};

int eval_expression(const std::string& expr);

}} // namespace sash::math

#endif // SASH_MATH_EVALUATOR_HPP
