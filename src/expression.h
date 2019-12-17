#pragma once

#include <memory>
#include <vector>

#include "dictionary.h"
#include "operator.h"

template <typename VariableType>
class TExpression;

typedef std::shared_ptr< TExpression<number_t> > TNumberExpression_ptr;
typedef std::shared_ptr< TExpression<string_t> > TStringExpression_ptr;
typedef std::shared_ptr< TExpression<bool_t> >   TBoolExpression_ptr;

typedef std::vector<TNumberExpression_ptr> TNumberExpressions;
typedef std::vector<TStringExpression_ptr> TStringExpressions;
typedef std::vector<TBoolExpression_ptr>   TBoolExpressions;


template <typename VariableType>
class TExpression {
public:
    typedef std::shared_ptr< TExpression<VariableType> > TExpression_ptr;

    TExpression() {}
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


template <typename VariableType>
class TExprFunction : public TExpression<VariableType> {
public:
    TExprFunction(const function_t& function_name, const TNumberExpressions& number_expressions = {},
                  const TStringExpressions& string_expressions = {}, const TBoolExpressions& bool_expressions = {});
    VariableType calculate(TDictionary& dictionary);

private:
    function_t         _function_name;
    TNumberExpressions _number_expressions;
    TStringExpressions _string_expressions;
    TBoolExpressions   _bool_expressions;
};
