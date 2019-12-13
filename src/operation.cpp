#include <iostream>

#include "operation.h"

void TOperations::addOperation(TOperation* operation) {
    _operations.push_back(operation);
}

void TOperations::executeAll(dictionary_t& dictionary) {
    for (auto operation : _operations) {
        operation->execute(dictionary);
    }
}



TPrint:: TPrint(TMathExpression* math_expr) :
        _math_expr(math_expr)
{}

void TPrint::execute(dictionary_t& dictionary){
    std::cout << _math_expr->calculate(dictionary) << "\n";
}



TAssign::TAssign(const variable_t& variable, TMathExpression* math_expr) :
        _variable(variable),
        _math_expr(math_expr)
{}

void TAssign::execute(dictionary_t& dictionary) {
    dictionary[_variable] = _math_expr->calculate(dictionary);
}



TIfBlock::TIfBlock(TBoolExpression* bool_expr, TOperations operations_if_true, TOperations operations_if_false) :
        _bool_expr(bool_expr),
        _operations_if_true(operations_if_true),
        _operations_if_false(operations_if_false)
{}

void TIfBlock::execute(dictionary_t& dictionary) {
    if (_bool_expr->calculate(dictionary)) {
        _operations_if_true.executeAll(dictionary);
    } else {
        _operations_if_false.executeAll(dictionary);
    }
}