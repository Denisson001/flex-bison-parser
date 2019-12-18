#pragma once

#include <map>

#include "variable.h"

/*
 * Класс для хранения значений всех переменных в интерпретируемой программе
 */
class TDictionary {
public:
    /*
     * Методы для работы со структурой, как с обычным контейнером
     */
    number_t& operator[](const TVariable<number_t>& variable);
    const number_t& operator[](const TVariable<number_t>& variable) const;

    string_t& operator[](const TVariable<string_t>& variable);
    const string_t& operator[](const TVariable<string_t>& variable) const;

private:
    /*
     * Значения переменных по умолчанию
     */
    static const number_t _non_existing_number_variable;
    static const string_t _non_existing_string_variable;

    /*
     * Отдельные словари для разных типов переменных
     */
    std::map<TVariable<number_t>, number_t> _number_dictionary;
    std::map<TVariable<string_t>, string_t> _string_dictionary;
};
