#include "expression.h"

template class TExpression<number_t>;
template class TExprVariable<number_t>;
template class TExprValue<number_t>;

template class TExpression<string_t>;
template class TExprVariable<string_t>;



template <typename VariableType>
TExpression<VariableType>::TExpression(TExpression_ptr left_expr, TExpression_ptr right_expr, TExprOperator<VariableType> operation) :
        _left_expr(left_expr),
        _right_expr(right_expr),
        _operation(operation)
{}

template <typename VariableType>
TExpression<VariableType>::TExpression() :
        _left_expr(NULL),
        _right_expr(NULL)
{}



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

template <>
number_t TExpression<number_t>::calculate(TDictionary& dictionary) {
    const auto left_result  = _left_expr->calculate(dictionary);
    const auto right_result = _right_expr->calculate(dictionary);
    switch (_operation.type) {
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

template <>
string_t TExpression<string_t>::calculate(TDictionary& dictionary) {
    const auto left_result  = _left_expr->calculate(dictionary);
    const auto right_result = _right_expr->calculate(dictionary);
    switch (_operation.type) {
        case CONCAT:
            return left_result + right_result;
    }
}

/* bool_t */

TExpression<bool_t>::TExpression(TExpression_ptr left_expr, TExpression_ptr right_expr, TExprOperator<bool_t> operation) :
        _left_expr(left_expr),
        _right_expr(right_expr),
        _operation(operation)
{}

bool_t TExpression<bool_t>::calculate(TDictionary& dictionary) {
    const auto left_result  = _left_expr->calculate(dictionary);
    const auto right_result = _right_expr->calculate(dictionary);
    switch (_operation.type) {
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