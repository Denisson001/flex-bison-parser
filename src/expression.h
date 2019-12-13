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

struct TBoolExpression {
    enum EBoolOperation {
        EQUAL,
        NOT_EQUAL,
        LESS,
        LESS_OR_EQUAL,
        GREATER,
        GREATER_OR_EQUAL
    };

    TBoolExpression(TMathExpression* left_expr, TMathExpression* right_expr, EBoolOperation operation);
    bool calculate(dictionary_t& dictionary);

private:
    TMathExpression* _left_expr;
    TMathExpression* _right_expr;
    EBoolOperation   _operation;
};