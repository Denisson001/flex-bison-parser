#include "variable.h"

template class TVariable<number_t>;
template class TVariable<string_t>;

template <typename VariableType>
TVariable<VariableType>::TVariable()
{}

template <typename VariableType>
TVariable<VariableType>::TVariable(const variable_t& variable_name) :
        variable_name(variable_name)
{}

template <typename VariableType>
bool TVariable<VariableType>::operator<(const TVariable<VariableType> &other_variable) const {
    return variable_name < other_variable.variable_name;
}