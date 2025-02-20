%{
    #include "expression.h"
    #include "error_handler.h"
    #include "node.h"

    /*
     * Устанавливает тип для вершины абстрактного дерева разбора
     */
    #define YYSTYPE TNode

    /*
     * Bison начинает генерировать более подробные сообщения об ошибке
     */
    #define YYERROR_VERBOSE

    /*
     * Используется в генерируемых файлах
     */
    extern int yylex();
    extern void yyerror(TOperations* ast_root, TErrorHandler* error_handler, const char* error_message);
%}


/*
 * Определение терминальных символов грамматики, возвращаемых из лексера
 */
%token _NUMBER _STRING
%token _NUMBER_VAR _STRING_VAR
%token _PRINT _IF _ELSE _WHILE _READ
%token _LEN_FUNC


/*
 * Далее идет определение нетерминалов грамматики с заданием их типов в вершине дерева разбора
 */


/*
 * Нетерминалы переменных разных типов
 */
%type<number_variable>   NUMBER_VAR
%type<string_variable>   STRING_VAR


/*
 * Нетерминалы разных операций и наборов операций
 */
%type<operation>         OPERATION  PRINT READ ASSIGN IF WHILE
%type<operations>        OPERATIONS UNIT


/*
 * Нетерминалы, используемые в разоборе математических выражений разных типов
 */
%type<number_expression> NUMBER_EXPR ADD_EXPR    MULT_EXPR  MOD_EXPR    BRACKET_EXPR NUMBER_TERM
%type<string_expression> STRING_EXPR CONCAT_EXPR SLICE_EXPR STRING_TERM
%type<bool_expression>   BOOL_EXPR   OR_EXPR     AND_EXPR   BOOL_TERM


/*
 * Нетерминал, соответствующий множеству операций сравнения, например, "==" или "<"
 */
%type<function>          BOOL_FUNCTION


/*
 * Дает доступ к корню дерева разбора парсера Bison
 */
%parse-param { TOperations* ast_root }

/*
 * Дает доступ к обработчику ошибок из парсера Bison
 */
%parse-param { TErrorHandler* error_handler }


%%


/*
 * PROGRAM - стартовый нетерминал
 */
PROGRAM:       UNIT                                  { *ast_root = $1; }
;


/*
 * UNIT - набор операций, обернутых в фигурные скобки
 */
UNIT:          '{' OPERATIONS '}'                    { $$ = $2; }
|              '{' '}'                               { $$ = TOperations(); }


/*
 * OPERATIONS - набор операций
 */
OPERATIONS:    OPERATION                             {
                                                        $$ = TOperations();
                                                        $$.addOperation($1);
                                                     }
|              OPERATIONS OPERATION                  {
                                                        $1.addOperation($2);
                                                        $$ = $1;
                                                     }
;


/*
 * OPERATION - одна из возможных операций
 */
OPERATION:     PRINT                                 { $$ = $1; }
|              READ                                  { $$ = $1; }
|              ASSIGN                                { $$ = $1; }
|              IF                                    { $$ = $1; }
|              WHILE                                 { $$ = $1; }
;


/*
 * ASSIGN - операция присвоения значения выражения в переменную
 * Третье правило нужно для присвоения элементу строки
 */
ASSIGN:        NUMBER_VAR '=' NUMBER_EXPR ';'        { $$ = std::make_shared< TAssign<number_t> >($1, $3); }
|              STRING_VAR '=' STRING_EXPR ';'        { $$ = std::make_shared< TAssign<string_t> >($1, $3); }
|              STRING_VAR '[' NUMBER_EXPR ']' '=' STRING_EXPR ';'
                                                     { $$ = std::make_shared<TIndexAssign>($1, $3, $6); }
;


/*
 * PRINT - операция вывода значения выражения
 */
