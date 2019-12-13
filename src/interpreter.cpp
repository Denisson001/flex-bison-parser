#include "interpreter.h"

void TInterpreter::setOperations(TOperations operations) {
    _operations = operations;
}

void TInterpreter::interpret() {
    _operations.executeAll(_dictionary);
}
