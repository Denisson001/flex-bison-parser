#pragma once

#include <string>


class TErrorHandler {
public:
    typedef std::string THandlerName;
    typedef std::string error_t;
    typedef int         line_t;

    /*
     * Зарегистрировать обработчик ошибок
     */
    TErrorHandler(const THandlerName& handler_name);

    /*
     * Обработать ошибку компиляции
     */
    void handleCompilationError(const error_t& error_message, line_t line_number = _NAN) const;

    /*
     * Обработать ошибку исполнения
     */
    void handleRuntimeError(const error_t& error_message, line_t line_number = _NAN) const;

private:
    static const line_t _NAN = -1;
    /*
     * Зарегистрировать обработчик ошибок
     */
    THandlerName _handler_name;
};