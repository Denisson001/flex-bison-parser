#pragma once

#include <string>

#include "operation.h"
#include "expression.h"

struct TNode {
    TOperation_ptr                 operation;
    TOperations                    operations;
    TMathExpression_ptr            math_expression;
    TBoolExpression_ptr            bool_expression;
    TBoolExpression::EBoolOperator bool_operator;
    TVariable<number_t>            number_variable;
    TVariable<string_t>            string_variable;
    number_t                       number;
};