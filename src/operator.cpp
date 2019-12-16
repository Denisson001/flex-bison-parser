#include "operator.h"

TExprOperator<bool_t>::TExprOperator()
{}

TExprOperator<bool_t>::TExprOperator(EBoolOperator type) :
        type(type)
{}

TExprOperator<number_t >::TExprOperator()
{}

TExprOperator<number_t >::TExprOperator(ENumberOperator type) :
        type(type)
{}