#pragma once

#include <iostream>
#include <string>

#include "expression.h"

struct TOperation {
    virtual void calculate(dictionary_t& dictionary) = 0;
    virtual ~TOperation() {}
};

struct TPrint : public TOperation {
    TPrint(TMathExpression* math_expr);
    void calculate(dictionary_t& dictionary);

private:
    TMathExpression* _math_expr;
};

struct TAssign : public TOperation {
    TAssign(const variable_t& variable, TMathExpression* math_expr);
    void calculate(dictionary_t& dictionary);

private:
    variable_t       _variable;
    TMathExpression* _math_expr;
};