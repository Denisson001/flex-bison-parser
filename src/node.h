#pragma once

#include "operation.h"
#include "expression.h"

struct TNode {
    TOperation_ptr        operation;
    TOperations           operations;
    TNumberExpression_ptr number_expression;
    TStringExpression_ptr string_expression;
    TBoolExpression_ptr   bool_expression;
    EBoolOperator         bool_operator;
    TVariable<number_t>   number_variable;
    TVariable<string_t>   string_variable;
    number_t              number;
    string_t              string;
    function_t            function;
};
