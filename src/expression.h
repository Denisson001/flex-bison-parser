#pragma once

#include <string>
#include <memory>

#include "cfg.h"
#include "dictionary.h"

enum ENumberOperator {
    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD
};

enum EBoolOperator {
    EQUAL,
    NOT_EQUAL,
    LESS,
    LESS_OR_EQUAL,
    GREATER,
    GREATER_OR_EQUAL
};

template <typename VariableType>
class TExpression;

template <typename VariableType>
class TExpression {
public:
    typedef std::shared_ptr<TExpression> TExpression_ptr;

    TExpression();
    TExpression(TExpression_ptr left_expr, TExpression_ptr right_expr, ENumberOperator operation);
    virtual VariableType calculate(TDictionary& dictionary);
    virtual ~TExpression() {}

private:
    TExpression_ptr _left_expr;
    TExpression_ptr _right_expr;
    ENumberOperator _operation;
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
    TExprValue(VariableType number);
    VariableType calculate(TDictionary& dictionary);

private:
    VariableType _number;
};



template <>
class TExpression<bool_t> {
public:
    typedef std::shared_ptr< TExpression<number_t> > TNumberExpression_ptr;

    TExpression();
    TExpression(TNumberExpression_ptr left_expr, TNumberExpression_ptr right_expr, EBoolOperator operation);
    virtual bool_t calculate(TDictionary& dictionary);
    virtual ~TExpression() {}

private:
    TNumberExpression_ptr _left_expr;
    TNumberExpression_ptr _right_expr;
    EBoolOperator         _operation;
};