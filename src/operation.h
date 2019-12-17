#pragma once

#include <list>

#include "expression.h"

class TOperation;

typedef std::shared_ptr<TOperation> TOperation_ptr;


class TOperation {
public:
    virtual void execute(TDictionary& dictionary) = 0;
    virtual ~TOperation() {}
};


class TOperations {
public:
    void addOperation(TOperation_ptr operation);
    void executeAll(TDictionary& dictionary);
private:
    std::list<TOperation_ptr> _operations;
};


template <typename VariableType>
class TPrint : public TOperation {
public:
    typedef std::shared_ptr< TExpression<VariableType> > TExpression_ptr;

    TPrint(TExpression_ptr expression);
    void execute(TDictionary& dictionary);

private:
    TExpression_ptr _expression;
};


template <typename VariableType>
class TRead : public TOperation {
public:
    TRead(const TVariable<VariableType>& variable);
    void execute(TDictionary& dictionary);

private:
    TVariable<VariableType> _variable;
};


template <typename VariableType>
class TAssign : public TOperation {
public:
    typedef std::shared_ptr< TExpression<VariableType> > TExpression_ptr;

    TAssign(const TVariable<VariableType>& variable, TExpression_ptr expression);
    void execute(TDictionary& dictionary);

private:
    TExpression_ptr         _expression;
    TVariable<VariableType> _variable;
};


class TIndexAssign : public TOperation {
public:
    TIndexAssign(const TVariable<string_t>& variable, TNumberExpression_ptr index_expression, TStringExpression_ptr expression);
    void execute(TDictionary& dictionary);

private:
    TNumberExpression_ptr _index_expression;
    TStringExpression_ptr _expression;
    TVariable<string_t>   _variable;
};


class TIfBlock : public TOperation {
public:
    TIfBlock(TBoolExpression_ptr bool_expr, TOperations operations_if_true, TOperations operations_if_false);
    void execute(TDictionary& dictionary);

private:
    TOperations         _operations_if_true;
    TOperations         _operations_if_false;
    TBoolExpression_ptr _bool_expr;
};


class TWhileBlock : public TOperation {
public:
    TWhileBlock(TBoolExpression_ptr bool_expr, TOperations operations);
    void execute(TDictionary& dictionary);

private:
    TOperations         _operations;
    TBoolExpression_ptr _bool_expr;
};
