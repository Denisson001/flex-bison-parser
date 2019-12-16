#include <iostream>

#include "operation.h"

void TOperations::addOperation(TOperation_ptr operation) {
    _operations.push_back(operation);
}

void TOperations::executeAll(dictionary_t& dictionary) {
    for (auto operation : _operations) {
        operation->execute(dictionary);
    }
}



TPrint:: TPrint(TMathExpression_ptr math_expr) :
        _math_expr(math_expr)
{}

void TPrint::execute(dictionary_t& dictionary){
    std::cout << _math_expr->calculate(dictionary) << "\n";
}



TRead::TRead(const variable_t& variable) :
        _variable(variable)
{}

void TRead::execute(dictionary_t& dictionary) {
    std::cin >> dictionary[_variable];
}



TAssign::TAssign(const variable_t& variable, TMathExpression_ptr math_expr) :
        _variable(variable),
        _math_expr(math_expr)
{}

void TAssign::execute(dictionary_t& dictionary) {
    dictionary[_variable] = _math_expr->calculate(dictionary);
}



TIfBlock::TIfBlock(TBoolExpression_ptr bool_expr, TOperations operations_if_true, TOperations operations_if_false) :
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



TWhileBlock::TWhileBlock(TBoolExpression_ptr bool_expr, TOperations operations) :
        _bool_expr(bool_expr),
        _operations(operations)
{}

void TWhileBlock::execute(dictionary_t& dictionary) {
    while (_bool_expr->calculate(dictionary)) {
        _operations.executeAll(dictionary);
    }
}
