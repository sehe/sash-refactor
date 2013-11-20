/* Copyright (c) 2013 by Pierre Talbot
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
*/

#ifndef SASH_MATH_EVALUATOR_HPP
#define SASH_MATH_EVALUATOR_HPP
 
#include <stdexcept>
#include <string>

namespace sash{
namespace math{

class divide_by_zero : std::logic_error
{
public:
  divide_by_zero();
};

int eval_expression(const std::string& expr);

}} // namespace sash::math

#endif // SASH_MATH_EVALUATOR_HPP
