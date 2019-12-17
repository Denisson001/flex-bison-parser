%{
   #include "node.h"
   #define YYSTYPE TNode

   #include "grammar.tab.h"

   void yyerror(TOperations* ast_root, char* errmsg);
%}

%option yylineno
%option noyywrap

%x STRING_MODE

%%

[0-9]+                   {
                           yylval.number = std::stoll(yytext);
                           return _NUMBER;
                         }

if                       { return _IF; }
else                     { return _ELSE; }
print                    { return _PRINT; }
read                     { return _READ; }
while                    { return _WHILE; }

len                      { return _LEN_FUNC; }

["]                      {
                           yylval.string = "";
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

[a-zA-Z_][a-zA-Z0-9_]*_s {
                           yylval.string_variable = TVariable<string_t>(yytext);
                           return _STRING_VAR;
                         }

[a-zA-Z_][a-zA-Z0-9_]*   {
                           yylval.number_variable = TVariable<number_t>(yytext);
                           return _NUMBER_VAR;
                         }

[-+*/%{}()=;:\[\]<>!&|]  { return *yytext; }

[ \t\r\n]                ;

.                        { yyerror(NULL, "Invalid character"); } // не использовать здесь

%%