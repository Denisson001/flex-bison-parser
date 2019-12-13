#pragma once

#include <string>

#include "operation.h"
#include "expression.h"

struct TNode {
    TOperation*                     operation;
    TOperations                     operations;
    TMathExpression*                math_expression;
    TBoolExpression*                bool_expression;
    TBoolExpression::EBoolOperation bool_operation;
    variable_t                      variable;
    number_t                        number;
};