#pragma once

#include <list>

#include "expression.h"

class TOperation;

/*
 * Объявление синонима к указателю на операцию
 */
typedef std::shared_ptr<TOperation> TOperation_ptr;


/*
 * Класс-интерфейс для реализации операции в интерпретируемой программе
 */
class TOperation {
public:
    virtual ~TOperation() {}

    /*
     * Выполнить операцию
     */
    virtual void execute(TDictionary& dictionary) = 0;
};

/*
 * Класс для хранения и выполнения набора операций
 */
class TOperations {
public:
    /*
     * Добавить операцию в набор
     */
    void addOperation(TOperation_ptr operation);

    /*
     * Выполнить все операции в наборе
     */
    void executeAll(TDictionary& dictionary);

private:
    /*
     * Список для хранения всех операций
     */
    std::list<TOperation_ptr> _operations;
};


/*
 * Операция print(...) для вывода значения
 */
template <typename VariableType>
class TPrint : public TOperation {
public:
    /*
     * Синоним к указателю на выражение, значение которого будет выведено
     */
    typedef std::shared_ptr< TExpression<VariableType> > TExpression_ptr;

    TPrint(TExpression_ptr expression);
    void execute(TDictionary& dictionary);

private:
    TExpression_ptr _expression;
};


/*
 * Операция read(var) для чтения значения переменной
 */
template <typename VariableType>
class TRead : public TOperation {
public:
    TRead(const TVariable<VariableType>& variable);
    void execute(TDictionary& dictionary);

private:
    TVariable<VariableType> _variable;
};


/*
 * Операция присвоения
 * В грамматике выражение выглядит как var = expr;
 */
template <typename VariableType>
class TAssign : public TOperation {
public:
    /*
     * Синоним к указателю на выражение, значение которого будет присвоено переменной
     */
    typedef std::shared_ptr< TExpression<VariableType> > TExpression_ptr;

    TAssign(const TVariable<VariableType>& variable, TExpression_ptr expression);
    void execute(TDictionary& dictionary);

private:
    TExpression_ptr         _expression;
    TVariable<VariableType> _variable;
};


/*
 * Операция присвоения элементу строки
 * В грамматике выражение выглядит как string_var[number_expr] = string_expr;
 * Где number_expr задает индекс элемента
 */
class TIndexAssign : public TOperation {
public:
    TIndexAssign(const TVariable<string_t>& variable, TNumberExpression_ptr index_expression, TStringExpression_ptr expression);
    void execute(TDictionary& dictionary);

private:
    TNumberExpression_ptr _index_expression;
    TStringExpression_ptr _expression;
    TVariable<string_t>   _variable;
};


/*
 * Операция if (bool_expr) { ... } else { ... }
 */
class TIfBlock : public TOperation {
public:
    TIfBlock(TBoolExpression_ptr bool_expr, TOperations operations_if_true, TOperations operations_if_false);
    void execute(TDictionary& dictionary);

private:
    TOperations         _operations_if_true;
    TOperations         _operations_if_false;
    TBoolExpression_ptr _bool_expr;
};


/*
 * Операция while (bool_expr) { ... }
 */
class TWhileBlock : public TOperation {
public:
    TWhileBlock(TBoolExpression_ptr bool_expr, TOperations operations);
    void execute(TDictionary& dictionary);

private:
    TOperations         _operations;
    TBoolExpression_ptr _bool_expr;
};
