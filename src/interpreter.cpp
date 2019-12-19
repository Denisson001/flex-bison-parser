#include "interpreter.h"


/*
 * Точка входа в парсер Bison
 * Принимает указатель на корень абстрактного дерева разбора
 */
extern int yyparse(TOperations* ast_root, TErrorHandler* error_handler);

/*
 * Запускает построение абстрактного дерева разбора
 * В случае успешного построения вызывается интерпретатор
 */
int TInterpreter::run(char* program_filename) {
    const auto parse_result = _buildAST(program_filename);
    if (parse_result != 0) {
        return parse_result;
    }
    _interpret();
    return 0;
}

/*
 * Bison парсер читает код интерпретируемой программы из stdin
 * Поэтому подменяем stdin на поток из файла program_filename
 * А после того, как парсер отработал, возвращаем начальное значение stdin
 */
int TInterpreter::_buildAST(char* program_filename) {
    FILE* program_file = fopen(program_filename, "r");
    stdin = program_file;

    TErrorHandler parser_error_handler("Parser");
    const auto parse_result = yyparse(&_operations, &parser_error_handler);

    stdin = fdopen(0, "r");
    return parse_result;
}

/*
 * Запуск интерпретатора свелся к запуску всех операций интерпретируемой программы
 */
void TInterpreter::_interpret() {
    TErrorHandler interpreter_error_handler("Interpreter");
    try {
        _operations.executeAll(_dictionary);
    } catch(const std::exception& exception) {
        interpreter_error_handler.handleRuntimeError(exception.what());
    }
}
