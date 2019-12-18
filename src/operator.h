#pragma once

#include "cfg.h"

/*
 * Перечисление операторов для числовых выражений
 */
enum ENumberOperator {
    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD
};


/*
 * Перечисление операторов для строковых выражений
 */
enum EStringOperator {
    CONCAT
};


/*
 * Перечисление операторов для логических выражений
 * NOT реализован как функция, а не оператор
 */
enum EBoolOperator {
    OR,
    AND
};

/*
 * Шаблонный класс для работы с операторами в шаблонных выражениях
 */
template <typename VariableType>
struct TExprOperator;


/*
 * Далее идут специализации класса TExprOperator для разных типов
 */


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