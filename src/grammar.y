%{
    #include <iostream>

    #include "expression.h"
    #include "node.h"

    #define YYSTYPE TNode

    extern int yylineno;
    extern int yylex();

    void yyerror(TOperations* ast_root, char* errmsg) { // вынести
        std::cerr << errmsg << ", near line " << yylineno << std::endl;
        exit(1);
    }
%}

%token _NUMBER_VAR _STRING_VAR _NUMBER
%token _PRINT _IF _ELSE _WHILE _READ
%token _EQ _NE _LT _LE _GT _GE

%type<number_variable>   NUMBER_VAR
%type<string_variable>   STRING_VAR
%type<operation>         OPERATION PRINT READ ASSIGN IF WHILE
%type<operations>        OPERATIONS UNIT
%type<number_expression> NUMBER_EXPR ADD_EXPR MULT_EXPR MODULO_EXPR NUMBER_TERM
%type<string_expression> STRING_EXPR
%type<bool_expression>   BOOL_EXPR
%type<bool_operator>     BOOL_OPERATOR

%parse-param { TOperations* ast_root }

%%

PROGRAM:       UNIT                                  { *ast_root = $1; }
;

UNIT:          '{' OPERATIONS '}'                    { $$ = $2; }
|              '{' '}'                               { $$ = TOperations(); }

OPERATIONS:    OPERATION                             {
                                                        $$ = TOperations();
                                                        $$.addOperation($1);
                                                     }
|              OPERATIONS OPERATION                  {
                                                        $1.addOperation($2);
                                                        $$ = $1;
                                                     }
;

OPERATION:     PRINT                                 { $$ = $1; }
|              READ                                  { $$ = $1; }
|              ASSIGN                                { $$ = $1; }
|              IF                                    { $$ = $1; }
|              WHILE                                 { $$ = $1; }
;

ASSIGN:        NUMBER_VAR '=' NUMBER_EXPR ';'        { $$ = std::make_shared< TAssign<number_t> >($1, $3); }
|              STRING_VAR '=' STRING_EXPR ';'        { $$ = std::make_shared< TAssign<string_t> >($1, $3); }
;

NUMBER_VAR:    _NUMBER_VAR                           { $$ = yylval.number_variable; }
;

STRING_VAR:    _STRING_VAR                           { $$ = yylval.string_variable; }
;

PRINT:         _PRINT '(' NUMBER_EXPR ')' ';'        { $$ = std::make_shared< TPrint<number_t> >($3); }
|              _PRINT '(' STRING_EXPR ')' ';'        { $$ = std::make_shared< TPrint<string_t> >($3); }
;

READ:          _READ '(' NUMBER_VAR ')' ';'          { $$ = std::make_shared< TRead<number_t> >($3); }
|              _READ '(' STRING_VAR ')' ';'          { $$ = std::make_shared< TRead<string_t> >($3); }
;

STRING_EXPR:   STRING_VAR                            { $$ = std::make_shared< TExprVariable<string_t> >($1); }
|              STRING_EXPR '+' STRING_VAR            { $$ = std::make_shared<TStringExpression>($1, std::make_shared< TExprVariable<string_t> >($3), EStringOperator::CONCAT); }
;

NUMBER_EXPR:   NUMBER_EXPR '+' ADD_EXPR              { $$ = std::make_shared<TNumberExpression>($1, $3, ENumberOperator::PLUS); }
|              NUMBER_EXPR '-' ADD_EXPR              { $$ = std::make_shared<TNumberExpression>($1, $3, ENumberOperator::MINUS); }
|              ADD_EXPR                              { $$ = $1; }
;

ADD_EXPR:      ADD_EXPR '*' MULT_EXPR                { $$ = std::make_shared<TNumberExpression>($1, $3, ENumberOperator::MULT); }
|              ADD_EXPR '/' MULT_EXPR                { $$ = std::make_shared<TNumberExpression>($1, $3, ENumberOperator::DIV); }
|              MULT_EXPR                             { $$ = $1; }
;

MULT_EXPR:     MULT_EXPR '%' MODULO_EXPR             { $$ = std::make_shared<TNumberExpression>($1, $3, ENumberOperator::MOD); }
|              MODULO_EXPR                           { $$ = $1; }
;

MODULO_EXPR:  '(' NUMBER_EXPR ')'                    { $$ = $2; }
|              NUMBER_TERM                                  { $$ = $1; }
;

NUMBER_TERM:   NUMBER_VAR                            { $$ = std::make_shared< TExprVariable<number_t> >($1); }
|              _NUMBER                               { $$ = std::make_shared< TExprValue<number_t> >(yylval.number); }
;

IF:            _IF '(' BOOL_EXPR ')' UNIT            { $$ = std::make_shared<TIfBlock>($3, $5, TOperations()); }
|              _IF '(' BOOL_EXPR ')' UNIT _ELSE UNIT { $$ = std::make_shared<TIfBlock>($3, $5, $7); }
;

BOOL_EXPR:     NUMBER_EXPR BOOL_OPERATOR NUMBER_EXPR { $$ = std::make_shared< TBoolExpression<number_t> >($1, $3, $2); }
;

BOOL_OPERATOR: _EQ                                   { $$ = EBoolOperator::EQUAL; }
|              _NE                                   { $$ = EBoolOperator::NOT_EQUAL; }
|              _LT                                   { $$ = EBoolOperator::LESS; }
|              _LE                                   { $$ = EBoolOperator::LESS_OR_EQUAL; }
|              _GT                                   { $$ = EBoolOperator::GREATER; }
|              _GE                                   { $$ = EBoolOperator::GREATER_OR_EQUAL; }
;

WHILE:         _WHILE '(' BOOL_EXPR ')' UNIT         { $$ = std::make_shared<TWhileBlock>($3, $5); }
;

%%
