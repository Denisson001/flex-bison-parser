#pragma once

#include <string>
#include <memory>

#include "dictionary.h"
#include "operator.h"

template <typename VariableType>
class TExpression;

template <typename VariableType>
class TExpression {
public:
    typedef std::shared_ptr<TExpression> TExpression_ptr;

    TExpression();
    TExpression(TExpression_ptr left_expr, TExpression_ptr right_expr, TExprOperator<VariableType> operation);
    virtual VariableType calculate(TDictionary& dictionary);
    virtual ~TExpression() {}

private:
    TExpression_ptr             _left_expr;
    TExpression_ptr             _right_expr;
    TExprOperator<VariableType> _operation;
};

template <typename VariableType>
class TExprVariable : public TExpression<VariableType> {
public:
    TExprVariable(const TVariable<VariableType>& variable);
    VariableType calculate(TDictionary& dictionary);

private:
    TVariable<VariableType> _variable;
};

template <typename VariableType>
class TExprValue : public TExpression<VariableType> {
public:
    TExprValue(VariableType value);
    VariableType calculate(TDictionary& dictionary);

private:
    VariableType _value;
};



template <>
class TExpression<bool_t> {
public:
    typedef std::shared_ptr< TExpression<number_t> > TExpression_ptr;

    TExpression();
    TExpression(TExpression_ptr left_expr, TExpression_ptr right_expr, TExprOperator<bool_t> operation);
    virtual bool_t calculate(TDictionary& dictionary);
    virtual ~TExpression() {}

private:
    TExpression_ptr       _left_expr;
    TExpression_ptr       _right_expr;
    TExprOperator<bool_t> _operation;
};