#include <exception>
#include <variant>

#include "expression.h"

/*
 * Объявление всех шаблонных подстановок для классов-выражений
 * Можно было бы не выносить реализацию в отдельный файл,
 * Но для текущей задачи такое объявление позволяет явно следить за всеми типами
 */
template class TExpression<number_t>;
template class TExprVariable<number_t>;
template class TExprValue<number_t>;
template class TExprFunction<number_t>;

template class TExpression<string_t>;
template class TExprVariable<string_t>;
template class TExprValue<string_t>;
template class TExprFunction<string_t>;

template class TExpression<bool_t>;
template class TExprFunction<bool_t>;

/*
 * Шаблонной конструктор для класса выражений
 */
template <typename VariableType>
TExpression<VariableType>::TExpression(TExpression_ptr left_expr, TExpression_ptr right_expr, TExprOperator<VariableType> operation) :
        _left_expr(left_expr),
        _right_expr(right_expr),
        _operation(operation)
{}

/*
 * Далее идут специализации метода TExpression<VariableType>::calculate для разных типов
 * Все они работают схожим образом
 * Вычисляются значения подвыражений слева и справа от оператора
 * А дальше разбираются случаи относительно оператора
 */

/* number_t */

template <>
number_t TExpression<number_t>::calculate(TDictionary& dictionary) {
    const auto left_result  = _left_expr->calculate(dictionary);
    const auto right_result = _right_expr->calculate(dictionary);
    switch (_operation.type) {
        case PLUS:
            return left_result + right_result;

        case MINUS:
            return left_result - right_result;

        case MULT:
            return left_result * right_result;

        case DIV:
            if (right_result == 0) {
                throw std::domain_error("Division by zero");
            }
            return left_result / right_result;

        case MOD:
            if (right_result == 0) {
                throw std::domain_error("Division by zero");
            }
            return left_result % right_result;
    }
    return {};
}

/* string_t */

template <>
string_t TExpression<string_t>::calculate(TDictionary& dictionary) {
    const auto left_result  = _left_expr->calculate(dictionary);
    const auto right_result = _right_expr->calculate(dictionary);
    switch (_operation.type) {
        case CONCAT:
            return left_result + right_result;
    }
    return {};
}

/* bool_t */

template <>
bool_t TExpression<bool_t>::calculate(TDictionary& dictionary) {
    const auto left_result  = _left_expr->calculate(dictionary);
    const auto right_result = _right_expr->calculate(dictionary);
    switch (_operation.type) {
        case AND:
            return left_result && right_result;

        case OR:
            return left_result || right_result;
    }
    return {};
}


/*
 * Конструктор для выражения из одной переменной
 */
template <typename VariableType>
TExprVariable<VariableType>::TExprVariable(const TVariable<VariableType>& variable) :
        _variable(variable)
{}

/*
 * В случае выражения из одной переменной все вычисления выраждаются в возврат значения из словаря перменных
 */
template <typename VariableType>
VariableType TExprVariable<VariableType>::calculate(TDictionary& dictionary) {
    return dictionary[_variable];
}


/*
 * Конструктор для выражения из одного значения типа VariableType
 */
template <typename VariableType>
TExprValue<VariableType>::TExprValue(VariableType value) :
        _value(value)
{}

/*
 * В случае выражения из одного значения все вычисления выраждаются в возврат этого значения
 */
template <typename VariableType>
VariableType TExprValue<VariableType>::calculate(TDictionary& dictionary) {
    return _value;
}


template <typename VariableType>
TExprFunction<VariableType>::TExprFunction(const function_t& function_name, const TNumberExpressions& number_expressions,
                                           const TStringExpressions& string_expressions, const TBoolExpressions& bool_expressions) :
        _function_name(function_name),
        _number_expressions(number_expressions),
        _string_expressions(string_expressions),
        _bool_expressions(bool_expressions)
{}

/*
 * Далее идут специализации метода TExprFunction<VariableType>::calculate для разных типов
 */

/*
 * Есть только одна функция, которая возвращает number_t
 * len(string_expr) - возвращает длину строки
 * Есть проверка корректности вызова
 */
template <>
number_t TExprFunction<number_t >::calculate(TDictionary& dictionary) {
    if (_function_name == "len") {
        if (_string_expressions.size() < 1) {
            throw std::invalid_argument("invalid args number");
        }
        return _string_expressions[0]->calculate(dictionary).size();
    }
    throw std::logic_error("invalid function name");
}

/*
 * Есть две функции, которые возвращают string_t
 * slice - string_expr[number_expr : number_expr] - возвращает подстроку
 * index - string_expr[index] - возвращает элемент строки по индексу
 * Есть проверка корректности вызова
 */
template <>
string_t TExprFunction<string_t>::calculate(TDictionary& dictionary) {
    if (_function_name == "slice") {
        if (_string_expressions.size() < 1 || _number_expressions.size() < 2) {
            throw std::invalid_argument("invalid args number");
        }

        const auto left_border  = _number_expressions[0]->calculate(dictionary);
        const auto right_border = _number_expressions[1]->calculate(dictionary);
        const auto string       = _string_expressions[0]->calculate(dictionary);

        if (left_border  > right_border   ||
            right_border >= string.size() ||
            left_border  < 0) {
            throw std::out_of_range("slice function: invalid borders");
        }

        return string.substr(left_border, right_border - left_border + 1);

    } else if (_function_name == "index") {
        if (_string_expressions.size() < 1 || _number_expressions.size() < 1) {
            throw std::invalid_argument("invalid args number");
        }

        const auto index  = _number_expressions[0]->calculate(dictionary);
        const auto string = _string_expressions[0]->calculate(dictionary);

        if (index >= string.size() ||
            index <  0) {
            throw std::out_of_range("slice function: invalid index");
        }

        return string_t(1, string[index]);
    }
    throw std::logic_error("invalid function name");
}

/*
 * Функции, которые возвращают bool_t
 * "!" - функция NOT - инвертирует значение логического выражения
 * "==", "!=", "<=", ">=", "<", ">" - логические функции
 * Выражения по обе стороны от оператора должны совпадать и могут быть number_t или string_t
 * Чтобы не разбирать случаи используется std::variant
 * Есть проверка корректности вызова
 */
template <>
bool_t TExprFunction<bool_t>::calculate(TDictionary& dictionary) {
    if (_function_name == "!") {
        if (_bool_expressions.size() < 1) {
            throw std::invalid_argument("invalid args number");
        }
        return !_bool_expressions[0]->calculate(dictionary);
    }

    std::variant<number_t, string_t> left_value;
    std::variant<number_t, string_t> right_value;

    if (_number_expressions.size() >= 2) {
        left_value = _number_expressions[0]->calculate(dictionary);
        right_value = _number_expressions[1]->calculate(dictionary);

    } else if (_string_expressions.size() >= 2) {
        left_value = _string_expressions[0]->calculate(dictionary);
        right_value = _string_expressions[1]->calculate(dictionary);

    } else {
        throw std::invalid_argument("invalid args number");
    }

    if (_function_name == "==") {
        return left_value == right_value;

    } else if (_function_name == "!=") {
        return left_value != right_value;

    } else if (_function_name == "<=") {
        return left_value <= right_value;

    } else if (_function_name == ">=") {
        return left_value >= right_value;

    } else if (_function_name == "<") {
        return left_value < right_value;

    } else if (_function_name == ">") {
        return left_value > right_value;
    }

    throw std::logic_error("invalid function name");
}
