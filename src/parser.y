%{
    #include <iostream>
    #include <stdlib.h>

    #include "interpreter.h"
    #include "expression.h"
    #include "node.h"

    extern int yylineno;
    extern int yylex();

    void yyerror(char *s) {
        std::cerr << s << ", line " << yylineno << std::endl;
        exit(1);
    }

    TInterpreter interpreter;

    #define YYSTYPE TNode
%}

%token _VARIABLE
%token _NUMBER
%token _PRINT

%type<variable>        VARIABLE
%type<operation>       OPERATION PRINT ASSIGN
%type<math_expression> MATH_EXPR ADD_EXPR MULT_EXPR TERM

%%

PROGRAM:    UNIT
;

UNIT:       '{' OPERATIONS '}'
|           '{' '}'

OPERATIONS: OPERATION                    { interpreter.addOperation($1); }
|           OPERATIONS OPERATION         { interpreter.addOperation($2); }
;

OPERATION:  PRINT                        { $$ = $1; }
|           ASSIGN                       { $$ = $1;  }
;

ASSIGN:     VARIABLE '=' MATH_EXPR ';'   { $$ = new TAssign($1, $3); }
;

VARIABLE:   _VARIABLE                    { $$ = yylval.variable; }
;

PRINT:      _PRINT '(' MATH_EXPR ')' ';' { $$ = new TPrint($3); }
;

MATH_EXPR:  MATH_EXPR '+' ADD_EXPR       { $$ = new TMathExpression($1, $3, '+'); }
|           MATH_EXPR '-' ADD_EXPR       { $$ = new TMathExpression($1, $3, '-'); }
|           ADD_EXPR                     { $$ = $1; }
;

ADD_EXPR:   ADD_EXPR '*' MULT_EXPR       { $$ = new TMathExpression($1, $3, '*'); }
|           ADD_EXPR '/' MULT_EXPR       { $$ = new TMathExpression($1, $3, '/'); }
|           MULT_EXPR                    { $$ = $1; }
;

MULT_EXPR:  '(' MATH_EXPR ')'            { $$ = $2; }
|           TERM                         { $$ = $1; }
;

TERM:       _VARIABLE                    { $$ = new TVariable(yylval.variable); }
|           _NUMBER                      { $$ = new TNumber(yylval.number); }


%%

int main() {
    const auto result = yyparse();
    interpreter.interpret();
}