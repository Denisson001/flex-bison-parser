#pragma once

#include <string>

#include "cfg.h"

struct TMathExpression {
    TMathExpression();
    TMathExpression(TMathExpression* left_expr, TMathExpression* right_expr, char operation);
    virtual number_t calculate(dictionary_t& dictionary);
    virtual ~TMathExpression() {}

private:
    TMathExpression* _left_expr;
    TMathExpression* _right_expr;
    char             _operation;
};

struct TVariable : public TMathExpression {
    TVariable(const std::string& variable);
    number_t calculate(dictionary_t& dictionary);

private:
    variable_t _variable;
};

struct TNumber : public TMathExpression {
    TNumber(number_t number);
    number_t calculate(dictionary_t& dictionary);

private:
    number_t _number;
};