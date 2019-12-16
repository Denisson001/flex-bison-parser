#include "expression.h"

TMathExpression::TMathExpression(TMathExpression_ptr left_expr, TMathExpression_ptr right_expr, char operation) :
        _left_expr(left_expr),
        _right_expr(right_expr),
        _operation(operation)
{}

TMathExpression::TMathExpression() :
        _left_expr(NULL),
        _right_expr(NULL)
{}

number_t TMathExpression::calculate(TDictionary& dictionary) {
    const auto left_result  = _left_expr->calculate(dictionary);
    const auto right_result = _right_expr->calculate(dictionary);
    switch (_operation) {
        case '+':
            return left_result + right_result;
        case '-':
            return left_result - right_result;
        case '*':
            return left_result * right_result;
        case '/':
            return left_result / right_result;
        case '%':
            return left_result % right_result;
    }
}

TMathVariable::TMathVariable(const TVariable<number_t>& variable) :
    _variable(variable)
{}

number_t TMathVariable::calculate(TDictionary& dictionary) {
    return dictionary[_variable];
}

TMathNumber::TMathNumber(number_t number) :
    _number(number)
{}

number_t TMathNumber::calculate(TDictionary& dictionary) {
    return _number;
}

TBoolExpression::TBoolExpression(TMathExpression_ptr left_expr, TMathExpression_ptr right_expr, EBoolOperator operation) :
        _left_expr(left_expr),
        _right_expr(right_expr),
        _operation(operation)
{}

bool TBoolExpression::calculate(TDictionary& dictionary) {
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

