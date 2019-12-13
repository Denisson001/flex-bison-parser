#include "operation.h"

TPrint:: TPrint(TMathExpression* math_expr) :
        _math_expr(math_expr)
{}

void TPrint::calculate(dictionary_t& dictionary){
    std::cout << _math_expr->calculate(dictionary) << "\n";
}

TAssign::TAssign(const variable_t& variable, TMathExpression* math_expr) :
        _variable(variable),
        _math_expr(math_expr)
{}

void TAssign::calculate(dictionary_t& dictionary) {
    dictionary[_variable] = _math_expr->calculate(dictionary);
}
