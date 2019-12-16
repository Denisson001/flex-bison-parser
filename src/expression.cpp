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

number_t TMathExpression::calculate(dictionary_t& dictionary) {
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

TVariable::TVariable(const std::string& variable) :
    _variable(variable)
{}

number_t TVariable::calculate(dictionary_t& dictionary) {
    return dictionary[_variable];
}

TNumber::TNumber(number_t number) :
    _number(number)
{}

number_t TNumber::calculate(dictionary_t& dictionary) {
    return _number;
}

TBoolExpression::TBoolExpression(TMathExpression_ptr left_expr, TMathExpression_ptr right_expr, EBoolOperator operation) :
        _left_expr(left_expr),
        _right_expr(right_expr),
        _operation(operation)
{}

bool TBoolExpression::calculate(dictionary_t& dictionary) {
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

