#pragma once

#include <memory>
#include <vector>

#include "dictionary.h"
#include "operator.h"

template <typename VariableType>
class TExpression;

/*
 * Объявление синонимов к указателям на фундаментальные типы переменных
 */
typedef std::shared_ptr< TExpression<number_t> > TNumberExpression_ptr;
typedef std::shared_ptr< TExpression<string_t> > TStringExpression_ptr;
typedef std::shared_ptr< TExpression<bool_t> >   TBoolExpression_ptr;

/*
 * Объявление синонимов к наборам указателей
 */
typedef std::vector<TNumberExpression_ptr> TNumberExpressions;
typedef std::vector<TStringExpression_ptr> TStringExpressions;
typedef std::vector<TBoolExpression_ptr>   TBoolExpressions;


/*
 * Главный класс для работы с математическими выражениями
 */
template <typename VariableType>
class TExpression {
public:
    /*
     * Указатель на подвыражения
     */
    typedef std::shared_ptr< TExpression<VariableType> > TExpression_ptr;

    TExpression() {}
    TExpression(TExpression_ptr left_expr, TExpression_ptr right_expr, TExprOperator<VariableType> operation);
    virtual ~TExpression() {}

    /*
     * Виртуальный метод для вычисления значения выражения
     * Принимает словарь со значениями переменных
     */
    virtual VariableType calculate(TDictionary& dictionary);

private:
    /*
     * Выражение в левой части от оператора
     */
    TExpression_ptr             _left_expr;

    /*
     * Выражение в правой части от оператора
     */
    TExpression_ptr             _right_expr;

    /*
     * Оператор
     */
    TExprOperator<VariableType> _operation;
};


/*
 * Класс-наследник TExpression
 * Является термом, т.е. листом дерева разбора выражения
 * Хранит переменную
 */
template <typename VariableType>
class TExprVariable : public TExpression<VariableType> {
public:
    TExprVariable(const TVariable<VariableType>& variable);
    VariableType calculate(TDictionary& dictionary);

private:
    TVariable<VariableType> _variable;
};


/*
 * Класс-наследник TExpression
 * Является термом, т.е. листом дерева разбора выражения
 * Хранит значение типа VariableType
 */
template <typename VariableType>
class TExprValue : public TExpression<VariableType> {
public:
    TExprValue(VariableType value);
    VariableType calculate(TDictionary& dictionary);

private:
    VariableType _value;
};


/*
 * Класс-наследник TExpression
 * Является термом, т.е. листом дерева разбора выражения
 * Хранит имя вызываемой функции и аргументы вызова
 * Такой реализации класса достаточно для текущей задачи
 */
template <typename VariableType>
class TExprFunction : public TExpression<VariableType> {
public:
    TExprFunction(const function_t& function_name, const TNumberExpressions& number_expressions = {},
                  const TStringExpressions& string_expressions = {}, const TBoolExpressions& bool_expressions = {});
    VariableType calculate(TDictionary& dictionary);

private:
    /*
     * Имя вызываемой функции
     */
    function_t         _function_name;

    /*
     * Аргументы вызова
     */
    TNumberExpressions _number_expressions;
    TStringExpressions _string_expressions;
    TBoolExpressions   _bool_expressions;
};
