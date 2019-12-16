#pragma once

#include <string>
#include <list>

#include "expression.h"

struct TOperation;

typedef std::shared_ptr<TOperation> TOperation_ptr;


struct TOperation {
    virtual void execute(dictionary_t& dictionary) = 0;
    virtual ~TOperation() {}
};

struct TOperations {
    void addOperation(TOperation_ptr operation);
    void executeAll(dictionary_t& dictionary);
private:
    std::list<TOperation_ptr> _operations;
};

struct TPrint : public TOperation {
    TPrint(TMathExpression_ptr math_expr);
    void execute(dictionary_t& dictionary);

private:
    TMathExpression_ptr _math_expr;
};

struct TAssign : public TOperation {
    TAssign(const variable_t& variable, TMathExpression_ptr math_expr);
    void execute(dictionary_t& dictionary);

private:
    TMathExpression_ptr _math_expr;
    variable_t          _variable;
};

struct TIfBlock : public TOperation {
    TIfBlock(TBoolExpression_ptr bool_expr, TOperations operations_if_true, TOperations operations_if_false);
    void execute(dictionary_t& dictionary);

private:
    TOperations         _operations_if_true;
    TOperations         _operations_if_false;
    TBoolExpression_ptr _bool_expr;
};

struct TWhileBlock : public TOperation {
    TWhileBlock(TBoolExpression_ptr bool_expr, TOperations operations);
    void execute(dictionary_t& dictionary);

private:
    TOperations         _operations;
    TBoolExpression_ptr _bool_expr;
};