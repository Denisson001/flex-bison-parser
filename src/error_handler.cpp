#include <iostream>

#include "error_handler.h"
#include "operation.h"


/*
 * Номер текущей строки лексера
 */
extern int yylineno;

/*
 * Обработчик ошибок парсера Bison
 */
void yyerror(TOperations* ast_root, TErrorHandler* error_handler, char* error_message) {
    error_handler->handleCompilationError(error_message, yylineno);
}

/*
 * Зарегистрировать обработчик ошибок
 */
TErrorHandler::TErrorHandler(const THandlerName& handler_name) :
        _handler_name(handler_name)
{}

/*
 * Обработать ошибку компиляции
 */
void TErrorHandler::handleCompilationError(const error_t& error_message, line_t line_number) const {
    std::cout << _handler_name << ": сompilation error - " << error_message;
    if (line_number != _NAN) {
        std::cout << " near line " << line_number;
    }
    std::cout << std::endl;
    exit(1);
}

/*
 * Обработать ошибку исполнения
 */
void TErrorHandler::handleRuntimeError(const error_t& error_message, line_t line_number) const {
    std::cout << _handler_name << ": runtime error - " << error_message;
    if (line_number != _NAN) {
        std::cout << " near line " << line_number;
    }
    std::cout << std::endl;
    exit(2);
}