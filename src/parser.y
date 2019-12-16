%{
    #include <iostream>
    #include <stdlib.h>

    #include "interpreter.h"
    #include "expression.h"
    #include "node.h"

    #define YYSTYPE TNode

    extern int yylineno;
    extern int yylex();

    void yyerror(char *s) { // вынести
        std::cerr << s << ", line " << yylineno << std::endl;
        exit(1);
    }

    TInterpreter interpreter;
%}

%token _VARIABLE _NUMBER
%token _PRINT _IF _ELSE _WHILE
%token _EQ _NE _LT _LE _GT _GE

%type<variable>        VARIABLE
%type<operation>       OPERATION PRINT ASSIGN IF WHILE
%type<operations>      OPERATIONS UNIT
%type<math_expression> MATH_EXPR ADD_EXPR MULT_EXPR MODULO_EXPR TERM
%type<bool_expression> BOOL_EXPR
%type<bool_operator>   BOOL_OPERATOR

%%

PROGRAM:       UNIT                                   { interpreter.setOperations($1); }
;

UNIT:          '{' OPERATIONS '}'                     { $$ = $2; }
|              '{' '}'                                { $$ = TOperations(); }

OPERATIONS:    OPERATION                              {
                                                         $$ = TOperations();
                                                         $$.addOperation($1);
                                                      }
|              OPERATIONS OPERATION                   {
                                                         $1.addOperation($2);
                                                         $$ = $1;
                                                      }
;

OPERATION:     PRINT                                  { $$ = $1; }
|              ASSIGN                                 { $$ = $1; }
|              IF                                     { $$ = $1; }
|              WHILE                                  { $$ = $1; }
;

ASSIGN:        VARIABLE '=' MATH_EXPR ';'             { $$ = std::make_shared<TAssign>($1, $3); }
;

VARIABLE:      _VARIABLE                              { $$ = yylval.variable; }
;

PRINT:         _PRINT '(' MATH_EXPR ')' ';'           { $$ = std::make_shared<TPrint>($3); }
;

MATH_EXPR:     MATH_EXPR '+' ADD_EXPR                 { $$ = std::make_shared<TMathExpression>($1, $3, '+'); }
|              MATH_EXPR '-' ADD_EXPR                 { $$ = std::make_shared<TMathExpression>($1, $3, '-'); }
|              ADD_EXPR                               { $$ = $1; }
;

ADD_EXPR:      ADD_EXPR '*' MULT_EXPR                 { $$ = std::make_shared<TMathExpression>($1, $3, '*'); }
|              ADD_EXPR '/' MULT_EXPR                 { $$ = std::make_shared<TMathExpression>($1, $3, '/'); }
|              MULT_EXPR                              { $$ = $1; }
;

MULT_EXPR:     MULT_EXPR '%' MODULO_EXPR               { $$ = std::make_shared<TMathExpression>($1, $3, '%'); }
|              MODULO_EXPR                             { $$ = $1; }
;

MODULO_EXPR:  '(' MATH_EXPR ')'                       { $$ = $2; }
|              TERM                                   { $$ = $1; }
;

TERM:          _VARIABLE                              { $$ = std::make_shared<TVariable>(yylval.variable); }
|              _NUMBER                                { $$ = std::make_shared<TNumber>(yylval.number); }
;

IF:            _IF '(' BOOL_EXPR ')' UNIT             { $$ = std::make_shared<TIfBlock>($3, $5, TOperations()); }
|              _IF '(' BOOL_EXPR ')' UNIT _ELSE UNIT  { $$ = std::make_shared<TIfBlock>($3, $5, $7); }
;

BOOL_EXPR:     MATH_EXPR BOOL_OPERATOR MATH_EXPR      { $$ = std::make_shared<TBoolExpression>($1, $3, $2); }
;

BOOL_OPERATOR: _EQ                                    { $$ = TBoolExpression::EBoolOperator::EQUAL; }
|              _NE                                    { $$ = TBoolExpression::EBoolOperator::NOT_EQUAL; }
|              _LT                                    { $$ = TBoolExpression::EBoolOperator::LESS; }
|              _LE                                    { $$ = TBoolExpression::EBoolOperator::LESS_OR_EQUAL; }
|              _GT                                    { $$ = TBoolExpression::EBoolOperator::GREATER; }
|              _GE                                    { $$ = TBoolExpression::EBoolOperator::GREATER_OR_EQUAL; }
;

WHILE:         _WHILE '(' BOOL_EXPR ')' UNIT          { $$ = std::make_shared<TWhileBlock>($3, $5); }
;


%%

int main() {
    const auto result = yyparse();
    interpreter.interpret();
}