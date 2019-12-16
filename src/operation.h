#pragma once

#include <string>
#include <list>

#include "expression.h"

struct TOperation;

typedef std::shared_ptr<TOperation> TOperation_ptr;


struct TOperation {
    virtual void execute(TDictionary& dictionary) = 0;
    virtual ~TOperation() {}
};

struct TOperations {
    void addOperation(TOperation_ptr operation);
    void executeAll(TDictionary& dictionary);
private:
    std::list<TOperation_ptr> _operations;
};

template <typename VariableType>
struct TPrint : public TOperation {
    typedef std::shared_ptr< TExpression<VariableType> > TExpression_ptr;

    TPrint(TExpression_ptr expression);
    void execute(TDictionary& dictionary);

private:
    TExpression_ptr _expression;
};

template <typename VariableType>
struct TRead : public TOperation {
    TRead(const TVariable<VariableType>& variable);
    void execute(TDictionary& dictionary);

private:
    TVariable<VariableType> _variable;
};

template <typename VariableType>
struct TAssign : public TOperation {
    typedef std::shared_ptr< TExpression<VariableType> > TExpression_ptr;

    TAssign(const TVariable<VariableType>& variable, TExpression_ptr expression);
    void execute(TDictionary& dictionary);

private:
    TExpression_ptr         _expression;
    TVariable<VariableType> _variable;
};

struct TIfBlock : public TOperation {
    typedef std::shared_ptr< TExpression<bool_t> > TBoolExpression_ptr;

    TIfBlock(TBoolExpression_ptr bool_expr, TOperations operations_if_true, TOperations operations_if_false);
    void execute(TDictionary& dictionary);

private:
    TOperations         _operations_if_true;
    TOperations         _operations_if_false;
    TBoolExpression_ptr _bool_expr;
};

struct TWhileBlock : public TOperation {
    typedef std::shared_ptr< TExpression<bool_t> > TBoolExpression_ptr;

    TWhileBlock(TBoolExpression_ptr bool_expr, TOperations operations);
    void execute(TDictionary& dictionary);

private:
    TOperations         _operations;
    TBoolExpression_ptr _bool_expr;
};