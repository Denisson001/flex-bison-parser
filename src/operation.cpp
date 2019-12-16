#include <iostream>

#include "operation.h"

template class TPrint<number_t>;
template class TPrint<string_t>;
template class TAssign<number_t>;
template class TRead<number_t>;
template class TRead<string_t>;



void TOperations::addOperation(TOperation_ptr operation) {
    _operations.push_back(operation);
}

void TOperations::executeAll(TDictionary& dictionary) {
    for (auto operation : _operations) {
        operation->execute(dictionary);
    }
}



template <typename VariableType>
TPrint<VariableType>::TPrint(TExpression_ptr expression) :
        _expression(expression)
{}

template <typename VariableType>
void TPrint<VariableType>::execute(TDictionary& dictionary){
    std::cout << _expression->calculate(dictionary) << "\n";
}


template <typename VariableType>
TRead<VariableType>::TRead(const TVariable<VariableType>& variable) :
        _variable(variable)
{}

template <typename VariableType>
void TRead<VariableType>::execute(TDictionary& dictionary) {
    std::cin >> dictionary[_variable];
}



template <typename VariableType>
TAssign<VariableType>::TAssign(const TVariable<VariableType>& variable, TExpression_ptr expression) :
        _variable(variable),
        _expression(expression)
{}

template <typename VariableType>
void TAssign<VariableType>::execute(TDictionary& dictionary) {
    dictionary[_variable] = _expression->calculate(dictionary);
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
