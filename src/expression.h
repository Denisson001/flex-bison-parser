#pragma once

#include <string>
#include <memory>

#include "cfg.h"

struct TMathExpression;
struct TBoolExpression;

typedef std::shared_ptr<TMathExpression> TMathExpression_ptr;
typedef std::shared_ptr<TBoolExpression> TBoolExpression_ptr;


struct TMathExpression {
    TMathExpression();
    TMathExpression(TMathExpression_ptr left_expr, TMathExpression_ptr right_expr, char operation);
    virtual number_t calculate(dictionary_t& dictionary);
    virtual ~TMathExpression() {}

private:
    TMathExpression_ptr _left_expr;
    TMathExpression_ptr _right_expr;
    char                _operation;
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
    enum EBoolOperator {
        EQUAL,
        NOT_EQUAL,
        LESS,
        LESS_OR_EQUAL,
        GREATER,
        GREATER_OR_EQUAL
    };

    TBoolExpression(TMathExpression_ptr left_expr, TMathExpression_ptr right_expr, EBoolOperator operation);
    bool calculate(dictionary_t& dictionary);

private:
    TMathExpression_ptr _left_expr;
    TMathExpression_ptr _right_expr;
    EBoolOperator       _operation;
};