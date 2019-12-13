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

%token _VARIABLE _NUMBER
%token _PRINT _IF _ELSE
%token _EQ _NE _LT _LE _GT _GE

%type<variable>        VARIABLE
%type<operation>       OPERATION PRINT ASSIGN IF
%type<operations>      OPERATIONS UNIT
%type<math_expression> MATH_EXPR ADD_EXPR MULT_EXPR TERM
%type<bool_expression> BOOL_EXPR
%type<bool_operation>  BOOL_OPERATION

%%

PROGRAM:    UNIT                         { interpreter.setOperations($1); }
;

UNIT:       '{' OPERATIONS '}'           { $$ = $2; }
|           '{' '}'                      { $$ = TOperations(); }

OPERATIONS: OPERATION                    { $$ = TOperations();
                                           $$.addOperation($1); }
|           OPERATIONS OPERATION         { $1.addOperation($2);
                                           $$ = $1; }
;

OPERATION:  PRINT                        { $$ = $1; }
|           ASSIGN                       { $$ = $1; }
|           IF                           { $$ = $1; }
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
;

IF:         _IF '(' BOOL_EXPR ')' UNIT             { $$ = new TIfBlock($3, $5, TOperations()); }
|           _IF '(' BOOL_EXPR ')' UNIT _ELSE UNIT  { $$ = new TIfBlock($3, $5, $7); }
;

BOOL_EXPR:  MATH_EXPR BOOL_OPERATION MATH_EXPR     { $$ = new TBoolExpression($1, $3, $2); }
;

BOOL_OPERATION: _EQ { $$ = TBoolExpression::EBoolOperation::EQUAL; }
|               _NE { $$ = TBoolExpression::EBoolOperation::NOT_EQUAL; }
|               _LT { $$ = TBoolExpression::EBoolOperation::LESS; }
|               _LE { $$ = TBoolExpression::EBoolOperation::LESS_OR_EQUAL; }
|               _GT { $$ = TBoolExpression::EBoolOperation::GREATER; }
|               _GE { $$ = TBoolExpression::EBoolOperation::GREATER_OR_EQUAL; }
;

%%

int main() {
    const auto result = yyparse();
    interpreter.interpret();
}