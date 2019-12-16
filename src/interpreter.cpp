#include "interpreter.h"

extern int yyparse(TOperations* ast_root);

int TInterpreter::run(char* program_filename) {
    const auto parse_result = _buildAST(program_filename);
    if (parse_result != 0) {
        return parse_result;
    }
    _interpret();
    return 0;
}

int TInterpreter::_buildAST(char* program_filename) {
    freopen(program_filename, "r", stdin);
    const auto parse_result = yyparse(&_operations);
    stdin = fdopen(0, "r");
    return parse_result;
}

void TInterpreter::_interpret() {
    _operations.executeAll(_dictionary);
}
