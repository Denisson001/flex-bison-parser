#pragma once

#include <string>

#include "operation.h"
#include "expression.h"

struct TNode {
    TOperation_ptr                           operation;
    TOperations                              operations;
    std::shared_ptr< TExpression<number_t> > math_expression;
    std::shared_ptr< TExpression<bool_t> >   bool_expression;
    TExprOperator<bool_t>                    bool_operator;
    TVariable<number_t>                      number_variable;
    TVariable<string_t>                      string_variable;
    number_t                                 number;
};