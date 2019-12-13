#pragma once

#include <vector>

#include "operation.h"

class TInterpreter {
public:

    void addOperation(TOperation* operation);
    void interpret();
    ~TInterpreter();

private:
    typedef std::vector<TOperation*> _TOperations;

    _TOperations _operations;
    dictionary_t _dictionary;
};

