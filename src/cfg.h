#pragma once

#include <string>

/*
 * Файл с фундаментальными типами
 * bool_t     - тип логической переменной
 * number_t   - тип числовой переменной
 * string_t   - тип строковой переменной
 * variable_t - тип имени переменной
 * function_t - тип имени функции
 * Например, достаточно только здесь поменять тип number_t на long long
 * или длинную арифметику
 */

typedef bool        bool_t;
typedef int         number_t;
typedef std::string string_t;
typedef std::string variable_t;
typedef std::string function_t;
