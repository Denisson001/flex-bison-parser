#include "dictionary.h"

const number_t TDictionary::_non_existing_number_variable = {};
const string_t TDictionary::_non_existing_string_variable = {};

number_t& TDictionary::operator[](const TVariable<number_t>& variable) {
    return _number_dictionary[variable];
}

const number_t& TDictionary::operator[](const TVariable<number_t>& variable) const {
    if (!_number_dictionary.count(variable)) {
        return _non_existing_number_variable;
    }
    return _number_dictionary.at(variable);
}

string_t& TDictionary::operator[](const TVariable<string_t>& variable) {
    return _string_dictionary[variable];
}

const string_t& TDictionary::operator[](const TVariable<string_t>& variable) const {
    if (!_string_dictionary.count(variable)) {
        return _non_existing_string_variable;
    }
    return _string_dictionary.at(variable);
}
