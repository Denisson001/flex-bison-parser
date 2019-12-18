#include "dictionary.h"

/*
 * Значения переменных по умолчанию
 */
const number_t TDictionary::_non_existing_number_variable = {};
const string_t TDictionary::_non_existing_string_variable = {};

/*
 * Метод для изменения значения переменной
 */
number_t& TDictionary::operator[](const TVariable<number_t>& variable) {
    return _number_dictionary[variable];
}

/*
 * Возвращает значение переменной
 * Если значение переменной не было установлено, то возвращает значение по умолчанию
 */
const number_t& TDictionary::operator[](const TVariable<number_t>& variable) const {
    if (!_number_dictionary.count(variable)) {
        return _non_existing_number_variable;
    }
    return _number_dictionary.at(variable);
}

/*
 * Аналогичная реализация для строковых переменных
 */
string_t& TDictionary::operator[](const TVariable<string_t>& variable) {
    return _string_dictionary[variable];
}

const string_t& TDictionary::operator[](const TVariable<string_t>& variable) const {
    if (!_string_dictionary.count(variable)) {
        return _non_existing_string_variable;
    }
    return _string_dictionary.at(variable);
}
