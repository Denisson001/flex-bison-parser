#pragma once

#include <map>

#include "variable.h"

class TDictionary {
public:
    number_t& operator[](const TVariable<number_t>& variable);
    const number_t& operator[](const TVariable<number_t>& variable) const;

    string_t& operator[](const TVariable<string_t>& variable);
    const string_t& operator[](const TVariable<string_t>& variable) const;

private:
    static const number_t _non_existing_number_variable;
    static const string_t _non_existing_string_variable;

    std::map<TVariable<number_t>, number_t> _number_dictionary;
    std::map<TVariable<string_t>, string_t> _string_dictionary;
};