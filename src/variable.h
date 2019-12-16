#pragma once

#include "cfg.h"

template <typename VariableType>
struct TVariable {
    TVariable();
    TVariable(const variable_t& variable_name);
    bool operator<(const TVariable<VariableType>& other_variable) const;

    variable_t variable_name;
};
