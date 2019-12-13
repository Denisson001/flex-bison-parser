#pragma once

#include <vector>

#include "operation.h"
#include "node.h"

class TInterpreter {
public:
    void setOperations(TOperations operations);
    void interpret();

private:
    TOperations  _operations;
    dictionary_t _dictionary;
};