PRINT:         _PRINT '(' NUMBER_EXPR ')' ';'        { $$ = std::make_shared< TPrint<number_t> >($3); }
|              _PRINT '(' STRING_EXPR ')' ';'        { $$ = std::make_shared< TPrint<string_t> >($3); }
;


/*
 * READ - операция чтения значения переменной
 */
READ:          _READ '(' NUMBER_VAR ')' ';'          { $$ = std::make_shared< TRead<number_t> >($3); }
|              _READ '(' STRING_VAR ')' ';'          { $$ = std::make_shared< TRead<string_t> >($3); }
;


/*
 * IF - операция if
 * Имеет две языковые формы - с блоком else и без него
 */
IF:            _IF '(' BOOL_EXPR ')' UNIT            { $$ = std::make_shared<TIfBlock>($3, $5, TOperations()); }
|              _IF '(' BOOL_EXPR ')' UNIT _ELSE UNIT { $$ = std::make_shared<TIfBlock>($3, $5, $7); }
;


/*
 * WHILE - цикл while
 */
WHILE:         _WHILE '(' BOOL_EXPR ')' UNIT         { $$ = std::make_shared<TWhileBlock>($3, $5); }
;



/*
 * STRING_VAR - нетерминал для строковой переменной
 */
STRING_VAR:    _STRING_VAR                           { $$ = yylval.string_variable; }
;


/*
 * STRING_EXPR - нетерминал для строкового выражения
 */
STRING_EXPR:   CONCAT_EXPR                           { $$ = $1; }
|              STRING_EXPR '+' CONCAT_EXPR           { $$ = std::make_shared< TExpression<string_t> >($1, $3, EStringOperator::CONCAT); }
;


/*
 * CONCAT_EXPR - слагаемое конкатенации
 */
CONCAT_EXPR:   '(' STRING_EXPR ')'                   { $$ = $2; }
|              STRING_TERM                           { $$ = $1; }
|              SLICE_EXPR                            { $$ = $1; }
;


/*
 * SLICE_EXPR - нетерминал для обработки функции взятия подстроки или элемента по индексу
 */
SLICE_EXPR:    CONCAT_EXPR '[' NUMBER_EXPR ':' NUMBER_EXPR ']'
                                                     { $$ = std::make_shared< TExprFunction<string_t> >("slice", TNumberExpressions{ $3, $5 }, TStringExpressions{ $1 }); }
|              CONCAT_EXPR '[' NUMBER_EXPR ']'       { $$ = std::make_shared< TExprFunction<string_t> >("index", TNumberExpressions{ $3 }, TStringExpressions{ $1 }); }
;


/*
 * STRING_TERM - строковый терм - строковая переменная или строковое значение
 */
STRING_TERM:   STRING_VAR                            { $$ = std::make_shared< TExprVariable<string_t> >($1); }
|              _STRING                               { $$ = std::make_shared< TExprValue<string_t> >(yylval.string); }
;



/*
 * NUMBER_VAR - нетерминал для числовой переменной
 */
NUMBER_VAR:    _NUMBER_VAR                           { $$ = yylval.number_variable; }
;


/*
 * NUMBER_EXPR - числовое выражение
 * Учитывается унарный минус
 */
NUMBER_EXPR:   '-' ADD_EXPR                          { $$ = std::make_shared< TExpression<number_t> >(std::make_shared< TExprValue<number_t> >(0), $2, ENumberOperator::MINUS); }
|              ADD_EXPR                              { $$ = $1; }
;


/*
 * ADD_EXPR - числовое выражение
 * Учитывается сложение и разность
 */
ADD_EXPR:      ADD_EXPR '+' MULT_EXPR                { $$ = std::make_shared< TExpression<number_t> >($1, $3, ENumberOperator::PLUS); }
|              ADD_EXPR '-' MULT_EXPR                { $$ = std::make_shared< TExpression<number_t> >($1, $3, ENumberOperator::MINUS); }
|              MULT_EXPR                             { $$ = $1; }
;


