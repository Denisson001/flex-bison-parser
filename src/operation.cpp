#include <iostream>

#include "operation.h"

/*
 * Объявление всех шаблонных подстановок для классов-операций
 * Можно было бы не выносить реализацию в отдельный файл,
 * Но для текущей задачи такое объявление позволяет явно следить за всеми типами
 */
template class TPrint<number_t>;
template class TPrint<string_t>;
template class TAssign<number_t>;
template class TAssign<string_t>;
template class TRead<number_t>;
template class TRead<string_t>;


/*
 * Добавить операцию в набор
 */
void TOperations::addOperation(TOperation_ptr operation) {
    _operations.push_back(operation);
}

/*
 * Выполнить все операции в наборе
 */
void TOperations::executeAll(TDictionary& dictionary) {
    for (auto operation : _operations) {
        operation->execute(dictionary);
    }
}


template <typename VariableType>
TPrint<VariableType>::TPrint(TExpression_ptr expression) :
        _expression(expression)
{}

/*
 * Вычисляет значение выражения и выводит это значение
 */
template <typename VariableType>
void TPrint<VariableType>::execute(TDictionary& dictionary){
    std::cout << _expression->calculate(dictionary) << "\n";
}


template <typename VariableType>
TRead<VariableType>::TRead(const TVariable<VariableType>& variable) :
        _variable(variable)
{}

/*
 * Читает и устанавливает значение переменной
 */
template <typename VariableType>
void TRead<VariableType>::execute(TDictionary& dictionary) {
    std::cin >> dictionary[_variable];
}


template <typename VariableType>
TAssign<VariableType>::TAssign(const TVariable<VariableType>& variable, TExpression_ptr expression) :
        _variable(variable),
        _expression(expression)
{}

/*
 * Вычисляет значение выражения и устанавливает его в переменную, используя dictionary
 */
template <typename VariableType>
void TAssign<VariableType>::execute(TDictionary& dictionary) {
    dictionary[_variable] = _expression->calculate(dictionary);
}


TIndexAssign::TIndexAssign(const TVariable<string_t>& variable, TNumberExpression_ptr index_expression, TStringExpression_ptr expression) :
        _variable(variable),
        _index_expression(index_expression),
        _expression(expression)
{}

/*
 * Вычисляет значения выражения для индекса элемента, используя dictionary
 * Вычисляет значение выражения в правой части и устанавливает его в переменную, используя dictionary
 * Также есть проверка на корректность индекса
 */
void TIndexAssign::execute(TDictionary& dictionary) {
    const auto index = _index_expression->calculate(dictionary);
    dictionary[_variable][index] = _expression->calculate(dictionary)[0];        //!!!!!!!!!!!!!!!!!!! ПРОВЕРКА НА КОРРЕКТНОСТЬ!!!!!!!!!!!!!!!!!!!!!!!
}


TIfBlock::TIfBlock(TBoolExpression_ptr bool_expr, TOperations operations_if_true, TOperations operations_if_false) :
        _bool_expr(bool_expr),
        _operations_if_true(operations_if_true),
        _operations_if_false(operations_if_false)
{}

/*
 * Вычисляет значения логического выражения, используя dictionary
 * На основе этого значения запускается на исполнение один из наборов операций
 */
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

/*
 * Вычисляет значения логического выражения на каждой итерации цикла
 * На основе этого значения выполнение прекращается
 * Или запускается на исполнение набор операций
 */
void TWhileBlock::execute(TDictionary& dictionary) {
    while (_bool_expr->calculate(dictionary)) {
        _operations.executeAll(dictionary);
    }
}
