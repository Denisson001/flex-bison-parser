#include "variable.h"

/*
 * Объявление всех шаблонных подстановок для типов переменных
 * Можно было бы не выносить реализацию в отдельный файл,
 * Но для текущей задачи такое объявление позволяет явно следить за всеми типами
 */
template class TVariable<number_t>;
template class TVariable<string_t>;


template <typename VariableType>
TVariable<VariableType>::TVariable()
{}

template <typename VariableType>
TVariable<VariableType>::TVariable(const variable_t& variable_name) :
        _variable_name(variable_name)
{}

/*
 * Переменные упорядочиваются по их именам
 */
template <typename VariableType>
bool TVariable<VariableType>::operator<(const TVariable<VariableType> &other_variable) const {
    return _variable_name < other_variable._variable_name;
}