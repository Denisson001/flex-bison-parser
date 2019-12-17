#include "expression.h"

template class TExpression<number_t>;
template class TExprVariable<number_t>;
template class TExprValue<number_t>;
template class TBoolExpression<number_t>;

template class TExpression<string_t>;
template class TExprVariable<string_t>;

template class TExpression<bool_t>;


template <typename VariableType>
TExprVariable<VariableType>::TExprVariable(const TVariable<VariableType>& variable) :
        _variable(variable)
{}

template <typename VariableType>
VariableType TExprVariable<VariableType>::calculate(TDictionary& dictionary) {
    return dictionary[_variable];
}



template <typename VariableType>
TExprValue<VariableType>::TExprValue(VariableType value) :
        _value(value)
{}

template <typename VariableType>
VariableType TExprValue<VariableType>::calculate(TDictionary& dictionary) {
    return _value;
}

/* number_t */

TNumberExpression::TNumberExpression(TNumberExpression_ptr left_expr, TNumberExpression_ptr right_expr, ENumberOperator operation) :
        _left_expr(left_expr),
        _right_expr(right_expr),
        _operation(operation)
{}

number_t TNumberExpression::calculate(TDictionary& dictionary) {
    const auto left_result  = _left_expr->calculate(dictionary);
    const auto right_result = _right_expr->calculate(dictionary);
    switch (_operation) {
        case PLUS:
            return left_result + right_result;
        case MINUS:
            return left_result - right_result;
        case MULT:
            return left_result * right_result;
        case DIV:
            return left_result / right_result;
        case MOD:
            return left_result % right_result;
    }
}

/* string_t */

TStringExpression::TStringExpression(TStringExpression_ptr left_expr, TStringExpression_ptr right_expr, EStringOperator operation) :
        _left_expr(left_expr),
        _right_expr(right_expr),
        _operation(operation)
{}

string_t TStringExpression::calculate(TDictionary& dictionary) {
    const auto left_result  = _left_expr->calculate(dictionary);
    const auto right_result = _right_expr->calculate(dictionary);
    switch (_operation) {
        case CONCAT:
            return left_result + right_result;
    }
}

/* bool_t */

template <typename ExpressionsType>
TBoolExpression<ExpressionsType>::TBoolExpression(TExpression_ptr left_expr, TExpression_ptr right_expr,
                                                  EBoolOperator operation) :
        _left_expr(left_expr),
        _right_expr(right_expr),
        _operation(operation)
{}

template <typename ExpressionsType>
bool_t TBoolExpression<ExpressionsType>::calculate(TDictionary& dictionary) {
  const auto left_result  = _left_expr->calculate(dictionary);
  const auto right_result = _right_expr->calculate(dictionary);
  switch (_operation) {
      case EQUAL:
          return left_result == right_result;
      case NOT_EQUAL:
          return left_result != right_result;
      case LESS:
          return left_result <  right_result;
      case LESS_OR_EQUAL:
          return left_result <= right_result;
      case GREATER:
          return left_result >  right_result;
      case GREATER_OR_EQUAL:
          return left_result >= right_result;
  }
}
