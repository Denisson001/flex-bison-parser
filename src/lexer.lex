%{
   #include <string>

   #include "node.h"
   #define YYSTYPE TNode

   #include "parser.tab.h"

   void yyerror(char *s);
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
>                      { return _GE; }
>=                     { return _GT; }
[<]                    { return _LT; }
[<]=                   { return _LE; }

if                     { return _IF; }
else                   { return _ELSE; }
print                  { return _PRINT; }

[a-zA-Z_][a-zA-Z0-9_]* {
                         yylval.variable = yytext;
                         return _VARIABLE;
                       }

[-+*/{}=;()]           { return *yytext; }

[ \t\r\n]              ;

.                      yyerror("Invalid character");

%%