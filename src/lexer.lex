%{
   #include <string>

   #include "node.h"
   #define YYSTYPE TNode

   #include "grammar.tab.h"

   void yyerror(TOperations* ast_root, char* errmsg);
%}

%option yylineno
%option noyywrap

%%

[0-9]+                 {
                         yylval.number = std::stoll(yytext);
                         return _NUMBER;
                       }

==                     { return _EQ; }
!=                     { return _NE; }
>=                     { return _GE; }
>                      { return _GT; }
[<]=                   { return _LE; }
[<]                    { return _LT; }

if                     { return _IF; }
else                   { return _ELSE; }
print                  { return _PRINT; }
read                   { return _READ; }
while                  { return _WHILE; }

[a-zA-Z_][a-zA-Z0-9_]* {
                         yylval.number_variable = TVariable<number_t>(yytext);
                         return _VARIABLE;
                       }

[-+*/%{}()=;]          { return *yytext; }

[ \t\r\n]              ;

.                      { yyerror(NULL, "Invalid character"); } // не использовать здесь

%%