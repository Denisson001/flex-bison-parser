#include "operator.h"

TExprOperator<bool_t>::TExprOperator(EBoolOperator type) :
        type(type)
{}


TExprOperator<string_t>::TExprOperator(EStringOperator type) :
        type(type)
{}


TExprOperator<number_t >::TExprOperator(ENumberOperator type) :
        type(type)
{}