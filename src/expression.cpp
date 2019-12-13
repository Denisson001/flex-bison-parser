#include "expression.h"

TMathExpression::TMathExpression(TMathExpression* left_expr, TMathExpression* right_expr, char operation) :
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
