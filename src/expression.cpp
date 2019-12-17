#include <variant>

#include "expression.h"

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


template <typename VariableType>
TExpression<VariableType>::TExpression(TExpression_ptr left_expr, TExpression_ptr right_expr, TExprOperator<VariableType> operation) :
        _left_expr(left_expr),
        _right_expr(right_expr),
        _operation(operation)
{}


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
            return left_result / right_result;
        case MOD:
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


template <typename VariableType>
TExprVariable<VariableType>::TExprVariable(const TVariable<VariableType>& variable) :
        _variable(variable)
{}

template <typename VariableType>
VariableType TExprVariable<VariableType>::calculate(TDictionary& dictionary) {
    return dictionary[_variable];
}


template <typename VariableType>
TExprValue<VariableType>::TExprValue(VariableType value) :
        _value(value)
{}

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

template <>
number_t TExprFunction<number_t >::calculate(TDictionary& dictionary) {
    if (_function_name == "len") {
        if (_string_expressions.size() < 1) {
            return {};
        }
        return _string_expressions[0]->calculate(dictionary).size();
    }
    return {};
}

template <>
string_t TExprFunction<string_t>::calculate(TDictionary& dictionary) {
    if (_function_name == "slice") {
        if (_string_expressions.size() < 1 || _number_expressions.size() < 2) {
            return {};
        }
        const auto left_border  = _number_expressions[0]->calculate(dictionary);
        const auto right_border = std::max(left_border, _number_expressions[1]->calculate(dictionary));
        return _string_expressions[0]->calculate(dictionary).substr(left_border, right_border - left_border + 1); // ошибки?
    } else if (_function_name == "index") {
        if (_string_expressions.size() < 1 || _number_expressions.size() < 1) {
            return {};
        }
        const auto index = _number_expressions[0]->calculate(dictionary);
        return string_t(1, _string_expressions[0]->calculate(dictionary)[index]); // ошибки?
    }
    return {};
}

template <>
bool_t TExprFunction<bool_t>::calculate(TDictionary& dictionary) {
    if (_function_name == "!") {
        if (_bool_expressions.size() < 1) {
            return {};
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
        return {};
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

    return {};
}
