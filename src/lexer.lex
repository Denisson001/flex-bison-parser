%{
    #include "node.h"

    /*
     * Устанавливает тип для вершины абстрактного дерева разбора
     */
    #define YYSTYPE TNode

    /*
     * Подключает таблицу терминальных символов из Bison парсера
     */
    #include "grammar.tab.h"

   void yyerror(TOperations* ast_root, char* errmsg);
%}


/*
 * Опция для доступа к номеру текущей строки разбора
 */
%option yylineno

/*
 * Опция, чтобы разбираться ровно одну программу
 */
%option noyywrap

/*
 * Режим лексера для разбора строкового значения
 */
%x STRING_MODE

%%

[0-9]+                   {                                       // Регулярное выражение для числа
                           yylval.number = std::stoll(yytext);
                           return _NUMBER;
                         }

if                       { return _IF; }                         // Лексемы для служебных операций
else                     { return _ELSE; }
print                    { return _PRINT; }
read                     { return _READ; }
while                    { return _WHILE; }
len                      { return _LEN_FUNC; }

["]                      {                                       // Разбор строкового значения
                           yylval.string = "";                   // Отдельная обработка символов \n и "
                           BEGIN(STRING_MODE);
                         }
<STRING_MODE>[^\\\n"]+   { yylval.string += yytext; }
<STRING_MODE>\\n         { yylval.string += '\n'; }
<STRING_MODE>\\["]       { yylval.string += '"'; }
<STRING_MODE>\\          { yyerror(NULL, "Invalid escape sequence"); }
<STRING_MODE>\n          { yyerror(NULL, "Newline in string literal"); }
<STRING_MODE>["]         {
                           BEGIN(INITIAL);
                           return _STRING;
                         }

[a-zA-Z_][a-zA-Z0-9_]*_s {                                       // Регулярное выражение для строковой переменной
                           yylval.string_variable = TVariable<string_t>(yytext);
                           return _STRING_VAR;
                         }

[a-zA-Z_][a-zA-Z0-9_]*   {                                       // Регулярное выражение для числовой переменной
                           yylval.number_variable = TVariable<number_t>(yytext);
                           return _NUMBER_VAR;
                         }

[-+*/%{}()=;:\[\]<>!&|]  { return *yytext; }                     // Все оставшиеся используемые терминальные символы в языке

[ \t\r\n]                ;                                       // Убирает все пробельные символы из программмы

.                        { yyerror(NULL, "Invalid character"); } // Остальные символы вызывают ошибку компиляции

%%