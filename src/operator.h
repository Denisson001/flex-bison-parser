#pragma once

#include "cfg.h"

enum ENumberOperator {
    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD
};

enum EStringOperator {
    CONCAT
};

enum EBoolOperator {
    EQUAL,
    NOT_EQUAL,
    LESS,
    LESS_OR_EQUAL,
    GREATER,
    GREATER_OR_EQUAL
};

template <typename VariableType>
struct TExprOperator;

template <>
struct TExprOperator<number_t> {
    TExprOperator();
    TExprOperator(ENumberOperator type);
    ENumberOperator type;
};

template <>
struct TExprOperator<string_t> {
    EStringOperator type;
};

template <>
struct TExprOperator<bool_t> {
    TExprOperator();
    TExprOperator(EBoolOperator type);
    EBoolOperator type;
};