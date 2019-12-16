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

struct TPrint : public TOperation {
    TPrint(TMathExpression_ptr math_expr);
    void execute(TDictionary& dictionary);

private:
    TMathExpression_ptr _math_expr;
};

struct TRead : public TOperation {
    TRead(const TVariable<number_t>& variable);
    void execute(TDictionary& dictionary);

private:
    TVariable<number_t> _variable;
};

struct TAssign : public TOperation {
    TAssign(const TVariable<number_t>& variable, TMathExpression_ptr math_expr);
    void execute(TDictionary& dictionary);

private:
    TMathExpression_ptr _math_expr;
    TVariable<number_t> _variable;
};

struct TIfBlock : public TOperation {
    TIfBlock(TBoolExpression_ptr bool_expr, TOperations operations_if_true, TOperations operations_if_false);
    void execute(TDictionary& dictionary);

private:
    TOperations         _operations_if_true;
    TOperations         _operations_if_false;
    TBoolExpression_ptr _bool_expr;
};

struct TWhileBlock : public TOperation {
    TWhileBlock(TBoolExpression_ptr bool_expr, TOperations operations);
    void execute(TDictionary& dictionary);

private:
    TOperations         _operations;
    TBoolExpression_ptr _bool_expr;
};