#pragma once

#include "operation.h"
#include "expression.h"

/*
 * Корень абстрактного дерева разбора
 * Используется во внутреннем представлении Bison парсера
 */
struct TNode {
    TOperation_ptr        operation;         // указатель на операцию
    TOperations           operations;        // набор операций
    TNumberExpression_ptr number_expression; // указатель на числовое выражение
    TStringExpression_ptr string_expression; // указатель на строковое выражение
    TBoolExpression_ptr   bool_expression;   // указатель на логическое выражение
    TVariable<number_t>   number_variable;   // числовая переменная
    TVariable<string_t>   string_variable;   // строковая переменная
    number_t              number;            // числовая величина
    string_t              string;            // строковая величина
    function_t            function;          // название функции
};
