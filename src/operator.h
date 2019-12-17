#pragma once

#include "cfg.h"

enum ENumberOperator {
    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD
};

enum EStringOperator {
    CONCAT
};

enum EBoolOperator {
    EQUAL,
    NOT_EQUAL,
    LESS,
    LESS_OR_EQUAL,
    GREATER,
    GREATER_OR_EQUAL
};
