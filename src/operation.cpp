#include <iostream>

#include "operation.h"

void TOperations::addOperation(TOperation_ptr operation) {
    _operations.push_back(operation);
}

void TOperations::executeAll(TDictionary& dictionary) {
    for (auto operation : _operations) {
        operation->execute(dictionary);
    }
}



TPrint:: TPrint(TMathExpression_ptr math_expr) :
        _math_expr(math_expr)
{}

void TPrint::execute(TDictionary& dictionary){
    std::cout << _math_expr->calculate(dictionary) << "\n";
}



TRead::TRead(const TVariable<number_t>& variable) :
        _variable(variable)
{}

void TRead::execute(TDictionary& dictionary) {
    std::cin >> dictionary[_variable];
}



TAssign::TAssign(const TVariable<number_t>& variable, TMathExpression_ptr math_expr) :
        _variable(variable),
        _math_expr(math_expr)
{}

void TAssign::execute(TDictionary& dictionary) {
    dictionary[_variable] = _math_expr->calculate(dictionary);
}



TIfBlock::TIfBlock(TBoolExpression_ptr bool_expr, TOperations operations_if_true, TOperations operations_if_false) :
        _bool_expr(bool_expr),
        _operations_if_true(operations_if_true),
        _operations_if_false(operations_if_false)
{}

void TIfBlock::execute(TDictionary& dictionary) {
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

void TWhileBlock::execute(TDictionary& dictionary) {
    while (_bool_expr->calculate(dictionary)) {
        _operations.executeAll(dictionary);
    }
}
