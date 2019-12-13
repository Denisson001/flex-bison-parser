#pragma once

#include <string>

#include "operation.h"
#include "expression.h"

struct TNode {
    TOperation*      operation;
    TMathExpression* math_expression;
    variable_t       variable;
    number_t         number;
};