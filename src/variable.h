#pragma once

#include "cfg.h"

/*
 * Класс для реализации сущности перeменной
 * По факту хранится имя переменной, а значение достается из dictionary
 */
template <typename VariableType>
class TVariable {
public:
    TVariable();
    TVariable(const variable_t& variable_name);

    /*
     * Оператор меньше нужен для работы с dictionary
     */
    bool operator<(const TVariable<VariableType>& other_variable) const;

private:
    /*
     * Имя переменной
     */
    variable_t _variable_name;
};
