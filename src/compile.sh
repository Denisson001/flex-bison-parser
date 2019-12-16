bison -d  grammar.y
lex lexer.lex
g++ -fsanitize=address -std=c++11 grammar.tab.c lex.yy.c \
interpreter.cpp operation.cpp expression.cpp dictionary.cpp variable.cpp main.cpp -o main

./main in.txt