#pragma once

#include <memory>

#include "dictionary.h"
#include "operator.h"

template <typename VariableType>
class TExpression;

typedef std::shared_ptr< TExpression<number_t> > TNumberExpression_ptr;
typedef std::shared_ptr< TExpression<string_t> > TStringExpression_ptr;
typedef std::shared_ptr< TExpression<bool_t> >   TBoolExpression_ptr;


template <typename VariableType>
class TExpression {
public:
    virtual VariableType calculate(TDictionary& dictionary) = 0;
    virtual ~TExpression() {}
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


class TNumberExpression : public TExpression<number_t> {
public:
    TNumberExpression(TNumberExpression_ptr left_expr, TNumberExpression_ptr right_expr, ENumberOperator operation);
    number_t calculate(TDictionary& dictionary);
    ~TNumberExpression() {}

private:
    TNumberExpression_ptr _left_expr;
    TNumberExpression_ptr _right_expr;
    ENumberOperator       _operation;
};


class TStringExpression : public TExpression<string_t> {
public:
    TStringExpression(TStringExpression_ptr left_expr, TStringExpression_ptr right_expr, EStringOperator operation);
    string_t calculate(TDictionary& dictionary);
    ~TStringExpression() {}

private:
    TStringExpression_ptr _left_expr;
    TStringExpression_ptr _right_expr;
    EStringOperator       _operation;
};


template <typename ExpressionsType>
class TBoolExpression : public TExpression<bool_t> {
public:
    typedef std::shared_ptr< TExpression<ExpressionsType> > TExpression_ptr;

    TBoolExpression(TExpression_ptr left_expr, TExpression_ptr right_expr, EBoolOperator operation);
    bool_t calculate(TDictionary& dictionary);
    ~TBoolExpression() {}

private:
    TExpression_ptr _left_expr;
    TExpression_ptr _right_expr;
    EBoolOperator   _operation;
};
