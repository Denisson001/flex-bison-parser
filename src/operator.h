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
    OR,
    AND
};

template <typename VariableType>
struct TExprOperator;

template <>
struct TExprOperator<number_t> {
    TExprOperator() {}
    TExprOperator(ENumberOperator type);
    ENumberOperator type;
};

template <>
struct TExprOperator<string_t> {
    TExprOperator() {}
    TExprOperator(EStringOperator type);
    EStringOperator type;
};

template <>
struct TExprOperator<bool_t> {
    TExprOperator() {}
    TExprOperator(EBoolOperator type);
    EBoolOperator type;
};