#pragma once

#include "operation.h"
#include "expression.h"

/*
 * Корень абстрактного дерева разбора
 * Используется во внутреннем представлении Bison парсера
 */
struct TNode {
    TOperation_ptr        operation;
    TOperations           operations;
    TNumberExpression_ptr number_expression;
    TStringExpression_ptr string_expression;
    TBoolExpression_ptr   bool_expression;
    TVariable<number_t>   number_variable;
    TVariable<string_t>   string_variable;
    number_t              number;
    string_t              string;
    function_t            function;
};
