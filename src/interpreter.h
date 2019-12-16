#pragma once

#include "operation.h"
#include "node.h"

class TInterpreter {
public:
    int run(char* program_filename);

private:
    int _buildAST(char* program_filename);
    void _interpret();

    TOperations  _operations;
    dictionary_t _dictionary;
};

