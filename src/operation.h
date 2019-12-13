#pragma once

#include <string>
#include <list>

#include "expression.h"

struct TOperation {
    virtual void execute(dictionary_t& dictionary) = 0;
    virtual ~TOperation() {}
};

struct TOperations {
    void addOperation(TOperation* operation);
    void executeAll(dictionary_t& dictionary);
private:
    std::list<TOperation*> _operations;
};

struct TPrint : public TOperation {
    TPrint(TMathExpression* math_expr);
    void execute(dictionary_t& dictionary);

private:
    TMathExpression* _math_expr;
};

struct TAssign : public TOperation {
    TAssign(const variable_t& variable, TMathExpression* math_expr);
    void execute(dictionary_t& dictionary);

private:
    TMathExpression* _math_expr;
    variable_t       _variable;
};

struct TIfBlock : public TOperation {
    TIfBlock(TBoolExpression* bool_expr, TOperations operations_if_true, TOperations operations_if_false);
    void execute(dictionary_t& dictionary);

private:
    TOperations      _operations_if_true;
    TOperations      _operations_if_false;
    TBoolExpression* _bool_expr;
};