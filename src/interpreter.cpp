#include "interpreter.h"

/*
 * Точка входа в парсер Bison
 * Принимает указатель на корень абстрактного дерева разбора
 */
extern int yyparse(TOperations* ast_root);

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
    const auto parse_result = yyparse(&_operations);
    stdin = fdopen(0, "r");
    return parse_result;
}

/*
 * Запуск интерпретатора свелся к запуску всех операций интерпретируемой программы
 */
void TInterpreter::_interpret() {
    _operations.executeAll(_dictionary);
}
