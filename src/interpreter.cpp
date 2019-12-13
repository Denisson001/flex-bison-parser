#include "interpreter.h"

void TInterpreter:: addOperation(TOperation* operation) {
    _operations.push_back(operation);
}

void TInterpreter:: interpret() {
    for (auto operation : _operations) {
        operation->calculate(_dictionary);
    }
}

TInterpreter:: ~TInterpreter() {
    for (auto operation : _operations) {
        delete operation;
    }
}