/*
 * MULT_EXPR - числовое выражение
 * Учитывается умножение и деление
 */
MULT_EXPR:     MULT_EXPR '*' MOD_EXPR                { $$ = std::make_shared< TExpression<number_t> >($1, $3, ENumberOperator::MULT); }
|              MULT_EXPR '/' MOD_EXPR                { $$ = std::make_shared< TExpression<number_t> >($1, $3, ENumberOperator::DIV); }
|              MOD_EXPR                              { $$ = $1; }
;


/*
 * MOD_EXPR - числовое выражение
 * Учитывается взятие по модулю
 */
MOD_EXPR:      MOD_EXPR '%' BRACKET_EXPR             { $$ = std::make_shared< TExpression<number_t> >($1, $3, ENumberOperator::MOD); }
|              BRACKET_EXPR                          { $$ = $1; }
;


/*
 * BRACKET_EXPR - нетерминал числового выражения для обработки навешивания скобок или ухода на числовой терм
 */
BRACKET_EXPR:  '(' NUMBER_EXPR ')'                   { $$ = $2; }
|              NUMBER_TERM                           { $$ = $1; }
;


/*
 * NUMBER_TERM - числовой терм - числовая переменная, число или функция
 */
NUMBER_TERM:   NUMBER_VAR                            { $$ = std::make_shared< TExprVariable<number_t> >($1); }
|              _NUMBER                               { $$ = std::make_shared< TExprValue<number_t> >(yylval.number); }
|              _LEN_FUNC '(' STRING_EXPR ')'         { $$ = std::make_shared< TExprFunction<number_t> >("len", TNumberExpressions{}, TStringExpressions{ $3 }); }
;



/*
 * BOOL_EXPR - логическое выражение
 * Учитывается логическая операция "ИЛИ"
 */
BOOL_EXPR:     BOOL_EXPR '|''|' OR_EXPR              { $$ = std::make_shared< TExpression<bool_t> >($1, $4, EBoolOperator::OR); }
|              OR_EXPR                               { $$ = $1; }
;


/*
 * OR_EXPR - член логического выражения
 * Учитывается логическая операция "И"
 */
OR_EXPR:       OR_EXPR '&''&' AND_EXPR               { $$ = std::make_shared< TExpression<bool_t> >($1, $4, EBoolOperator::AND); }
|              AND_EXPR                              { $$ = $1; }
;


/*
 * AND_EXPR - член логического выражения
 * Учитывается логическая операция "НЕ"
 * Или происходит уход на логический терм
 */
AND_EXPR:      BOOL_TERM                             { $$ = $1; }
|              '(' BOOL_EXPR ')'                     { $$ = $2; }
|              '!' '(' BOOL_EXPR ')'                 { $$ = std::make_shared< TExprFunction<bool_t> >("!",
                                                                 TNumberExpressions{}, TStringExpressions{}, TBoolExpressions{ $3 }); }
;


/*
 * BOOL_TERM - логический терм - одна из логических функций сравнения двух выражений
 */
BOOL_TERM:     NUMBER_EXPR BOOL_FUNCTION NUMBER_EXPR { $$ = std::make_shared< TExprFunction<bool_t> >($2, TNumberExpressions{ $1, $3 }, TStringExpressions{}); }
|              STRING_EXPR BOOL_FUNCTION STRING_EXPR { $$ = std::make_shared< TExprFunction<bool_t> >($2, TNumberExpressions{}, TStringExpressions{ $1, $3 }); }
;


/*
 * BOOL_FUNCTION - логическая функция сравнения
 */
BOOL_FUNCTION: '=''='                                { $$ = "=="; }
|              '!''='                                { $$ = "!="; }
|              '<''='                                { $$ = "<="; }
|              '>''='                                { $$ = ">="; }
|              '<'                                   { $$ = "<"; }
|              '>'                                   { $$ = ">"; }
;


%%
